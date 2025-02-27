#include <QApplication>
#include <QMainWindow>

#include "gl_widget.hpp"
#include "main_3d_window.hpp"

#ifdef _WIN32
#include <windows.h>
#endif

MainWindow::MainWindow() {
  glWidget = new GLWidget();
  setCentralWidget(glWidget);
  setWindowTitle(tr("3D Viewer"));
}
MainWindow::~MainWindow() { delete glWidget; }

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

  QApplication a(argc, argv);

  QSurfaceFormat::setDefaultFormat(QSurfaceFormat::defaultFormat());
  MainWindow window;
  window.show();
  return QApplication::exec();
}
