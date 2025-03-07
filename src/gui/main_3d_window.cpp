#include "main_3d_window.hpp"

#include <qmessagebox.h>

#include "ui_main_3d_window.h"

Main3DWindow::Main3DWindow() : ui(std::make_unique<Ui::Main3DWindow>()) {
  gl_widget = std::make_unique<GLWidget>(this);
  // setCentralWidget(gl_widget.get());
  setWindowTitle(tr("Blaze 3D"));
  try {
    if (!QIcon::hasThemeIcon("list-add")) {
      QIcon::setThemeName("Humanity");
      QIcon::setFallbackThemeName("default");
    }
    ui->setupUi(this);

    // connect(ui->actionOpen, &QAction::triggered, this,
    //[this] { ui->config_editor->open_config_file(); });
    // connect(ui->actionAbout, &QAction::triggered, this, &MainWindow::about);
    ui->horizontalLayout->addWidget(gl_widget.get());

  } catch (const std::exception& e) {
    QMessageBox::critical(this, "Error", e.what());
    exit(1);
  }
}
Main3DWindow::~Main3DWindow() {}
