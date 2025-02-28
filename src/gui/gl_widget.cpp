
#include "gl_widget.hpp"

#include <math.h>

#include <QCoreApplication>
#include <QMatrix4x4>
#include <QMouseEvent>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QVector3D>
#include <QtWidgets>
#include <iostream>

GLWidget::GLWidget(QWidget *parent) : QOpenGLWidget(parent), m_camera(width(), height()) {}

GLWidget::~GLWidget() {}

QSize GLWidget::sizeHint() const { return QSize(1000, 1000); }

void GLWidget::initializeGL() {
  initializeOpenGLFunctions();

  setFocusPolicy(Qt::StrongFocus);

  QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();

  std::cout << "Detected OpenGL version: " << f->glGetString(GL_VERSION) << std::endl;

  Assert(f->glGetError() == GL_NO_ERROR, "OpenGL error");
  Assert(QOpenGLContext::currentContext()->isValid(), "OpenGL context is invalid");

  // f->glEnableVertexAttribArray(0);
  // f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), nullptr);
  f->glEnable(GL_PROGRAM_POINT_SIZE);
  f->glEnable(GL_DEPTH_TEST);
  QPair<int, int> version = QOpenGLContext::currentContext()->format().version();
  if (version.first < 3 || (version.first == 3 && version.second < 3)) {
    f->glEnable(GL_POINT_SPRITE);
  }
  f->glEnable(GL_BLEND);
  f->glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  f->glClearColor(0.2, 0.2, 0.2, 1.0);

  QSurfaceFormat format = QOpenGLContext::currentContext()->format();

  if (format.profile() == QSurfaceFormat::CompatibilityProfile) {
    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
    GLint point_sprite_coord_origin;
    f->glGetIntegerv(GL_POINT_SPRITE_COORD_ORIGIN, &point_sprite_coord_origin);
    AssertEQ(point_sprite_coord_origin, GL_UPPER_LEFT);
  }

  GLenum err;
  while ((err = glGetError()) != GL_NO_ERROR) {
    std::cout << "OpenGL Initialization Error: " << err << std::endl;
  }
}

void GLWidget::paintGL() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  m_camera.set_screen_size(width(), height());

  for (const auto &renderer : m_renderers) {
    renderer->render(m_camera);
  }

  GLenum err;
  while ((err = glGetError()) != GL_NO_ERROR) {
    std::cout << "OpenGL Error: " << err << std::endl;
  }
}

void GLWidget::mousePressEvent(QMouseEvent *event) {
  m_last_mouse_pos = event->position().toPoint();
}

void GLWidget::mouseMoveEvent(QMouseEvent *event) {
  int dx = event->position().toPoint().x() - m_last_mouse_pos.x();
  int dy = event->position().toPoint().y() - m_last_mouse_pos.y();

  if (event->buttons() & Qt::LeftButton) {
    m_camera.rotate_around_center(0.2 * dx, 0.2 * dy);
  } else if (event->buttons() & Qt::MiddleButton) {
    m_camera.rotate_view(0.2 * dx, 0.2 * dy);
  } else if (event->buttons() & Qt::RightButton) {
    m_camera.pan(dx / 400.0f, dy / 400.0f);
  }

  m_last_mouse_pos = event->position().toPoint();
  update();
}

void GLWidget::wheelEvent(QWheelEvent *event) {
  QVector3D world_pos = m_camera.unproject(event->position());
  m_camera.move_towards(world_pos,
                        m_camera.direction().length() * event->angleDelta().y() / 2000.0f, true);
  update();
}

void GLWidget::keyPressEvent(QKeyEvent *event) {
  if (event->key() == Qt::Key_W) {
    m_camera.fly(1 / 20., 0, 0);
  } else if (event->key() == Qt::Key_S) {
    m_camera.fly(-1 / 20., 0, 0);
  } else if (event->key() == Qt::Key_A) {
    m_camera.fly(0, -1 / 20., 0);
  } else if (event->key() == Qt::Key_D) {
    m_camera.fly(0, 1 / 20., 0);
  } else if (event->key() == Qt::Key_Q) {
    m_camera.fly(0, 0, -1 / 10.);
  } else if (event->key() == Qt::Key_E) {
    m_camera.fly(0, 0, 1 / 10.);
  } else if (event->key() == Qt::Key_R) {
    m_camera.reset_to_origin();
  } else if (event->key() == Qt::Key_F) {
    Extent3D bounds;
    for (const auto &layer : m_layers) {
      bounds.grow(layer->extent());
    }
    m_camera.zoom_to_fit(bounds);
  }
  update();
}
