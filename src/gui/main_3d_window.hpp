#pragma once

#include <QMainWindow>

#include "gl_widget.hpp"

class MainWindow : public QMainWindow {
  // Q_OBJECT

 public:
  MainWindow();
  ~MainWindow();

  GLWidget *glWidget;
};
