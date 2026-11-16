#include <QApplication>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

#include "io/proj_data.hpp"
#include "las/crs_self_check.hpp"
#include "main_window.hpp"
#include "utilities/env.hpp"
#include "utilities/filesystem.hpp"

namespace {

struct LaunchOptions {
  std::vector<fs::path> las_files;
  bool check_crs = false;
};

static void print_usage(const char* program) {
  std::cerr << "Usage: " << program << " [options]\n"
            << "\n"
            << "Options:\n"
            << "  --las-file <path>   Pre-populate a LAS/LAZ input (repeatable)\n"
            << "  --check-crs         Check PROJ/CRS setup (and the --las-file inputs),\n"
            << "                      print a report and exit without opening a window\n"
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
    if (arg == "--check-crs") {
      opts.check_crs = true;
    } else if (arg == "--las-file") {
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
  configure_bundled_proj_data();
  const LaunchOptions opts = parse_args(argc, argv);
  if (opts.check_crs) {
    return run_crs_self_check(opts.las_files);
  }

  QApplication a(argc, argv);
  QCoreApplication::setOrganizationName("Trailblaze Software");
  QCoreApplication::setApplicationName("Blaze");

  MainWindow window(opts.las_files);
  window.show();
  return QApplication::exec();
}
