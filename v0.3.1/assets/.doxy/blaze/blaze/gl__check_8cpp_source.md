

# File gl\_check.cpp

[**File List**](files.md) **>** [**gui**](dir_99d0482cf009f9d97a0877749b817f19.md) **>** [**gl\_check.cpp**](gl__check_8cpp.md)

[Go to the documentation of this file](gl__check_8cpp.md)


```C++
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
```


