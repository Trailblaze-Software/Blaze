#include "gui/point_cloud_gl.hpp"

#include <QOpenGLContext>
#include <QOpenGLExtraFunctions>
#include <cstddef>
#include <cstring>

void PointCloudGL::destroy() {
  auto* gl = QOpenGLContext::currentContext() ? QOpenGLContext::currentContext()->extraFunctions()
                                              : nullptr;
  if (m_vbo && gl) gl->glDeleteBuffers(1, &m_vbo);
  if (m_vao && gl) gl->glDeleteVertexArrays(1, &m_vao);
  m_vbo = 0;
  m_vao = 0;
  m_ready = false;
  m_uploaded = false;
}

void PointCloudGL::configure_attributes(QOpenGLFunctions* f) {
  const GLsizei stride = static_cast<GLsizei>(sizeof(OctreePoint));
  f->glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
  f->glEnableVertexAttribArray(0);
  f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride,
                           reinterpret_cast<const void*>(offsetof(OctreePoint, x)));
  f->glEnableVertexAttribArray(1);
  f->glVertexAttribPointer(1, 1, GL_UNSIGNED_SHORT, GL_TRUE, stride,
                           reinterpret_cast<const void*>(offsetof(OctreePoint, intensity)));
  f->glEnableVertexAttribArray(2);
  f->glVertexAttribPointer(2, 1, GL_UNSIGNED_BYTE, GL_FALSE, stride,
                           reinterpret_cast<const void*>(offsetof(OctreePoint, classification)));
  f->glEnableVertexAttribArray(3);
  f->glVertexAttribPointer(3, 3, GL_UNSIGNED_BYTE, GL_TRUE, stride,
                           reinterpret_cast<const void*>(offsetof(OctreePoint, file_r)));
  f->glEnableVertexAttribArray(4);
  f->glVertexAttribPointer(4, 1, GL_UNSIGNED_BYTE, GL_FALSE, stride,
                           reinterpret_cast<const void*>(offsetof(OctreePoint, has_file_rgb)));
}

void PointCloudGL::ensure_initialized(QOpenGLFunctions* f) {
  if (m_ready) return;
  auto* gl = QOpenGLContext::currentContext()->extraFunctions();
  if (!gl) return;
  gl->glGenVertexArrays(1, &m_vao);
  gl->glGenBuffers(1, &m_vbo);
  gl->glBindVertexArray(m_vao);
  configure_attributes(f);
  gl->glBindVertexArray(0);
  gl->glBindBuffer(GL_ARRAY_BUFFER, 0);
  m_ready = true;
}

void PointCloudGL::upload_points(QOpenGLFunctions* f, const OctreePoint* data, size_t count) {
  if (!data || count == 0) return;
  const GLsizeiptr bytes = static_cast<GLsizeiptr>(count * sizeof(OctreePoint));
  f->glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
  f->glBufferData(GL_ARRAY_BUFFER, bytes, data, GL_STATIC_DRAW);
  f->glBindBuffer(GL_ARRAY_BUFFER, 0);
  m_uploaded = true;
}

size_t PointCloudGL::draw_leaves(QOpenGLFunctions* f, const GLint* firsts, const GLsizei* counts,
                                 size_t leaf_count) {
  if (!m_uploaded || leaf_count == 0) return 0;
  size_t total = 0;
  for (size_t i = 0; i < leaf_count; ++i) {
    if (counts[i] <= 0) continue;
    f->glDrawArrays(GL_POINTS, firsts[i], counts[i]);
    total += static_cast<size_t>(counts[i]);
  }
  return total;
}

size_t PointCloudGL::draw_points(QOpenGLFunctions* f, const OctreePoint* data, size_t count) {
  if (!data || count == 0) return 0;
  const GLsizeiptr bytes = static_cast<GLsizeiptr>(count * sizeof(OctreePoint));
  f->glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
  f->glBufferData(GL_ARRAY_BUFFER, bytes, nullptr, GL_STREAM_DRAW);
  f->glBufferSubData(GL_ARRAY_BUFFER, 0, bytes, data);
  f->glDrawArrays(GL_POINTS, 0, static_cast<GLsizei>(count));
  return count;
}

void PointCloudGL::bind(QOpenGLFunctions* f) const {
  auto* gl = QOpenGLContext::currentContext()->extraFunctions();
  if (gl) {
    gl->glBindVertexArray(m_vao);
  } else {
    f->glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
  }
}
