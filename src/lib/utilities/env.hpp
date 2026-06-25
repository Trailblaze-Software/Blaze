#pragma once

#include <cstdlib>

namespace blaze {

// Wrapper around std::getenv that silences MSVC's C4996 "getenv is unsafe" warning.
inline const char* get_env(const char* name) {
#ifdef _WIN32
#pragma warning(push)
#pragma warning(disable : 4996)
#endif
  const char* value = std::getenv(name);
#ifdef _WIN32
#pragma warning(pop)
#endif
  return value;
}

}  // namespace blaze
