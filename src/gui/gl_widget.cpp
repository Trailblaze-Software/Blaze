
#include "gl_widget.hpp"

#include <math.h>
#include <qmatrix4x4.h>
#include <qnamespace.h>
#include <qvectornd.h>

#include <QCoreApplication>
#include <QMouseEvent>
#include <QOpenGLShaderProgram>
#include <QtWidgets>
#include <iostream>

#include "lib/las/las_file.hpp"
#include "utilities/coordinate.hpp"
#include "utilities/progress_tracker.hpp"

GLWidget::GLWidget(QWidget *parent) : QOpenGLWidget(parent) {}

GLWidget::~GLWidget() {}

QSize GLWidget::sizeHint() const { return QSize(1000, 1000); }

static const char *vertexShaderSource =
    "#version 330\n"
    "in vec3 position;\n"
    "uniform float point_radius;\n"
    "uniform mat4 proj_matrix;\n"
    "out vec4 color;\n"
    "void main() {\n"
    "   color = vec4(1.0, 1.0, 1.0, 0.5);\n"
    "   vec4 pos = proj_matrix * vec4(position, 1.0);\n"
    "   gl_Position = pos;\n"
    "   float out_point_radius = point_radius / pos.w;\n"
    "   if (out_point_radius < 1.0) {\n"
    "       out_point_radius = 1.0;\n"
    "   }\n"
    "   gl_PointSize = out_point_radius;\n"
    "}\n";

static const char *fragmentShaderSource =
    "#version 330\n"
    "in vec4 color;\n"
    "out vec4 fragColor;\n"
    "void main() {\n"
    "float distance = length(gl_PointCoord - vec2(0.5, 0.5));\n"
    "if (distance > 0.5) {\n"
    "   discard;\n"
    "}\n"
    " vec4 new_color = color * (gl_PointCoord.x + gl_PointCoord.y) * 0.6;\n"
    //"   if (gl_PointCoord.x > 0.5) {\n"
    //"      fragColor = vec4(1.0, 0.0, 0.0, 1.0);\n"
    //"   } else {\n"
    "   fragColor = new_color;\n"
    //"   }\n"
    "}\n";

#define CHECK_PROGRAM_BIND()                                                                 \
  if (!m_shader->bind()) {                                                                   \
    std::cout << "Error: unable to bind a shader program: " << m_shader->log().toStdString() \
              << std::endl;                                                                  \
    qDebug() << "Error: unable to bind a shader program: " << m_shader->log();               \
    return;                                                                                  \
  }

void GLWidget::initializeGL() {
  // m_las_file = LASFile("assets/sample.laz", ProgressTracker());
  m_las_file = LASFile("laz_files/Blackie.laz", ProgressTracker());
  points.reserve(m_las_file->n_points() * 3);
  for (size_t i = 0; i < m_las_file->n_points(); i++) {
    points.push_back(m_las_file.value()[i].x() - m_las_file->bounds().minx);
    points.push_back(m_las_file.value()[i].y() - m_las_file->bounds().miny);
    points.push_back(m_las_file.value()[i].z() - m_las_file->bounds().minz);
  }

  initializeOpenGLFunctions();
  glClearColor(0, 0, 0, 1);
  setFocusPolicy(Qt::StrongFocus);
  GLenum err;
  while ((err = glGetError()) != GL_NO_ERROR) {
    std::cout << "ErrorE: " << err << std::endl;
  }

  m_shader = std::make_unique<QOpenGLShaderProgram>();
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
  while ((err = glGetError()) != GL_NO_ERROR) {
    std::cout << "ErrorD: " << err << std::endl;
  }

  // Create a vertex array object. In OpenGL ES 2.0 and OpenGL 2.x
  // implementations this is optional and support may not be present
  // at all. Nonetheless the below code works in all cases and makes
  // sure there is a VAO when one is needed.
  m_vao.create();
  QOpenGLVertexArrayObject::Binder vaoBinder(&m_vao);
  m_vao.bind();

  m_vbo.create();
  m_vbo.bind();
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

  // Store the vertex attribute bindings for the program.
  m_vao.bind();
  m_vbo.bind();
  QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
  f->glEnableVertexAttribArray(0);
  f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), nullptr);
  m_vbo.release();
  m_vao.release();

  m_shader->release();

  while ((err = glGetError()) != GL_NO_ERROR) {
    std::cout << "ErrorA: " << err << std::endl;
  }
}

