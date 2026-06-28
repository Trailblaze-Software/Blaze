

# File test\_progress\_tracker.cpp

[**File List**](files.md) **>** [**lib**](dir_c85d3e3c5052e9ad9ce18c6863244a25.md) **>** [**utilities**](dir_f68f3bc40609949e989ead5b0b6dedfd.md) **>** [**tests**](dir_61cbaf6f69b3ff38c8740f6eb1724d7a.md) **>** [**test\_progress\_tracker.cpp**](test__progress__tracker_8cpp.md)

[Go to the documentation of this file](test__progress__tracker_8cpp.md)


```C++
#include <gtest/gtest.h>

#include <fstream>
#include <string>
#include <vector>

#include "utilities/filesystem.hpp"
#include "utilities/progress_tracker.hpp"
#include "utilities/trace_recorder.hpp"

namespace {

void run_loop(ProgressTracker& tracker) {
  for (int i = 0; i < 10; i++) {
    ProgressTracker trackerA =
        tracker.subtracker(i / 10.0, (i + 1) / 10.0, "loop " + std::to_string(i));
  }
}

}  // namespace

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
    ProgressTracker trackerA(tracker1.subtracker(0.2, 0.6, "test A"));
    EXPECT_EQ(tracker1.proportion(), 0.2);

    trackerA.set_proportion(0.25);
    EXPECT_DOUBLE_EQ(tracker1.proportion(), 0.3);
  }

  EXPECT_DOUBLE_EQ(tracker1.proportion(), 0.6);

  {
    ProgressTracker trackerB = tracker1.subtracker(0.7, 0.9, "test B");

    trackerB.set_proportion(0.5);
    EXPECT_DOUBLE_EQ(tracker1.proportion(), 0.8);
  }

  {
    ProgressTracker trackerC = tracker1.subtracker(0.9, 0.9, "test C");

    trackerC.set_proportion(0.5);
    EXPECT_DOUBLE_EQ(tracker1.proportion(), 0.9);
  }

  EXPECT_DOUBLE_EQ(tracker1.proportion(), 0.9);
}

TEST(ProgressTracker, ForLoop) {
  ProgressTracker tracker1;
  EXPECT_EQ(tracker1.proportion(), 0.0);

  for (int i = 0; i < 10; i++) {
    ProgressTracker trackerA =
        tracker1.subtracker(i / 10.0, (i + 1) / 10.0, "loop " + std::to_string(i));
  }

  ProgressBar bar;
  ProgressTracker loop_tracker(&bar);
  run_loop(loop_tracker);
}

TEST(ProgressTracker, BackwardsSubtrackerUpdateFails) {
  ProgressTracker root;
  ProgressTracker child = root.subtracker(0.77, 0.78, "child");

  child.set_proportion(0.99);
  EXPECT_THROW(child.set_proportion(0.55), std::runtime_error);
}

TEST(ProgressTracker, ParallelRowProgressIsMonotonic) {
  RecordingProgressBar bar;
  ProgressTracker root(&bar);
  ProgressTracker map_tracker = root.subtracker(0.0, 1.0, "map");

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

TEST(ProgressTracker, ProgressScope) {
  ProgressTracker root;
  ProgressTracker child = SUBTRACKER(0.2, 0.8, root);
  child.set_proportion(0.5);
  EXPECT_DOUBLE_EQ(root.proportion(), 0.5);
}

TEST(ProgressTracker, ParentSetProportionBlockedWhileChildActive) {
  ProgressTracker root;
  ProgressTracker child = root.subtracker(0.2, 0.6, "child scope");
  EXPECT_THROW(root.set_proportion(0.3), std::runtime_error);
  child.set_proportion(1.0);
}

TEST(ProgressTracker, StartTrackerBeginsDeferredSubtracker) {
  ProgressTracker root;
  ProgressTracker child = SUBTRACKER(0.2, 0.8, root);
  START_TRACKER(child, "reading test.gpkg");
  child.set_proportion(0.5);
  EXPECT_DOUBLE_EQ(root.proportion(), 0.5);
}

TEST(ProgressTracker, StartTrackerNamesRoot) {
  const fs::path path = fs::temp_directory_path() / "blaze_scope_stack_test.json";
  blaze::trace::RecordTrace trace(path);
  ProgressTracker root;
  START_TRACKER(root, "using 8 threads for processing");
  const std::string stack = blaze::trace::format_active_scopes();
  EXPECT_NE(stack.find("Using 8 threads for processing"), std::string::npos);
}

TEST(ProgressTracker, RootScopeCompletesBeforeTraceWrite) {
  const fs::path path = fs::temp_directory_path() / "blaze_progress_trace_test.json";
  {
    blaze::trace::RecordTrace trace(path);
    ProgressTracker root;
    START_TRACKER(root, "using 8 threads for processing");
  }

  std::ifstream in(path);
  ASSERT_TRUE(in.is_open());
  const std::string json((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());

  size_t begin_count = 0;
  size_t end_count = 0;
  for (size_t pos = 0; (pos = json.find("\"ph\":\"B\"", pos)) != std::string::npos; ++pos) {
    ++begin_count;
  }
  for (size_t pos = 0; (pos = json.find("\"ph\":\"E\"", pos)) != std::string::npos; ++pos) {
    ++end_count;
  }
  EXPECT_EQ(begin_count, end_count);
  EXPECT_GE(begin_count, 1u);
  EXPECT_NE(json.find("\"name\":\"Using 8 threads for processing\""), std::string::npos);

  std::error_code ec;
  fs::remove(path, ec);
}

TEST(ProgressTracker, StartTrackerPatchesCallSiteInTrace) {
  const fs::path path = fs::temp_directory_path() / "blaze_callsite_trace_test.json";
  {
    blaze::trace::RecordTrace trace(path);
    ProgressTracker root;
    ProgressTracker child = SUBTRACKER(0.0, 1.0, root);
    START_TRACKER(child, "reading test.gpkg");
    child.set_proportion(1.0);
  }

  std::ifstream in(path);
  ASSERT_TRUE(in.is_open());
  const std::string json((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
  EXPECT_NE(json.find("\"name\":\"Reading test.gpkg\""), std::string::npos);
  EXPECT_NE(json.find("\"call_function\""), std::string::npos);
  EXPECT_NE(json.find("StartTrackerPatchesCallSiteInTrace"), std::string::npos);

  std::error_code ec;
  fs::remove(path, ec);
}

TEST(ProgressTracker, StartTrackerRecordsCallSiteInScopeStack) {
  const fs::path path = fs::temp_directory_path() / "blaze_scope_stack_callsite_test.json";
  blaze::trace::RecordTrace trace(path);
  ProgressTracker root;
  ProgressTracker child = SUBTRACKER(0.0, 1.0, root);
  START_TRACKER(child, "reading test.gpkg");
  const std::string stack = blaze::trace::format_active_scopes();
  EXPECT_NE(stack.find("Reading test.gpkg"), std::string::npos);
  EXPECT_NE(stack.find("called from"), std::string::npos);
  EXPECT_NE(stack.find("StartTrackerRecordsCallSiteInScopeStack"), std::string::npos);
  child.set_proportion(1.0);
}

TEST(ProgressTracker, SiblingSubtrackersRequireSequentialLifetime) {
  ProgressTracker root;
  {
    ProgressTracker first = root.subtracker(0.0, 0.4, "first");
    first.set_proportion(1.0);
  }
  ProgressTracker second = root.subtracker(0.4, 0.8, "second");
  second.set_proportion(1.0);
  EXPECT_DOUBLE_EQ(root.proportion(), 0.8);
}

TEST(ProgressTracker, ProgressScopeStackOnFailure) {
  const fs::path path = fs::temp_directory_path() / "blaze_scope_stack_failure_test.json";
  blaze::trace::RecordTrace trace(path);
  ProgressTracker root;
  ProgressTracker child = root.subtracker(0.0, 1.0, "tracked scope");
  try {
    root.set_proportion(0.5);
    FAIL() << "expected set_proportion to fail";
  } catch (const std::runtime_error& error) {
    EXPECT_NE(std::string(error.what()).find("Tracked scope"), std::string::npos);
    EXPECT_NE(std::string(error.what()).find("Active progress scopes"), std::string::npos);
  }
  child.set_proportion(1.0);
}
```


