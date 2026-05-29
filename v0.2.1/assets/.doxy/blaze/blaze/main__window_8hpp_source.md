

# File main\_window.hpp

[**File List**](files.md) **>** [**gui**](dir_99d0482cf009f9d97a0877749b817f19.md) **>** [**main\_window.hpp**](main__window_8hpp.md)

[Go to the documentation of this file](main__window_8hpp.md)


```C++
#pragma once

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow();
  ~MainWindow();

 private slots:
  void about();
  void run_blaze();

 private:
  std::unique_ptr<Ui::MainWindow> ui;
};
```


