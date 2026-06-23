#include "gui/point_cloud_framebuffer.hpp"

#include <array>
#include <iostream>

#include "gui/gl_check.hpp"
#include "lib/assert/assert.hpp"

namespace {

const char* COMPOSITE_VERTEX_SHADER = R"(
    #version 330 core
    out vec2 texCoord;
    void main() {
        const vec2 positions[3] = vec2[](
            vec2(-1.0, -1.0),
            vec2( 3.0, -1.0),
            vec2(-1.0,  3.0));
        texCoord = 0.5 * positions[gl_VertexID] + 0.5;
        gl_Position = vec4(positions[gl_VertexID], 0.0, 1.0);
    }
)";

const char* COMPOSITE_FRAGMENT_SHADER = R"(
    #version 330 core
    in vec2 texCoord;
    uniform sampler2D pointColor;
    uniform sampler2D pointDepth;
    uniform float layerAlpha;
    out vec4 fragColor;
    void main() {
        float depth = texture(pointDepth, texCoord).r;
        if (depth >= 0.99999) {
            discard;
        }
        vec4 point = texture(pointColor, texCoord);
        float alpha = clamp(point.a * layerAlpha, 0.0, 1.0);
        gl_FragDepth = depth;
        fragColor = vec4(point.rgb * alpha, alpha);
    }
)";

}  // namespace

void PointCloudFramebuffer::destroy() {
  // May run at teardown after the widget has called doneCurrent(); without a
  // current context there is nothing (and no safe way) to delete — the GL
  // objects are freed when the context itself is destroyed.
  auto* context = QOpenGLContext::currentContext();
  if (m_fbo != 0 && context) {
    auto* f = context->functions();
    CHECK_GL(f->glDeleteFramebuffers(1, &m_fbo));
    CHECK_GL(f->glDeleteTextures(1, &m_color_tex));
    CHECK_GL(f->glDeleteTextures(1, &m_depth_tex));
    CHECK_GL(f->glDeleteTextures(1, &m_pick_tex));
  }
  m_fbo = 0;
  m_color_tex = 0;
  m_depth_tex = 0;
  m_pick_tex = 0;
  m_width = 0;
  m_height = 0;
}

