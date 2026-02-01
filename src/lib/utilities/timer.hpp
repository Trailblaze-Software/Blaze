
#pragma once

#include <chrono>
#include <iostream>
#include <ostream>

#include "printing/to_string.hpp"
#include "progress_tracker.hpp"

inline std::ostream& operator<<(std::ostream& os, const std::chrono::duration<double>& duration) {
  if (duration.count() < 1e-6) {
    os << duration.count() * 1e9 << "ns";
  } else if (duration.count() < 1e-3) {
    os << duration.count() * 1e6 << "us";
  } else if (duration.count() < 1) {
    os << duration.count() * 1e3 << "ms";
  } else {
    os << duration.count() << "s";
  }
  return os;
}

class Timer {
  std::chrono::time_point<std::chrono::high_resolution_clock> m_start;

 public:
  Timer() : m_start(std::chrono::high_resolution_clock::now()) {}

  std::chrono::duration<double> duration() const {
    return std::chrono::high_resolution_clock::now() - m_start;
  }

  friend std::ostream& operator<<(std::ostream& os, const Timer& timer) {
    os << timer.duration();
    return os;
  }
};

class TimeFunction : public Timer {
  std::string m_name;
  ProgressTracker* m_progress_tracker;

 public:
  TimeFunction(const std::string& name, ProgressTracker* progress_tracker = nullptr)
      : m_name(name), m_progress_tracker(progress_tracker) {
    if (m_progress_tracker) {
      m_progress_tracker->text_update(to_string("Starting ", m_name, " ..."));
    } else {
      std::cout << "Starting " << m_name << " ..." << std::endl;
    }
  }

  TimeFunction(const std::string& name, std::optional<ProgressTracker>& progress_tracker)
      : TimeFunction(name, progress_tracker ? &*progress_tracker : nullptr) {}

  ~TimeFunction() {
    if (m_progress_tracker) {
      m_progress_tracker->text_update(to_string("Finished ", m_name, " in ", duration().count()));
    } else {
      std::cout << "Finished " << m_name << " in " << duration().count() << std::endl;
    }
  }
};
