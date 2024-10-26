#pragma once

#include <QToolBox>

#include "config_input/config_input.hpp"

namespace Ui {
class ConfigEditor;
}

class ConfigEditor : public QWidget {
  Q_OBJECT

 public:
  explicit ConfigEditor(QWidget* parent = nullptr);
  ~ConfigEditor();

  const Config& get_config() { return m_config; }

 public slots:
  void open_config_file();
  void save_config_file();

 private:
  void set_ui_to_config(const Config& config);

  void open_output_directory();

  Ui::ConfigEditor* ui;
  Config m_config;
};
