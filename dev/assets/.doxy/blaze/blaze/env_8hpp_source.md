

# File env.hpp

[**File List**](files.md) **>** [**lib**](dir_c85d3e3c5052e9ad9ce18c6863244a25.md) **>** [**testing**](dir_30341ad8f18900961f37cfbd7fe13068.md) **>** [**env.hpp**](env_8hpp.md)

[Go to the documentation of this file](env_8hpp.md)


```C++
#pragma once

#include <cstdlib>

namespace blaze::test {

// Wrapper around std::getenv that silences MSVC's C4996 "getenv is unsafe"
// warning in one place so individual tests don't need to repeat the pragma
// dance. Test code doesn't care about getenv_s; env vars here are only used to
// toggle debug/verbose behavior and to keep test artifacts.
inline const char* get_env(const char* name) {
#ifdef _WIN32
#pragma warning(push)
#pragma warning(disable : 4996)  // getenv is safe for test code
#endif
  const char* value = std::getenv(name);
#ifdef _WIN32
#pragma warning(pop)
#endif
  return value;
}

}  // namespace blaze::test
```


