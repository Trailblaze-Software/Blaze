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
