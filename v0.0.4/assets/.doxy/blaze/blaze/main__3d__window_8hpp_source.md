

# File main\_3d\_window.hpp

[**File List**](files.md) **>** [**gui**](dir_99d0482cf009f9d97a0877749b817f19.md) **>** [**main\_3d\_window.hpp**](main__3d__window_8hpp.md)

[Go to the documentation of this file](main__3d__window_8hpp.md)


```C++
#pragma once

#include <QMainWindow>
#include <QProgressBar>

#include "gl_widget.hpp"

QT_BEGIN_NAMESPACE
namespace Ui {
class Main3DWindow;
}
QT_END_NAMESPACE

class ProgressTrackerBar : public QProgressBar, public ProgressObserver {
  AsyncProgressTracker m_progress_tracker;
  bool m_tracker_obtained = false;

 public:
  explicit ProgressTrackerBar(QWidget* parent) : QProgressBar(parent), m_progress_tracker() {
    setMinimum(0);
    setMaximum(1000);
  }

  virtual void update_progress(double progress) override { setValue(progress * 1000); }

  virtual void text_update(const std::string& text, int depth = 0) override {
    (void)text;
    (void)depth;
  }

  AsyncProgressTracker tracker() {
    Assert(!m_tracker_obtained);
    m_tracker_obtained = true;
    return m_progress_tracker;
  }
};

class Main3DWindow : public QMainWindow {
  Q_OBJECT

 public:
  Main3DWindow();
  ~Main3DWindow();

  void add_layer(std::unique_ptr<Layer> layer);

  AsyncProgressTracker add_progress_tracker();

 private slots:
  void open_layer_file();

 private:
  std::unique_ptr<Ui::Main3DWindow> ui;
  std::unique_ptr<GLWidget> gl_widget;
};
```


