#pragma once

#include <QOpenGLFunctions>
#include <cstddef>
#include <vector>

#include "gui/point_octree.hpp"

// GPU point cloud rendering with optional persistent buffer.
// When upload_points() is called, all subsequent draw_leaves() calls
// draw sub-ranges from the GPU buffer eliminating per-frame uploads.
// Falls back to per-frame upload (draw_points) for small/preview draws.
class PointCloudGL {
 public:
  ~PointCloudGL() { destroy(); }

  void ensure_initialized(QOpenGLFunctions* f);
  // Upload all points to GPU once. Call from render thread with active context.
  void upload_points(QOpenGLFunctions* f, const OctreePoint* data, size_t count);
  // Draw multiple sub-ranges from the pre-uploaded buffer.
  size_t draw_leaves(QOpenGLFunctions* f, const GLint* firsts, const GLsizei* counts,
                     size_t leaf_count);
  // Draw a single contiguous range (uploads inline, for small draws).
  size_t draw_points(QOpenGLFunctions* f, const OctreePoint* data, size_t count);
  void bind(QOpenGLFunctions* f) const;
  void destroy();

 private:
  void configure_attributes(QOpenGLFunctions* f);

  GLuint m_vao = 0;
  GLuint m_vbo = 0;
  bool m_ready = false;
  bool m_uploaded = false;
};
