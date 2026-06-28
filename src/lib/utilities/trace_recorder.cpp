#include "utilities/trace_recorder.hpp"

#include <algorithm>
#include <chrono>
#include <cstdio>
#include <fstream>
#include <mutex>
#include <nlohmann/json.hpp>
#include <optional>
#include <sstream>
#include <string>
#include <string_view>
#include <thread>
#include <vector>

#include "utilities/env.hpp"

namespace blaze::trace {

using json = nlohmann::json;

namespace {

constexpr int k_pid = 1;

struct DiagnosticScopeFrame {
  uint64_t scope_id = 0;
  std::string name;
  std::string file;
  int line = 0;
  std::string function;
  std::optional<std::string> call_file;
  std::optional<int> call_line;
  std::optional<std::string> call_function;
};

std::vector<json> g_events;
std::mutex g_events_mutex;
uint64_t g_next_scope_id = 1;
std::chrono::steady_clock::time_point g_origin{std::chrono::steady_clock::now()};
int g_recording_depth = 0;

thread_local std::vector<DiagnosticScopeFrame> g_scope_stack;

const char* trace_output_path() {
  static const char* path = []() -> const char* {
    const char* value = blaze::get_env("BLAZE_TRACE");
    return (value != nullptr && value[0] != '\0') ? value : nullptr;
  }();
  return path;
}

uint64_t timestamp_us() {
  const auto now = std::chrono::steady_clock::now();
  return static_cast<uint64_t>(
      std::chrono::duration_cast<std::chrono::microseconds>(now - g_origin).count());
}

uint64_t thread_id() {
  static thread_local const uint64_t id =
      static_cast<uint64_t>(std::hash<std::thread::id>{}(std::this_thread::get_id()));
  return id;
}

std::string format_scope_id(const uint64_t scope_id) {
  std::ostringstream ss;
  ss << "0x" << std::hex << scope_id;
  return ss.str();
}

std::string basename_path(const char* path) {
  if (path == nullptr || path[0] == '\0') {
    return "unknown";
  }
  std::string_view view(path);
  const size_t pos = view.find_last_of("/\\");
  if (pos != std::string_view::npos) {
    view = view.substr(pos + 1);
  }
  return std::string(view);
}

void append_trace_event(json event) {
  if (!enabled()) {
    return;
  }
  event["ts"] = timestamp_us();
  std::lock_guard lock(g_events_mutex);
  if (g_events.empty()) {
    g_events.push_back(
        json{{"name", "process_name"}, {"ph", "M"}, {"pid", k_pid}, {"args", {{"name", "Blaze"}}}});
  }
  g_events.push_back(std::move(event));
}

void append_scope_event(const char phase, const std::string& name, const uint64_t scope_id,
                        json args) {
  json event = {{"name", name}, {"cat", "progress"},  {"ph", std::string(1, phase)},
                {"pid", k_pid}, {"tid", thread_id()}, {"id", format_scope_id(scope_id)}};
  if (!args.empty()) {
    event["args"] = std::move(args);
  }
  append_trace_event(std::move(event));
}

json scope_begin_args(const double range_start, const double range_end,
                      const std::source_location& location, const std::source_location* call_site) {
  json args{{"depth", static_cast<int>(g_scope_stack.size())},
            {"scope_id", ""},
            {"range_start", range_start},
            {"range_end", range_end},
            {"function", location.function_name()},
            {"file", basename_path(location.file_name())},
            {"line", location.line()}};
  if (call_site != nullptr) {
    args["call_function"] = call_site->function_name();
    args["call_file"] = basename_path(call_site->file_name());
    args["call_line"] = call_site->line();
  }
  return args;
}

void push_scope_frame(const uint64_t scope_id, const std::string& name,
                      const std::source_location& location, const std::source_location* call_site) {
  DiagnosticScopeFrame frame{};
  frame.scope_id = scope_id;
  frame.name = name;
  frame.file = basename_path(location.file_name());
  frame.line = static_cast<int>(location.line());
  frame.function = location.function_name();
  if (call_site != nullptr) {
    frame.call_file = basename_path(call_site->file_name());
    frame.call_line = static_cast<int>(call_site->line());
    frame.call_function = call_site->function_name();
  }
  g_scope_stack.push_back(std::move(frame));
}

DiagnosticScopeFrame* find_scope_frame(const uint64_t scope_id) {
  for (DiagnosticScopeFrame& frame : g_scope_stack) {
    if (frame.scope_id == scope_id) {
      return &frame;
    }
  }
  return nullptr;
}

void pop_scope_frame(const uint64_t scope_id) {
  if (g_scope_stack.empty()) {
    return;
  }
  if (g_scope_stack.back().scope_id == scope_id) {
    g_scope_stack.pop_back();
    return;
  }
  const auto it = std::find_if(
      g_scope_stack.rbegin(), g_scope_stack.rend(),
      [scope_id](const DiagnosticScopeFrame& frame) { return frame.scope_id == scope_id; });
  if (it != g_scope_stack.rend()) {
    g_scope_stack.erase(it.base() - 1, g_scope_stack.end());
  }
}

std::string scope_name_or_location(const std::source_location& location, const std::string& name) {
  if (!name.empty()) {
    return name;
  }
  return basename_path(location.file_name()) + ':' + std::to_string(location.line());
}

void patch_scope_begin(const uint64_t scope_id, const std::string& name,
                       const std::source_location& location, const DiagnosticScopeFrame* frame) {
  const std::string id_str = format_scope_id(scope_id);
  std::lock_guard lock(g_events_mutex);
  for (json& event : g_events) {
    if (event.value("ph", "") != "B" || event.value("id", "") != id_str) {
      continue;
    }
    event["name"] = name;
    json args = scope_begin_args(event["args"].value("range_start", 0.0),
                                 event["args"].value("range_end", 1.0), location, nullptr);
    args["scope_id"] = id_str;
    if (event["args"].contains("depth")) {
      args["depth"] = event["args"]["depth"];
    }
    if (frame != nullptr && frame->call_function.has_value()) {
      args["call_function"] = *frame->call_function;
      args["call_file"] = *frame->call_file;
      args["call_line"] = *frame->call_line;
    } else if (event["args"].contains("call_function")) {
      args["call_function"] = event["args"]["call_function"];
      args["call_file"] = event["args"]["call_file"];
      args["call_line"] = event["args"]["call_line"];
    }
    event["args"] = std::move(args);
    return;
  }
}

}  // namespace

bool enabled() { return g_recording_depth > 0 || trace_output_path() != nullptr; }

std::string format_active_scopes() {
  if (g_scope_stack.empty()) {
    return {};
  }
  std::ostringstream ss;
  ss << "Active progress scopes:";
  for (size_t i = 0; i < g_scope_stack.size(); ++i) {
    const DiagnosticScopeFrame& frame = g_scope_stack[i];
    ss << "\n  [" << i << "] " << frame.name << " (" << frame.function << " @ " << frame.file << ':'
       << frame.line << ')';
    if (frame.call_function.has_value()) {
      ss << " [called from " << *frame.call_function << " @ " << *frame.call_file << ':'
         << *frame.call_line << ']';
    }
  }
  return ss.str();
}

RecordTrace::RecordTrace(fs::path path) : m_path(std::move(path)) {
  if (g_recording_depth++ == 0) {
    std::lock_guard lock(g_events_mutex);
    g_events.clear();
    g_next_scope_id = 1;
    g_origin = std::chrono::steady_clock::now();
  }
}

RecordTrace::~RecordTrace() {
  if (g_recording_depth == 0) {
    return;
  }
  --g_recording_depth;
  if (g_recording_depth > 0) {
    return;
  }
  if (!m_path.parent_path().empty()) {
    fs::create_directories(m_path.parent_path());
  }
  write_chrome_trace(m_path);
}

uint64_t register_progress_scope(const std::source_location& location, const double range_start,
                                 const double range_end, const std::string& name,
                                 const std::source_location* call_site) {
  const uint64_t scope_id = g_next_scope_id++;
  const std::string scope_name = scope_name_or_location(location, name);
  const std::source_location* effective_call_site = call_site;
  if (call_site == nullptr && name.empty()) {
    effective_call_site = &location;
  }
  if (enabled()) {
    json args = scope_begin_args(range_start, range_end, location, effective_call_site);
    args["scope_id"] = format_scope_id(scope_id);
    append_scope_event('B', scope_name, scope_id, std::move(args));
    push_scope_frame(scope_id, scope_name, location, effective_call_site);
  }
  return scope_id;
}

void progress_scope_set_display(const uint64_t scope_id, const std::string& name,
                                const std::source_location& callee_location) {
  if (!enabled()) {
    return;
  }
  DiagnosticScopeFrame* frame = find_scope_frame(scope_id);
  if (frame != nullptr) {
    frame->name = name;
    frame->file = basename_path(callee_location.file_name());
    frame->line = static_cast<int>(callee_location.line());
    frame->function = callee_location.function_name();
  }
  patch_scope_begin(scope_id, name, callee_location, frame);
}

void progress_end(const uint64_t scope_id, const double proportion) {
  if (enabled()) {
    const int depth = static_cast<int>(g_scope_stack.size()) - 1;
    append_scope_event('E', "", scope_id,
                       json{{"scope_id", format_scope_id(scope_id)},
                            {"depth", depth < 0 ? 0 : depth},
                            {"proportion", proportion}});
  }
  pop_scope_frame(scope_id);
}

void memory_counters(const uint64_t total_bytes, const uint64_t las_bytes,
                     const uint64_t grid_bytes) {
  constexpr double BYTES_PER_GB = 1e9;
  const auto emit_counter = [](const char* counter_name, const uint64_t bytes) {
    append_trace_event(json{{"name", counter_name},
                            {"cat", "memory"},
                            {"ph", "C"},
                            {"pid", k_pid},
                            {"tid", thread_id()},
                            {"args", {{"value", static_cast<double>(bytes) / BYTES_PER_GB}}}});
  };
  emit_counter("memory_total", total_bytes);
  emit_counter("memory_las", las_bytes);
  emit_counter("memory_grid", grid_bytes);
}

void write_chrome_trace(const fs::path& path) {
  std::vector<json> events;
  {
    std::lock_guard lock(g_events_mutex);
    events = g_events;
  }
  std::sort(events.begin(), events.end(),
            [](const json& a, const json& b) { return a.value("ts", 0ULL) < b.value("ts", 0ULL); });

  json trace_events = json::array();
  for (json& event : events) {
    trace_events.push_back(std::move(event));
  }

  const json output = {{"traceEvents", std::move(trace_events)}, {"displayTimeUnit", "ms"}};

  std::ofstream out(path);
  if (!out) {
    std::fprintf(stderr, "Failed to write trace to %s\n", path.string().c_str());
    return;
  }
  out << output.dump() << '\n';
}

void write_chrome_trace_if_configured() {
  const char* path = trace_output_path();
  if (path == nullptr) {
    return;
  }
  write_chrome_trace(path);
}

}  // namespace blaze::trace
