

# File env.hpp

[**File List**](files.md) **>** [**lib**](dir_c85d3e3c5052e9ad9ce18c6863244a25.md) **>** [**utilities**](dir_f68f3bc40609949e989ead5b0b6dedfd.md) **>** [**env.hpp**](utilities_2env_8hpp.md)

[Go to the documentation of this file](utilities_2env_8hpp.md)


```C++
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
```


