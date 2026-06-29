

# File timer.hpp

[**File List**](files.md) **>** [**lib**](dir_c85d3e3c5052e9ad9ce18c6863244a25.md) **>** [**utilities**](dir_f68f3bc40609949e989ead5b0b6dedfd.md) **>** [**timer.hpp**](timer_8hpp.md)

[Go to the documentation of this file](timer_8hpp.md)


```C++
#pragma once

#include <chrono>
#include <iostream>
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
```


