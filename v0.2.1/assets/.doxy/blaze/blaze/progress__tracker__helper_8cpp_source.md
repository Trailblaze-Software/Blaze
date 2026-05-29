

# File progress\_tracker\_helper.cpp

[**File List**](files.md) **>** [**lib**](dir_c85d3e3c5052e9ad9ce18c6863244a25.md) **>** [**utilities**](dir_f68f3bc40609949e989ead5b0b6dedfd.md) **>** [**tests**](dir_61cbaf6f69b3ff38c8740f6eb1724d7a.md) **>** [**progress\_tracker\_helper.cpp**](progress__tracker__helper_8cpp.md)

[Go to the documentation of this file](progress__tracker__helper_8cpp.md)


```C++
#include "utilities/progress_tracker.hpp"

void run_loop(ProgressTracker tracker) {
  for (int i = 0; i < 10; i++) {
    ProgressTracker trackerA = tracker.subtracker(i / 10.0, (i + 1) / 10.0);
  }
}
```


