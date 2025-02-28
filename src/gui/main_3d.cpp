#include <QApplication>
#include <QMainWindow>

#include "gl_widget.hpp"
#include "main_3d_window.hpp"
#include "utilities/resources.hpp"

#ifdef _WIN32
#include <windows.h>
#endif

MainWindow::MainWindow() {
  gl_widget = new GLWidget();
  setCentralWidget(gl_widget);
  setWindowTitle(tr("Blaze 3D"));
}
MainWindow::~MainWindow() { delete gl_widget; }

int main(int argc, char *argv[]) {
#ifdef _WIN32
  AllocConsole();
  freopen("CONOUT$", "w", stdout);
  freopen("CONOUT$", "w", stderr);
#endif

  QSurfaceFormat format;
  format.setVersion(3, 3);
  format.setProfile(QSurfaceFormat::CoreProfile);
  QSurfaceFormat::setDefaultFormat(format);

  std::optional<fs::path> file_path;
  if (argc > 1) {
    file_path = argv[1];
  }

  QApplication a(argc, argv);

  QSurfaceFormat::setDefaultFormat(QSurfaceFormat::defaultFormat());
  MainWindow window;
  window.gl_widget->load_las_file(file_path.value_or(AssetRetriever::get_asset("sample.laz")));
  window.show();
  return QApplication::exec();
}
