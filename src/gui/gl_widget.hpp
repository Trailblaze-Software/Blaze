
#pragma once

#include <qevent.h>

#include <QMatrix4x4>
#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLWidget>

#include "gui/camera.hpp"
#include "las/las_file.hpp"

QT_FORWARD_DECLARE_CLASS(QOpenGLShaderProgram)

class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions {
  Q_OBJECT

 public:
  GLWidget(QWidget *parent = nullptr);
  ~GLWidget();

  void load_las_file(const fs::path &file);

 protected:
  QSize sizeHint() const override;
  void initializeGL() override;
  void paintGL() override;
  void mousePressEvent(QMouseEvent *event) override;
  void mouseMoveEvent(QMouseEvent *event) override;
  void wheelEvent(QWheelEvent *event) override;
  void keyPressEvent(QKeyEvent *event) override;

 private:
  QPoint m_last_mouse_pos;
  QOpenGLVertexArrayObject m_vao;
  QOpenGLBuffer m_vbo;
  std::unique_ptr<QOpenGLShaderProgram> m_shader;

  int m_proj_matrix_loc = 0;
  int m_point_radius_loc = 0;

  Camera m_camera;

  std::vector<GLfloat> points;
  std::optional<LASFile> m_las_file;
};
