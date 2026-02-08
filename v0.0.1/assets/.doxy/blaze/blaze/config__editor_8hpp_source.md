

# File config\_editor.hpp

[**File List**](files.md) **>** [**gui**](dir_99d0482cf009f9d97a0877749b817f19.md) **>** [**config\_editor.hpp**](config__editor_8hpp.md)

[Go to the documentation of this file](config__editor_8hpp.md)


```C++
#pragma once

#include <QToolBox>

struct Config;
class QComboBox;

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

  // Contours
  void add_contour();
  void remove_contour();
  void on_contour_selected();
  void update_contour_from_ui();

  // Water
  void add_water();
  void remove_water();
  void on_water_selected();
  void update_water_from_ui();

  // Vegetation
  void add_vege();
  void remove_vege();
  void on_vege_selected();
  void update_vege_from_ui();
  void add_vege_color();
  void remove_vege_color();
  void update_vege_color_from_ui(int row, int column);

  // Colors
  void add_color();
  void remove_color();
  void on_color_selected();
  void update_color_from_ui();
  void pick_color();
  void on_color_type_changed(int index);

  // General
  void update_general_from_ui();

 signals:
  void config_changed();

 private:
  void set_ui_to_config(const Config& config);

  void open_output_directory();

  std::unique_ptr<Ui::ConfigEditor> ui;
  std::unique_ptr<Config> m_config;

  // Helpers
  void populate_contour_list();
  void populate_water_list();
  void populate_vege_list();
  void populate_color_list();
  void load_contour_details(const std::string& name);
  void load_water_details(const std::string& name);
  void load_vege_details(int index);
  void load_color_details(const std::string& name);
  void populate_color_combo(QComboBox* combo);

  bool m_updating_ui = false;
};
```


