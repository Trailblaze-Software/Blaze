#pragma once

#include <QOpenGLContext>
#include <QOpenGLFunctions>

inline const char* gl_error_name(GLenum err) {
  switch (err) {
    case GL_NO_ERROR:
      return "GL_NO_ERROR";
    case GL_INVALID_ENUM:
      return "GL_INVALID_ENUM";
    case GL_INVALID_VALUE:
      return "GL_INVALID_VALUE";
    case GL_INVALID_OPERATION:
      return "GL_INVALID_OPERATION";
    case GL_OUT_OF_MEMORY:
      return "GL_OUT_OF_MEMORY";
    case GL_INVALID_FRAMEBUFFER_OPERATION:
      return "GL_INVALID_FRAMEBUFFER_OPERATION";
    default:
      return "GL_UNKNOWN_ERROR";
  }
}

#ifdef NDEBUG
#define CHECK_GL(expr) expr
#define CHECK_GL_AFTER() ((void)0)
#else
void log_gl_error(const char* kind, GLenum err, const char* file, int line, const char* expr);

inline void drain_gl_errors(QOpenGLFunctions* f, const char* kind, const char* file, int line,
                            const char* expr) {
  if (!f) {
    return;
  }
  GLenum err;
  while ((err = f->glGetError()) != GL_NO_ERROR) {
    log_gl_error(kind, err, file, line, expr);
  }
}

#define CHECK_GL_AFTER()                                                                \
  do {                                                                                  \
    if (auto* _ctx = QOpenGLContext::currentContext()) {                                \
      drain_gl_errors(_ctx->functions(), "pending error", __FILE__, __LINE__, nullptr); \
    }                                                                                   \
  } while (0)

#define CHECK_GL(expr)                                                                \
  do {                                                                                \
    if (auto* _ctx = QOpenGLContext::currentContext()) {                              \
      drain_gl_errors(_ctx->functions(), "pending error", __FILE__, __LINE__, #expr); \
    }                                                                                 \
    expr;                                                                             \
    if (auto* _ctx = QOpenGLContext::currentContext()) {                              \
      drain_gl_errors(_ctx->functions(), "error", __FILE__, __LINE__, #expr);         \
    }                                                                                 \
  } while (0)
#endif
