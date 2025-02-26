#include <QApplication>
#include <QMainWindow>

#include "gl_widget.hpp"
#include "main_3d_window.hpp"

MainWindow::MainWindow() {
  glWidget = new GLWidget();
  setCentralWidget(glWidget);
  setWindowTitle(tr("3D Viewer"));
}
MainWindow::~MainWindow() { delete glWidget; }

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  MainWindow window;
  window.show();
  return QApplication::exec();
}