void PointCloudFramebuffer::ensure_size(int width, int height) {
  if (width <= 0 || height <= 0) {
    return;
  }
  if (valid() && m_width == width && m_height == height) {
    return;
  }
  destroy();

  auto* context = QOpenGLContext::currentContext();
  if (!context) {
    return;
  }
  auto* f = context->functions();
  m_width = width;
  m_height = height;

  CHECK_GL(f->glGenTextures(1, &m_color_tex));
  CHECK_GL(f->glBindTexture(GL_TEXTURE_2D, m_color_tex));
  CHECK_GL(f->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
  CHECK_GL(f->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
  CHECK_GL(f->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
  CHECK_GL(f->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
  CHECK_GL(f->glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE,
                           nullptr));

  CHECK_GL(f->glGenTextures(1, &m_depth_tex));
  CHECK_GL(f->glBindTexture(GL_TEXTURE_2D, m_depth_tex));
  CHECK_GL(f->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
  CHECK_GL(f->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
  CHECK_GL(f->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
  CHECK_GL(f->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
  CHECK_GL(f->glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32F, width, height, 0,
                           GL_DEPTH_COMPONENT, GL_FLOAT, nullptr));

  // Pick attachment: RG32UI — .r = global index + 1, .g = layer slot.
  auto* ef = context->extraFunctions();
  CHECK_GL(ef->glGenTextures(1, &m_pick_tex));
  CHECK_GL(ef->glBindTexture(GL_TEXTURE_2D, m_pick_tex));
  CHECK_GL(ef->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
  CHECK_GL(ef->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
  CHECK_GL(ef->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
  CHECK_GL(ef->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
  CHECK_GL(ef->glTexImage2D(GL_TEXTURE_2D, 0, GL_RG32UI, width, height, 0, GL_RG_INTEGER,
                            GL_UNSIGNED_INT, nullptr));

  CHECK_GL(f->glGenFramebuffers(1, &m_fbo));
  CHECK_GL(f->glBindFramebuffer(GL_FRAMEBUFFER, m_fbo));
  CHECK_GL(f->glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,
                                     m_color_tex, 0));
  CHECK_GL(f->glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D,
                                     m_depth_tex, 0));
  CHECK_GL(f->glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D,
                                     m_pick_tex, 0));
  // Attachment 1 is GL_RG32UI — compositor only samples attachment 0 + depth.
  GLenum bufs[] = {GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1};
  CHECK_GL(ef->glDrawBuffers(2, bufs));

  GLenum status = GL_FRAMEBUFFER_UNDEFINED;
  CHECK_GL(status = ef->glCheckFramebufferStatus(GL_FRAMEBUFFER));
  Assert(status == GL_FRAMEBUFFER_COMPLETE, "FBO not complete after adding pick attachment");

  CHECK_GL(f->glBindFramebuffer(GL_FRAMEBUFFER, 0));
  CHECK_GL(f->glBindTexture(GL_TEXTURE_2D, 0));
}

void PointCloudFramebuffer::bind() const {
  if (m_fbo == 0) {
    return;
  }
  auto* f = QOpenGLContext::currentContext()->functions();
  CHECK_GL(f->glBindFramebuffer(GL_FRAMEBUFFER, m_fbo));
  // Ensure both draw buffers are active so MRT writes to both colour
  // attachments (0 = RGBA8 colour, 1 = RG32UI pick ID).
  auto* ef = QOpenGLContext::currentContext()->extraFunctions();
  if (ef) {
    GLenum bufs[] = {GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1};
    CHECK_GL(ef->glDrawBuffers(2, bufs));
  }
  // Blending with an integer colour attachment is INVALID_OPERATION.
  CHECK_GL(f->glDisable(GL_BLEND));
}

void PointCloudFramebuffer::bind_read() const {
  if (m_fbo != 0) {
    auto* f = QOpenGLContext::currentContext()->functions();
    CHECK_GL(f->glBindFramebuffer(GL_READ_FRAMEBUFFER, m_fbo));
  }
}

void PointCloudFramebuffer::clear() const {
  if (m_fbo == 0) {
    return;
  }
  auto* f = QOpenGLContext::currentContext()->functions();
  auto* ef = QOpenGLContext::currentContext()->extraFunctions();
  if (!ef) {
    return;
  }

  // Caller should have bound this FBO; ensure draw-buffer state is correct.
  GLenum bufs[] = {GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1};
  CHECK_GL(ef->glDrawBuffers(2, bufs));
  CHECK_GL(f->glDisable(GL_BLEND));

  // Clear each colour attachment individually.  glClear(GL_COLOR_BUFFER_BIT)
  // would generate GL_INVALID_OPERATION because attachment 1 is GL_RG32UI
  // (integer) — the spec forbids glClear when any draw buffer is integer.
  const GLfloat zeros[4] = {0.0f, 0.0f, 0.0f, 0.0f};
  CHECK_GL(ef->glClearBufferfv(GL_COLOR, 0, zeros));
  const GLuint zero_u[4] = {0, 0, 0, 0};
  CHECK_GL(ef->glClearBufferuiv(GL_COLOR, 1, zero_u));

  CHECK_GL(f->glClearDepthf(1.0f));
  CHECK_GL(f->glClear(GL_DEPTH_BUFFER_BIT));
}

void PointCloudCompositor::ensure_initialized(QOpenGLFunctions* f) {
  if (m_ready) {
    return;
  }
  m_shader = std::make_unique<QOpenGLShaderProgram>();
  if (!m_shader->addShaderFromSourceCode(QOpenGLShader::Vertex, COMPOSITE_VERTEX_SHADER) ||
      !m_shader->addShaderFromSourceCode(QOpenGLShader::Fragment, COMPOSITE_FRAGMENT_SHADER) ||
      !m_shader->link()) {
    std::cerr << "Point compositor shader error: " << m_shader->log().toStdString() << std::endl;
    m_shader.reset();
    return;
  }
  m_color_loc = m_shader->uniformLocation("pointColor");
  m_depth_loc = m_shader->uniformLocation("pointDepth");
  m_alpha_loc = m_shader->uniformLocation("layerAlpha");
  m_vao.create();
  (void)f;
  m_ready = true;
}

void PointCloudCompositor::composite(QOpenGLExtraFunctions* gl, GLuint dest_fbo,
                                     GLuint point_color_tex, GLuint point_depth_tex,
                                     float layer_alpha, int width, int height) {
  if (point_color_tex == 0 || point_depth_tex == 0 || layer_alpha <= 0.0f) {
    return;
  }
  ensure_initialized(gl);
  if (!m_ready || !m_shader) {
    return;
  }

  CHECK_GL(gl->glBindFramebuffer(GL_FRAMEBUFFER, dest_fbo));
  CHECK_GL(gl->glViewport(0, 0, width, height));
  CHECK_GL(gl->glEnable(GL_BLEND));
  CHECK_GL(gl->glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
  CHECK_GL(gl->glEnable(GL_DEPTH_TEST));
  CHECK_GL(gl->glDepthFunc(GL_LESS));
  CHECK_GL(gl->glDepthMask(GL_TRUE));

  m_shader->bind();
  CHECK_GL_AFTER();
  CHECK_GL(gl->glActiveTexture(GL_TEXTURE0));
  CHECK_GL(gl->glBindTexture(GL_TEXTURE_2D, point_color_tex));
  m_shader->setUniformValue(m_color_loc, 0);
  CHECK_GL(gl->glActiveTexture(GL_TEXTURE1));
  CHECK_GL(gl->glBindTexture(GL_TEXTURE_2D, point_depth_tex));
  m_shader->setUniformValue(m_depth_loc, 1);
  m_shader->setUniformValue(m_alpha_loc, layer_alpha);

  QOpenGLVertexArrayObject::Binder vao_binder(&m_vao);
  CHECK_GL(gl->glDrawArrays(GL_TRIANGLES, 0, 3));

  m_shader->release();
  CHECK_GL_AFTER();
  CHECK_GL(gl->glBindTexture(GL_TEXTURE_2D, 0));
}
