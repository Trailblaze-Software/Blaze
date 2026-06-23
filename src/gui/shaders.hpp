#pragma once

#include <QOpenGLShaderProgram>
#include <iostream>
#include <string>

#include "gui/gl_check.hpp"

// Point cloud shaders
extern const char* POINT_VERTEX_SHADER_PROLOGUE;
extern const char* POINT_VERTEX_SHADER_MAIN;
extern const char* POINT_FRAGMENT_SHADER;

// Mesh shaders
extern const char* MESH_VERTEX_SHADER;
extern const char* MESH_FRAGMENT_SHADER;

// Textured mesh shaders
extern const char* TEXTURED_MESH_VERTEX_SHADER;
extern const char* TEXTURED_MESH_FRAGMENT_SHADER;

// Shader compilation helper
inline bool bind_shader(QOpenGLShaderProgram* shader) {
  if (!shader->bind()) {
    std::cout << "Shader bind error: " << shader->log().toStdString() << std::endl;
    return false;
  }
  CHECK_GL_AFTER();
  return true;
}
