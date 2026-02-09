

# File main\_3d.cpp

[**File List**](files.md) **>** [**gui**](dir_99d0482cf009f9d97a0877749b817f19.md) **>** [**main\_3d.cpp**](main__3d_8cpp.md)

[Go to the documentation of this file](main__3d_8cpp.md)


```C++
#include <QApplication>
#include <QMainWindow>

#include "gl_widget.hpp"
#include "main_3d_window.hpp"
#include "utilities/resources.hpp"

#ifdef _WIN32
#include <windows.h>
#endif

int main(int argc, char* argv[]) {
#ifdef _WIN32
  AllocConsole();
  freopen("CONOUT$", "w", stdout);
  freopen("CONOUT$", "w", stderr);
#endif

  QSurfaceFormat format;
  format.setVersion(3, 3);
  format.setProfile(QSurfaceFormat::CoreProfile);
#ifdef GL_DEBUG
  format.setOption(QSurfaceFormat::DebugContext);
#endif
  QSurfaceFormat::setDefaultFormat(format);

  std::optional<fs::path> file_path;
  if (argc > 1) {
    file_path = argv[1];
  }

  QApplication a(argc, argv);

  QSurfaceFormat::setDefaultFormat(QSurfaceFormat::defaultFormat());

  Main3DWindow window;

  window.show();

  window.add_layer(std::make_unique<LASLayer>(
      file_path.value_or(AssetRetriever::get_asset("sample.laz")), window.add_progress_tracker()));

  return QApplication::exec();
}
```


