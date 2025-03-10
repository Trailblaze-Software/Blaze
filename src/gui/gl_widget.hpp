
#pragma once

#include <QEvent>
#include <QFutureWatcher>
#include <QMatrix4x4>
#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLWidget>
#include <QtConcurrent>

#include "gui/camera.hpp"
#include "gui/layer.hpp"
#include "gui/layer_renderer.hpp"

QT_FORWARD_DECLARE_CLASS(QOpenGLShaderProgram)

class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions {
  Q_OBJECT

 public:
  GLWidget(QWidget *parent = nullptr);
  ~GLWidget();

  void add_layer(std::unique_ptr<Layer> layer) {
    if (m_layers.empty()) {
      m_projection = layer->projection();
      m_offset = layer->extent().center();
    } else if (m_projection != layer->projection()) {
      throw std::runtime_error(
          "New layer must have same projection as existing layers. New layer has projection: " +
          layer->projection() + ", existing layers have projection: " + m_projection + ".");
    }
    makeCurrent();
    m_layers.emplace_back(std::move(layer));
    m_renderers.emplace_back(LayerRenderer::create(m_layers.back(), m_offset));
    m_camera.zoom_to_fit(m_layers.back()->extent() - m_offset);
  }

  std::vector<std::shared_ptr<Layer>> layers() const { return m_layers; }

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

  int m_proj_matrix_loc = 0;
  int m_point_radius_loc = 0;

  Camera m_camera;

  std::vector<std::shared_ptr<Layer>> m_layers;
  std::vector<std::unique_ptr<LayerRenderer>> m_renderers;

  std::string m_projection;
  Coordinate3D<double> m_offset;
};
