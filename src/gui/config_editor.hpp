#pragma once

#include <QToolBox>

struct Config;

namespace Ui {
class ConfigEditor;
}

class ConfigEditor : public QWidget {
  Q_OBJECT

 public:
  explicit ConfigEditor(QWidget* parent = nullptr);
  ~ConfigEditor();

  const Config& get_config() { return *m_config; }

  bool is_valid() const;

 public slots:
  void open_config_file();
  void save_config_file();
  void add_las_file();
  void remove_las_file();
  void add_las_folder();

 signals:
  void config_changed();

 private:
  void set_ui_to_config(const Config& config);

  void open_output_directory();

  std::unique_ptr<Ui::ConfigEditor> ui;
  std::unique_ptr<Config> m_config;
};
