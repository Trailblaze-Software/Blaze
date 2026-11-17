

# File progress\_tracker.hpp

[**File List**](files.md) **>** [**lib**](dir_c85d3e3c5052e9ad9ce18c6863244a25.md) **>** [**utilities**](dir_f68f3bc40609949e989ead5b0b6dedfd.md) **>** [**progress\_tracker.hpp**](progress__tracker_8hpp.md)

[Go to the documentation of this file](progress__tracker_8hpp.md)


```C++
#pragma once

#include <chrono>
#include <cstdint>
#include <memory>
#include <optional>
#include <source_location>
#include <string>
#include <utility>

class ProgressTracker;

class ProgressObserver {
  ProgressTracker* m_child;

 protected:
  virtual void update_progress(double progress) = 0;
  virtual void text_update(const std::string& text, int depth = 0) = 0;

  ProgressObserver() : m_child(nullptr) {}

 public:
  ProgressTracker* child() { return m_child; }

  virtual ~ProgressObserver();
  friend class ProgressTracker;
};

// CLI terminal progress: ProgressTracker updates propagate immediately to all observers;
// only stdout printing is rate-limited here. GUI observers (ProgressBox, etc.) are unaffected.
class ProgressBar : public ProgressObserver {
  static constexpr std::chrono::milliseconds PRINT_INTERVAL{500};

  double m_last_printed_progress = -1;
  double m_latest_progress = -1;
  std::chrono::steady_clock::time_point m_last_print_time{};

  void print_progress(double progress);
  void maybe_print_progress(double progress);

 protected:
  virtual void update_progress(double progress) override;
  virtual void text_update(const std::string& text, int depth = 0) override;

 public:
  ~ProgressBar() override;
};

class ProgressTracker : public ProgressObserver {
  double m_proportion;
  ProgressObserver* m_observer;
  std::optional<std::pair<double, double>> m_subtracker_range;
  bool m_visible = true;
  uint64_t m_trace_scope_id = 0;

  void _set_proportion(double proportion);

 protected:
  virtual void update_progress(double progress) override;

 public:
  explicit ProgressTracker(ProgressObserver* observer = nullptr, std::string name = "",
                           std::source_location location = std::source_location::current(),
                           double range_start = 0.0, double range_end = 1.0);

  virtual void text_update(const std::string& text, int depth = 0) override;

  ProgressTracker(const ProgressTracker& other) = delete;
  ProgressTracker& operator=(const ProgressTracker& other) = delete;
  ProgressTracker(ProgressTracker&& other);
  ProgressTracker& operator=(ProgressTracker&& other) = delete;

  void set_proportion(double proportion);
  void set_visible(bool v) { m_visible = v; }
  bool is_visible() const { return m_visible; }

  // Thread-safe: only advances when `proportion` exceeds the current value (for OpenMP loops
  // where work completes out of order).
  void report_parallel_progress(double proportion);

  // visible: nullopt = inherit parent, true = force visible, false = force invisible
  ProgressTracker subtracker(double start, double end, std::string name = "",
                             std::source_location location = std::source_location::current(),
                             std::optional<bool> visible = std::nullopt);

  // Callee entry: set scope display name and emit status text.
  void begin_tracking(std::string text, std::source_location location);

  virtual ~ProgressTracker();

  double proportion() const { return m_proportion; }
};

class AsyncProgressTracker {
  std::shared_ptr<ProgressTracker> m_tracker;

 public:
  explicit AsyncProgressTracker(ProgressObserver* observer = nullptr, std::string name = "")
      : m_tracker(std::make_shared<ProgressTracker>(observer, std::move(name))) {}

  std::shared_ptr<ProgressTracker> tracker() { return m_tracker; }
};

// Default parent tracker is progress_tracker.
#define SUBTRACKER_GET(_1, _2, _3, NAME, ...) NAME
#define SUBTRACKER(...) SUBTRACKER_GET(__VA_ARGS__, SUBTRACKER_3, SUBTRACKER_2)(__VA_ARGS__)
#define SUBTRACKER_2(start, end) \
  (progress_tracker).subtracker((start), (end), "", std::source_location::current())
#define SUBTRACKER_3(start, end, tracker) \
  ((tracker)).subtracker((start), (end), "", std::source_location::current())

#define SUBTRACKER_HIDDEN(...) \
  SUBTRACKER_GET(__VA_ARGS__, SUBTRACKER_HIDDEN_3, SUBTRACKER_HIDDEN_2)(__VA_ARGS__)
#define SUBTRACKER_HIDDEN_2(start, end) \
  (progress_tracker).subtracker((start), (end), "", std::source_location::current(), false)
#define SUBTRACKER_HIDDEN_3(start, end, tracker) \
  ((tracker)).subtracker((start), (end), "", std::source_location::current(), false)

#define SUBTRACKER_VISIBLE(...) \
  SUBTRACKER_GET(__VA_ARGS__, SUBTRACKER_VISIBLE_3, SUBTRACKER_VISIBLE_2)(__VA_ARGS__)
#define SUBTRACKER_VISIBLE_2(start, end) \
  (progress_tracker).subtracker((start), (end), "", std::source_location::current(), true)
#define SUBTRACKER_VISIBLE_3(start, end, tracker) \
  ((tracker)).subtracker((start), (end), "", std::source_location::current(), true)

#define START_TRACKER_GET(_1, _2, NAME, ...) NAME
#define START_TRACKER(...) \
  START_TRACKER_GET(__VA_ARGS__, START_TRACKER_2, START_TRACKER_1)(__VA_ARGS__)
#define START_TRACKER_1(text) \
  (progress_tracker).begin_tracking((text), std::source_location::current())
#define START_TRACKER_2(tracker, text) \
  ((tracker)).begin_tracking((text), std::source_location::current())
```


