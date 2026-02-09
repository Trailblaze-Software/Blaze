

# File progress\_tracker.hpp

[**File List**](files.md) **>** [**lib**](dir_c85d3e3c5052e9ad9ce18c6863244a25.md) **>** [**utilities**](dir_f68f3bc40609949e989ead5b0b6dedfd.md) **>** [**progress\_tracker.hpp**](progress__tracker_8hpp.md)

[Go to the documentation of this file](progress__tracker_8hpp.md)


```C++
#pragma once

#include <memory>
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
  double m_last_progress = -1;

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

class AsyncProgressTracker {
  std::shared_ptr<ProgressTracker> m_tracker;

 public:
  AsyncProgressTracker() : m_tracker(std::make_shared<ProgressTracker>()) {}

  std::shared_ptr<ProgressTracker> tracker() { return m_tracker; }
};

void run_loop(ProgressTracker tracker);
```


