

# File main.cpp

[**File List**](files.md) **>** [**gui**](dir_99d0482cf009f9d97a0877749b817f19.md) **>** [**main.cpp**](main_8cpp.md)

[Go to the documentation of this file](main_8cpp.md)


```C++
#include <QApplication>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

#include "main_window.hpp"
#include "utilities/env.hpp"
#include "utilities/filesystem.hpp"

namespace {

struct LaunchOptions {
  std::vector<fs::path> las_files;
};

static void print_usage(const char* program) {
  std::cerr << "Usage: " << program << " [options]\n"
            << "\n"
            << "Options:\n"
            << "  --las-file <path>   Pre-populate a LAS/LAZ input (repeatable)\n"
            << "  --help              Show this help\n"
            << "\n"
            << "Environment:\n"
            << "  BLAZE_INITIAL_LAS_FILES   Semicolon-separated LAS/LAZ paths\n";
}

static void append_las_path(std::vector<fs::path>& las_files, const std::string& path) {
  if (path.empty()) {
    return;
  }
  las_files.push_back(path);
}

static LaunchOptions parse_args(int argc, char* argv[]) {
  LaunchOptions opts;

  if (const char* env = blaze::get_env("BLAZE_INITIAL_LAS_FILES")) {
    std::string value = env;
    size_t start = 0;
    while (start <= value.size()) {
      const size_t end = value.find(';', start);
      const std::string part =
          value.substr(start, end == std::string::npos ? std::string::npos : end - start);
      append_las_path(opts.las_files, part);
      if (end == std::string::npos) {
        break;
      }
      start = end + 1;
    }
  }

  for (int i = 1; i < argc; ++i) {
    const std::string arg = argv[i];
    if (arg == "--help" || arg == "-h") {
      print_usage(argv[0]);
      std::exit(0);
    }
    if (arg == "--las-file") {
      if (i + 1 >= argc) {
        std::cerr << "Missing path after --las-file\n";
        print_usage(argv[0]);
        std::exit(1);
      }
      append_las_path(opts.las_files, argv[++i]);
    } else if (!arg.empty() && arg[0] == '-') {
      std::cerr << "Unknown option: " << arg << "\n";
      print_usage(argv[0]);
      std::exit(1);
    }
  }

  return opts;
}

}  // namespace

int main(int argc, char* argv[]) {
  const LaunchOptions opts = parse_args(argc, argv);

  QApplication a(argc, argv);
  QCoreApplication::setOrganizationName("Trailblaze Software");
  QCoreApplication::setApplicationName("Blaze");

  MainWindow window(opts.las_files);
  window.show();
  return QApplication::exec();
}
```


