#pragma once

#include <QMainWindow>

struct Config;
#include <vector>

#include "utilities/filesystem.hpp"
#include "utilities/progress_tracker.hpp"

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
  void open();
  void about();
  void run_blaze();

 private:
  Ui::MainWindow* ui;
};
