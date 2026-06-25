

# File scene\_framebuffer.cpp

[**File List**](files.md) **>** [**gui**](dir_99d0482cf009f9d97a0877749b817f19.md) **>** [**scene\_framebuffer.cpp**](scene__framebuffer_8cpp.md)

[Go to the documentation of this file](scene__framebuffer_8cpp.md)


```C++
#include "gui/scene_framebuffer.hpp"

#include <QOpenGLShader>
#include <iostream>

#include "gui/gl_check.hpp"

namespace {

const char* SCENE_COMPOSITE_VERTEX_SHADER = R"(
    #version 330 core
    out vec2 tex_coord;
    void main() {
        const vec2 positions[3] = vec2[](
            vec2(-1.0, -1.0),
            vec2( 3.0, -1.0),
            vec2(-1.0,  3.0));
        tex_coord = 0.5 * positions[gl_VertexID] + 0.5;
        gl_Position = vec4(positions[gl_VertexID], 0.0, 1.0);
    }
)";

const char* SCENE_COMPOSITE_FRAGMENT_SHADER = R"(
    #version 330 core
    in vec2 tex_coord;
    uniform sampler2D scene_color;
    uniform vec3 background_color;
    out vec4 frag_color;
    void main() {
        vec4 scene = texture(scene_color, tex_coord);
        vec3 straight_rgb = scene.a > 1e-5 ? scene.rgb / scene.a : vec3(0.0);
        frag_color = vec4(mix(background_color, straight_rgb, scene.a), 1.0);
    }
)";

}  // namespace

void SceneFramebuffer::ensure_compositor(QOpenGLFunctions* f) {
  if (m_compositor_ready) {
    return;
  }
  m_compositor_shader = std::make_unique<QOpenGLShaderProgram>();
  if (!m_compositor_shader->addShaderFromSourceCode(QOpenGLShader::Vertex,
                                                    SCENE_COMPOSITE_VERTEX_SHADER) ||
      !m_compositor_shader->addShaderFromSourceCode(QOpenGLShader::Fragment,
                                                    SCENE_COMPOSITE_FRAGMENT_SHADER) ||
      !m_compositor_shader->link()) {
    std::cerr << "Scene compositor shader error: " << m_compositor_shader->log().toStdString()
              << std::endl;
    m_compositor_shader.reset();
    return;
  }
  m_scene_color_loc = m_compositor_shader->uniformLocation("scene_color");
  m_background_color_loc = m_compositor_shader->uniformLocation("background_color");
  m_compositor_vao.create();
  (void)f;
  m_compositor_ready = true;
}

void SceneFramebuffer::composite_to_widget_fbo(QOpenGLExtraFunctions* gl, GLuint widget_fbo,
                                               int width, int height) {
  if (!m_fbo || widget_fbo == 0) {
    return;
  }
  ensure_compositor(gl);
  if (!m_compositor_ready || !m_compositor_shader) {
    blit_to_widget_fbo(widget_fbo, width, height);
    return;
  }

  CHECK_GL(gl->glBindFramebuffer(GL_FRAMEBUFFER, widget_fbo));
  CHECK_GL(gl->glViewport(0, 0, width, height));
  CHECK_GL(gl->glDisable(GL_BLEND));
  CHECK_GL(gl->glDisable(GL_DEPTH_TEST));

  m_compositor_shader->bind();
  CHECK_GL_AFTER();
  CHECK_GL(gl->glActiveTexture(GL_TEXTURE0));
  CHECK_GL(gl->glBindTexture(GL_TEXTURE_2D, m_fbo->texture()));
  m_compositor_shader->setUniformValue(m_scene_color_loc, 0);
  m_compositor_shader->setUniformValue(m_background_color_loc, 0.2f, 0.2f, 0.2f);

  QOpenGLVertexArrayObject::Binder vao_binder(&m_compositor_vao);
  CHECK_GL(gl->glDrawArrays(GL_TRIANGLES, 0, 3));

  m_compositor_shader->release();
  CHECK_GL_AFTER();
  CHECK_GL(gl->glBindTexture(GL_TEXTURE_2D, 0));
  CHECK_GL(gl->glEnable(GL_DEPTH_TEST));
}
```


