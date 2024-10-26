#pragma once

#include <QMainWindow>

#include "ui_main_window.h"
#include "utilities/filesystem.hpp"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow();

 private slots:
  void about();
  void run_blaze();

 private:
  std::unique_ptr<Ui::MainWindow> ui;
};
