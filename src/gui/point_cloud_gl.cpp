#include "gui/point_cloud_gl.hpp"

#include <QOpenGLContext>
#include <QOpenGLExtraFunctions>
#include <cstddef>
#include <cstring>

void PointCloudGL::destroy() {
  if (m_vao == 0 && m_vbo == 0) {
    m_ready = false;
    return;
  }
  auto* gl = QOpenGLContext::currentContext()->extraFunctions();
  if (!gl) {
    m_vao = 0;
    m_vbo = 0;
    m_ready = false;
    return;
  }
  if (m_vao != 0) {
    gl->glDeleteVertexArrays(1, &m_vao);
    m_vao = 0;
  }
  if (m_vbo != 0) {
    gl->glDeleteBuffers(1, &m_vbo);
    m_vbo = 0;
  }
  m_ready = false;
}

void PointCloudGL::configure_attributes(QOpenGLFunctions* f, GLuint program) {
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
  (void)program;
}

void PointCloudGL::ensure_initialized(QOpenGLFunctions* f, GLuint program) {
  if (m_ready) {
    return;
  }
  auto* gl = QOpenGLContext::currentContext()->extraFunctions();
  if (!gl) {
    return;
  }
  gl->glGenVertexArrays(1, &m_vao);
  gl->glGenBuffers(1, &m_vbo);
  gl->glBindVertexArray(m_vao);
  configure_attributes(f, program);
  gl->glBindVertexArray(0);
  gl->glBindBuffer(GL_ARRAY_BUFFER, 0);
  m_ready = true;
}

void PointCloudGL::bind(QOpenGLFunctions* f) const {
  auto* gl = QOpenGLContext::currentContext()->extraFunctions();
  if (gl) {
    gl->glBindVertexArray(m_vao);
  } else {
    f->glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
  }
}

size_t PointCloudGL::draw_slice(QOpenGLFunctions* f, const OctreePoint* points, size_t count) {
  if (points == nullptr || count == 0) {
    return 0;
  }
  const GLsizeiptr bytes = static_cast<GLsizeiptr>(count * sizeof(OctreePoint));
  f->glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
  f->glBufferData(GL_ARRAY_BUFFER, bytes, nullptr, GL_STREAM_DRAW);
  f->glBufferSubData(GL_ARRAY_BUFFER, 0, bytes, points);
  f->glDrawArrays(GL_POINTS, 0, static_cast<GLsizei>(count));
  return count;
}