float deg2rad(float deg) { return deg * M_PI / 180.0f; }

float rad2deg(float rad) { return rad * 180.0f / M_PI; }

void GLWidget::paintGL() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_PROGRAM_POINT_SIZE);
  glEnable(GL_DEPTH_TEST);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_BLEND);
  glClearColor(0.0, 0.0, 0.0, 0.0);

  QMatrix4x4 camera_proj;
  camera_proj.setToIdentity();
  camera_proj.perspective(45.0f, GLfloat(width()) / height(), 0.01f, 10000.0f);
  camera_proj.lookAt(m_camera_position, m_camera_position + m_camera_direction, m_camera_up);

  CHECK_PROGRAM_BIND();
  m_shader->setUniformValue(m_proj_matrix_loc, camera_proj);
  float proj_scale = height() / (2.0f * tan(deg2rad(45) / 2.0f));
  float point_radius = 0.1f * proj_scale;
  m_shader->setUniformValue(m_point_radius_loc, point_radius);

  m_vao.bind();
  m_vbo.bind();

  glDrawArrays(GL_POINTS, 0, points.size() / 3);

  m_vbo.release();
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
    QVector3D rotation_point = m_camera_position + m_camera_direction;
    m_camera_position = -m_camera_direction;

    float current_altitude_angle = asin(m_camera_direction.z() / m_camera_direction.length());
    float angle_to_rotate = -0.2 * dy;
    if (current_altitude_angle + deg2rad(angle_to_rotate) > M_PI / 2) {
      angle_to_rotate = rad2deg(M_PI / 2 - 1e-3 - current_altitude_angle);
    } else if (current_altitude_angle + deg2rad(angle_to_rotate) < -M_PI / 2) {
      angle_to_rotate = rad2deg(-M_PI / 2 + 1e-3 - current_altitude_angle);
    }

    QMatrix4x4 rotation;
    rotation.setToIdentity();
    rotation.rotate(-0.2 * dx, m_camera_up);
    rotation.rotate(angle_to_rotate, QVector3D::crossProduct(m_camera_direction, m_camera_up));
    m_camera_position = rotation.map(m_camera_position);
    m_camera_position += rotation_point;
    m_camera_direction = rotation_point - m_camera_position;
  } else if (event->buttons() & Qt::MiddleButton) {
    QMatrix4x4 rotation;
    rotation.setToIdentity();
    rotation.rotate(-0.2 * dx, m_camera_up);

    float current_altitude_angle = asin(m_camera_direction.z() / m_camera_direction.length());
    float angle_to_rotate = -0.2 * dy;
    if (current_altitude_angle + deg2rad(angle_to_rotate) > M_PI / 2) {
      angle_to_rotate = rad2deg(M_PI / 2 - 1e-3 - current_altitude_angle);
    } else if (current_altitude_angle + deg2rad(angle_to_rotate) < -M_PI / 2) {
      angle_to_rotate = rad2deg(-M_PI / 2 + 1e-3 - current_altitude_angle);
    }

    rotation.rotate(angle_to_rotate, QVector3D::crossProduct(m_camera_direction, m_camera_up));
    m_camera_direction = rotation.map(m_camera_direction);

  } else if (event->buttons() & Qt::RightButton) {
    QVector3D right = QVector3D::crossProduct(m_camera_up, m_camera_direction);
    m_camera_position += right * dx / 400.0f;
    m_camera_position +=
        QVector3D::crossProduct(m_camera_direction.normalized(), right) * dy / 400.0f;
  }

  m_last_mouse_pos = event->position().toPoint();
  update();
}

