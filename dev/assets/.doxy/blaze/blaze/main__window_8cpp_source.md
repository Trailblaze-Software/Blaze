

# File main\_window.cpp

[**File List**](files.md) **>** [**gui**](dir_99d0482cf009f9d97a0877749b817f19.md) **>** [**main\_window.cpp**](main__window_8cpp.md)

[Go to the documentation of this file](main__window_8cpp.md)


```C++
#include "main_window.hpp"

#include <QtConcurrent>
#include <QtWidgets>

#include "config_input/config_input.hpp"
#include "progress_box.hpp"
#include "run.hpp"
#include "ui_main_window.h"

MainWindow::MainWindow() : ui(std::make_unique<Ui::MainWindow>()) {
  try {
    if (!QIcon::hasThemeIcon("list-add")) {
      QIcon::setThemeName("Humanity");
      QIcon::setFallbackThemeName("default");
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

    ui->runButton->setEnabled(ui->config_editor->is_valid());

  } catch (const std::exception& e) {
    QMessageBox::critical(this, "Error", e.what());
    exit(1);
  }
}

MainWindow::~MainWindow() {}

void MainWindow::about() {
  QMessageBox::about(this, "About Blaze",
                     QString("This is the Blaze LIDAR mapping tool. It is free and open-source, "
                             "released under the GPLv3 license.<br><br>"
                             "Please contact us at <a "
                             "href=\"mailto:trailblaze.software@gmail.com\">trailblaze.software@"
                             "gmail.com</a> for other licensing options.<br><br>"
                             "Version: " BLAZE_VERSION "<br>"
                             "Commit hash: " GIT_COMMIT_HASH "<br><br>"
                             "<a href=\"https://github.com/Trailblaze-Software/Blaze\">Source "
                             "code</a> available.<br>"));
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
```


