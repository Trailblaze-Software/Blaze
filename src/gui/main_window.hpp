#pragma once

#include <QMainWindow>

struct Config;
#include <vector>

#include "utilities/filesystem.hpp"

QT_BEGIN_NAMESPACE
class QAction;
class QLabel;
class QMenu;
class QPushButton;
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow();
  virtual ~MainWindow() = default;

 private slots:
  void open();
  void about();
  void run_blaze();
  void run_stuff(std::shared_ptr<Config> config, const std::vector<fs::path> additional_las_files);

 private:
  QMenu *m_file_menu;
  QAction *m_open_action;
  QAction *m_exit_action;

  QMenu *m_help_menu;
  QAction *m_about_action;

  QLabel *m_filename_label;
  QPushButton *m_run_button;
};
