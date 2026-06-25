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
  explicit ProgressTracker(ProgressObserver* observer = nullptr,
                           std::source_location location = std::source_location::current());

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
  ProgressTracker subtracker(double start, double end, std::optional<bool> visible = std::nullopt,
                             std::source_location location = std::source_location::current());

  virtual ~ProgressTracker();

  double proportion() const { return m_proportion; }
};

class AsyncProgressTracker {
  std::shared_ptr<ProgressTracker> m_tracker;

 public:
  explicit AsyncProgressTracker(ProgressObserver* observer = nullptr)
      : m_tracker(std::make_shared<ProgressTracker>(observer)) {}

  std::shared_ptr<ProgressTracker> tracker() { return m_tracker; }
};

void run_loop(ProgressTracker tracker);
