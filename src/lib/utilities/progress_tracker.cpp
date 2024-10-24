#include "progress_tracker.hpp"

#include <optional>
#include <utility>

ProgressObserver::~ProgressObserver() {};

void ProgressBar::update_progress(double progress) {
  std::cout << "Progress: " << progress * 100 << "%" << std::endl;
}

void ProgressTracker::_set_proportion(double proportion) {
  Assert(proportion >= m_proportion && proportion <= 1);
  m_proportion = proportion;
  if (m_observer != nullptr) {
    m_observer->update_progress(m_proportion);
  }
}

ProgressTracker::ProgressTracker(ProgressObserver* observer)
    : m_proportion(0), m_observer(observer) {
  if (m_observer != nullptr) {
    m_observer->m_child = this;
  }
  ProgressTracker* parent_tracker = dynamic_cast<ProgressTracker*>(observer);
  if (parent_tracker != nullptr) {
    Assert(parent_tracker->m_subtracker_range.has_value());
  }
}

ProgressTracker::ProgressTracker(ProgressTracker&& other) {
  m_proportion = other.m_proportion;
  m_observer = other.m_observer;
  Assert(!other.m_subtracker_range.has_value());
  other.m_observer = nullptr;
};

void ProgressTracker::set_proportion(double proportion) {
  Assert(!m_subtracker_range.has_value());
  _set_proportion(proportion);
}

void ProgressTracker::update_progress(double progress) {
  Assert(m_subtracker_range.has_value());
  _set_proportion(m_subtracker_range->first +
                  progress * (m_subtracker_range->second - m_subtracker_range->first));
}

ProgressTracker ProgressTracker::subtracker(double start, double end) {
  set_proportion(start);
  AssertGE(start, m_proportion);
  AssertGE(end, start);
  AssertGE(1, end);
  m_subtracker_range = std::make_pair(start, end);
  std::cout << "Subtracker: " << start * 100 << "% to " << end * 100 << "%" << std::endl;
  ProgressTracker to_return(this);
  m_child = &to_return;
  m_child->_set_proportion(0);
  return to_return;
}

ProgressTracker::~ProgressTracker() {
  _set_proportion(1);
  if (m_observer != nullptr) {
    m_observer->m_child = nullptr;
  }
  ProgressTracker* ptr = dynamic_cast<ProgressTracker*>(m_observer);
  if (ptr != nullptr) {
    ptr->m_subtracker_range.reset();
  }
}
