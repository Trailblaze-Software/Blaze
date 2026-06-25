#pragma once

#include <cstdint>
#include <source_location>
#include <string>

#include "utilities/filesystem.hpp"

namespace blaze::trace {

// RAII session: enables recording on construction and writes Chrome trace JSON on destruction.
class RecordTrace {
  fs::path m_path;

 public:
  explicit RecordTrace(fs::path path);
  ~RecordTrace();

  RecordTrace(const RecordTrace&) = delete;
  RecordTrace& operator=(const RecordTrace&) = delete;
  RecordTrace(RecordTrace&&) = delete;
  RecordTrace& operator=(RecordTrace&&) = delete;
};

// True while a RecordTrace session is active (or BLAZE_TRACE is set).
bool enabled();

uint64_t register_progress_scope(const std::source_location& location, double range_start,
                                 double range_end, bool start_immediately,
                                 const std::string& initial_name);
uint64_t thread_id();

void write_chrome_trace(const fs::path& path);
void write_chrome_trace_if_configured();
void memory_counters(uint64_t total_bytes, uint64_t las_bytes, uint64_t grid_bytes);

// Progress tracker scopes and updates. Scope depth is tracked per-thread inside the recorder.
void progress_scope_text(uint64_t scope_id, const std::string& text);
void progress_end(uint64_t scope_id, double proportion);
void progress_update(uint64_t scope_id, double proportion);
void progress_status(const std::string& text, int depth);

}  // namespace blaze::trace
