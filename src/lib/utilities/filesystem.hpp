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
