#include "gui/point_cloud_framebuffer.hpp"

#include <array>

namespace {

const char* kFullscreenTriangleVS = R"(
    #version 330 core
    void main() {
        const vec2 positions[3] = vec2[](
            vec2(-1.0, -1.0), vec2(3.0, -1.0), vec2(-1.0, 3.0));
        gl_Position = vec4(positions[gl_VertexID], 0.0, 1.0);
    }
)";

const char* kCompositeVertexShader = R"(
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

const char* kCompositeFragmentShader = R"(
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
        vec3 rgb = texture(pointColor, texCoord).rgb;
        gl_FragDepth = depth;
        fragColor = vec4(rgb * layerAlpha, layerAlpha);
    }
)";

}  // namespace

void PointCloudFramebuffer::destroy() {
  if (m_fbo != 0) {
    auto* f = QOpenGLContext::currentContext()->functions();
    f->glDeleteFramebuffers(1, &m_fbo);
    f->glDeleteTextures(1, &m_color_tex);
    f->glDeleteTextures(1, &m_depth_tex);
    m_fbo = 0;
    m_color_tex = 0;
    m_depth_tex = 0;
  }
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

  auto* f = QOpenGLContext::currentContext()->functions();
  m_width = width;
  m_height = height;

  f->glGenTextures(1, &m_color_tex);
  f->glBindTexture(GL_TEXTURE_2D, m_color_tex);
  f->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  f->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  f->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  f->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  f->glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

  f->glGenTextures(1, &m_depth_tex);
  f->glBindTexture(GL_TEXTURE_2D, m_depth_tex);
  f->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  f->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  f->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  f->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  f->glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32F, width, height, 0, GL_DEPTH_COMPONENT,
                  GL_FLOAT, nullptr);

  f->glGenFramebuffers(1, &m_fbo);
  f->glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
  f->glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_color_tex, 0);
  f->glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_depth_tex, 0);
  f->glBindFramebuffer(GL_FRAMEBUFFER, 0);
  f->glBindTexture(GL_TEXTURE_2D, 0);
}

void PointCloudFramebuffer::bind() const {
  if (m_fbo != 0) {
    QOpenGLContext::currentContext()->functions()->glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
  }
}

void PointCloudFramebuffer::clear() const {
  if (m_fbo == 0) {
    return;
  }
  auto* f = QOpenGLContext::currentContext()->functions();
  f->glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  f->glClearDepthf(1.0f);
  f->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void PointCloudCompositor::ensure_initialized(QOpenGLFunctions* f) {
  if (m_ready) {
    return;
  }
  m_shader = std::make_unique<QOpenGLShaderProgram>();
  m_shader->addShaderFromSourceCode(QOpenGLShader::Vertex, kCompositeVertexShader);
  m_shader->addShaderFromSourceCode(QOpenGLShader::Fragment, kCompositeFragmentShader);
  m_shader->link();
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

  gl->glBindFramebuffer(GL_FRAMEBUFFER, dest_fbo);
  gl->glViewport(0, 0, width, height);
  gl->glEnable(GL_BLEND);
  gl->glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  gl->glEnable(GL_DEPTH_TEST);
  gl->glDepthFunc(GL_LESS);
  gl->glDepthMask(GL_TRUE);

  m_shader->bind();
  gl->glActiveTexture(GL_TEXTURE0);
  gl->glBindTexture(GL_TEXTURE_2D, point_color_tex);
  m_shader->setUniformValue(m_color_loc, 0);
  gl->glActiveTexture(GL_TEXTURE1);
  gl->glBindTexture(GL_TEXTURE_2D, point_depth_tex);
  m_shader->setUniformValue(m_depth_loc, 1);
  m_shader->setUniformValue(m_alpha_loc, layer_alpha);

  QOpenGLVertexArrayObject::Binder vao_binder(&m_vao);
  gl->glDrawArrays(GL_TRIANGLES, 0, 3);

  m_shader->release();
  gl->glBindTexture(GL_TEXTURE_2D, 0);
}

void PointCloudCompositor::fade_points_fbo(QOpenGLExtraFunctions* gl, GLuint points_fbo,
                                           float decay, int width, int height) {
  if (points_fbo == 0 || decay >= 1.0f) return;
  // Simple full-screen pass: multiply existing content by decay using a
  // trivial fragment shader and the compositor's existing VAO.
  static const char* kFadeFS = R"(
      #version 330 core
      uniform float uDecay;
      out vec4 fragColor;
      void main() { fragColor = vec4(vec3(uDecay), 1.0); }
  )";
  static QOpenGLShaderProgram* s_fade_shader = nullptr;
  if (!s_fade_shader) {
    s_fade_shader = new QOpenGLShaderProgram();
    s_fade_shader->addShaderFromSourceCode(QOpenGLShader::Vertex, kFullscreenTriangleVS);
    s_fade_shader->addShaderFromSourceCode(QOpenGLShader::Fragment, kFadeFS);
    s_fade_shader->link();
  }

  gl->glBindFramebuffer(GL_FRAMEBUFFER, points_fbo);
  gl->glViewport(0, 0, width, height);
  gl->glEnable(GL_BLEND);
  gl->glBlendFunc(GL_DST_COLOR, GL_ZERO);  // multiply dst by src color
  gl->glDisable(GL_DEPTH_TEST);

  s_fade_shader->bind();
  s_fade_shader->setUniformValue("uDecay", decay);
  QOpenGLVertexArrayObject::Binder vao_binder(&m_vao);
  gl->glDrawArrays(GL_TRIANGLES, 0, 3);
  s_fade_shader->release();
}
