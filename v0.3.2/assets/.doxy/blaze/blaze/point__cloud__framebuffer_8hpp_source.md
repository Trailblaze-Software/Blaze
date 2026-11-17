

# File point\_cloud\_framebuffer.hpp

[**File List**](files.md) **>** [**gui**](dir_99d0482cf009f9d97a0877749b817f19.md) **>** [**point\_cloud\_framebuffer.hpp**](point__cloud__framebuffer_8hpp.md)

[Go to the documentation of this file](point__cloud__framebuffer_8hpp.md)


```C++
#pragma once

#include <QOpenGLExtraFunctions>
#include <QOpenGLFunctions>
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <memory>

// Off-screen RGBA + depth-texture target for incremental point accumulation.
// Also carries an RG32UI pick attachment (COLOR_ATTACHMENT1):
//   .r = global point index + 1 (0 = no point, supports >1B points per layer)
//   .g = layer slot (1-based, 0 = pick suppressed)
class PointCloudFramebuffer {
 public:
  ~PointCloudFramebuffer() { destroy(); }

  void ensure_size(int width, int height);
  void bind() const;
  void bind_read() const;
  void clear() const;
  bool valid() const { return m_fbo != 0; }
  GLuint fbo() const { return m_fbo; }
  GLuint color_texture() const { return m_color_tex; }
  GLuint depth_texture() const { return m_depth_tex; }

 private:
  void destroy();

  int m_width = 0;
  int m_height = 0;
  GLuint m_fbo = 0;
  GLuint m_color_tex = 0;
  GLuint m_depth_tex = 0;
  GLuint m_pick_tex = 0;
};

// Composites an accumulated point buffer over the scene with uniform layer opacity.
class PointCloudCompositor {
 public:
  void ensure_initialized(QOpenGLFunctions* f);
  void composite(QOpenGLExtraFunctions* gl, GLuint dest_fbo, GLuint point_color_tex,
                 GLuint point_depth_tex, float layer_alpha, int width, int height);

 private:
  std::unique_ptr<QOpenGLShaderProgram> m_shader;
  QOpenGLVertexArrayObject m_vao;
  int m_color_loc = 0;
  int m_depth_loc = 0;
  int m_alpha_loc = 0;
  bool m_ready = false;
};
```


