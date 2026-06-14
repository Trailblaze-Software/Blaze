
#include "gl_widget.hpp"

#include <math.h>

#include <QCoreApplication>
#include <QMatrix4x4>
#include <QMouseEvent>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QPainter>
#include <QVector3D>
#include <QtWidgets>
#include <algorithm>
#include <chrono>
#include <iostream>
#include <limits>

GLWidget::GLWidget(QWidget* parent) : QOpenGLWidget(parent), m_camera(width(), height()) {
  m_idle_timer = new QTimer(this);
  m_idle_timer->setSingleShot(true);
  m_idle_timer->setInterval(50);
  connect(m_idle_timer, &QTimer::timeout, this, &GLWidget::on_camera_idle);

  m_stream_timer = new QTimer(this);
  m_stream_timer->setInterval(16);
  connect(m_stream_timer, &QTimer::timeout, this, &GLWidget::on_stream_tick);
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

  makeCurrent();
  m_renderers.erase(m_renderers.begin() + static_cast<std::ptrdiff_t>(index));
  m_layers.erase(it);
  restart_render();
  update();
}

QSize GLWidget::sizeHint() const { return QSize(1000, 1000); }

void GLWidget::initializeGL() {
  initializeOpenGLFunctions();

  setFocusPolicy(Qt::StrongFocus);

  QOpenGLFunctions* f = QOpenGLContext::currentContext()->functions();

  std::cout << "Detected OpenGL version: " << f->glGetString(GL_VERSION) << std::endl;

  Assert(f->glGetError() == GL_NO_ERROR, "OpenGL error");
  Assert(QOpenGLContext::currentContext()->isValid(), "OpenGL context is invalid");

  f->glEnable(GL_PROGRAM_POINT_SIZE);
  f->glEnable(GL_DEPTH_TEST);
  QPair<int, int> version = QOpenGLContext::currentContext()->format().version();
  if (version.first < 3 || (version.first == 3 && version.second < 3)) {
    f->glEnable(GL_POINT_SPRITE);
  }
  f->glEnable(GL_BLEND);
  f->glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  f->glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

  QSurfaceFormat format = QOpenGLContext::currentContext()->format();

  if (format.profile() == QSurfaceFormat::CompatibilityProfile) {
    QOpenGLFunctions* opengl_functions = QOpenGLContext::currentContext()->functions();
    GLint point_sprite_coord_origin;
    opengl_functions->glGetIntegerv(GL_POINT_SPRITE_COORD_ORIGIN, &point_sprite_coord_origin);
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
  if (w > 0 && h > 0) {
    m_camera.set_screen_size(w, h);
    apply_pending_zoom();
    restart_render();
  }
}

void GLWidget::restart_render() { m_incremental_draw = false; }

void GLWidget::paintGL() {
  if (m_painting) {
    return;
  }
  m_painting = true;

  const auto frame_start = std::chrono::steady_clock::now();

  QOpenGLFunctions* f = QOpenGLContext::currentContext()->functions();

  if (width() > 0 && height() > 0) {
    m_camera.set_screen_size(width(), height());
    apply_pending_zoom();
    const int fb_w = static_cast<int>(width() * devicePixelRatioF());
    const int fb_h = static_cast<int>(height() * devicePixelRatioF());
    if (fb_w > 0 && fb_h > 0) {
      m_framebuffer_width = fb_w;
      m_framebuffer_height = fb_h;
      m_scene_fbo.ensure_size(fb_w, fb_h);
      m_points_fbo.ensure_size(fb_w, fb_h);
    }
  }

  if (m_framebuffer_width <= 0 || m_framebuffer_height <= 0) {
    m_painting = false;
    return;
  }

  const bool incremental_points = m_incremental_draw;
  const RenderContext ctx{incremental_points};

  f->glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

  if (!incremental_points) {
    if (m_scene_fbo.valid()) {
      m_scene_fbo.bind();
      f->glViewport(0, 0, m_framebuffer_width, m_framebuffer_height);
      f->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    } else {
      f->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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
      f->glViewport(0, 0, m_framebuffer_width, m_framebuffer_height);
      m_points_fbo.clear();
    }
  } else if (m_points_fbo.valid()) {
    m_points_fbo.bind();
    f->glViewport(0, 0, m_framebuffer_width, m_framebuffer_height);
    f->glDepthFunc(GL_LEQUAL);
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
  f->glBindFramebuffer(GL_FRAMEBUFFER, widget_fbo);
  f->glViewport(0, 0, m_framebuffer_width, m_framebuffer_height);

  if (m_scene_fbo.valid()) {
    m_scene_fbo.blit_to_widget_fbo(widget_fbo, m_framebuffer_width, m_framebuffer_height);
  }

  float point_layer_alpha = 1.0f;
  for (size_t i = 0; i < m_layers.size(); ++i) {
    if (m_layers[i]->kind() != LayerKind::PointCloud || !m_layers[i]->visible()) {
      continue;
    }
    if (auto las_layer = std::dynamic_pointer_cast<LASLayer>(m_layers[i])) {
      point_layer_alpha = las_layer->point_alpha();
      break;
    }
  }

  if (m_points_fbo.valid() && point_layer_alpha > 0.0f) {
    if (auto* gl = QOpenGLContext::currentContext()->extraFunctions()) {
      m_point_compositor.composite(gl, widget_fbo, m_points_fbo.color_texture(),
                                   m_points_fbo.depth_texture(), point_layer_alpha,
                                   m_framebuffer_width, m_framebuffer_height);
    }
  }
  for (size_t i = 0; i < m_renderers.size(); ++i) {
    if (m_layers[i]->kind() != LayerKind::PointCloud || !m_layers[i]->visible()) {
      continue;
    }
    if (auto* las_renderer = dynamic_cast<OctreeLASLayerRenderer*>(m_renderers[i].get())) {
      las_renderer->render_selection_highlight(m_camera, ctx);
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

  // Displaz-style: next frame accumulates unless restart_render() is called.
  if (!m_camera_interacting) {
    m_incremental_draw = true;
  }

  m_last_point_draw_ms = 0.0;
  m_last_point_vertices = 0;
  for (size_t i = 0; i < m_renderers.size(); ++i) {
    if (m_layers[i]->kind() != LayerKind::PointCloud) {
      continue;
    }
    if (auto* las_renderer = dynamic_cast<OctreeLASLayerRenderer*>(m_renderers[i].get())) {
      m_last_point_draw_ms += las_renderer->last_point_draw_ms();
      m_last_point_vertices += las_renderer->last_point_vertices_drawn();
    }
  }

  m_last_frame_ms =
      std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - frame_start)
          .count();
  m_frame_ms_ema = m_frame_ms_ema * 0.88 + m_last_frame_ms * 0.12;

  draw_stats_overlay();

  GLenum err;
  while ((err = glGetError()) != GL_NO_ERROR) {
    std::cout << "OpenGL Error: " << err << std::endl;
  }

  m_painting = false;
}

void GLWidget::draw_stats_overlay() {
  QPainter painter(this);
  painter.setRenderHint(QPainter::TextAntialiasing);

  const double fps = m_frame_ms_ema > 0.0 ? 1000.0 / m_frame_ms_ema : 0.0;
  const QString text = tr("%1 fps  %2 ms frame  %3 ms buf  %4k verts")
                           .arg(fps, 0, 'f', 0)
                           .arg(m_last_frame_ms, 0, 'f', 1)
                           .arg(m_last_point_draw_ms, 0, 'f', 2)
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
}

void GLWidget::begin_camera_interaction() {
  if (!m_camera_interacting) {
    m_stream_timer->stop();
    restart_render();
  }
  m_camera_interacting = true;
}

void GLWidget::note_camera_motion() {
  begin_camera_interaction();
  schedule_camera_idle();
}

void GLWidget::schedule_camera_idle() { m_idle_timer->start(); }

void GLWidget::on_camera_idle() {
  m_camera_interacting = false;
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

void GLWidget::focus_on_selected_point() {
  if (!m_selected_point.has_value()) {
    return;
  }
  m_camera.look_at_target(QVector3D(static_cast<float>(m_selected_point->world_x),
                                    static_cast<float>(m_selected_point->world_y),
                                    static_cast<float>(m_selected_point->world_z)));
  restart_render();
  update();
}

void GLWidget::set_selected_point(const std::optional<PointPickResult>& pick) {
  m_selected_point = pick;
  for (size_t i = 0; i < m_renderers.size(); ++i) {
    auto* las_renderer = dynamic_cast<OctreeLASLayerRenderer*>(m_renderers[i].get());
    if (!las_renderer) {
      continue;
    }
    las_renderer->set_highlight(std::nullopt);
  }
  if (pick) {
    for (size_t i = 0; i < m_renderers.size(); ++i) {
      if (m_layers[i]->name() != pick->layer_name) {
        continue;
      }
      if (auto* las_renderer = dynamic_cast<OctreeLASLayerRenderer*>(m_renderers[i].get())) {
        las_renderer->set_highlight(pick);
        break;
      }
    }
  }
  update();
}

void GLWidget::try_pick_point(const QPoint& pixel, bool focus_on_pick) {
  std::optional<PointPickResult> best;
  float best_dist_sq = std::numeric_limits<float>::infinity();

  for (size_t i = 0; i < m_renderers.size(); ++i) {
    if (m_layers[i]->kind() != LayerKind::PointCloud || !m_layers[i]->visible()) {
      continue;
    }
    auto* las_renderer = dynamic_cast<OctreeLASLayerRenderer*>(m_renderers[i].get());
    if (!las_renderer) {
      continue;
    }
    const std::optional<PointPickResult> hit = las_renderer->pick_point(m_camera, pixel);
    if (!hit) {
      continue;
    }
    const float dx = static_cast<float>(hit->world_x) - m_camera.position().x();
    const float dy = static_cast<float>(hit->world_y) - m_camera.position().y();
    const float dz = static_cast<float>(hit->world_z) - m_camera.position().z();
    const float dist_sq = dx * dx + dy * dy + dz * dz;
    if (dist_sq < best_dist_sq) {
      best_dist_sq = dist_sq;
      best = hit;
    }
  }

  if (best) {
    set_selected_point(*best);
    if (m_point_pick_callback) {
      m_point_pick_callback(*best);
    }
    if (focus_on_pick) {
      focus_on_selected_point();
    }
  } else {
    set_selected_point(std::nullopt);
    if (m_point_pick_callback) {
      m_point_pick_callback(std::nullopt);
    }
  }
}

void GLWidget::mousePressEvent(QMouseEvent* event) {
  m_last_mouse_pos = event->position().toPoint();
  m_press_mouse_pos = m_last_mouse_pos;
  if (event->button() == Qt::LeftButton) {
    m_left_button_pressed = true;
  }
  if (event->button() == Qt::LeftButton || event->button() == Qt::MiddleButton ||
      event->button() == Qt::RightButton) {
    begin_camera_interaction();
  }
}

void GLWidget::mouseReleaseEvent(QMouseEvent* event) {
  if (event->button() == Qt::LeftButton && m_left_button_pressed) {
    const QPoint release_pos = event->position().toPoint();
    const int drag_dx = release_pos.x() - m_press_mouse_pos.x();
    const int drag_dy = release_pos.y() - m_press_mouse_pos.y();
    if (drag_dx * drag_dx + drag_dy * drag_dy <= 36) {
      const bool focus_on_pick = event->modifiers().testFlag(Qt::ShiftModifier);
      try_pick_point(release_pos, focus_on_pick);
    }
    m_left_button_pressed = false;
  }
  schedule_camera_idle();
}

void GLWidget::mouseMoveEvent(QMouseEvent* event) {
  int dx = event->position().toPoint().x() - m_last_mouse_pos.x();
  int dy = event->position().toPoint().y() - m_last_mouse_pos.y();

  if (event->buttons() & Qt::LeftButton) {
    m_camera.rotate_around_center(0.28 * dx, 0.28 * dy);
  } else if (event->buttons() & Qt::MiddleButton) {
    m_camera.rotate_view(0.28 * dx, 0.28 * dy);
  } else if (event->buttons() & Qt::RightButton) {
    m_camera.pan(dx / 320.0f, dy / 320.0f);
  }

  m_last_mouse_pos = event->position().toPoint();
  if (event->buttons() != Qt::NoButton) {
    if (dx != 0 || dy != 0) {
      note_camera_motion();
    } else {
      schedule_camera_idle();
    }
    update();
  }
}

void GLWidget::wheelEvent(QWheelEvent* event) {
  note_camera_motion();
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
    focus_on_selected_point();
    return;
  }
  note_camera_motion();
  update();
}
