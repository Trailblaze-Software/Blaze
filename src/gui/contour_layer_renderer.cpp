#include <QOpenGLContext>
#include <QOpenGLFunctions>
#include <QOpenGLVertexArrayObject>
#include <array>
#include <cmath>

#include "gui/gl_check.hpp"
#include "gui/layer_renderer.hpp"
#include "gui/shaders.hpp"

namespace {

struct MeshVertex {
  float position[3];
  float color[3];
};

void append_contour_ribbon(const Contour& contour, double half_width,
                           std::vector<MeshVertex>& vertices, std::vector<unsigned int>& indices) {
  const auto& points = contour.points();
  if (points.size() < 2) {
    return;
  }

  const float z = static_cast<float>(contour.height() + 0.5);
  const std::array<float, 3> color{0.6f, 0.35f, 0.1f};

  auto add_vertex = [&](double x, double y) {
    MeshVertex vertex;
    vertex.position[0] = static_cast<float>(x);
    vertex.position[1] = static_cast<float>(y);
    vertex.position[2] = z;
    vertex.color[0] = color[0];
    vertex.color[1] = color[1];
    vertex.color[2] = color[2];
    vertices.push_back(vertex);
    return static_cast<unsigned int>(vertices.size() - 1);
  };

  for (size_t i = 0; i + 1 < points.size(); ++i) {
    const double x0 = points[i].x();
    const double y0 = points[i].y();
    const double x1 = points[i + 1].x();
    const double y1 = points[i + 1].y();
    const double dx = x1 - x0;
    const double dy = y1 - y0;
    const double len = std::hypot(dx, dy);
    if (len < 1e-6) {
      continue;
    }
    const double nx = -dy / len * half_width;
    const double ny = dx / len * half_width;

    const unsigned int v0 = add_vertex(x0 - nx, y0 - ny);
    const unsigned int v1 = add_vertex(x0 + nx, y0 + ny);
    const unsigned int v2 = add_vertex(x1 + nx, y1 + ny);
    const unsigned int v3 = add_vertex(x1 - nx, y1 - ny);
    indices.push_back(v0);
    indices.push_back(v1);
    indices.push_back(v2);
    indices.push_back(v0);
    indices.push_back(v2);
    indices.push_back(v3);
  }
}

}  // namespace

ContourLayerRenderer::ContourLayerRenderer(std::shared_ptr<ContourLayer> layer,
                                           const Coordinate3D<double>& /*offset*/)
    : m_layer(layer) {}

void ContourLayerRenderer::upload_contours(const std::vector<Contour>& contours,
                                           const Coordinate3D<double>& offset) {
  std::vector<MeshVertex> vertices;
  std::vector<unsigned int> indices;
  vertices.reserve(contours.size() * 8);
  indices.reserve(contours.size() * 12);

  constexpr double HALF_WIDTH_METERS = 1.5;
  for (const auto& contour : contours) {
    append_contour_ribbon(contour, HALF_WIDTH_METERS, vertices, indices);
  }
  if (vertices.empty() || indices.empty()) {
    return;
  }

  for (MeshVertex& vertex : vertices) {
    vertex.position[0] -= static_cast<float>(offset.x());
    vertex.position[1] -= static_cast<float>(offset.y());
    vertex.position[2] -= static_cast<float>(offset.z());
  }

  m_shader = std::make_unique<QOpenGLShaderProgram>();
  if (!m_shader->addShaderFromSourceCode(QOpenGLShader::Vertex, MESH_VERTEX_SHADER) ||
      !m_shader->addShaderFromSourceCode(QOpenGLShader::Fragment, MESH_FRAGMENT_SHADER)) {
    m_shader.reset();
    return;
  }
  m_shader->bindAttributeLocation("position", 0);
  m_shader->bindAttributeLocation("color", 1);
  if (!m_shader->link()) {
    m_shader.reset();
    return;
  }
  m_proj_matrix_loc = m_shader->uniformLocation("proj_matrix");
  m_layer_alpha_loc = m_shader->uniformLocation("layer_alpha");

  if (m_vao.isCreated()) {
    m_vao.destroy();
  }
  if (m_vbo.isCreated()) {
    m_vbo.destroy();
  }
  if (m_ibo.isCreated()) {
    m_ibo.destroy();
  }

  m_vao.create();
  QOpenGLVertexArrayObject::Binder vao_binder(&m_vao);
  m_vbo.create();
  m_vbo.bind();
  m_vbo.allocate(vertices.data(), static_cast<int>(vertices.size() * sizeof(MeshVertex)));
  CHECK_GL_AFTER();

  m_ibo.create();
  m_ibo.bind();
  m_ibo.allocate(indices.data(), static_cast<int>(indices.size() * sizeof(unsigned int)));
  CHECK_GL_AFTER();

  if (!bind_shader(m_shader.get())) {
    return;
  }
  const int stride = static_cast<int>(sizeof(MeshVertex));
  m_shader->enableAttributeArray(0);
  m_shader->setAttributeBuffer(0, GL_FLOAT, offsetof(MeshVertex, position), 3, stride);
  m_shader->enableAttributeArray(1);
  m_shader->setAttributeBuffer(1, GL_FLOAT, offsetof(MeshVertex, color), 3, stride);
  m_shader->release();
  CHECK_GL_AFTER();

  m_index_count = indices.size();
  m_uploaded = true;
  m_vbo.release();
  CHECK_GL_AFTER();
}

void ContourLayerRenderer::render(const Camera& camera, const RenderContext& ctx) {
  if (ctx.incremental_points) {
    return;
  }
  if (!m_visible) {
    return;
  }
  auto layer = m_layer.lock();
  if (!layer) {
    return;
  }

  if (!m_uploaded) {
    std::vector<Contour> contours;
    {
      if (!layer->ready()) {
        emit repaint_required();
        return;
      }
      contours = layer->copy_contours();
    }
    if (contours.empty()) {
      emit repaint_required();
      return;
    }
    upload_contours(contours, camera.world_offset());
  }
  if (!m_shader || !m_uploaded || m_index_count == 0) {
    return;
  }

  QOpenGLFunctions* f = QOpenGLContext::currentContext()->functions();
  if (!f) {
    return;
  }
  CHECK_GL(f->glEnable(GL_DEPTH_TEST));
  if (!bind_shader(m_shader.get())) {
    return;
  }
  m_shader->setUniformValue(m_proj_matrix_loc, camera.proj_matrix());
  if (m_layer_alpha_loc >= 0) {
    m_shader->setUniformValue(m_layer_alpha_loc, layer->opacity());
  }
  QOpenGLVertexArrayObject::Binder vao_binder(&m_vao);
  m_vbo.bind();
  m_ibo.bind();
  CHECK_GL_AFTER();
  const int stride = static_cast<int>(sizeof(MeshVertex));
  m_shader->enableAttributeArray(0);
  m_shader->setAttributeBuffer(0, GL_FLOAT, offsetof(MeshVertex, position), 3, stride);
  m_shader->enableAttributeArray(1);
  m_shader->setAttributeBuffer(1, GL_FLOAT, offsetof(MeshVertex, color), 3, stride);
  CHECK_GL_AFTER();
  CHECK_GL(f->glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(m_index_count), GL_UNSIGNED_INT,
                             nullptr));
  m_shader->release();
  CHECK_GL_AFTER();
}
