

# File gl\_widget.cpp

[**File List**](files.md) **>** [**gui**](dir_99d0482cf009f9d97a0877749b817f19.md) **>** [**gl\_widget.cpp**](gl__widget_8cpp.md)

[Go to the documentation of this file](gl__widget_8cpp.md)


```C++

#include "gl_widget.hpp"

#include <math.h>

#include <QCoreApplication>
#include <QMatrix4x4>
#include <QMouseEvent>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QPainter>
#include <QVector3D>
#include <QVector4D>
#include <QtWidgets>
#include <algorithm>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <limits>
#include <vector>

#include "gui/gl_check.hpp"

namespace {

double point_separation_m(const PointPickResult& a, const PointPickResult& b) {
  const double dx = a.world_x - b.world_x;
  const double dy = a.world_y - b.world_y;
  const double dz = a.world_z - b.world_z;
  return std::sqrt(dx * dx + dy * dy + dz * dz);
}

float point_diameter_px(const Camera& camera, float viewport_height, qreal dpr,
                        const PointPickResult& pick,
                        const std::vector<std::shared_ptr<Layer>>& layers) {
  const QVector3D pt(static_cast<float>(pick.world_x), static_cast<float>(pick.world_y),
                     static_cast<float>(pick.world_z));
  const float fb_viewport_h = viewport_height * static_cast<float>(dpr);
  const float proj_scale =
      fb_viewport_h / static_cast<float>(2.0 * std::tan(camera.fov_rad() * 0.5));
  float diameter_px = 1.0f / static_cast<float>(dpr);
  for (const auto& layer : layers) {
    if (layer->name() != pick.layer_name) {
      continue;
    }
    if (auto las_layer = std::dynamic_pointer_cast<LASLayer>(layer)) {
      const QVector4D eye = camera.view_matrix() * QVector4D(pt, 1.0f);
      const float eye_w = -eye.z();
      if (eye_w > 0) {
        const float diameter_device =
            std::clamp(2.0f * las_layer->point_radius_m() * proj_scale / eye_w, 1.0f, 4096.0f);
        diameter_px = diameter_device / static_cast<float>(dpr);
      }
    }
    break;
  }
  return diameter_px;
}

QPointF snap_device_center(const QPointF& pt, qreal dpr) {
  return QPointF((std::floor(pt.x() * dpr) + 0.5) / dpr, (std::floor(pt.y() * dpr) + 0.5) / dpr);
}

QVector3D normalize_or_default(const QVector3D& value, const QVector3D& fallback) {
  if (value.lengthSquared() < 1e-8f) {
    return fallback;
  }
  return value.normalized();
}

float clamp_float(float value, float min_v, float max_v) {
  return std::max(min_v, std::min(max_v, value));
}

QVector3D light_lub_from_polar(float azimuth_deg, float elevation_deg) {
  const float azimuth_rad = static_cast<float>(azimuth_deg * M_PI / 180.0);
  const float elevation_rad = static_cast<float>(elevation_deg * M_PI / 180.0);
  const float horizontal = std::cos(elevation_rad);
  const float left = -std::sin(azimuth_rad) * horizontal;
  const float up = std::sin(elevation_rad);
  const float behind = std::cos(azimuth_rad) * horizontal;
  return normalize_or_default(QVector3D(left, up, behind), QVector3D(0.35f, 0.45f, 0.82f));
}

void draw_device_hline(QPainter& painter, qreal x0, qreal x1, qreal y, qreal dpr,
                       const QColor& color) {
  const qreal px = 1.0 / dpr;
  const qreal cy = (std::floor(y * dpr) + 0.5) / dpr;
  const qreal left = std::floor(std::min(x0, x1) * dpr) / dpr;
  const qreal right = std::ceil(std::max(x0, x1) * dpr) / dpr;
  painter.fillRect(QRectF(left, cy - px * 0.5, right - left, px), color);
}

void draw_device_vline(QPainter& painter, qreal x, qreal y0, qreal y1, qreal dpr,
                       const QColor& color) {
  const qreal px = 1.0 / dpr;
  const qreal cx = (std::floor(x * dpr) + 0.5) / dpr;
  const qreal top = std::floor(std::min(y0, y1) * dpr) / dpr;
  const qreal bottom = std::ceil(std::max(y0, y1) * dpr) / dpr;
  painter.fillRect(QRectF(cx - px * 0.5, top, px, bottom - top), color);
}

void draw_point_crosshair(QPainter& painter, const std::optional<QPointF>& screen_pt,
                          const Camera& camera, float viewport_height, const PointPickResult& pick,
                          const std::vector<std::shared_ptr<Layer>>& layers, qreal dpr,
                          const QColor& cross_color,
                          std::optional<double> distance_m = std::nullopt) {
  if (!screen_pt.has_value()) {
    return;
  }
  const QPointF& pt = *screen_pt;

  const QPointF center = snap_device_center(pt, dpr);
  const float point_px = point_diameter_px(camera, viewport_height, dpr, pick, layers);
  const float gap_px = point_px * 0.5f + 1.0f;
  const float arm_len = (12.0f + point_px) * 0.5f;
  const float arm_px = gap_px + arm_len;

  painter.save();
  painter.setRenderHint(QPainter::Antialiasing, false);
  painter.setPen(Qt::NoPen);

  draw_device_hline(painter, center.x() + gap_px, center.x() + arm_px, center.y(), dpr,
                    cross_color);
  draw_device_hline(painter, center.x() - gap_px, center.x() - arm_px, center.y(), dpr,
                    cross_color);
  draw_device_vline(painter, center.x(), center.y() + gap_px, center.y() + arm_px, dpr,
                    cross_color);
  draw_device_vline(painter, center.x(), center.y() - gap_px, center.y() - arm_px, dpr,
                    cross_color);
  painter.restore();

  if (distance_m.has_value()) {
    painter.setPen(QColor(100, 200, 255));
    painter.drawText(center + QPointF(arm_px + 4, -4), QString("%1 m").arg(*distance_m, 0, 'f', 2));
  }
}

}  // namespace

GLWidget::GLWidget(QWidget* parent) : QOpenGLWidget(parent), m_camera(width(), height()) {
  setMouseTracking(true);

  m_idle_timer = new QTimer(this);
  m_idle_timer->setSingleShot(true);
  m_idle_timer->setInterval(50);
  connect(m_idle_timer, &QTimer::timeout, this, &GLWidget::on_camera_idle);

  m_stream_timer = new QTimer(this);
  m_stream_timer->setInterval(16);
  connect(m_stream_timer, &QTimer::timeout, this, &GLWidget::on_stream_tick);

  m_orbit_timer = new QTimer(this);
  m_orbit_timer->setInterval(16);
  connect(m_orbit_timer, &QTimer::timeout, this, &GLWidget::on_orbit_tick);
}

GLWidget::~GLWidget() {
  makeCurrent();
  m_renderers.clear();
  doneCurrent();
}

void GLWidget::remove_layer(Layer* layer) {
  const auto it =
      std::find_if(m_layers.begin(), m_layers.end(),
                   [layer](const std::shared_ptr<Layer>& ptr) { return ptr.get() == layer; });
  if (it == m_layers.end()) {
    return;
  }
  const size_t index = static_cast<size_t>(std::distance(m_layers.begin(), it));
  Layer* layer_ptr = it->get();
  LayerRenderer* renderer = m_renderers[index].get();

  disconnect(layer_ptr, nullptr, renderer, nullptr);
  disconnect(renderer, nullptr, this, nullptr);
  disconnect(layer_ptr, nullptr, this, nullptr);

  m_zoomed_layers.erase(layer_ptr);
  clear_picks_for_layer(layer_ptr->name());
  if (auto* las = dynamic_cast<OctreeLASLayerRenderer*>(renderer)) {
    const int slot = las->layer_slot();
    las->set_layer_slot(0);
    if (slot > 0) {
      release_layer_slot(slot);
    }
  }

  makeCurrent();
  m_renderers.erase(m_renderers.begin() + static_cast<std::ptrdiff_t>(index));
  m_layers.erase(it);
  restart_render();
  update();
}

QSize GLWidget::sizeHint() const { return minimumSizeHint(); }

QSize GLWidget::minimumSizeHint() const { return QSize(320, 240); }

void GLWidget::initializeGL() {
  initializeOpenGLFunctions();

  setFocusPolicy(Qt::StrongFocus);

  QOpenGLFunctions* f = QOpenGLContext::currentContext()->functions();

  std::cout << "Detected OpenGL version: " << f->glGetString(GL_VERSION) << std::endl;
  std::cout << "Detected OpenGL renderer: " << f->glGetString(GL_RENDERER) << std::endl;

  Assert(f->glGetError() == GL_NO_ERROR, "OpenGL error");
  Assert(QOpenGLContext::currentContext()->isValid(), "OpenGL context is invalid");

  CHECK_GL(f->glEnable(GL_PROGRAM_POINT_SIZE));
  CHECK_GL(f->glEnable(GL_DEPTH_TEST));
  QPair<int, int> version = QOpenGLContext::currentContext()->format().version();
  if (version.first < 3 || (version.first == 3 && version.second < 3)) {
    CHECK_GL(f->glEnable(GL_POINT_SPRITE));
  }
  CHECK_GL(f->glEnable(GL_BLEND));
  CHECK_GL(f->glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
  CHECK_GL(f->glClearColor(0.2f, 0.2f, 0.2f, 1.0f));

  QSurfaceFormat format = QOpenGLContext::currentContext()->format();

  if (format.profile() == QSurfaceFormat::CompatibilityProfile) {
    QOpenGLFunctions* opengl_functions = QOpenGLContext::currentContext()->functions();
    GLint point_sprite_coord_origin = 0;
    CHECK_GL(
        opengl_functions->glGetIntegerv(GL_POINT_SPRITE_COORD_ORIGIN, &point_sprite_coord_origin));
    AssertEQ(point_sprite_coord_origin, GL_UPPER_LEFT);
  }

  GLenum err;
  while ((err = glGetError()) != GL_NO_ERROR) {
    std::cout << "OpenGL Initialization Error: " << err << std::endl;
  }
}

void GLWidget::showEvent(QShowEvent* event) {
  QOpenGLWidget::showEvent(event);
  apply_pending_zoom();
  update();
}

void GLWidget::resizeGL(int w, int h) {
  Q_UNUSED(w);
  Q_UNUSED(h);
  // resizeGL receives device pixels; camera and input use logical widget pixels.
  const int screen_w = width();
  const int screen_h = height();
  if (screen_w > 0 && screen_h > 0) {
    m_camera.set_screen_size(screen_w, screen_h);
    apply_pending_zoom();
    restart_render();
  }
}

void GLWidget::restart_render() {
  m_incremental_draw = false;
  if (m_painting) {
    m_restarted_during_paint = true;
  }
}

void GLWidget::update_scene_bounds() {
  Extent3D bounds;
  for (const auto& layer : m_layers) {
    if (!layer->visible() || layer->extent().max_extent() <= 0) {
      continue;
    }
    bounds.grow(layer->extent() - m_camera.world_offset());
  }
  if (bounds.max_extent() <= 0) {
    m_camera.set_scene_bounds(QVector3D(), 0.0f);
    return;
  }
  const QVector3D center(static_cast<float>(0.5 * (bounds.minx + bounds.maxx)),
                         static_cast<float>(0.5 * (bounds.miny + bounds.maxy)),
                         static_cast<float>(0.5 * (bounds.minz + bounds.maxz)));
  const double dx = bounds.maxx - bounds.minx;
  const double dy = bounds.maxy - bounds.miny;
  const double dz = bounds.maxz - bounds.minz;
  const float radius = static_cast<float>(0.5 * std::sqrt(dx * dx + dy * dy + dz * dz));
  m_camera.set_scene_bounds(center, radius);
}

void GLWidget::paintGL() {
  if (m_painting) {
    return;
  }
  m_painting = true;

  const auto paint_start = std::chrono::steady_clock::now();
  if (m_prev_paint_time) {
    m_last_present_frame_ms =
        std::chrono::duration<double, std::milli>(paint_start - *m_prev_paint_time).count();
    m_present_frame_ms_ema = m_present_frame_ms_ema * 0.88 + m_last_present_frame_ms * 0.12;
  }
  m_prev_paint_time = paint_start;

  QOpenGLFunctions* f = QOpenGLContext::currentContext()->functions();

  const int screen_w = width();
  const int screen_h = height();
  const qreal dpr = devicePixelRatioF();
  const int fb_w = std::max(1, static_cast<int>(std::lround(screen_w * dpr)));
  const int fb_h = std::max(1, static_cast<int>(std::lround(screen_h * dpr)));
  if (screen_w > 0 && screen_h > 0) {
    m_camera.set_screen_size(screen_w, screen_h);
    update_scene_bounds();
    apply_pending_zoom();
    m_scene_fbo.ensure_size(fb_w, fb_h);
    m_points_fbo.ensure_size(fb_w, fb_h);
  }

  if (screen_w <= 0 || screen_h <= 0) {
    m_painting = false;
    return;
  }

  const bool incremental_points = m_incremental_draw;
  RenderContext ctx;
  ctx.incremental_points = incremental_points;
  ctx.viewport_height = static_cast<float>(fb_h);
  const QVector3D camera_forward = normalize_or_default(m_camera.direction(), QVector3D(0, 0, -1));
  const QVector3D camera_up = normalize_or_default(m_camera.up(), QVector3D(0, 0, 1));
  QVector3D camera_right = QVector3D::crossProduct(camera_forward, camera_up);
  camera_right = normalize_or_default(camera_right, QVector3D(1, 0, 0));
  const QVector3D ortho_up = normalize_or_default(
      QVector3D::crossProduct(camera_right, camera_forward), QVector3D(0, 0, 1));
  const QVector3D light_lub = light_lub_from_polar(m_light_azimuth_deg, m_light_elevation_deg);
  const QVector3D light_world =
      -light_lub.x() * camera_right + light_lub.y() * ortho_up - light_lub.z() * camera_forward;
  const QVector3D light_eye(-light_lub.x(), light_lub.y(), light_lub.z());
  ctx.light_direction_world = normalize_or_default(light_world, QVector3D(0, 0, 1));
  ctx.light_direction_eye = normalize_or_default(light_eye, QVector3D(0, 0, 1));
  ctx.ambient_light = m_ambient_light;
  ctx.diffuse_light = m_diffuse_light;
  ctx.point_ambient_light = m_point_ambient_light;

  CHECK_GL(f->glClearColor(0.2f, 0.2f, 0.2f, 1.0f));

  if (!incremental_points) {
    if (m_scene_fbo.valid()) {
      m_scene_fbo.bind();
      CHECK_GL_AFTER();
      CHECK_GL(f->glViewport(0, 0, fb_w, fb_h));
      CHECK_GL(f->glClearColor(0.0f, 0.0f, 0.0f, 0.0f));
      CHECK_GL(f->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    } else {
      CHECK_GL(f->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    }
    for (size_t i = 0; i < m_renderers.size(); ++i) {
      if (m_layers[i]->kind() == LayerKind::PointCloud) {
        continue;
      }
      if (m_renderers[i] && !m_load_only) {
        m_renderers[i]->render(m_camera, ctx);
      }
    }

    if (m_points_fbo.valid()) {
      m_points_fbo.bind();
      CHECK_GL_AFTER();
      CHECK_GL(f->glViewport(0, 0, fb_w, fb_h));
      m_points_fbo.clear();
    }
  } else if (m_points_fbo.valid()) {
    m_points_fbo.bind();
    CHECK_GL_AFTER();
    CHECK_GL(f->glViewport(0, 0, fb_w, fb_h));
    CHECK_GL(f->glDepthFunc(GL_LEQUAL));
  }

  for (size_t i = 0; i < m_renderers.size(); ++i) {
    if (m_layers[i]->kind() != LayerKind::PointCloud) {
      continue;
    }
    if (m_renderers[i]) {
      m_renderers[i]->render(m_camera, ctx);
    }
  }

  const GLuint widget_fbo = defaultFramebufferObject();
  CHECK_GL(f->glBindFramebuffer(GL_FRAMEBUFFER, widget_fbo));
  CHECK_GL(f->glViewport(0, 0, fb_w, fb_h));
  CHECK_GL(f->glClearColor(0.2f, 0.2f, 0.2f, 1.0f));
  CHECK_GL(f->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

  if (m_scene_fbo.valid()) {
    if (auto* gl = QOpenGLContext::currentContext()->extraFunctions()) {
      m_scene_fbo.composite_to_widget_fbo(gl, widget_fbo, fb_w, fb_h);
      m_scene_fbo.blit_depth_to_widget_fbo(widget_fbo, fb_w, fb_h);
      CHECK_GL_AFTER();
    }
  }

  const float point_layer_alpha = this->point_layer_alpha();

  if (m_points_fbo.valid() && point_layer_alpha > 0.0f) {
    if (auto* gl = QOpenGLContext::currentContext()->extraFunctions()) {
      m_point_compositor.composite(gl, widget_fbo, m_points_fbo.color_texture(),
                                   m_points_fbo.depth_texture(), 1.0f, fb_w, fb_h);
      CHECK_GL_AFTER();
    }
  }

  const bool pick_ready = fbo_pick_ready() && point_layer_alpha > 0.0f;
  if (!pick_ready && m_fbo_was_pick_ready) {
    apply_hover_result(std::nullopt, /*repaint=*/false);
    m_last_hover_probe_pos.reset();
  }
  if (pick_ready && !m_fbo_was_pick_ready) {
    m_hover_probe_needed = true;
  }
  m_fbo_was_pick_ready = pick_ready;
  if (m_pending_pick_pixel && pick_ready) {
    do_pick_at(*m_pending_pick_pixel, m_pending_pick_action, /*repaint=*/false);
    m_pending_pick_pixel.reset();
    m_pending_pick_action = PickAction::None;
  }
  // Probe hover after compositing so pick reads match the displayed frame.
  if (pick_ready && !m_left_button_pressed && !m_camera_interacting) {
    const bool cursor_moved =
        !m_last_hover_probe_pos.has_value() || *m_last_hover_probe_pos != m_last_mouse_pos;
    if (cursor_moved || m_hover_probe_needed) {
      update_hover_at(m_last_mouse_pos, /*max_radius=*/5, /*repaint=*/false);
      m_last_hover_probe_pos = m_last_mouse_pos;
      m_hover_probe_needed = false;
    }
  }

  bool point_streaming = false;
  bool layer_loading = false;
  for (size_t i = 0; i < m_renderers.size(); ++i) {
    if (m_layers[i]->kind() != LayerKind::PointCloud) {
      continue;
    }
    if (auto* las_renderer = dynamic_cast<OctreeLASLayerRenderer*>(m_renderers[i].get())) {
      if (las_renderer->has_stream_backlog()) {
        point_streaming = true;
      }
    }
    if (auto las_layer = std::dynamic_pointer_cast<LASLayer>(m_layers[i])) {
      if (!las_layer->las_data().load_complete()) {
        layer_loading = true;
      }
    }
  }
  if (point_streaming || layer_loading) {
    if (!m_stream_timer->isActive()) {
      m_stream_timer->start();
    }
  } else if (!m_camera_interacting) {
    m_stream_timer->stop();
  }

  // Inspired by Displaz: next frame accumulates unless restart_render() is called.
  if (!m_camera_interacting && !m_restarted_during_paint) {
    m_incremental_draw = true;
  }
  m_restarted_during_paint = false;

  m_last_point_draw_ms = 0.0;
  m_last_point_gpu_ms = 0.0;
  m_last_point_vertices = 0;
  for (size_t i = 0; i < m_renderers.size(); ++i) {
    if (m_layers[i]->kind() != LayerKind::PointCloud) {
      continue;
    }
    if (auto* las_renderer = dynamic_cast<OctreeLASLayerRenderer*>(m_renderers[i].get())) {
      m_last_point_draw_ms += las_renderer->last_point_draw_ms();
      m_last_point_gpu_ms += las_renderer->last_point_gpu_ms();
      m_last_point_vertices += las_renderer->last_point_vertices_drawn();
    }
  }

  m_last_paint_ms =
      std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - paint_start)
          .count();

  // Periodic frame benchmark (every 60 frames).
  {
    static int bench_frame = 0;
    if (++bench_frame % 60 == 0) {
      const double fps = m_present_frame_ms_ema > 0.0 ? 1000.0 / m_present_frame_ms_ema : 0.0;
      std::cerr << "[blaze bench frame] fps=" << fps << "  present_ms=" << m_last_present_frame_ms
                << "  paint_ms=" << m_last_paint_ms << "  gpu_ms=" << m_last_point_gpu_ms
                << "  pts_ms=" << m_last_point_draw_ms << "  verts=" << m_last_point_vertices
                << "  cam=(" << m_camera.position().x() << "," << m_camera.position().y() << ","
                << m_camera.position().z() << ")" << std::endl;
    }
  }

  // Poll errors from our GL rendering before QPainter — QPainter does not
  // preserve OpenGL state and may itself enqueue GL_INVALID_OPERATION on core
  // profiles, which would otherwise drown out real issues.
  GLenum err;
  while ((err = glGetError()) != GL_NO_ERROR) {
    std::cerr << "OpenGL error: " << gl_error_name(err) << " (0x" << std::hex << err << std::dec
              << ")" << std::endl;
  }

  draw_stats_overlay();

  // QPainter does not preserve framebuffer bindings; restore for next frame.
  CHECK_GL(f->glBindFramebuffer(GL_FRAMEBUFFER, defaultFramebufferObject()));

  m_painting = false;
}

bool GLWidget::fbo_pick_ready() const {
  // Pick/hover reads the accumulated points FBO. That buffer is cleared only
  // on restart_render() (camera interaction). Incremental streaming appends
  // more points each frame without invalidating existing pick IDs, so we must
  // not gate on m_incremental_draw — paintGL sets that true after every idle
  // frame, which would block hover until the camera moves again.
  if (m_camera_interacting) {
    return false;
  }
  bool any_point_layer = false;
  for (size_t i = 0; i < m_renderers.size(); ++i) {
    if (m_layers[i]->kind() != LayerKind::PointCloud || !m_layers[i]->visible()) {
      continue;
    }
    const auto* las = dynamic_cast<const OctreeLASLayerRenderer*>(m_renderers[i].get());
    if (!las) {
      continue;
    }
    any_point_layer = true;
    if (!las->can_fbo_pick()) {
      return false;
    }
  }
  return any_point_layer;
}

float GLWidget::point_layer_alpha() const {
  float alpha = 0.0f;
  for (size_t i = 0; i < m_layers.size(); ++i) {
    if (m_layers[i]->kind() != LayerKind::PointCloud || !m_layers[i]->visible()) {
      continue;
    }
    if (auto las_layer = std::dynamic_pointer_cast<LASLayer>(m_layers[i])) {
      alpha = std::max(alpha, las_layer->point_alpha());
    }
  }
  return alpha;
}

bool GLWidget::pick_interaction_enabled() const {
  return fbo_pick_ready() && point_layer_alpha() > 0.0f;
}

void GLWidget::draw_stats_overlay() {
  QPainter painter(this);
  painter.setRenderHint(QPainter::TextAntialiasing);

  const double fps = m_present_frame_ms_ema > 0.0 ? 1000.0 / m_present_frame_ms_ema : 0.0;
  const QString text = tr("%1 fps  %2 ms  %3 ms gpu  %4k verts")
                           .arg(fps, 0, 'f', 0)
                           .arg(m_last_present_frame_ms, 0, 'f', 1)
                           .arg(m_last_point_gpu_ms, 0, 'f', 1)
                           .arg(static_cast<double>(m_last_point_vertices) / 1000.0, 0, 'f', 1);

  const QFontMetrics fm(painter.font());
  const int pad_x = 8;
  const int pad_y = 4;
  const int text_w = fm.horizontalAdvance(text);
  const int text_h = fm.height();
  const int box_w = text_w + pad_x * 2;
  const int box_h = text_h + pad_y * 2;
  const int margin = 10;
  const QRect box_rect(width() - box_w - margin, height() - box_h - margin, box_w, box_h);

  painter.setPen(Qt::NoPen);
  painter.setBrush(QColor(0, 0, 0, 150));
  painter.drawRoundedRect(box_rect, 4, 4);

  painter.setPen(QColor(230, 230, 230));
  painter.drawText(box_rect.adjusted(pad_x, pad_y, -pad_x, -pad_y),
                   Qt::AlignLeft | Qt::AlignVCenter, text);

  const auto layer_exists = [&](const std::string& name) {
    return std::any_of(m_layers.begin(), m_layers.end(),
                       [&](const std::shared_ptr<Layer>& layer) { return layer->name() == name; });
  };

  // Crosshairs anchored to the picked point's screen position (not the cursor).
  const float logical_viewport_h = static_cast<float>(height());
  const qreal dpr = devicePixelRatioF();
  if (m_selected_point.has_value() && layer_exists(m_selected_point->layer_name)) {
    if (auto screen_pt = project_pick_to_screen(*m_selected_point)) {
      draw_point_crosshair(painter, screen_pt, m_camera, logical_viewport_h, *m_selected_point,
                           m_layers, dpr, QColor(255, 235, 40));
    }
  }
  if (m_hovered_point.has_value() && m_hovered_point != m_selected_point &&
      layer_exists(m_hovered_point->layer_name)) {
    if (auto screen_pt = project_pick_to_screen(*m_hovered_point)) {
      std::optional<double> sep;
      if (m_selected_point.has_value()) {
        sep = point_separation_m(*m_selected_point, *m_hovered_point);
      }
      draw_point_crosshair(painter, screen_pt, m_camera, logical_viewport_h, *m_hovered_point,
                           m_layers, dpr, QColor(80, 220, 255), sep);
    }
  }
}

void GLWidget::begin_camera_interaction() {
  if (!m_camera_interacting) {
    m_stream_timer->stop();
    restart_render();
  }
  m_camera_interacting = true;
  m_hover_probe_needed = false;
  m_hovered_point.reset();
  m_last_hover_probe_pos.reset();
}

void GLWidget::note_camera_motion() {
  begin_camera_interaction();
  schedule_camera_idle();
}

void GLWidget::schedule_camera_idle() { m_idle_timer->start(); }

void GLWidget::on_camera_idle() {
  m_camera_interacting = false;
  m_hover_probe_needed = true;
  if (!m_stream_timer->isActive()) {
    m_stream_timer->start();
  }
  update();
}

void GLWidget::on_stream_tick() {
  if (!m_camera_interacting) {
    update();
  }
}

void GLWidget::refresh_point_cloud_style() {
  for (size_t i = 0; i < m_renderers.size(); ++i) {
    if (m_layers[i]->kind() != LayerKind::PointCloud) {
      continue;
    }
    if (auto* las_renderer = dynamic_cast<OctreeLASLayerRenderer*>(m_renderers[i].get())) {
      las_renderer->refresh_after_style_change();
    }
  }
  restart_render();
  if (!m_stream_timer->isActive()) {
    m_stream_timer->start();
  }
  update();
}

void GLWidget::set_camera_light_angles(float azimuth_deg, float elevation_deg) {
  const float clamped_azimuth = clamp_float(azimuth_deg, -180.0f, 180.0f);
  const float clamped_elevation = clamp_float(elevation_deg, -89.0f, 89.0f);
  if (std::abs(clamped_azimuth - m_light_azimuth_deg) < 1e-6f &&
      std::abs(clamped_elevation - m_light_elevation_deg) < 1e-6f) {
    return;
  }
  m_light_azimuth_deg = clamped_azimuth;
  m_light_elevation_deg = clamped_elevation;
  restart_render();
  update();
}

void GLWidget::set_lighting_strength(float ambient_light, float diffuse_light) {
  const float clamped_ambient = clamp_float(ambient_light, 0.0f, 1.0f);
  const float clamped_diffuse = clamp_float(diffuse_light, 0.0f, 2.0f);
  if (std::abs(clamped_ambient - m_ambient_light) < 1e-6f &&
      std::abs(clamped_diffuse - m_diffuse_light) < 1e-6f) {
    return;
  }
  m_ambient_light = clamped_ambient;
  m_diffuse_light = clamped_diffuse;
  restart_render();
  update();
}

void GLWidget::set_point_ambient_light(float point_ambient_light) {
  const float clamped_point_ambient = clamp_float(point_ambient_light, 0.0f, 1.0f);
  if (std::abs(clamped_point_ambient - m_point_ambient_light) < 1e-6f) {
    return;
  }
  m_point_ambient_light = clamped_point_ambient;
  restart_render();
  update();
}

void GLWidget::pan_to_selected_point() {
  if (!m_selected_point.has_value()) {
    return;
  }
  m_camera.pan_to_target(QVector3D(static_cast<float>(m_selected_point->world_x),
                                   static_cast<float>(m_selected_point->world_y),
                                   static_cast<float>(m_selected_point->world_z)));
  restart_render();
  update();
}

void GLWidget::look_at_selected_point() {
  if (!m_selected_point.has_value()) {
    return;
  }
  m_camera.look_at_target(QVector3D(static_cast<float>(m_selected_point->world_x),
                                    static_cast<float>(m_selected_point->world_y),
                                    static_cast<float>(m_selected_point->world_z)));
  restart_render();
  update();
}

void GLWidget::clear_picks_for_layer(const std::string& layer_name) {
  if (m_selected_point.has_value() && m_selected_point->layer_name == layer_name) {
    set_selected_point(std::nullopt, false);
    if (m_point_pick_callback) {
      m_point_pick_callback(std::nullopt);
    }
  }
  if (m_hovered_point.has_value() && m_hovered_point->layer_name == layer_name) {
    m_hovered_point.reset();
  }
}

std::optional<QPointF> GLWidget::project_pick_to_screen(const PointPickResult& pick) const {
  return m_camera.project_world_to_screen(QVector3D(static_cast<float>(pick.world_x),
                                                    static_cast<float>(pick.world_y),
                                                    static_cast<float>(pick.world_z)));
}

int GLWidget::allocate_layer_slot() {
  if (!m_free_layer_slots.empty()) {
    const int slot = m_free_layer_slots.back();
    m_free_layer_slots.pop_back();
    return slot;
  }
  if (m_next_layer_slot > 255) {
    std::cerr << "Warning: Maximum of 255 point cloud layers with picking support reached. "
                 "Additional layers will not support point picking.\n";
    return 0;
  }
  return m_next_layer_slot++;
}

void GLWidget::release_layer_slot(int slot) {
  if (slot > 0) {
    m_free_layer_slots.push_back(slot);
  }
}

void GLWidget::set_selected_point(const std::optional<PointPickResult>& pick, bool repaint) {
  m_selected_point = pick;
  if (repaint) {
    update();
  }
}

void GLWidget::try_pick_point(const QPointF& pixel, PickAction action) {
  m_pending_pick_pixel = pixel;
  m_pending_pick_action = action;
  update();
}

void GLWidget::do_pick_at(const QPointF& pixel, PickAction action, bool repaint) {
  if (!pick_interaction_enabled()) {
    return;
  }
  auto best = fb_pick_point(pixel, /*max_radius=*/5);

  if (best) {
    set_selected_point(*best, repaint);
    if (m_point_pick_callback) {
      m_point_pick_callback(*best);
    }
    if (action == PickAction::PanToPoint) {
      pan_to_selected_point();
    } else if (action == PickAction::LookAtPoint) {
      look_at_selected_point();
    }
  } else {
    set_selected_point(std::nullopt, repaint);
    if (m_point_pick_callback) {
      m_point_pick_callback(std::nullopt);
    }
  }
}

void GLWidget::apply_hover_result(const std::optional<PointPickResult>& result, bool repaint) {
  if (result == m_hovered_point) {
    return;
  }
  m_hovered_point = result;
  if (repaint) {
    update();
  }
}

void GLWidget::update_hover_at(const QPointF& pixel, int max_radius, bool repaint) {
  if (!pick_interaction_enabled()) {
    if (m_hovered_point.has_value()) {
      apply_hover_result(std::nullopt, repaint);
    }
    return;
  }
  apply_hover_result(fb_pick_point(pixel, max_radius), repaint);
}

std::optional<PointPickResult> GLWidget::fb_pick_point(const QPointF& pixel, int max_radius) {
  if (!m_points_fbo.valid()) {
    return std::nullopt;
  }

  makeCurrent();
  auto* ef = QOpenGLContext::currentContext()->extraFunctions();
  if (!ef) {
    return std::nullopt;
  }

  GLint prev_read_fbo = 0;
  GLint prev_read_buffer = 0;
  CHECK_GL(ef->glGetIntegerv(GL_READ_FRAMEBUFFER_BINDING, &prev_read_fbo));
  CHECK_GL(ef->glGetIntegerv(GL_READ_BUFFER, &prev_read_buffer));

  const qreal dpr = devicePixelRatioF();
  const int fb_w = static_cast<int>(std::lround(width() * dpr));
  const int fb_h = static_cast<int>(std::lround(height() * dpr));
  const int cx = static_cast<int>(std::floor(pixel.x() * dpr + 0.5));
  const int cy = fb_h - static_cast<int>(std::floor(pixel.y() * dpr + 0.5)) - 1;
  const int pick_radius = std::max(1, static_cast<int>(std::lround(max_radius * dpr)));
  const GLuint widget_fbo = defaultFramebufferObject();

  const int x0 = std::max(0, cx - pick_radius);
  const int y0 = std::max(0, cy - pick_radius);
  const int x1 = std::min(fb_w - 1, cx + pick_radius);
  const int y1 = std::min(fb_h - 1, cy + pick_radius);
  const int region_w = x1 - x0 + 1;
  const int region_h = y1 - y0 + 1;
  const size_t pixel_count = static_cast<size_t>(region_w) * static_cast<size_t>(region_h);

  std::vector<uint32_t> pick_pixels(pixel_count * 2);
  std::vector<float> point_depths(pixel_count);
  std::vector<float> widget_depths(pixel_count);

  m_points_fbo.bind_read();
  CHECK_GL(ef->glReadBuffer(GL_COLOR_ATTACHMENT1));
  CHECK_GL(ef->glReadPixels(x0, y0, region_w, region_h, GL_RG_INTEGER, GL_UNSIGNED_INT,
                            pick_pixels.data()));

  CHECK_GL(ef->glBindFramebuffer(GL_READ_FRAMEBUFFER, m_points_fbo.fbo()));
  CHECK_GL(ef->glReadPixels(x0, y0, region_w, region_h, GL_DEPTH_COMPONENT, GL_FLOAT,
                            point_depths.data()));

  CHECK_GL(ef->glBindFramebuffer(GL_READ_FRAMEBUFFER, widget_fbo));
  CHECK_GL(ef->glReadPixels(x0, y0, region_w, region_h, GL_DEPTH_COMPONENT, GL_FLOAT,
                            widget_depths.data()));

  struct PickCandidate {
    uint32_t pick_index = 0;
    uint32_t slot = 0;
    float widget_depth = 1.0f;
    int screen_dist_sq = 0;
  };
  std::optional<PickCandidate> best;

  for (int row = 0; row < region_h; ++row) {
    for (int col = 0; col < region_w; ++col) {
      const int sx = x0 + col;
      const int sy = y0 + row;
      const size_t idx =
          static_cast<size_t>(row) * static_cast<size_t>(region_w) + static_cast<size_t>(col);
      const uint32_t pick_index = pick_pixels[idx * 2];
      const uint32_t slot = pick_pixels[idx * 2 + 1];
      if (pick_index == 0 || slot == 0) {
        continue;
      }

      const float widget_depth = widget_depths[idx];
      if (widget_depth >= 0.99999f) {
        continue;
      }
      if (point_depths[idx] > widget_depth + 2e-4f) {
        continue;
      }

      const int pdx = sx - cx;
      const int pdy = sy - cy;
      const int screen_dist_sq = pdx * pdx + pdy * pdy;
      if (!best || screen_dist_sq < best->screen_dist_sq ||
          (screen_dist_sq == best->screen_dist_sq && widget_depth < best->widget_depth)) {
        best = PickCandidate{pick_index, slot, widget_depth, screen_dist_sq};
      }
    }
  }

  CHECK_GL(ef->glBindFramebuffer(GL_READ_FRAMEBUFFER, prev_read_fbo));
  CHECK_GL(ef->glReadBuffer(prev_read_buffer));

  if (!best) {
    return std::nullopt;
  }

  for (size_t i = 0; i < m_renderers.size(); ++i) {
    if (m_layers[i]->kind() != LayerKind::PointCloud || !m_layers[i]->visible()) {
      continue;
    }
    auto* las = dynamic_cast<OctreeLASLayerRenderer*>(m_renderers[i].get());
    if (!las || las->layer_slot() != static_cast<int>(best->slot)) {
      continue;
    }
    if (!las->can_fbo_pick()) {
      continue;
    }
    return las->point_from_index(best->slot, best->pick_index, m_camera.world_offset());
  }
  return std::nullopt;
}

void GLWidget::mousePressEvent(QMouseEvent* event) {
  m_last_mouse_pos = event->position();
  m_press_mouse_pos = m_last_mouse_pos;
  if (event->button() == Qt::LeftButton) {
    m_left_button_pressed = true;
  }
  // Defer begin_camera_interaction() for left button until the first drag pixel.
  // restart_render() clears the points FBO; starting orbit on press would wipe
  // pick IDs before a click-release can read them from the accumulated buffer.
  if (event->button() == Qt::MiddleButton || event->button() == Qt::RightButton) {
    begin_camera_interaction();
  }
}

void GLWidget::mouseReleaseEvent(QMouseEvent* event) {
  if (event->button() == Qt::LeftButton && m_left_button_pressed) {
    const QPointF release_pos = event->position();
    const qreal drag_dx = release_pos.x() - m_press_mouse_pos.x();
    const qreal drag_dy = release_pos.y() - m_press_mouse_pos.y();
    if (drag_dx * drag_dx + drag_dy * drag_dy <= 36) {
      PickAction action = PickAction::None;
      if (event->modifiers().testFlag(Qt::ShiftModifier)) {
        action = PickAction::PanToPoint;
      } else if (event->modifiers().testFlag(Qt::ControlModifier)) {
        action = PickAction::LookAtPoint;
      }
      try_pick_point(release_pos, action);
    }
    m_left_button_pressed = false;
  }
  schedule_camera_idle();
}

void GLWidget::mouseMoveEvent(QMouseEvent* event) {
  const QPointF pos = event->position();
  const qreal dx = pos.x() - m_last_mouse_pos.x();
  const qreal dy = pos.y() - m_last_mouse_pos.y();

  if (event->buttons() & Qt::LeftButton) {
    if (!m_camera_interacting && (std::abs(dx) > 0 || std::abs(dy) > 0)) {
      begin_camera_interaction();
    }
    m_camera.rotate_around_center(0.28 * dx, 0.28 * dy);
  } else if (event->buttons() & Qt::MiddleButton) {
    m_camera.rotate_view(0.28 * dx, 0.28 * dy);
  } else if (event->buttons() & Qt::RightButton) {
    m_camera.pan(dx / 320.0f, dy / 320.0f);
  }

  m_last_mouse_pos = pos;
  if (event->buttons() != Qt::NoButton) {
    if (std::abs(dx) > 0 || std::abs(dy) > 0) {
      note_camera_motion();
    } else {
      schedule_camera_idle();
    }
    // Clear hover during drag
    if (m_hovered_point.has_value()) {
      m_hovered_point.reset();
    }
    update();
  } else if (!m_camera_interacting) {
    if (std::abs(dx) > 0 || std::abs(dy) > 0) {
      m_hover_probe_needed = true;
    }
    update();
  }
}

void GLWidget::leaveEvent(QEvent* event) {
  Q_UNUSED(event);
  if (m_hovered_point.has_value()) {
    apply_hover_result(std::nullopt, /*repaint=*/false);
  }
  m_last_hover_probe_pos.reset();
  update();
}

void GLWidget::wheelEvent(QWheelEvent* event) {
  m_last_mouse_pos = event->position();
  note_camera_motion();
  m_hovered_point.reset();
  m_last_hover_probe_pos.reset();
  QVector3D world_pos = m_camera.unproject(event->position());
  m_camera.move_towards(world_pos,
                        m_camera.direction().length() * event->angleDelta().y() / 2000.0f, true);
  update();
}

void GLWidget::keyPressEvent(QKeyEvent* event) {
  if (event->key() == Qt::Key_W) {
    m_camera.fly(1 / 20., 0, 0);
  } else if (event->key() == Qt::Key_S) {
    m_camera.fly(-1 / 20., 0, 0);
  } else if (event->key() == Qt::Key_A) {
    m_camera.fly(0, 1 / 20., 0);
  } else if (event->key() == Qt::Key_D) {
    m_camera.fly(0, -1 / 20., 0);
  } else if (event->key() == Qt::Key_Q) {
    m_camera.fly(0, 0, -1 / 10.);
  } else if (event->key() == Qt::Key_E) {
    m_camera.fly(0, 0, 1 / 10.);
  } else if (event->key() == Qt::Key_R) {
    m_camera.reset_to_origin();
  } else if (event->key() == Qt::Key_F) {
    Extent3D bounds;
    for (const auto& layer : m_layers) {
      bounds.grow(layer->extent() - m_camera.world_offset());
    }
    if (bounds.max_extent() > 0) {
      request_zoom_to_extent(bounds);
    }
  } else if (event->key() == Qt::Key_Z && m_selected_point.has_value()) {
    pan_to_selected_point();
    return;
  } else if (event->key() == Qt::Key_Space) {
    if (m_orbit_timer->isActive())
      stop_animation();
    else
      start_animation(m_last_anim_type);
    return;
  } else {
    event->ignore();
    return;
  }
  note_camera_motion();
  update();
}

void GLWidget::set_anim_type(int t) {
  AnimType type = static_cast<AnimType>(t);
  if (type != AnimType::None) m_last_anim_type = type;
  if (type == m_anim_type) return;
  m_anim_type = type;
  if (type == AnimType::None)
    stop_animation();
  else
    start_animation(type);
}

void GLWidget::start_animation(AnimType type) {
  if (m_layers.empty()) return;
  m_anim_type = type;
  m_last_orbit_tick = std::chrono::steady_clock::now();
  m_anim_phase = 0.0;
  restart_render();
  m_orbit_timer->start();
  update();
}

void GLWidget::stop_animation() {
  m_anim_type = AnimType::None;
  m_orbit_timer->stop();
  update();
}

void GLWidget::start_bench_orbit(double duration_seconds) {
  start_animation(AnimType::Orbit);
  QTimer::singleShot(static_cast<int>(duration_seconds * 1000), [] { std::exit(0); });
}

void GLWidget::on_orbit_tick() {
  if (m_layers.empty() || m_anim_type == AnimType::None) return;
  auto now = std::chrono::steady_clock::now();
  double dt = std::chrono::duration<double>(now - m_last_orbit_tick).count();
  m_last_orbit_tick = now;
  constexpr double FULL_CIRCLE_DEG = 360.0;
  double period = (m_anim_type == AnimType::Orbit) ? m_orbit_period_secs : m_wobble_period_secs;
  double degrees = FULL_CIRCLE_DEG * dt / period;
  m_anim_phase += 2.0 * 3.1415926535 * dt / period;  // radians

  switch (m_anim_type) {
    case AnimType::Orbit:
      m_camera.rotate_around_center(degrees, 0);
      break;
    case AnimType::Wobble: {
      // Wobble traces a circle with angular radius = amplitude (degrees).
      // Per-tick rotation must be scaled by dt/period to convert position to velocity.
      double dphase = 2.0 * 3.1415926535 * dt / period;
      double h = m_wobble_amplitude_deg * dphase * std::cos(m_anim_phase);
      double v = -m_wobble_amplitude_deg * dphase * std::sin(m_anim_phase);
      m_camera.rotate_around_center(h, v);
      break;
    }
    case AnimType::None:
      break;
  }
  restart_render();
  update();
}
```


