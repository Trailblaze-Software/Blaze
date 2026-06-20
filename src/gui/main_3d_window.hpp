#pragma once

#include <QMainWindow>
#include <QMetaObject>
#include <QProcess>
#include <QProgressBar>
#include <QTreeWidgetItem>
#include <QWidget>
#include <optional>

#include "gl_widget.hpp"
#include "gui/layer_renderer.hpp"
#include "utilities/filesystem.hpp"

class QComboBox;
class QGroupBox;
class QLabel;
class QPushButton;
class QSlider;
class QListWidget;

QT_BEGIN_NAMESPACE
namespace Ui {
class Main3DWindow;
}
QT_END_NAMESPACE

class ProgressTrackerBar : public QProgressBar, public ProgressObserver {
  AsyncProgressTracker m_progress_tracker;
  bool m_tracker_obtained = false;

 public:
  explicit ProgressTrackerBar(QWidget* parent) : QProgressBar(parent), m_progress_tracker(this) {
    setMinimum(0);
    setMaximum(1000);
  }

  virtual void update_progress(double progress) override {
    const int value = static_cast<int>(progress * 1000.0);
    const bool finished = progress >= 0.999;
    QMetaObject::invokeMethod(
        this,
        [this, value, finished]() {
          setValue(value);
          if (finished) {
            hide();
          }
        },
        Qt::QueuedConnection);
  }

  virtual void text_update(const std::string& text, int depth = 0) override {
    (void)text;
    (void)depth;
  }

  AsyncProgressTracker tracker() {
    Assert(!m_tracker_obtained);
    m_tracker_obtained = true;
    return m_progress_tracker;
  }
};

class Main3DWindow : public QMainWindow {
  Q_OBJECT

 public:
  Main3DWindow();
  ~Main3DWindow();

  void add_layer(std::unique_ptr<Layer> layer);

  void import_blaze_output_from_path(const std::string& directory);
  void set_exit_after_load(bool exit_after_load);
  void set_exit_after_render(bool exit_after_render) { m_exit_after_render = exit_after_render; }
  void set_bench_mode(bool bench) { m_bench_mode = bench; }
  void set_defer_render_until_loaded(bool defer);

  AsyncProgressTracker add_progress_tracker();
  const std::string& scene_reference_crs() const { return gl_widget->reference_crs_wkt(); }

 private slots:
  void open_layer_file();
  void import_blaze_output();
  void run_blaze_on_layers();
  void handle_blaze_process_finished(int exit_code, QProcess::ExitStatus status);
  void on_treeWidget_itemChanged(QTreeWidgetItem* item, int column);
  void on_treeWidget_customContextMenuRequested(const QPoint& pos);
  void remove_selected_layer();
  void maybe_exit_after_load();
  void finish_exit_after_load();

 private:
  void add_layer_to_tree(std::shared_ptr<Layer> layer);
  void remove_layer(const std::shared_ptr<Layer>& layer);
  QTreeWidgetItem* find_tree_item_for_layer(Layer* layer) const;
  void update_render_mode();

  static bool layer_is_ready(const Layer& layer);

  std::unique_ptr<Ui::Main3DWindow> ui;
  std::unique_ptr<GLWidget> gl_widget;
  std::unique_ptr<QProcess> m_blaze_process;
  std::optional<fs::path> m_pending_blaze_output;
  // Accumulated stdout/stderr from the most recent Blaze run, used to surface
  // the real failure reason if Blaze exits with a non-zero code.
  QString m_blaze_output;
  std::vector<std::shared_ptr<Layer>> m_layers;
  std::vector<ProgressTrackerBar*> m_layer_progress_bars;
  bool m_exit_after_load = false;
  bool m_exit_after_render = false;
  bool m_exit_after_load_fired = false;
  bool m_bench_mode = false;
  bool m_defer_render_until_loaded = false;

  QWidget* m_point_cloud_panel = nullptr;
  QGroupBox* m_surface_layer_panel = nullptr;
  QSlider* m_surface_opacity_slider = nullptr;
  QLabel* m_surface_opacity_value_label = nullptr;
  QSlider* m_point_size_slider = nullptr;
  QSlider* m_point_alpha_slider = nullptr;
  QSlider* m_point_stream_budget_slider = nullptr;
  QLabel* m_point_size_value_label = nullptr;
  QLabel* m_point_alpha_value_label = nullptr;
  QLabel* m_point_stream_budget_value_label = nullptr;
  QComboBox* m_point_color_mode_combo = nullptr;
  QPushButton* m_point_fixed_color_button = nullptr;
  QGroupBox* m_point_details_panel = nullptr;
  QLabel* m_point_details_label = nullptr;
  std::weak_ptr<LASLayer> m_active_las_layer;
  std::weak_ptr<Layer> m_active_surface_layer;
  bool m_updating_point_cloud_ui = false;
  bool m_updating_surface_ui = false;
  QListWidget* m_classification_list = nullptr;

  void setup_animation_panel();
  void setup_point_cloud_panel();
  void setup_surface_layer_panel();
  void setup_point_details_panel();
  void show_point_pick_details(const PointPickResult& pick);
  void clear_point_pick_details();
  void update_layer_panels_for_selection();
  void update_point_cloud_panel_for_selection();
  void update_surface_layer_panel_for_selection();
  void update_point_cloud_value_labels();
  void update_surface_layer_value_labels();
  void apply_point_cloud_style_from_ui();
  void apply_surface_layer_style_from_ui();
  void update_classification_list_from_active_layer();
};
