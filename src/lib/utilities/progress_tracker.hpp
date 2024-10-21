#pragma once

#include <optional>
#include <utility>

#include "assert/assert.hpp"

class ProgressObserver {
 protected:
  virtual void update_progress(double progress) = 0;

 public:
  virtual ~ProgressObserver();

  friend class ProgressTracker;
};

class ProgressBar : public ProgressObserver {
 protected:
  virtual void update_progress(double progress) override;
};

class ProgressTracker : public ProgressObserver {
 public:
  double m_proportion;
  ProgressObserver* m_observer;
  std::optional<std::pair<double, double>> m_subtracker_range;

  void _set_proportion(double proportion);

 protected:
  virtual void update_progress(double progress) override;

 public:
  explicit ProgressTracker(ProgressObserver* observer = nullptr);

  ProgressTracker(const ProgressTracker& other) = delete;
  ProgressTracker& operator=(const ProgressTracker& other) = delete;
  ProgressTracker(ProgressTracker&& other);
  ProgressTracker& operator=(ProgressTracker&& other) = delete;

  void set_proportion(double proportion);

  ProgressTracker subtracker(double start, double end);

  virtual ~ProgressTracker();
};

void run_loop(ProgressTracker tracker);
