

# File filesystem.hpp

[**File List**](files.md) **>** [**lib**](dir_c85d3e3c5052e9ad9ce18c6863244a25.md) **>** [**utilities**](dir_f68f3bc40609949e989ead5b0b6dedfd.md) **>** [**filesystem.hpp**](filesystem_8hpp.md)

[Go to the documentation of this file](filesystem_8hpp.md)


```C++
// Check if the compiler supports C++17 or later
#if __cplusplus >= 201703L || defined(_HAS_CXX17) || defined(_MSC_VER) && _MSVC_LANG >= 201703L
#include <filesystem>
namespace fs = std::filesystem;
#elif __cplusplus >= 201402L  // Check if the compiler supports C++14
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;
#else
#error "No filesystem support"
#endif
```


