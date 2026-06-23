#include <gtest/gtest.h>

#include <vector>

#include "utilities/progress_tracker.hpp"

class RecordingProgressBar : public ProgressBar {
  std::vector<double> m_updates;

 public:
  const std::vector<double>& updates() const { return m_updates; }

 protected:
  void update_progress(double progress) override {
    m_updates.push_back(progress);
    ProgressBar::update_progress(progress);
  }
};

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

TEST(ProgressTracker, BackwardsSubtrackerUpdateFails) {
  ProgressTracker root;
  ProgressTracker child = root.subtracker(0.77, 0.78);

  child.set_proportion(0.99);
  EXPECT_THROW(child.set_proportion(0.55), std::runtime_error);
}

TEST(ProgressTracker, ParallelRowProgressIsMonotonic) {
  RecordingProgressBar bar;
  ProgressTracker root(&bar);
  ProgressTracker map_tracker = root.subtracker(0.0, 1.0);

  constexpr size_t ROWS = 512;
#pragma omp parallel for
  for (size_t i = 0; i < ROWS; ++i) {
    (void)i;
    map_tracker.report_parallel_progress(static_cast<double>(i + 1) / ROWS);
  }

  for (size_t i = 1; i < bar.updates().size(); ++i) {
    EXPECT_GE(bar.updates()[i], bar.updates()[i - 1]) << "progress went backwards at index " << i;
  }
  EXPECT_DOUBLE_EQ(root.proportion(), 1.0);
}
