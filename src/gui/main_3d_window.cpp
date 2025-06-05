#include "main_3d_window.hpp"

#include <qmessagebox.h>
#include <qtreewidget.h>

#include "ui_main_3d_window.h"
#include "utilities/progress_tracker.hpp"

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

    connect(ui->actionOpen, &QAction::triggered, this, &Main3DWindow::open_layer_file);
    // connect(ui->actionAbout, &QAction::triggered, this, &MainWindow::about);
    ui->horizontalLayout->addWidget(gl_widget.get());

  } catch (const std::exception& e) {
    QMessageBox::critical(this, "Error", e.what());
    exit(1);
  }
}

Main3DWindow::~Main3DWindow() {}

AsyncProgressTracker Main3DWindow::add_progress_tracker() {
  ProgressTrackerBar* bar = new ProgressTrackerBar(ui->statusBar);
  ui->statusBar->addPermanentWidget(bar);
  return bar->tracker();
}

void Main3DWindow::add_layer(std::unique_ptr<Layer> layer) {
  QTreeWidgetItem* item = new QTreeWidgetItem(ui->treeWidget);
  item->setText(0, QString::fromStdString(layer->name()));
  ui->treeWidget->addTopLevelItem(item);
  ui->treeWidget->resizeColumnToContents(0);
  gl_widget->add_layer(std::move(layer));
}

void Main3DWindow::open_layer_file() {
  std::string filename =
      QFileDialog::getOpenFileName(this, "Open LAS file", "", "LIDAR Point Clouds (*.las, *.laz)")
          .toStdString();
  add_layer(std::make_unique<LASLayer>(filename, add_progress_tracker()));
}
