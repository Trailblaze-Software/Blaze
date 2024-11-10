#pragma once

#include <optional>
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

class ProgressBar : public ProgressObserver {
  double m_last_progress;

 protected:
  virtual void update_progress(double progress) override;
  virtual void text_update(const std::string& text, int depth = 0) override;
};

class ProgressTracker : public ProgressObserver {
  double m_proportion;
  ProgressObserver* m_observer;
  std::optional<std::pair<double, double>> m_subtracker_range;

  void _set_proportion(double proportion);

 protected:
  virtual void update_progress(double progress) override;

 public:
  explicit ProgressTracker(ProgressObserver* observer = nullptr);

  virtual void text_update(const std::string& text, int depth = 0) override;

  ProgressTracker(const ProgressTracker& other) = delete;
  ProgressTracker& operator=(const ProgressTracker& other) = delete;
  ProgressTracker(ProgressTracker&& other);
  ProgressTracker& operator=(ProgressTracker&& other) = delete;

  void set_proportion(double proportion);

  ProgressTracker subtracker(double start, double end);

  virtual ~ProgressTracker();

  double proportion() const { return m_proportion; }
};

void run_loop(ProgressTracker tracker);
