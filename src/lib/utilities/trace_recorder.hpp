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
                                 double range_end, const std::string& name,
                                 const std::source_location* call_site = nullptr);

// Update scope display name when START_TRACKER runs (callee location + status text).
void progress_scope_set_display(uint64_t scope_id, const std::string& name,
                                const std::source_location& callee_location);

void write_chrome_trace(const fs::path& path);
void write_chrome_trace_if_configured();
void memory_counters(uint64_t total_bytes, uint64_t las_bytes, uint64_t grid_bytes);

// Progress scope stack for assertion diagnostics (only populated while tracing is enabled).
std::string format_active_scopes();

void progress_end(uint64_t scope_id, double proportion);

}  // namespace blaze::trace
