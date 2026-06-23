#pragma once

#include <QOpenGLContext>
#include <QOpenGLExtraFunctions>
#include <QOpenGLFramebufferObject>
#include <memory>

#include "gui/gl_check.hpp"

// Off-screen color+depth target for the (non-point) scene layers. It is cleared
// and fully redrawn every non-incremental frame, then blitted to the widget's
// default framebuffer. The point cloud uses a separate PointCloudFramebuffer,
// which is the buffer that accumulates points across incremental frames.
class SceneFramebuffer {
 public:
  void ensure_size(int width, int height) {
    if (width <= 0 || height <= 0) {
      return;
    }
    if (m_fbo && m_fbo->width() == width && m_fbo->height() == height) {
      return;
    }
    QOpenGLFramebufferObjectFormat format;
    format.setAttachment(QOpenGLFramebufferObject::CombinedDepthStencil);
    format.setInternalTextureFormat(GL_RGBA8);
    m_fbo = std::make_unique<QOpenGLFramebufferObject>(width, height, format);
  }

  bool valid() const { return m_fbo && m_fbo->isValid(); }

  void bind() const {
    if (m_fbo) {
      m_fbo->bind();
      CHECK_GL_AFTER();
    }
  }

  // QOpenGLWidget does not render to FBO 0; blit to its defaultFramebufferObject().
  void blit_to_widget_fbo(GLuint widget_fbo, int width, int height) const {
    if (!m_fbo || widget_fbo == 0) {
      return;
    }
    auto* gl = QOpenGLContext::currentContext()->extraFunctions();
    if (!gl) {
      return;
    }
    CHECK_GL(gl->glBindFramebuffer(GL_READ_FRAMEBUFFER, m_fbo->handle()));
    CHECK_GL(gl->glBindFramebuffer(GL_DRAW_FRAMEBUFFER, widget_fbo));
    CHECK_GL(gl->glBlitFramebuffer(0, 0, width, height, 0, 0, width, height,
                                   GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT, GL_NEAREST));
    CHECK_GL(gl->glBindFramebuffer(GL_DRAW_FRAMEBUFFER, widget_fbo));
  }

 private:
  std::unique_ptr<QOpenGLFramebufferObject> m_fbo;
};
