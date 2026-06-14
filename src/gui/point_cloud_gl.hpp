#pragma once

#include <QOpenGLFunctions>
#include <cstddef>

#include "gui/point_octree.hpp"

// Native OpenGL point draw path (VAO/VBO + glDrawArrays).
class PointCloudGL {
 public:
  ~PointCloudGL() { destroy(); }

  void ensure_initialized(QOpenGLFunctions* f, GLuint program);
  void bind(QOpenGLFunctions* f) const;
  size_t draw_slice(QOpenGLFunctions* f, const OctreePoint* points, size_t count);
  void destroy();

 private:
  void configure_attributes(QOpenGLFunctions* f, GLuint program);

  GLuint m_vao = 0;
  GLuint m_vbo = 0;
  bool m_ready = false;
};
