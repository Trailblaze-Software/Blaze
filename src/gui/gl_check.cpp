#include "gui/gl_check.hpp"

#ifndef NDEBUG

#include <iostream>

void log_gl_error(const char* kind, GLenum err, const char* file, int line, const char* expr) {
  std::cerr << "OpenGL " << kind << " " << gl_error_name(err) << " (0x" << std::hex << err
            << std::dec << ") at " << file << ":" << line;
  if (expr != nullptr && expr[0] != '\0') {
    std::cerr << ": " << expr;
  }
  std::cerr << std::endl;
}

#endif  // NDEBUG
