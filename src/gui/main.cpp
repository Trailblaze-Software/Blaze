#include <QApplication>

#include "main_window.hpp"

int main(int argc, char* argv[]) {
  QApplication a(argc, argv);
  QCoreApplication::setOrganizationName("Trailblaze Software");
  QCoreApplication::setApplicationName("Blaze");

  MainWindow window;
  window.show();
  return QApplication::exec();
}
