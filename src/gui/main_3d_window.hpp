#pragma once

#include <QMainWindow>

#include "gl_widget.hpp"

QT_BEGIN_NAMESPACE
namespace Ui {
class Main3DWindow;
}
QT_END_NAMESPACE

class Main3DWindow : public QMainWindow {
  Q_OBJECT

 public:
  Main3DWindow();
  ~Main3DWindow();

  std::unique_ptr<Ui::Main3DWindow> ui;
  std::unique_ptr<GLWidget> gl_widget;
};
