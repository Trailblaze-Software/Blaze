#include "main_window.hpp"

#include <QtConcurrent>
#include <QtWidgets>

#include "config_input/config_input.hpp"
#include "progress_box.hpp"
#include "run.hpp"
#include "ui_main_window.h"

MainWindow::MainWindow() : ui(new Ui::MainWindow) {
  ui->setupUi(this);

  connect(ui->runButton, &QPushButton::clicked, this, &MainWindow::run_blaze);
  connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::open);
  connect(ui->actionAbout, &QAction::triggered, this, &MainWindow::about);
}

void MainWindow::open() {
  QString config_file_name = QFileDialog::getOpenFileName(
      this, ("Open Config"), "", ("Config Files (*.json *.jsonc);;All files (*)"), nullptr,
      QFileDialog::ReadOnly);
  ui->label->setText(config_file_name);
  ui->runButton->setEnabled(true);
}

void MainWindow::about() {
  QMessageBox::about(this, "About Blaze",
                     QString("This is the Blaze LIDAR mapping tool. It is free for non-commercial "
                             "nav-sport mapping only.<br><br>"
                             "Please contact us at <a "
                             "href=\"mailto:trailblaze.software@gmail.com\">trailblaze.software@"
                             "gmail.com</a> for commercial licensing options.<br><br>"
                             "Version: " BLAZE_VERSION "<br>"
                             "Commit hash: " GIT_COMMIT_HASH "<br><br>"
                             "<a href=\"https://github.com/Trailblaze-Software/Blaze\">Source "
                             "code</a> available under the AGPLv3 license.<br>"));
}

void MainWindow::run_blaze() {
  QString config_file_name = ui->label->text();
  if (config_file_name.isEmpty()) {
    QMessageBox::warning(this, "No Config File", "Please select a config file first.");
    return;
  }

  bool read_config = false;
  try {
    std::shared_ptr<Config> config =
        std::make_shared<Config>(Config::FromFile(config_file_name.toStdString()));
    read_config = true;
    ProgressBox *message_box = new ProgressBox(this);
    message_box->show();
    message_box->start_task([config, message_box] {
      run_with_config(*config, std::vector<fs::path>(), ProgressTracker(message_box));
    });
  } catch (const std::exception &e) {
    std::string error_message =
        std::string(e.what()) + (read_config ? ""
                                             : "\n\nThis is likely an error due to an invalid "
                                               "config file. Please check the file and try again.");
    QMessageBox::critical(this, "Error Running Blaze", QString::fromStdString(error_message));
  }
}
