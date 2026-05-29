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
    connect(ui->actionResetDefaults, &QAction::triggered, this,
            [this] { ui->config_editor->reset_to_defaults(); });
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
  const Config& config = ui->config_editor->get_config();

  // Warn if the requested bin resolution will leave fewer than 5 LiDAR points
  // per bin on average. At that density ground/vegetation classifications and
  // contours tend to become noisy; it usually indicates the user either picked
  // too fine a bin resolution or loaded too little data for the area.
  constexpr double kMinPointsPerBin = 5.0;
  const double total_area = ui->config_editor->last_total_area_m2();
  const std::uint64_t total_points = ui->config_editor->last_total_points();
  const double bin_res = config.grid.bin_resolution;
  if (total_area > 0.0 && total_points > 0 && bin_res > 0.0) {
    const double density = static_cast<double>(total_points) / total_area;  // pts/m^2
    const double points_per_bin = density * bin_res * bin_res;
    if (points_per_bin < kMinPointsPerBin) {
      QMessageBox box(this);
      box.setIcon(QMessageBox::Warning);
      box.setWindowTitle("Low point density");
      box.setText(QString("Average density is only %1 point(s) per %2 m bin "
                          "(below the recommended minimum of %3).")
                      .arg(points_per_bin, 0, 'f', 2)
                      .arg(bin_res, 0, 'f', 2)
                      .arg(kMinPointsPerBin, 0, 'f', 0));
      box.setInformativeText(QString("Overall: %1 points over %2 km\u00B2 (%3 pts/m\u00B2).\n\n"
                                     "Consider increasing \"Bin Resolution\" on the General tab, "
                                     "or adding more LAS/LAZ data, before processing. Continue "
                                     "anyway?")
                                 .arg(QLocale().toString(static_cast<qulonglong>(total_points)))
                                 .arg(total_area / 1'000'000.0, 0, 'f', 3)
                                 .arg(density, 0, 'f', 2));
      box.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
      box.setDefaultButton(QMessageBox::Cancel);
      box.button(QMessageBox::Yes)->setText("Run anyway");
      if (box.exec() != QMessageBox::Yes) {
        return;
      }
    }
  }

  ProgressBox* message_box = new ProgressBox(this);
  message_box->show();
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
