#pragma once

#include <QEvent>
#include <QFutureWatcher>
#include <QMatrix4x4>
#include <QMetaObject>
#include <QMouseEvent>
#include <QOpenGLFunctions>
#include <QOpenGLWidget>
#include <QShowEvent>
#include <QTimer>
#include <QtConcurrent>
#include <functional>
#include <iostream>
#include <optional>
#include <unordered_set>

#include "gui/camera.hpp"
#include "gui/incremental_framebuffer.hpp"
#include "gui/layer.hpp"
#include "gui/layer_renderer.hpp"
#include "gui/point_cloud_framebuffer.hpp"
#include "io/crs.hpp"

QT_FORWARD_DECLARE_CLASS(QOpenGLShaderProgram)

class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions {
  Q_OBJECT

 public:
  GLWidget(QWidget* parent = nullptr);
  ~GLWidget();

  void add_layer(std::shared_ptr<Layer> layer) {
    const std::string layer_projection = layer->projection();
    const std::string layer_native = layer->native_projection();
    if (m_layers.empty()) {
      m_projection = layer_projection;
      m_camera.world_offset() = layer->extent().center();
    } else if (!layer_native.empty() && !m_projection.empty() &&
               !wkt_matches(normalize_crs_wkt(layer_native), normalize_crs_wkt(m_projection))) {
      std::cerr << "Reprojecting layer \"" << layer->name() << "\" from CRS " << layer_native
                << " to " << m_projection << ".\n";
    }
    makeCurrent();
    m_layers.emplace_back(layer);
    auto renderer = LayerRenderer::create(m_layers.back(), m_camera.world_offset());
    if (!renderer) {
      m_layers.pop_back();
      throw std::runtime_error("Unsupported layer type: " + layer->name());
    }
    m_renderers.emplace_back(std::move(renderer));
    m_renderers.back()->set_visible(layer->visible());
    connect(m_layers.back().get(), &Layer::data_updated, m_renderers.back().get(),
            &LayerRenderer::data_update_required);
    connect(m_layers.back().get(), &Layer::data_updated, this, [this, layer = m_layers.back()] {
      if (layer->kind() != LayerKind::PointCloud) {
        update();
        return;
      }
      const auto* las_layer = dynamic_cast<const LASLayer*>(layer.get());
      if (las_layer == nullptr) {
        update();
        return;
      }
      const Extent3D local_extent = layer->extent() - m_camera.world_offset();
      if (local_extent.max_extent() <= 0) {
        restart_render();
        update();
        return;
      }
      restart_render();
      if (m_zoomed_layers.count(layer.get()) == 0 && local_extent.max_extent() > 0) {
        request_zoom_to_extent(local_extent);
        m_zoomed_layers.insert(layer.get());
      }
      update();
    });
    if (auto las_layer = std::dynamic_pointer_cast<LASLayer>(m_layers.back())) {
      connect(las_layer.get(), &LASLayer::point_size_changed, this,
              [this] { refresh_point_cloud_style(); });
      connect(las_layer.get(), &LASLayer::point_colors_changed, this,
              [this] { refresh_point_cloud_style(); });
      connect(las_layer.get(), &LASLayer::point_opacity_changed, this, [this] { update(); });
      connect(las_layer.get(), &LASLayer::point_stream_budget_changed, this,
              [this] { refresh_point_cloud_style(); });
    }
    connect(m_renderers.back().get(), &LayerRenderer::repaint_required, this,
            [this] { QMetaObject::invokeMethod(this, "update", Qt::QueuedConnection); });
    connect(m_layers.back().get(), &Layer::visibility_changed, this,
            [this, renderer = m_renderers.back().get()](bool visible) {
              renderer->set_visible(visible);
              restart_render();
              update();
            });
    if (layer->extent().max_extent() > 0) {
      request_zoom_to_extent(layer->extent() - m_camera.world_offset());
    }
    restart_render();
    update();
  }

  void set_layer_visible(Layer* layer, bool visible) {
    for (size_t i = 0; i < m_layers.size(); ++i) {
      if (m_layers[i].get() == layer) {
        m_renderers[i]->set_visible(visible);
        restart_render();
        update();
        return;
      }
    }
  }

  void remove_layer(Layer* layer);

  std::vector<std::shared_ptr<Layer>> layers() const { return m_layers; }

  const std::string& reference_crs_wkt() const { return m_projection; }

  void set_load_only_mode(bool load_only) { m_load_only = load_only; }

  void zoom_to_layer(const Layer* layer) {
    if (!layer || layer->extent().max_extent() <= 0) {
      return;
    }
    request_zoom_to_extent(layer->extent() - m_camera.world_offset());
    restart_render();
    update();
  }

  void restart_render();
  void refresh_point_cloud_style();

  using PointPickCallback = std::function<void(const std::optional<PointPickResult>&)>;
  void set_point_pick_callback(PointPickCallback callback) {
    m_point_pick_callback = std::move(callback);
  }

  void set_selected_point(const std::optional<PointPickResult>& pick);

 protected:
  QSize sizeHint() const override;
  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void showEvent(QShowEvent* event) override;
  void paintGL() override;
  void mousePressEvent(QMouseEvent* event) override;
  void mouseMoveEvent(QMouseEvent* event) override;
  void mouseReleaseEvent(QMouseEvent* event) override;
  void wheelEvent(QWheelEvent* event) override;
  void keyPressEvent(QKeyEvent* event) override;

  void begin_camera_interaction();
  void note_camera_motion();
  void schedule_camera_idle();

 private slots:
  void on_camera_idle();
  void on_stream_tick();

 private:
  void request_zoom_to_extent(const Extent3D& extent) {
    m_pending_zoom_extent = extent;
    m_needs_zoom = true;
    apply_pending_zoom();
  }

  void apply_pending_zoom() {
    if (!m_needs_zoom || !m_pending_zoom_extent.has_value()) {
      return;
    }
    const int w = width();
    const int h = height();
    if (w <= 0 || h <= 0) {
      return;
    }
    m_camera.set_screen_size(w, h);
    m_camera.zoom_to_fit(*m_pending_zoom_extent);
    m_needs_zoom = false;
    m_pending_zoom_extent.reset();
    restart_render();
  }

  void try_pick_point(const QPoint& pixel, bool focus_on_pick = false);
  void focus_on_selected_point();
  void draw_stats_overlay();

  IncrementalFramebuffer m_scene_fbo;
  PointCloudFramebuffer m_points_fbo;
  PointCloudCompositor m_point_compositor;
  bool m_incremental_draw = false;
  bool m_camera_interacting = false;
  int m_framebuffer_width = 0;
  int m_framebuffer_height = 0;
  QTimer* m_idle_timer = nullptr;
  QTimer* m_stream_timer = nullptr;

  QPoint m_last_mouse_pos;
  QPoint m_press_mouse_pos;
  bool m_left_button_pressed = false;

  PointPickCallback m_point_pick_callback;
  std::optional<PointPickResult> m_selected_point;

  Camera m_camera;

  std::vector<std::shared_ptr<Layer>> m_layers;
  std::vector<std::unique_ptr<LayerRenderer>> m_renderers;

  std::string m_projection;
  bool m_painting = false;
  bool m_load_only = false;
  bool m_needs_zoom = false;
  std::optional<Extent3D> m_pending_zoom_extent;
  std::unordered_set<Layer*> m_zoomed_layers;

  double m_frame_ms_ema = 16.0;
  double m_last_frame_ms = 0.0;
  double m_last_point_draw_ms = 0.0;
  size_t m_last_point_vertices = 0;
};
