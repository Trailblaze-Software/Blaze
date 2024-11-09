#include "main_window.hpp"

#include <QtConcurrent>
#include <QtWidgets>

#include "config_input/config_input.hpp"
#include "progress_box.hpp"
#include "run.hpp"
#include "ui_main_window.h"

MainWindow::MainWindow() : ui(new Ui::MainWindow) {
  if (!QIcon::hasThemeIcon("list-add")) {
    QIcon::setThemeName("Humanity");
  }
  ui->setupUi(this);

  connect(ui->runButton, &QPushButton::clicked, this, &MainWindow::run_blaze);
  connect(ui->actionOpen, &QAction::triggered, this,
          [this] { ui->config_editor->open_config_file(); });
  connect(ui->actionSaveAs, &QAction::triggered, this,
          [this] { ui->config_editor->save_config_file(); });
  connect(ui->actionAbout, &QAction::triggered, this, &MainWindow::about);

  connect(ui->config_editor, &ConfigEditor::config_changed,
          [this] { ui->runButton->setEnabled(ui->config_editor->is_valid()); });
}

MainWindow::~MainWindow() {}

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
  ProgressBox* message_box = new ProgressBox(this);
  message_box->show();
  const Config& config = ui->config_editor->get_config();
  message_box->start_task(
      [&config, message_box] {
        run_with_config(config, std::vector<fs::path>(), ProgressTracker(message_box));
      },
      [&config] {
        QDialog* dialog = new QDialog();
        dialog->setWindowTitle("Blaze processing done!");
        QVBoxLayout* layout = new QVBoxLayout();
        dialog->setLayout(layout);
        QLabel* label = new QLabel("Processing complete!");
        layout->addWidget(label);
        if (config.processing_steps.contains(ProcessingStep::Combine)) {
          QLabel* label2 =
              new QLabel("The combined output is located at: " +
                         QString::fromStdString((config.output_path() / "combined").string()));
          layout->addWidget(label2);
          QImage image((config.output_path() / "combined" / "final_img.tif").string().c_str());
          if (image.isNull()) {
            std::cerr << "Failed to load image from "
                      << (config.output_path() / "combined" / "final_img.tif") << std::endl;
          } else {
            QScrollArea* scroll_area = new QScrollArea();
            layout->addWidget(scroll_area);

            QLabel* image_label = new QLabel();
            image_label->setPixmap(QPixmap::fromImage(image));
            scroll_area->setWidget(image_label);
            scroll_area->setWidgetResizable(true);
          }
        }
        QPushButton* button = new QPushButton("OK");
        layout->addWidget(button);
        connect(button, &QPushButton::clicked, dialog, &QDialog::accept);
        dialog->exec();
      });
}
