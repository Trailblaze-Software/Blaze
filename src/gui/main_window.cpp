#include "main_window.hpp"

#include <QtConcurrent>
#include <QtWidgets>

#include "config_input/config_input.hpp"
#include "progress_box.hpp"
#include "run.hpp"

#if QT_VERSION >= QT_VERSION_CHECK(6, 7, 0)
#define OPEN_ICON QIcon::fromTheme(QIcon::ThemeIcon::DocumentOpen)
#define EXIT_ICON QIcon::fromTheme(QIcon::ThemeIcon::ApplicationExit)
#define ABOUT_ICON QIcon::fromTheme(QIcon::ThemeIcon::HelpAbout)
#else
#define OPEN_ICON QIcon::fromTheme("document-open")
#define EXIT_ICON QIcon::fromTheme("application-exit")
#define ABOUT_ICON QIcon::fromTheme("help-about")
#endif

MainWindow::MainWindow() {
  QWidget *widget = new QWidget;
  setCentralWidget(widget);

  QWidget *top_filler = new QWidget;
  top_filler->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

  m_filename_label = new QLabel(("<i>Choose a Config file from the File menu</i>"));

  QWidget *bottom_filler = new QWidget;
  bottom_filler->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

  QVBoxLayout *layout = new QVBoxLayout;
  layout->setContentsMargins(20, 20, 20, 20);
  layout->addWidget(top_filler);
  layout->addWidget(m_filename_label);

  m_run_button = new QPushButton();
  m_run_button->setText("Run Blaze");
  m_run_button->setEnabled(false);
  m_run_button->setToolTip("Run Blaze with the selected config file");
  m_run_button->setFixedWidth(120);
  layout->addWidget(m_run_button);
  connect(m_run_button, &QPushButton::clicked, this, &MainWindow::run_blaze);

  layout->addWidget(bottom_filler);
  widget->setLayout(layout);

  m_open_action = new QAction(OPEN_ICON, "&Open...", this);
  m_open_action->setShortcuts(QKeySequence::Open);
  m_open_action->setStatusTip(("Open a config file"));
  connect(m_open_action, &QAction::triggered, this, &MainWindow::open);

  m_exit_action = new QAction(EXIT_ICON, "Exit", this);
  m_exit_action->setShortcuts(QKeySequence::Quit);
  m_exit_action->setStatusTip("Exit Blaze");
  connect(m_exit_action, &QAction::triggered, this, &QWidget::close);

  m_about_action = new QAction(ABOUT_ICON, "About", this);
  m_about_action->setStatusTip(("Show Blaze About Info"));
  connect(m_about_action, &QAction::triggered, this, &MainWindow::about);

  m_file_menu = menuBar()->addMenu(("File"));
  m_file_menu->addAction(m_open_action);
  m_file_menu->addSeparator();
  m_file_menu->addAction(m_exit_action);

  m_help_menu = menuBar()->addMenu(("Help"));
  m_help_menu->addAction(m_about_action);

  setMinimumSize(320, 160);
  resize(480, 320);
}

void MainWindow::open() {
  QString config_file_name = QFileDialog::getOpenFileName(
      this, ("Open Config"), "", ("Config Files (*.json *.jsonc);;All files (*)"), nullptr,
      QFileDialog::ReadOnly);
  m_filename_label->setText(config_file_name);
  m_run_button->setEnabled(true);
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

void MainWindow::run_stuff(std::shared_ptr<Config> config,
                           const std::vector<fs::path> additional_las_files,
                           ProgressObserver *observer) {
  try {
    run_with_config(*config, additional_las_files, ProgressTracker(observer));
  } catch (const std::exception &e) {
    QMessageBox::critical(this, "Error Running Blaze", e.what());
  }
}

void MainWindow::run_blaze() {
  QString config_file_name = m_filename_label->text();
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
    message_box->setWindowTitle("Running Blaze");
    message_box->setText(
        "Blaze is running with the selected config file. Please wait for the process to finish.");
    message_box->show();
    QFutureWatcher<void> *watcher = new QFutureWatcher<void>(this);
    connect(watcher, &QFutureWatcher<void>::finished, message_box,
            [message_box] { message_box->done(0); });
    connect(watcher, &QFutureWatcher<void>::finished, watcher, &QFutureWatcher<void>::deleteLater);
    watcher->setFuture(QtConcurrent::run([this, config, message_box] {
      this->run_stuff(config, std::vector<fs::path>(), message_box);
    }));
  } catch (const std::exception &e) {
    std::string error_message =
        std::string(e.what()) + (read_config ? ""
                                             : "\n\nThis is likely an error due to an invalid "
                                               "config file. Please check the file and try again.");
    QMessageBox::critical(this, "Error Running Blaze", QString::fromStdString(error_message));
  }
}