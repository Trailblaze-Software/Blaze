#include "utilities/trace_recorder.hpp"

#include <algorithm>
#include <atomic>
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
namespace {

using json = nlohmann::json;

constexpr int k_pid = 1;

struct TraceEvent {
  uint64_t timestamp_us = 0;
  json event;
};

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

std::mutex g_mutex;
std::vector<TraceEvent> g_events;
std::atomic<uint64_t> g_next_scope_id{1};
std::chrono::steady_clock::time_point g_origin{std::chrono::steady_clock::now()};
bool g_metadata_written = false;
int g_recording_depth = 0;

thread_local std::vector<DiagnosticScopeFrame> g_scope_stack;

void reset_recording() {
  std::lock_guard lock(g_mutex);
  g_events.clear();
  g_metadata_written = false;
  g_next_scope_id.store(1, std::memory_order_relaxed);
  g_origin = std::chrono::steady_clock::now();
}

int current_scope_depth() { return static_cast<int>(g_scope_stack.size()); }

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

std::string format_scope_id(uint64_t scope_id) {
  std::ostringstream ss;
  ss << "0x" << std::hex << scope_id;
  return ss.str();
}

void append_event(uint64_t ts, json event) {
  if (!enabled()) {
    return;
  }
  std::lock_guard lock(g_mutex);
  if (!g_metadata_written) {
    g_metadata_written = true;
    g_events.push_back({0, json{{"name", "process_name"},
                                {"ph", "M"},
                                {"pid", k_pid},
                                {"args", {{"name", "Blaze"}}}}});
  }
  g_events.push_back({ts, std::move(event)});
}

void append_scope_event(char phase, const char* category, const std::string& name,
                        uint64_t scope_id, const json& args) {
  const uint64_t ts = timestamp_us();
  json event = {{"name", name}, {"cat", category},    {"ph", std::string(1, phase)},    {"ts", ts},
                {"pid", k_pid}, {"tid", thread_id()}, {"id", format_scope_id(scope_id)}};
  if (!args.empty()) {
    event["args"] = args;
  }
  append_event(ts, std::move(event));
}

void append_instant_event(const char* category, const std::string& name, const json& args) {
  const uint64_t ts = timestamp_us();
  json event = {{"name", name}, {"cat", category},    {"ph", "i"}, {"ts", ts},
                {"pid", k_pid}, {"tid", thread_id()}, {"s", "t"}};
  if (!args.empty()) {
    event["args"] = args;
  }
  append_event(ts, std::move(event));
}

void append_counter_event(const std::string& name, double value_gb) {
  const uint64_t ts = timestamp_us();
  append_event(ts, json{{"name", name},
                        {"cat", "memory"},
                        {"ph", "C"},
                        {"ts", ts},
                        {"pid", k_pid},
                        {"tid", thread_id()},
                        {"args", {{"value", value_gb}}}});
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

void emit_progress_begin(uint64_t scope_id, const std::string& name, double range_start,
                         double range_end, const std::source_location& location,
                         const std::source_location* call_site) {
  if (!enabled()) {
    return;
  }
  const int depth = current_scope_depth();
  json args{{"depth", depth},
            {"scope_id", format_scope_id(scope_id)},
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
  append_scope_event('B', "progress", name, scope_id, std::move(args));
}

void emit_progress_update(uint64_t scope_id, double proportion) {
  if (!enabled()) {
    return;
  }
  append_instant_event("progress", "progress_update",
                       json{{"scope_id", format_scope_id(scope_id)},
                            {"depth", std::max(0, current_scope_depth() - 1)},
                            {"proportion", proportion}});
}

void emit_progress_end(uint64_t scope_id, double proportion) {
  if (!enabled()) {
    return;
  }
  const int depth = std::max(0, current_scope_depth() - 1);
  append_scope_event(
      'E', "progress", "", scope_id,
      json{{"scope_id", format_scope_id(scope_id)}, {"depth", depth}, {"proportion", proportion}});
}

std::string scope_name_or_location(const std::source_location& location, const std::string& name) {
  if (!name.empty()) {
    return name;
  }
  return basename_path(location.file_name()) + ':' + std::to_string(location.line());
}

void push_scope_frame(uint64_t scope_id, const std::string& name,
                      const std::source_location& location, const std::source_location* call_site,
                      const bool registration_is_call_site) {
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
  } else if (registration_is_call_site) {
    frame.call_file = frame.file;
    frame.call_line = frame.line;
    frame.call_function = frame.function;
  }
  g_scope_stack.push_back(std::move(frame));
}

void update_scope_display(uint64_t scope_id, const std::string& name,
                          const std::source_location& callee_location) {
  for (DiagnosticScopeFrame& frame : g_scope_stack) {
    if (frame.scope_id != scope_id) {
      continue;
    }
    frame.name = name;
    frame.file = basename_path(callee_location.file_name());
    frame.line = static_cast<int>(callee_location.line());
    frame.function = callee_location.function_name();
    return;
  }
}

void pop_scope_frame(uint64_t scope_id) {
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

std::string format_active_scopes_impl() {
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

}  // namespace

std::string format_active_scopes() { return format_active_scopes_impl(); }

bool enabled() { return g_recording_depth > 0 || trace_output_path() != nullptr; }

RecordTrace::RecordTrace(fs::path path) : m_path(std::move(path)) {
  if (g_recording_depth++ == 0) {
    reset_recording();
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
  const uint64_t scope_id = g_next_scope_id.fetch_add(1, std::memory_order_relaxed);
  const std::string scope_name = scope_name_or_location(location, name);
  emit_progress_begin(scope_id, scope_name, range_start, range_end, location, call_site);
  if (enabled()) {
    push_scope_frame(scope_id, scope_name, location, call_site,
                     name.empty() && call_site == nullptr);
  }
  return scope_id;
}

void progress_scope_set_display(const uint64_t scope_id, const std::string& name,
                                const std::source_location& callee_location) {
  if (!enabled()) {
    return;
  }
  update_scope_display(scope_id, name, callee_location);
  append_instant_event("progress", "progress_scope_name",
                       json{{"scope_id", format_scope_id(scope_id)},
                            {"name", name},
                            {"function", callee_location.function_name()},
                            {"file", basename_path(callee_location.file_name())},
                            {"line", callee_location.line()}});
}

uint64_t thread_id() {
  static thread_local const uint64_t id =
      static_cast<uint64_t>(std::hash<std::thread::id>{}(std::this_thread::get_id()));
  return id;
}

void memory_counters(uint64_t total_bytes, uint64_t las_bytes, uint64_t grid_bytes) {
  constexpr double BYTES_PER_GB = 1e9;
  append_counter_event("memory_total", static_cast<double>(total_bytes) / BYTES_PER_GB);
  append_counter_event("memory_las", static_cast<double>(las_bytes) / BYTES_PER_GB);
  append_counter_event("memory_grid", static_cast<double>(grid_bytes) / BYTES_PER_GB);
}

void progress_end(uint64_t scope_id, double proportion) {
  emit_progress_end(scope_id, proportion);
  pop_scope_frame(scope_id);
}

void progress_update(uint64_t scope_id, double proportion) {
  emit_progress_update(scope_id, proportion);
}

void progress_status(const uint64_t scope_id, const std::string& text) {
  if (scope_id == 0) {
    return;
  }
  append_instant_event("progress", "progress_status",
                       json{{"scope_id", format_scope_id(scope_id)}, {"text", text}});
}

void write_chrome_trace(const fs::path& path) {
  std::vector<TraceEvent> events;
  {
    std::lock_guard lock(g_mutex);
    events = g_events;
  }
  std::sort(events.begin(), events.end(), [](const TraceEvent& a, const TraceEvent& b) {
    return a.timestamp_us < b.timestamp_us;
  });

  json trace_events = json::array();
  for (const TraceEvent& event : events) {
    trace_events.push_back(event.event);
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
