#include "progress_tracker.hpp"

#include <cmath>
#include <iostream>
#include <optional>
#include <utility>

#include "assert/assert.hpp"
#include "utilities/memory_tracker.hpp"
#include "utilities/trace_recorder.hpp"

ProgressObserver::~ProgressObserver() {};

void ProgressBar::print_progress(double progress) {
  std::cout << "Progress: " << progress * 100 << "%  |  " << blaze::memory_tracker::format_summary()
            << std::endl;
  m_last_printed_progress = progress;
  m_last_print_time = std::chrono::steady_clock::now();
}

void ProgressBar::maybe_print_progress(double progress) {
  const auto now = std::chrono::steady_clock::now();
  const bool first_print = m_last_printed_progress < 0;
  const bool finished = progress >= 1.0;
  const bool due = first_print || (now - m_last_print_time) >= PRINT_INTERVAL;
  if (!due && !finished) {
    return;
  }
  if (progress - m_last_printed_progress < 0.0001 && !finished) {
    return;
  }
  print_progress(progress);
}

void ProgressBar::update_progress(double progress) {
  m_latest_progress = progress;
  maybe_print_progress(progress);
}

ProgressBar::~ProgressBar() {
  if (m_latest_progress < 0) {
    return;
  }
  if (m_latest_progress - m_last_printed_progress >= 0.0001) {
    print_progress(m_latest_progress);
  }
}

void ProgressBar::text_update(const std::string& text, int depth) {
  if (text.empty()) return;
  const size_t indent = depth > 1 ? static_cast<size_t>(2 * (depth - 1)) : 0u;
  std::cout << std::string(indent, ' ') << text << std::endl;
};

void ProgressTracker::_set_proportion(double proportion) {
  AssertGE(proportion, m_proportion);
  AssertGE(1, proportion);
  m_proportion = proportion;
  if (m_trace_scope_id != 0) {
    blaze::trace::progress_update(m_trace_scope_id, m_proportion);
  }
  if (m_observer != nullptr) {
    m_observer->update_progress(m_proportion);
  }
}

ProgressTracker::ProgressTracker(ProgressObserver* observer, const std::source_location location)
    : m_proportion(0), m_observer(observer) {
  if (m_observer != nullptr) {
    m_observer->m_child = this;
  }
  ProgressTracker* parent_tracker = dynamic_cast<ProgressTracker*>(observer);
  if (parent_tracker != nullptr) {
    Assert(parent_tracker->m_subtracker_range.has_value());
  } else {
    m_trace_scope_id = blaze::trace::register_progress_scope(location, 0.0, 1.0, true, "blaze");
  }
}

ProgressTracker::ProgressTracker(ProgressTracker&& other)
    : ProgressObserver(),
      m_proportion(other.m_proportion),
      m_observer(other.m_observer),
      m_subtracker_range(std::nullopt),
      m_visible(other.m_visible),
      m_trace_scope_id(other.m_trace_scope_id) {
  Assert(!other.m_subtracker_range.has_value());
  if (m_observer != nullptr) {
    m_observer->m_child = this;
  }
  other.m_observer = nullptr;
  other.m_trace_scope_id = 0;
};

void ProgressTracker::set_proportion(double proportion) {
  Assert(!m_subtracker_range.has_value());
  _set_proportion(proportion);
}

void ProgressTracker::report_parallel_progress(double proportion) {
  Assert(!m_subtracker_range.has_value());
#pragma omp critical(blaze_progress_tracker)
  {
    if (proportion > m_proportion) {
      _set_proportion(proportion);
    }
  }
}

void ProgressTracker::update_progress(double progress) {
  Assert(m_subtracker_range.has_value());
  _set_proportion(m_subtracker_range->first +
                  progress * (m_subtracker_range->second - m_subtracker_range->first));
}

void ProgressTracker::text_update(const std::string& text, int depth) {
  if (!text.empty() && m_trace_scope_id != 0) {
    blaze::trace::progress_scope_text(m_trace_scope_id, text);
  }
  if (!text.empty()) {
    blaze::trace::progress_status(text, depth);
  }
  if (m_observer != nullptr) {
    m_observer->text_update(text, depth + 1);
  }
};

ProgressTracker ProgressTracker::subtracker(double start, double end, std::optional<bool> visible,
                                            const std::source_location location) {
  set_proportion(start);
  AssertGE(end, start);
  AssertGE(1, end);
  m_subtracker_range = std::make_pair(start, end);
  ProgressTracker to_return(this);
  to_return.m_visible = visible.value_or(m_visible);
  to_return.m_trace_scope_id =
      blaze::trace::register_progress_scope(location, start, end, false, "");
  m_child = &to_return;
  m_child->_set_proportion(0);
  return to_return;
}

ProgressTracker::~ProgressTracker() {
  _set_proportion(1);
  if (m_trace_scope_id != 0) {
    blaze::trace::progress_end(m_trace_scope_id, m_proportion);
    m_trace_scope_id = 0;
  }
  if (m_observer != nullptr) {
    text_update("", 0);
    m_observer->m_child = nullptr;
  }
  ProgressTracker* ptr = dynamic_cast<ProgressTracker*>(m_observer);
  if (ptr != nullptr) {
    ptr->m_subtracker_range.reset();
  }
}
