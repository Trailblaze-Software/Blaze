
#pragma once

#include <chrono>
#include <ostream>

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