void GLWidget::wheelEvent(QWheelEvent *event) {
  QVector3D mouse_pos = QVector3D(event->position().x(), height() - event->position().y(), 0);

  QMatrix4x4 camera_proj;
  camera_proj.setToIdentity();
  camera_proj.lookAt(m_camera_position, m_camera_position + m_camera_direction, m_camera_up);
  QMatrix4x4 proj;
  proj.setToIdentity();
  proj.perspective(45.0f, GLfloat(width()) / height(), 0.01f, 10000.0f);

  QVector3D world_pos = mouse_pos.unproject(camera_proj, proj, QRect(0, 0, width(), height()));
  QVector3D direction = (world_pos - m_camera_position).normalized() * m_camera_direction.length();
  m_camera_position += direction * (event->angleDelta().y() / 2000.0f);
  m_camera_direction *= (1 - event->angleDelta().y() / 2000.0f);
  std::cout << "New position: " << m_camera_position.x() << " " << m_camera_position.y() << " "
            << m_camera_position.z() << std::endl;
  std::cout << "New direction: " << m_camera_direction.x() << " " << m_camera_direction.y() << " "
            << m_camera_direction.z() << std::endl;
  update();
}

void GLWidget::keyPressEvent(QKeyEvent *event) {
  std::cout << "Key pressed: " << event->key() << std::endl;

  QVector3D planar_camera_direction = m_camera_direction;
  planar_camera_direction.setZ(0);
  QVector3D right = QVector3D::crossProduct(m_camera_up.normalized(), planar_camera_direction);
  if (event->key() == Qt::Key_W) {
    m_camera_position += planar_camera_direction / 20.0f;
  } else if (event->key() == Qt::Key_S) {
    m_camera_position -= planar_camera_direction / 20.0f;
  } else if (event->key() == Qt::Key_A) {
    m_camera_position += right / 20.0f;
  } else if (event->key() == Qt::Key_D) {
    m_camera_position -= right / 20.0f;
  } else if (event->key() == Qt::Key_Q) {
    m_camera_position -= m_camera_up.normalized() * m_camera_direction.length() / 10.0f;
  } else if (event->key() == Qt::Key_E) {
    m_camera_position += m_camera_up.normalized() * m_camera_direction.length() / 10.0f;
  } else if (event->key() == Qt::Key_R) {
    m_camera_position = {2.0f, 2.0f, 2.0f};
    m_camera_direction = {-2.0f, -2.0f, -2.0f};
    m_camera_up = {0.0f, 0.0, 1.0f};
  } else if (event->key() == Qt::Key_F) {
    Extent3D min_max = m_las_file->bounds();
    QVector3D centroid(min_max.maxx - min_max.minx, min_max.maxy - min_max.miny,
                       min_max.maxz - min_max.minz);
    centroid /= 2;
    float max_dimension = centroid.length();
    m_camera_position = centroid - 10 * max_dimension * m_camera_direction.normalized();

    QMatrix4x4 camera_proj;
    camera_proj.setToIdentity();
    camera_proj.perspective(45.0f, GLfloat(width()) / height(), 0.01f, 10000.f);
    camera_proj.lookAt(m_camera_position, m_camera_position + m_camera_direction, m_camera_up);

    float zoom_out_amount = 0.0f;

    for (size_t i = 0; i < 2; i++) {
      for (size_t j = 0; j < 2; j++) {
        for (size_t k = 0; k < 2; k++) {
          QVector3D corner(i == 0 ? 0 : min_max.maxx - min_max.minx,
                           j == 0 ? 0 : min_max.maxy - min_max.miny,
                           k == 0 ? 0 : min_max.maxz - min_max.minz);
          QVector3D screen_pos = camera_proj.map(corner);
          zoom_out_amount = std::max(zoom_out_amount,
                                     std::max(std::abs(screen_pos.x()), std::abs(screen_pos.y())));
        }
      }
    }

    m_camera_position =
        centroid - m_camera_direction.normalized() * 10 * max_dimension * zoom_out_amount;
    m_camera_direction = centroid - m_camera_position;
  }
  update();
}
