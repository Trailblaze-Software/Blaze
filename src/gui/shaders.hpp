#pragma once

#include <QOpenGLShaderProgram>
#include <QString>
#include <iostream>
#include <string>

#include "gui/gl_check.hpp"

// Load shader source from Qt resource system
QString load_shader_source(const QString& resource_path);

// Get shader sources (with classification color function injected for point vertex shader)
QString get_point_vertex_shader();
QString get_point_fragment_shader();
QString get_mesh_vertex_shader();
QString get_mesh_fragment_shader();
QString get_textured_mesh_vertex_shader();
QString get_textured_mesh_fragment_shader();

// Shader compilation helper
inline bool bind_shader(QOpenGLShaderProgram* shader) {
  if (!shader->bind()) {
    std::cout << "Shader bind error: " << shader->log().toStdString() << std::endl;
    return false;
  }
  CHECK_GL_AFTER();
  return true;
}
