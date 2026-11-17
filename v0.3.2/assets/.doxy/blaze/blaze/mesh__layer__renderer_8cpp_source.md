

# File mesh\_layer\_renderer.cpp

[**File List**](files.md) **>** [**gui**](dir_99d0482cf009f9d97a0877749b817f19.md) **>** [**mesh\_layer\_renderer.cpp**](mesh__layer__renderer_8cpp.md)

[Go to the documentation of this file](mesh__layer__renderer_8cpp.md)


```C++
#include <QOpenGLContext>
#include <QOpenGLFunctions>
#include <QOpenGLTexture>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <mutex>

#include "gui/gl_check.hpp"
#include "gui/layer.hpp"
#include "gui/layer_renderer.hpp"
#include "gui/raster_data.hpp"
#include "gui/shaders.hpp"

namespace {

struct MeshVertex {
  float position[3];
  float color[3];
  float normal[3];
};

struct TexturedMeshVertex {
  float position[3];
  float texcoord[2];
  float normal[3];
};

std::vector<uint8_t> build_texture_rgb(const Geo<MultiBand<FlexGrid>>& texture) {
  const size_t width = texture.width();
  const size_t height = texture.height();
  const size_t rgb_bands = std::min<size_t>(texture.size(), 3);
  std::vector<uint8_t> rgb(width * height * 3);
  for (size_t y = 0; y < height; ++y) {
    const size_t dest_y = height - 1 - y;
    for (size_t x = 0; x < width; ++x) {
      const size_t i = (dest_y * width + x) * 3;
      const double r = flex_grid_value(texture[0], x, y);
      const double g = rgb_bands > 1 ? flex_grid_value(texture[1], x, y) : r;
      const double b = rgb_bands > 2 ? flex_grid_value(texture[2], x, y) : r;
      rgb[i] = static_cast<uint8_t>(std::clamp(r, 0.0, 255.0));
      rgb[i + 1] = static_cast<uint8_t>(std::clamp(g, 0.0, 255.0));
      rgb[i + 2] = static_cast<uint8_t>(std::clamp(b, 0.0, 255.0));
    }
  }
  return rgb;
}

}  // namespace

MeshLayerRenderer::MeshLayerRenderer(std::shared_ptr<Layer> layer,
                                     std::function<const AsyncRasterData*()> data_accessor,
                                     const Coordinate3D<double>& /*offset*/, bool gpu_texture)
    : m_layer(std::move(layer)),
      m_data_accessor(std::move(data_accessor)),
      m_gpu_texture(gpu_texture) {}

void MeshLayerRenderer::upload_texture(const Geo<MultiBand<FlexGrid>>& texture) {
  const size_t width = texture.width();
  const size_t height = texture.height();
  if (width == 0 || height == 0) {
    return;
  }

  const std::vector<uint8_t> rgb = build_texture_rgb(texture);
  QOpenGLFunctions* f = QOpenGLContext::currentContext()->functions();
  GLint unpack_alignment = 4;
  CHECK_GL(f->glGetIntegerv(GL_UNPACK_ALIGNMENT, &unpack_alignment));
  CHECK_GL(f->glPixelStorei(GL_UNPACK_ALIGNMENT, 1));
  m_texture = std::make_unique<QOpenGLTexture>(QOpenGLTexture::Target2D);
  m_texture->setSize(static_cast<int>(width), static_cast<int>(height));
  m_texture->setFormat(QOpenGLTexture::RGB8_UNorm);
  m_texture->allocateStorage(QOpenGLTexture::RGB, QOpenGLTexture::UInt8);
  m_texture->setData(QOpenGLTexture::RGB, QOpenGLTexture::UInt8, rgb.data());
  CHECK_GL_AFTER();
  CHECK_GL(f->glPixelStorei(GL_UNPACK_ALIGNMENT, unpack_alignment));
  m_texture->setMinificationFilter(QOpenGLTexture::Linear);
  m_texture->setMagnificationFilter(QOpenGLTexture::Linear);
  m_texture->setWrapMode(QOpenGLTexture::ClampToEdge);
  m_texture_uploaded = true;
}

void MeshLayerRenderer::upload_mesh(const DemMeshData& mesh, const Coordinate3D<double>& offset) {
  if (mesh.vertices.empty() || mesh.indices.empty()) {
    return;
  }
  const size_t vertex_count = mesh.vertices.size() / 3;
  const bool use_texture = m_gpu_texture && mesh.has_texture;
  if (!use_texture && mesh.colors.empty()) {
    return;
  }
  if (!use_texture && mesh.colors.size() != mesh.vertices.size()) {
    std::cerr << "Mesh color/vertex size mismatch" << std::endl;
    return;
  }
  if (use_texture && mesh.texcoords.size() != vertex_count * 2) {
    std::cerr << "Mesh texcoord/vertex size mismatch" << std::endl;
    return;
  }
  for (unsigned int index : mesh.indices) {
    if (index >= vertex_count) {
      std::cerr << "Mesh index out of range: " << index << " >= " << vertex_count << std::endl;
      return;
    }
  }

  if (!m_shader) {
    m_shader = std::make_unique<QOpenGLShaderProgram>();
    if (use_texture) {
      const QString vertex_src = get_textured_mesh_vertex_shader();
      const QString fragment_src = get_textured_mesh_fragment_shader();
      if (vertex_src.isEmpty() || fragment_src.isEmpty()) {
        std::cout << "Failed to load textured mesh shaders from resources" << std::endl;
        m_shader.reset();
        return;
      }
      if (!m_shader->addShaderFromSourceCode(QOpenGLShader::Vertex, vertex_src)) {
        std::cout << "Mesh textured vertex shader compile error: " << m_shader->log().toStdString()
                  << std::endl;
        m_shader.reset();
        return;
      }
      if (!m_shader->addShaderFromSourceCode(QOpenGLShader::Fragment, fragment_src)) {
        std::cout << "Mesh textured fragment shader compile error: "
                  << m_shader->log().toStdString() << std::endl;
        m_shader.reset();
        return;
      }
      m_shader->bindAttributeLocation("position", 0);
      m_shader->bindAttributeLocation("texcoord", 1);
      m_shader->bindAttributeLocation("normal", 2);
    } else {
      const QString vertex_src = get_mesh_vertex_shader();
      const QString fragment_src = get_mesh_fragment_shader();
      if (vertex_src.isEmpty() || fragment_src.isEmpty()) {
        std::cout << "Failed to load mesh shaders from resources" << std::endl;
        m_shader.reset();
        return;
      }
      if (!m_shader->addShaderFromSourceCode(QOpenGLShader::Vertex, vertex_src)) {
        std::cout << "Mesh vertex shader compile error: " << m_shader->log().toStdString()
                  << std::endl;
        m_shader.reset();
        return;
      }
      if (!m_shader->addShaderFromSourceCode(QOpenGLShader::Fragment, fragment_src)) {
        std::cout << "Mesh fragment shader compile error: " << m_shader->log().toStdString()
                  << std::endl;
        m_shader.reset();
        return;
      }
      m_shader->bindAttributeLocation("position", 0);
      m_shader->bindAttributeLocation("color", 1);
      m_shader->bindAttributeLocation("normal", 2);
    }
    if (!m_shader->link()) {
      std::cout << "Mesh shader link error: " << m_shader->log().toStdString() << std::endl;
      m_shader.reset();
      return;
    }
  }
  m_proj_matrix_loc = m_shader->uniformLocation("proj_matrix");
  m_light_direction_loc = m_shader->uniformLocation("light_direction");
  m_camera_position_loc = m_shader->uniformLocation("camera_position");
  m_ambient_light_loc = m_shader->uniformLocation("ambient_light");
  m_diffuse_light_loc = m_shader->uniformLocation("diffuse_light");
  if (use_texture) {
    m_texture_sampler_loc = m_shader->uniformLocation("dem_texture");
  }
  m_layer_alpha_loc = m_shader->uniformLocation("layer_alpha");
  m_vertical_offset_loc = m_shader->uniformLocation("vertical_offset");

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
  {
    QOpenGLVertexArrayObject::Binder vao_binder(&m_vao);

    m_vbo.create();
    m_vbo.bind();

    m_ibo = QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
    m_ibo.create();
    m_ibo.bind();
    m_ibo.allocate(mesh.indices.data(),
                   static_cast<int>(mesh.indices.size() * sizeof(unsigned int)));
    CHECK_GL_AFTER();

    DemMeshData mesh_with_normals = mesh;
    if (mesh_with_normals.normals.size() != mesh_with_normals.vertices.size()) {
      compute_mesh_normals(mesh_with_normals);
    }

    if (!bind_shader(m_shader.get())) {
      return;
    }

    if (use_texture) {
      std::vector<TexturedMeshVertex> interleaved;
      interleaved.reserve(vertex_count);
      for (size_t i = 0; i < mesh.vertices.size(); i += 3) {
        TexturedMeshVertex vertex;
        vertex.position[0] = static_cast<float>(mesh.vertices[i] - offset.x());
        vertex.position[1] = static_cast<float>(mesh.vertices[i + 1] - offset.y());
        vertex.position[2] = static_cast<float>(mesh.vertices[i + 2] - offset.z());
        const size_t tex_index = (i / 3) * 2;
        vertex.texcoord[0] = mesh.texcoords[tex_index];
        vertex.texcoord[1] = mesh.texcoords[tex_index + 1];
        vertex.normal[0] = mesh_with_normals.normals[i];
        vertex.normal[1] = mesh_with_normals.normals[i + 1];
        vertex.normal[2] = mesh_with_normals.normals[i + 2];
        for (float component : vertex.position) {
          if (!std::isfinite(component)) {
            return;
          }
        }
        interleaved.push_back(vertex);
      }
      m_vbo.allocate(interleaved.data(),
                     static_cast<int>(interleaved.size() * sizeof(TexturedMeshVertex)));
      const int stride = static_cast<int>(sizeof(TexturedMeshVertex));
      m_shader->enableAttributeArray(0);
      m_shader->setAttributeBuffer(0, GL_FLOAT, offsetof(TexturedMeshVertex, position), 3, stride);
      m_shader->enableAttributeArray(1);
      m_shader->setAttributeBuffer(1, GL_FLOAT, offsetof(TexturedMeshVertex, texcoord), 2, stride);
      m_shader->enableAttributeArray(2);
      m_shader->setAttributeBuffer(2, GL_FLOAT, offsetof(TexturedMeshVertex, normal), 3, stride);
    } else {
      std::vector<MeshVertex> interleaved;
      interleaved.reserve(vertex_count);
      for (size_t i = 0; i < mesh.vertices.size(); i += 3) {
        MeshVertex vertex;
        vertex.position[0] = static_cast<float>(mesh.vertices[i] - offset.x());
        vertex.position[1] = static_cast<float>(mesh.vertices[i + 1] - offset.y());
        vertex.position[2] = static_cast<float>(mesh.vertices[i + 2] - offset.z());
        vertex.color[0] = mesh.colors[i];
        vertex.color[1] = mesh.colors[i + 1];
        vertex.color[2] = mesh.colors[i + 2];
        vertex.normal[0] = mesh_with_normals.normals[i];
        vertex.normal[1] = mesh_with_normals.normals[i + 1];
        vertex.normal[2] = mesh_with_normals.normals[i + 2];
        for (float component : vertex.position) {
          if (!std::isfinite(component)) {
            return;
          }
        }
        interleaved.push_back(vertex);
      }
      m_vbo.allocate(interleaved.data(), static_cast<int>(interleaved.size() * sizeof(MeshVertex)));
      const int stride = static_cast<int>(sizeof(MeshVertex));
      m_shader->enableAttributeArray(0);
      m_shader->setAttributeBuffer(0, GL_FLOAT, offsetof(MeshVertex, position), 3, stride);
      m_shader->enableAttributeArray(1);
      m_shader->setAttributeBuffer(1, GL_FLOAT, offsetof(MeshVertex, color), 3, stride);
      m_shader->enableAttributeArray(2);
      m_shader->setAttributeBuffer(2, GL_FLOAT, offsetof(MeshVertex, normal), 3, stride);
    }
    m_shader->release();
    CHECK_GL_AFTER();
  }

  m_index_count = mesh.indices.size();
  m_mesh_uploaded = true;
}

void MeshLayerRenderer::render(const Camera& camera, const RenderContext& ctx) {
  if (ctx.incremental_points) {
    return;
  }
  if (!m_visible) {
    return;
  }
  const AsyncRasterData* data = m_data_accessor();
  if (!data) {
    return;
  }

  if (!data->ready()) {
    emit repaint_required();
    return;
  }

  if (m_data_update_required) {
    m_mesh_uploaded = false;
    m_texture_uploaded = false;
    m_texture.reset();
    m_shader.reset();
    m_data_update_required = false;
  }

  if (!m_mesh_uploaded || (m_gpu_texture && !m_texture_uploaded)) {
    DemMeshData mesh_copy;
    const Geo<MultiBand<FlexGrid>>* texture_grid = nullptr;
    {
      std::unique_lock<std::mutex> lock(data->mutex(), std::try_to_lock);
      if (!lock.owns_lock() || !data->ready()) {
        emit repaint_required();
        return;
      }
      mesh_copy = data->mesh();
      if (m_gpu_texture && mesh_copy.has_texture) {
        texture_grid = &data->texture_grid();
      }
    }
    if (!m_mesh_uploaded) {
      upload_mesh(mesh_copy, camera.world_offset());
    }
    if (m_gpu_texture && !m_texture_uploaded && texture_grid != nullptr) {
      upload_texture(*texture_grid);
    }
  }
  if (!m_shader || !m_mesh_uploaded || m_index_count == 0) {
    return;
  }
  if (m_gpu_texture && !m_texture_uploaded) {
    return;
  }

  QOpenGLFunctions* f = QOpenGLContext::currentContext()->functions();
  if (!f) {
    return;
  }
  CHECK_GL(f->glEnable(GL_DEPTH_TEST));
  CHECK_GL(f->glEnable(GL_BLEND));
  CHECK_GL(f->glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA));
  if (!bind_shader(m_shader.get())) {
    return;
  }
  m_shader->setUniformValue(m_proj_matrix_loc, camera.proj_matrix());
  if (m_light_direction_loc >= 0) {
    m_shader->setUniformValue(m_light_direction_loc, ctx.light_direction_world);
  }
  if (m_camera_position_loc >= 0) {
    m_shader->setUniformValue(m_camera_position_loc, camera.position());
  }
  if (m_ambient_light_loc >= 0) {
    m_shader->setUniformValue(m_ambient_light_loc, ctx.ambient_light);
  }
  if (m_diffuse_light_loc >= 0) {
    m_shader->setUniformValue(m_diffuse_light_loc, ctx.diffuse_light);
  }
  float layer_alpha = 1.0f;
  float vertical_offset = 0.0f;
  if (auto layer = m_layer.lock()) {
    layer_alpha = layer->opacity();
    vertical_offset = layer->vertical_offset();
  }
  if (m_layer_alpha_loc >= 0) {
    m_shader->setUniformValue(m_layer_alpha_loc, layer_alpha);
  }
  if (m_vertical_offset_loc >= 0) {
    m_shader->setUniformValue(m_vertical_offset_loc, vertical_offset);
  }
  // Keep depth writes enabled for partial opacity so later layers depth-test against
  // this surface instead of painting over it in list order.
  CHECK_GL(f->glDepthMask(GL_TRUE));
  if (m_gpu_texture && m_texture) {
    m_texture->bind(0);
    CHECK_GL_AFTER();
    m_shader->setUniformValue(m_texture_sampler_loc, 0);
  }

  QOpenGLVertexArrayObject::Binder vao_binder(&m_vao);
  if (!m_vao.isCreated() || !m_vbo.isCreated() || !m_ibo.isCreated()) {
    if (m_gpu_texture && m_texture) {
      m_texture->release();
      CHECK_GL_AFTER();
    }
    m_shader->release();
    CHECK_GL_AFTER();
    return;
  }
  m_vbo.bind();
  m_ibo.bind();
  CHECK_GL_AFTER();
  if (m_gpu_texture) {
    const int stride = static_cast<int>(sizeof(TexturedMeshVertex));
    m_shader->enableAttributeArray(0);
    m_shader->setAttributeBuffer(0, GL_FLOAT, offsetof(TexturedMeshVertex, position), 3, stride);
    m_shader->enableAttributeArray(1);
    m_shader->setAttributeBuffer(1, GL_FLOAT, offsetof(TexturedMeshVertex, texcoord), 2, stride);
    m_shader->enableAttributeArray(2);
    m_shader->setAttributeBuffer(2, GL_FLOAT, offsetof(TexturedMeshVertex, normal), 3, stride);
  } else {
    const int stride = static_cast<int>(sizeof(MeshVertex));
    m_shader->enableAttributeArray(0);
    m_shader->setAttributeBuffer(0, GL_FLOAT, offsetof(MeshVertex, position), 3, stride);
    m_shader->enableAttributeArray(1);
    m_shader->setAttributeBuffer(1, GL_FLOAT, offsetof(MeshVertex, color), 3, stride);
    m_shader->enableAttributeArray(2);
    m_shader->setAttributeBuffer(2, GL_FLOAT, offsetof(MeshVertex, normal), 3, stride);
  }
  CHECK_GL_AFTER();
  CHECK_GL(f->glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(m_index_count), GL_UNSIGNED_INT,
                             nullptr));
  if (m_gpu_texture && m_texture) {
    m_texture->release();
    CHECK_GL_AFTER();
  }
  CHECK_GL(f->glDepthMask(GL_TRUE));
  CHECK_GL(f->glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
  m_shader->release();
  CHECK_GL_AFTER();
}
```


