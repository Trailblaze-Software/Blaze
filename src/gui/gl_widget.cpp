
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

#include "lib/las/las_file.hpp"
#include "utilities/coordinate.hpp"
#include "utilities/progress_tracker.hpp"

GLWidget::GLWidget(QWidget *parent) : QOpenGLWidget(parent) {}

GLWidget::~GLWidget() {}

QSize GLWidget::sizeHint() const { return QSize(1000, 1000); }

static const char *vertexShaderSource =
    R"(
        #version 330 core
        in vec3 position;
        uniform float point_radius;
        uniform mat4 proj_matrix;
        out vec4 color;
        void main() {
            color = vec4(1.0, 1.0, 1.0, 0.5);
            vec4 pos = proj_matrix * vec4(position, 1.0);
            gl_Position = pos;
            float out_point_radius = point_radius / pos.w;
            if (out_point_radius < 1.0) {
                out_point_radius = 1.0;
            }
            gl_PointSize = out_point_radius;
        }
      )";

static const char *fragmentShaderSource =
    R"(
        #version 330 core
        in vec4 color;
        out vec4 fragColor;
        void main() {
            if (length(gl_PointCoord - vec2(0.5, 0.5)) > 0.5) {
                discard;
            }
            vec4 new_color = color * (gl_PointCoord.x + 1 - gl_PointCoord.y) * 0.6;
            fragColor = new_color;
        }
      )";

#define CHECK_PROGRAM_BIND()                                                                 \
  if (!m_shader->bind()) {                                                                   \
    std::cout << "Error: unable to bind a shader program: " << m_shader->log().toStdString() \
              << std::endl;                                                                  \
    qDebug() << "Error: unable to bind a shader program: " << m_shader->log();               \
    return;                                                                                  \
  }

void GLWidget::initializeGL() {
  initializeOpenGLFunctions();

  m_las_file = LASFile("assets/sample.laz", ProgressTracker());
  // m_las_file = LASFile("laz_files/Blackie.laz", ProgressTracker());
  points.reserve(m_las_file->n_points() * 3);
  for (size_t i = 0; i < m_las_file->n_points(); i++) {
    points.push_back(m_las_file.value()[i].x() - m_las_file->bounds().minx);
    points.push_back(m_las_file.value()[i].y() - m_las_file->bounds().miny);
    points.push_back(m_las_file.value()[i].z() - m_las_file->bounds().minz);
  }

  setFocusPolicy(Qt::StrongFocus);
  GLenum err;
  while ((err = glGetError()) != GL_NO_ERROR) {
    std::cout << "ErrorE: " << err << std::endl;
  }

  m_shader = std::make_unique<QOpenGLShaderProgram>(this);
  if (!m_shader->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource)) {
    std::cout << "Error: unable to add a vertex shader: " << m_shader->log().toStdString()
              << std::endl;
    qDebug() << "Error: unable to add a vertex shader: " << m_shader->log();
    return;
  }
  if (!m_shader->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource)) {
    std::cout << "Error: unable to add a fragment shader: " << m_shader->log().toStdString()
              << std::endl;
    qDebug() << "Error: unable to add a fragment shader: " << m_shader->log();
    return;
  }
  m_shader->bindAttributeLocation("position", 0);
  if (!m_shader->link()) {
    std::cout << "Error: unable to link a shader program: " << m_shader->log().toStdString()
              << std::endl;
    qDebug() << "Error: unable to link a shader program: " << m_shader->log();
    return;
  }
  CHECK_PROGRAM_BIND();

  m_vao.create();
  QOpenGLVertexArrayObject::Binder vaoBinder(&m_vao);
  m_vao.bind();

  m_vbo.create();
  m_vbo.bind();
  for (size_t i = 0; i < 10; i++) {
    std::cout << points[i] << " ";
  }
  std::cout << std::endl;

  m_vbo.allocate(points.data(), points.size() * sizeof(GLfloat));

  m_shader->enableAttributeArray(0);
  m_shader->setAttributeBuffer(0, GL_FLOAT, 0, 3);

  m_vbo.release();
  m_vao.release();

  GLfloat size[2];
  glGetFloatv(GL_POINT_SIZE_RANGE, size);
  std::cout << "Maximum point size: " << size[0] << " to " << size[1] << std::endl;

  m_proj_matrix_loc = m_shader->uniformLocation("proj_matrix");
  m_point_radius_loc = m_shader->uniformLocation("point_radius");

  m_vao.bind();
  m_vbo.bind();
  QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();

  std::cout << "Detected OpenGL version: " << f->glGetString(GL_VERSION) << std::endl;

  Assert(f->glGetError() == GL_NO_ERROR, "OpenGL error");
  Assert(QOpenGLContext::currentContext()->isValid(), "OpenGL context is invalid");

  f->glEnableVertexAttribArray(0);
  f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), nullptr);
  f->glEnable(GL_PROGRAM_POINT_SIZE);
  f->glEnable(GL_DEPTH_TEST);
  f->glEnable(GL_POINT_SPRITE);
  f->glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  f->glEnable(GL_BLEND);
  f->glClearColor(0.2, 0.2, 0.2, 1.0);

  QSurfaceFormat format = QOpenGLContext::currentContext()->format();

  if (format.profile() == QSurfaceFormat::CompatibilityProfile) {
    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
    GLint point_sprite_coord_origin;
    f->glGetIntegerv(GL_POINT_SPRITE_COORD_ORIGIN, &point_sprite_coord_origin);
    AssertEQ(point_sprite_coord_origin, GL_UPPER_LEFT);
  }

  m_vbo.release();
  m_vao.release();

  m_shader->release();

  while ((err = glGetError()) != GL_NO_ERROR) {
    std::cout << "OpenGL Initialization Error: " << err << std::endl;
  }
}

void GLWidget::paintGL() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  QMatrix4x4 camera_proj = m_camera.proj_matrix(width(), height());

  CHECK_PROGRAM_BIND();
  m_shader->setUniformValue(m_proj_matrix_loc, camera_proj);
  float point_radius = 0.1f * m_camera.projection_scale(height());
  m_shader->setUniformValue(m_point_radius_loc, point_radius);

  m_vao.bind();

  glDrawArrays(GL_POINTS, 0, points.size() / 3);

  m_vao.release();

  m_shader->release();

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
  QVector3D world_pos = m_camera.unproject(width(), height(), event->position());
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
    m_camera.zoom_to_fit(m_las_file->bounds(), width(), height());
  }
  update();
}
