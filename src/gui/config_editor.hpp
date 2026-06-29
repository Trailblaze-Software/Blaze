#pragma once

#include <QTimer>
#include <QToolBox>
#include <cstddef>
#include <cstdint>

#include "utilities/filesystem.hpp"

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

  // Cached summary stats from the most recent update_las_stats() run. Returns
  // 0 for all values if no LAS/LAZ files are selected or none could be read.
  std::uint64_t last_total_points() const { return m_last_total_points; }
  double last_total_area_m2() const { return m_last_total_area_m2; }
  std::size_t last_file_count() const { return m_last_file_count; }

 public slots:
  void open_config_file();
  void save_config_file();
  void reset_to_defaults();
  void add_las_file();
  void remove_las_file();
  void add_las_folder();
  void set_las_files(const std::vector<fs::path>& files);

  // Contours
  void add_contour();
  void remove_contour();
  void handle_contour_selected();
  void update_contour_from_ui();

  // Water
  void add_water();
  void remove_water();
  void handle_water_selected();
  void update_water_from_ui();
  void update_water_globals_from_ui();

  // Vegetation
  void add_vege();
  void remove_vege();
  void handle_vege_selected();
  void update_vege_from_ui();
  void add_vege_color();
  void remove_vege_color();
  void update_vege_color_from_ui(int row, int column);

  // Colors
  void add_color();
  void remove_color();
  void handle_color_selected();
  void update_color_from_ui();
  void pick_color();
  void handle_color_type_changed(int index);

  // General
  void update_general_from_ui();

 signals:
  void config_changed();

 private:
  static Config load_initial_config();
  void save_last_used_config();

  void set_ui_to_config(const Config& config);

  void open_output_directory();

  // Wrap each page of the main QTabWidget in a QScrollArea so that the tab
  // contents keep their preferred size when the window is too small, with the
  // user scrolling to reach off-screen widgets instead of Qt squishing them.
  void wrap_tabs_in_scroll_areas();

  // Activate the tab whose page (directly or transitively) contains
  // `content`. Needed because after wrap_tabs_in_scroll_areas() the
  // ui->*_tab widgets are nested inside a QScrollArea and are no longer
  // direct children of the QTabWidget.
  void activate_tab_containing(QWidget* content);

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

  void update_las_stats();

  bool m_updating_ui = false;
  bool m_persist_enabled = false;
  QTimer m_save_debounce_timer;

  // Cached aggregate statistics across all selected LAS/LAZ inputs. These
  // mirror what is shown in las_stats_label and are refreshed by
  // update_las_stats().
  std::uint64_t m_last_total_points = 0;
  double m_last_total_area_m2 = 0.0;
  std::size_t m_last_file_count = 0;

  // Whether any pair of selected input files' bounding boxes overlap in xy,
  // or whether different horizontal CRSes were detected. When either is true,
  // tiled mode must be enabled (tile_size > 0) for Blaze to produce correct
  // output. Recomputed by update_las_stats().
  bool m_inputs_overlap = false;
  bool m_inputs_mixed_crs = false;

  // Parse error for the current Override CRS field, or empty if the field
  // parses cleanly (including when it is blank). Refreshed by
  // refresh_override_crs_status() and consumed by is_valid().
  std::string m_override_crs_error;

  // Refresh the tile-size status label and styling based on the current
  // tile_size field, override_crs, and cached overlap/CRS flags.
  void refresh_tile_size_status();

  // Re-parse the current Override CRS field and update the line-edit styling
  // and override_crs_status label accordingly. Updates m_override_crs_error.
  void refresh_override_crs_status();
};
