#pragma once

#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>

#include "gui/camera.hpp"
#include "gui/layer.hpp"

class LayerRenderer {
 public:
  virtual void render(const Camera& camera) = 0;
  virtual ~LayerRenderer() = default;

  static std::unique_ptr<LayerRenderer> create(std::shared_ptr<Layer> layer);
};

static const char* vertexShaderSource =
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

static const char* fragmentShaderSource =
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

#define CHECK_SHADER_BIND(shader)                                                          \
  if (!shader->bind()) {                                                                   \
    std::cout << "Error: unable to bind a shader program: " << shader->log().toStdString() \
              << std::endl;                                                                \
    return;                                                                                \
  }

class LASLayerRenderer : public LayerRenderer {
  std::weak_ptr<LASLayer> m_layer;
  std::vector<GLfloat> m_points;

  QOpenGLVertexArrayObject m_vao;
  QOpenGLBuffer m_vbo;
  std::unique_ptr<QOpenGLShaderProgram> m_shader;

  int m_proj_matrix_loc = 0;
  int m_point_radius_loc = 0;

 public:
  LASLayerRenderer(std::shared_ptr<LASLayer> layer) : m_layer(layer) {
    m_points.reserve(layer->las_file().n_points() * 3);
    for (size_t i = 0; i < layer->las_file().n_points(); ++i) {
      auto point = layer->las_file()[i];
      m_points.push_back(point.x() - layer->las_file().bounds().minx);
      m_points.push_back(point.y() - layer->las_file().bounds().miny);
      m_points.push_back(point.z() - layer->las_file().bounds().minz);
    }

    m_shader = std::make_unique<QOpenGLShaderProgram>();
    if (!m_shader->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource)) {
      std::cout << "Error: unable to add a vertex shader: " << m_shader->log().toStdString()
                << std::endl;
      return;
    }
    if (!m_shader->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource)) {
      std::cout << "Error: unable to add a fragment shader: " << m_shader->log().toStdString()
                << std::endl;
      return;
    }
    m_shader->bindAttributeLocation("position", 0);
    if (!m_shader->link()) {
      std::cout << "Error: unable to link a shader program: " << m_shader->log().toStdString()
                << std::endl;
      return;
    }
    CHECK_SHADER_BIND(m_shader);

    m_vao.create();
    {
      QOpenGLVertexArrayObject::Binder vaoBinder(&m_vao);

      m_vbo.create();
      m_vbo.bind();

      m_vbo.allocate(m_points.data(), m_points.size() * sizeof(GLfloat));

      m_shader->enableAttributeArray(0);
      m_shader->setAttributeBuffer(0, GL_FLOAT, 0, 3);

      m_proj_matrix_loc = m_shader->uniformLocation("proj_matrix");
      m_point_radius_loc = m_shader->uniformLocation("point_radius");

      m_vbo.release();
    }
    m_shader->release();
  }

  virtual void render(const Camera& camera) override {
    CHECK_SHADER_BIND(m_shader);
    QOpenGLFunctions* f = QOpenGLContext::currentContext()->functions();

    QMatrix4x4 camera_proj = camera.proj_matrix();

    CHECK_SHADER_BIND(m_shader);
    m_shader->setUniformValue(m_proj_matrix_loc, camera_proj);
    float point_radius = 0.1f * camera.projection_scale();
    m_shader->setUniformValue(m_point_radius_loc, point_radius);

    {
      QOpenGLVertexArrayObject::Binder vaoBinder(&m_vao);

      f->glDrawArrays(GL_POINTS, 0, m_points.size() / 3);
    }

    m_shader->release();
  }

  virtual ~LASLayerRenderer() = default;
};

inline std::unique_ptr<LayerRenderer> LayerRenderer::create(std::shared_ptr<Layer> layer) {
  if (auto las_layer = std::dynamic_pointer_cast<LASLayer>(layer)) {
    return std::make_unique<LASLayerRenderer>(las_layer);
  }
  return nullptr;
}
