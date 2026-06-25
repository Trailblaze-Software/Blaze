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
#include <QVector3D>
#include <QtConcurrent>
#include <chrono>
#include <functional>
#include <iostream>
#include <optional>
#include <unordered_set>
#include <vector>

#include "gui/camera.hpp"
#include "gui/gl_check.hpp"
#include "gui/layer.hpp"
#include "gui/layer_renderer.hpp"
#include "gui/point_cloud_framebuffer.hpp"
#include "gui/scene_framebuffer.hpp"
#include "io/crs.hpp"

QT_FORWARD_DECLARE_CLASS(QOpenGLShaderProgram)

class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions {
  Q_OBJECT

 public:
  enum class PickAction { None, PanToPoint, LookAtPoint };

  GLWidget(QWidget* parent = nullptr);
  ~GLWidget();

  void add_layer(std::shared_ptr<Layer> layer, bool auto_zoom = true) {
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
    if (auto* las = dynamic_cast<OctreeLASLayerRenderer*>(m_renderers.back().get())) {
      las->set_layer_slot(allocate_layer_slot());
    }
    connect(m_layers.back().get(), &Layer::data_updated, m_renderers.back().get(),
            &LayerRenderer::data_update_required);
    connect(m_layers.back().get(), &Layer::data_updated, this,
            [this, layer = m_layers.back(), auto_zoom] {
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
              if (auto_zoom && m_zoomed_layers.count(layer.get()) == 0 &&
                  local_extent.max_extent() > 0) {
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
      connect(las_layer.get(), &LASLayer::point_opacity_changed, this, [this] {
        restart_render();
        update();
      });
      connect(las_layer.get(), &LASLayer::point_stream_budget_changed, this,
              [this] { refresh_point_cloud_style(); });
      connect(las_layer.get(), &LASLayer::lod_settings_changed, this,
              [this] { refresh_point_cloud_style(); });
    }
    connect(m_renderers.back().get(), &LayerRenderer::repaint_required, this,
            [this] { QMetaObject::invokeMethod(this, "update", Qt::QueuedConnection); });
    connect(m_renderers.back().get(), &LayerRenderer::stream_view_reset, this,
            [this] { restart_render(); });
    connect(m_layers.back().get(), &Layer::visibility_changed, this,
            [this, renderer = m_renderers.back().get()](bool visible) {
              renderer->set_visible(visible);
              restart_render();
              update();
            });
    connect(m_layers.back().get(), &Layer::opacity_changed, this, [this] {
      restart_render();
      update();
    });
    connect(m_layers.back().get(), &Layer::vertical_offset_changed, this, [this] {
      restart_render();
      update();
    });
    if (auto_zoom && layer->extent().max_extent() > 0) {
      request_zoom_to_extent(layer->extent() - m_camera.world_offset());
    }
    restart_render();
    update();
  }

  enum class AnimType { None, Orbit, Wobble };
  void start_bench_orbit(double duration_seconds = 10.0);
  void start_animation(AnimType type);
  void stop_animation();
  void set_anim_type(int t);
  int anim_type() const { return static_cast<int>(m_anim_type); }
  void set_orbit_period(double secs) { m_orbit_period_secs = secs; }
  double orbit_period() const { return m_orbit_period_secs; }
  void set_wobble_period(double secs) { m_wobble_period_secs = secs; }
  double wobble_period() const { return m_wobble_period_secs; }
  void set_wobble_amplitude(double deg) { m_wobble_amplitude_deg = deg; }
  double wobble_amplitude() const { return m_wobble_amplitude_deg; }
  bool is_anim_active() const { return m_orbit_timer && m_orbit_timer->isActive(); }

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

  void zoom_to_all_layers() {
    Extent3D combined_extent;
    for (const auto& layer : m_layers) {
      combined_extent.grow(layer->extent() - m_camera.world_offset());
    }
    if (combined_extent.max_extent() > 0) {
      request_zoom_to_extent(combined_extent);
      restart_render();
      update();
    }
  }

  void restart_render();
  void refresh_point_cloud_style();
  void set_camera_light_angles(float azimuth_deg, float elevation_deg);
  float camera_light_azimuth_deg() const { return m_light_azimuth_deg; }
  float camera_light_elevation_deg() const { return m_light_elevation_deg; }
  void set_lighting_strength(float ambient_light, float diffuse_light);
  float ambient_light() const { return m_ambient_light; }
  float diffuse_light() const { return m_diffuse_light; }
  void set_point_ambient_light(float point_ambient_light);
  float point_ambient_light() const { return m_point_ambient_light; }

  using PointPickCallback = std::function<void(const std::optional<PointPickResult>&)>;
  void set_point_pick_callback(PointPickCallback callback) {
    m_point_pick_callback = std::move(callback);
  }

  void set_selected_point(const std::optional<PointPickResult>& pick, bool repaint = true);

 protected:
  QSize sizeHint() const override;
  QSize minimumSizeHint() const override;
  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void showEvent(QShowEvent* event) override;
  void paintGL() override;
  void mousePressEvent(QMouseEvent* event) override;
  void mouseMoveEvent(QMouseEvent* event) override;
  void mouseReleaseEvent(QMouseEvent* event) override;
  void leaveEvent(QEvent* event) override;
  void wheelEvent(QWheelEvent* event) override;
  void keyPressEvent(QKeyEvent* event) override;

  void begin_camera_interaction();
  void note_camera_motion();
  void schedule_camera_idle();

 private slots:
  void on_camera_idle();
  void on_stream_tick();
  void on_orbit_tick();

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

  void try_pick_point(const QPointF& pixel, PickAction action = PickAction::None);
  void update_hover_at(const QPointF& pixel, int max_radius, bool repaint = true);
  void do_pick_at(const QPointF& pixel, PickAction action, bool repaint = true);
  std::optional<PointPickResult> fb_pick_point(const QPointF& pixel, int max_radius);
  bool fbo_pick_ready() const;
  float point_layer_alpha() const;
  bool pick_interaction_enabled() const;
  void apply_hover_result(const std::optional<PointPickResult>& result, bool repaint = true);
  std::optional<QPointF> project_pick_to_screen(const PointPickResult& pick) const;
  int allocate_layer_slot();
  void release_layer_slot(int slot);
  void pan_to_selected_point();
  void look_at_selected_point();
  void clear_picks_for_layer(const std::string& layer_name);
  void draw_stats_overlay();
  void update_scene_bounds();

  SceneFramebuffer m_scene_fbo;
  PointCloudFramebuffer m_points_fbo;
  PointCloudCompositor m_point_compositor;
  bool m_incremental_draw = false;
  bool m_restarted_during_paint = false;
  bool m_camera_interacting = false;
  QTimer* m_idle_timer = nullptr;
  QTimer* m_stream_timer = nullptr;
  QTimer* m_orbit_timer = nullptr;
  std::chrono::steady_clock::time_point m_last_orbit_tick;
  double m_anim_phase = 0.0;
  AnimType m_anim_type = AnimType::None;
  AnimType m_last_anim_type = AnimType::Orbit;  // remembered for Space toggle
  double m_orbit_period_secs = 15.0;
  double m_wobble_period_secs = 4.0;
  double m_wobble_amplitude_deg = 0.5;
  QPointF m_last_mouse_pos;
  QPointF m_press_mouse_pos;
  bool m_left_button_pressed = false;
  std::optional<QPointF> m_pending_pick_pixel;
  PickAction m_pending_pick_action = PickAction::None;

  PointPickCallback m_point_pick_callback;
  std::optional<PointPickResult> m_selected_point;
  std::optional<PointPickResult> m_hovered_point;
  bool m_fbo_was_pick_ready = false;
  std::optional<QPointF> m_last_hover_probe_pos;
  bool m_hover_probe_needed = false;
  int m_next_layer_slot = 1;
  std::vector<int> m_free_layer_slots;

  Camera m_camera;

  std::vector<std::shared_ptr<Layer>> m_layers;
  std::vector<std::unique_ptr<LayerRenderer>> m_renderers;

  std::string m_projection;
  bool m_painting = false;
  bool m_load_only = false;
  bool m_needs_zoom = false;
  std::optional<Extent3D> m_pending_zoom_extent;
  std::unordered_set<Layer*> m_zoomed_layers;

  std::optional<std::chrono::steady_clock::time_point> m_prev_paint_time;
  double m_present_frame_ms_ema = 16.0;
  double m_last_present_frame_ms = 0.0;
  double m_last_paint_ms = 0.0;
  double m_last_point_draw_ms = 0.0;
  double m_last_point_gpu_ms = 0.0;
  size_t m_last_point_vertices = 0;
  float m_light_azimuth_deg = -50.0f;
  float m_light_elevation_deg = 35.0f;
  float m_ambient_light = 0.30f;
  float m_diffuse_light = 1.00f;
  float m_point_ambient_light = 0.55f;
};
