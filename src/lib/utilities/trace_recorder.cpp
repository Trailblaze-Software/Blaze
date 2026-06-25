#include "utilities/trace_recorder.hpp"

#include <algorithm>
#include <atomic>
#include <chrono>
#include <cstdio>
#include <fstream>
#include <mutex>
#include <nlohmann/json.hpp>
#include <sstream>
#include <string>
#include <string_view>
#include <thread>
#include <unordered_map>
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

std::mutex g_mutex;
std::vector<TraceEvent> g_events;
std::atomic<uint64_t> g_next_scope_id{1};
std::chrono::steady_clock::time_point g_origin{std::chrono::steady_clock::now()};
bool g_metadata_written = false;
int g_recording_depth = 0;

thread_local std::vector<uint64_t> g_scope_stack;

struct ScopeState {
  bool started = false;
  std::source_location location;
  double range_start = 0.0;
  double range_end = 1.0;
  double last_proportion = 0.0;
};

std::mutex g_scope_mutex;
std::unordered_map<uint64_t, ScopeState> g_scopes;

void reset_recording() {
  std::lock_guard lock(g_mutex);
  g_events.clear();
  g_metadata_written = false;
  g_next_scope_id.store(1, std::memory_order_relaxed);
  g_origin = std::chrono::steady_clock::now();
  {
    std::lock_guard scope_lock(g_scope_mutex);
    g_scopes.clear();
  }
}

int current_scope_depth() { return static_cast<int>(g_scope_stack.size()); }

void pop_scope(uint64_t scope_id) {
  if (!g_scope_stack.empty() && g_scope_stack.back() == scope_id) {
    g_scope_stack.pop_back();
    return;
  }
  auto it = std::find(g_scope_stack.rbegin(), g_scope_stack.rend(), scope_id);
  if (it != g_scope_stack.rend()) {
    g_scope_stack.erase(it.base() - 1, g_scope_stack.end());
  }
}

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
                         double range_end) {
  if (!enabled()) {
    return;
  }
  const int depth = current_scope_depth();
  append_scope_event(
      'B', "progress", name, scope_id,
      json{{"depth", depth}, {"range_start", range_start}, {"range_end", range_end}});
  g_scope_stack.push_back(scope_id);
}

void emit_progress_update(uint64_t scope_id, double proportion) {
  if (!enabled()) {
    return;
  }
  const int depth = std::max(0, current_scope_depth() - 1);
  append_instant_event(
      "progress", "progress_update",
      json{{"scope_id", format_scope_id(scope_id)}, {"depth", depth}, {"proportion", proportion}});
}

void emit_progress_end(uint64_t scope_id, double proportion) {
  if (!enabled()) {
    return;
  }
  const int depth = current_scope_depth() - 1;
  append_scope_event('E', "progress", "", scope_id,
                     json{{"depth", depth}, {"proportion", proportion}});
  pop_scope(scope_id);
}

void ensure_scope_started(uint64_t scope_id, const std::string& name) {
  double range_start = 0.0;
  double range_end = 1.0;
  double proportion = 0.0;
  {
    std::lock_guard lock(g_scope_mutex);
    const auto it = g_scopes.find(scope_id);
    if (it == g_scopes.end() || it->second.started) {
      return;
    }
    it->second.started = true;
    range_start = it->second.range_start;
    range_end = it->second.range_end;
    proportion = it->second.last_proportion;
  }
  emit_progress_begin(scope_id, name, range_start, range_end);
  if (proportion > 0.0) {
    emit_progress_update(scope_id, proportion);
  }
}

std::string short_location(const std::source_location& location) {
  return basename_path(location.file_name()) + ':' + std::to_string(location.line());
}

std::string scope_label_from_status(const std::string& text) {
  constexpr std::string_view starting = "Starting ";
  constexpr std::string_view finished = "Finished ";
  if (text.starts_with(starting)) {
    std::string label = text.substr(starting.size());
    if (label.ends_with(" ...")) {
      label.resize(label.size() - 4);
    }
    return label;
  }
  if (text.starts_with(finished)) {
    const size_t in_pos = text.find(" in ");
    if (in_pos != std::string::npos) {
      return text.substr(finished.size(), in_pos - finished.size());
    }
  }
  return text;
}

}  // namespace

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

uint64_t register_progress_scope(const std::source_location& location, double range_start,
                                 double range_end, bool start_immediately,
                                 const std::string& initial_name) {
  const uint64_t scope_id = g_next_scope_id.fetch_add(1, std::memory_order_relaxed);
  {
    std::lock_guard lock(g_scope_mutex);
    g_scopes[scope_id] =
        ScopeState{.location = location, .range_start = range_start, .range_end = range_end};
  }
  if (start_immediately) {
    ensure_scope_started(scope_id, initial_name);
  }
  return scope_id;
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

void progress_scope_text(uint64_t scope_id, const std::string& text) {
  if (text.empty()) {
    return;
  }
  ensure_scope_started(scope_id, scope_label_from_status(text));
}

void progress_end(uint64_t scope_id, double proportion) {
  std::string fallback_name;
  bool need_begin = false;
  {
    std::lock_guard lock(g_scope_mutex);
    const auto it = g_scopes.find(scope_id);
    if (it == g_scopes.end()) {
      return;
    }
    it->second.last_proportion = proportion;
    if (!it->second.started) {
      need_begin = true;
      fallback_name = short_location(it->second.location);
    } else {
      g_scopes.erase(it);
    }
  }
  if (need_begin) {
    ensure_scope_started(scope_id, fallback_name);
    std::lock_guard lock(g_scope_mutex);
    g_scopes.erase(scope_id);
  }
  emit_progress_end(scope_id, proportion);
}

void progress_update(uint64_t scope_id, double proportion) {
  bool started = false;
  {
    std::lock_guard lock(g_scope_mutex);
    const auto it = g_scopes.find(scope_id);
    if (it == g_scopes.end()) {
      return;
    }
    it->second.last_proportion = proportion;
    started = it->second.started;
  }
  if (!started) {
    return;
  }
  emit_progress_update(scope_id, proportion);
}

void progress_status(const std::string& text, int depth) {
  append_instant_event("progress", "progress_status", json{{"depth", depth}, {"text", text}});
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
