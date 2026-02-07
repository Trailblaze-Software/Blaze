

# File main.cpp

[**File List**](files.md) **>** [**gui**](dir_99d0482cf009f9d97a0877749b817f19.md) **>** [**main.cpp**](main_8cpp.md)

[Go to the documentation of this file](main_8cpp.md)


```C++
#include <QApplication>

#include "main_window.hpp"

int main(int argc, char* argv[]) {
  QApplication a(argc, argv);

  MainWindow window;
  window.show();
  return QApplication::exec();
}
```


