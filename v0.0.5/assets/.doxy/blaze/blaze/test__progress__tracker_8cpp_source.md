

# File test\_progress\_tracker.cpp

[**File List**](files.md) **>** [**lib**](dir_c85d3e3c5052e9ad9ce18c6863244a25.md) **>** [**utilities**](dir_f68f3bc40609949e989ead5b0b6dedfd.md) **>** [**tests**](dir_61cbaf6f69b3ff38c8740f6eb1724d7a.md) **>** [**test\_progress\_tracker.cpp**](test__progress__tracker_8cpp.md)

[Go to the documentation of this file](test__progress__tracker_8cpp.md)


```C++
#include <gtest/gtest.h>

#include "utilities/progress_tracker.hpp"

TEST(ProgressTracker, ProgressTracker) {
  ProgressTracker tracker1;
  EXPECT_EQ(tracker1.proportion(), 0.0);

  tracker1.set_proportion(0.1);
  EXPECT_EQ(tracker1.proportion(), 0.1);

  {
    ProgressTracker trackerA(tracker1.subtracker(0.2, 0.6));
    EXPECT_EQ(tracker1.proportion(), 0.2);

    trackerA.set_proportion(0.25);
    EXPECT_DOUBLE_EQ(tracker1.proportion(), 0.3);
  }

  EXPECT_DOUBLE_EQ(tracker1.proportion(), 0.6);

  {
    ProgressTracker trackerB = tracker1.subtracker(0.7, 0.9);

    trackerB.set_proportion(0.5);
    EXPECT_DOUBLE_EQ(tracker1.proportion(), 0.8);
  }

  {
    ProgressTracker trackerC = tracker1.subtracker(0.9, 0.9);

    trackerC.set_proportion(0.5);
    EXPECT_DOUBLE_EQ(tracker1.proportion(), 0.9);
  }

  EXPECT_DOUBLE_EQ(tracker1.proportion(), 0.9);
}

TEST(ProgressTracker, ForLoop) {
  ProgressTracker tracker1;
  EXPECT_EQ(tracker1.proportion(), 0.0);

  for (int i = 0; i < 10; i++) {
    ProgressTracker trackerA = tracker1.subtracker(i / 10.0, (i + 1) / 10.0);
  }

  ProgressBar bar;
  run_loop(ProgressTracker(&bar));
}
```


