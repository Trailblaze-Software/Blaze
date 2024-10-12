// Check if the compiler supports C++17 or later
#if __cplusplus >= 201703L || _HAS_CXX17
#include <filesystem>
namespace fs = std::filesystem;
#elif __cplusplus >= 201402L  // Check if the compiler supports C++14
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;
#else
#error "No filesystem support"
#endif
