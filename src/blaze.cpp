#include <iostream>

#include "run.hpp"

int main([[maybe_unused]] int argc, char *argv[]) {
  fs::path config_path = "config.json";
  if (argc > 1) {
    config_path = argv[1];
  }
  Config config = Config::FromFile(config_path);
  std::cout << config << std::endl;

  std::vector<fs::path> las_files;
  if (config.las_files.size() == 0) {
    std::cerr << "No LAS files specified in config.json" << std::endl;
    if (argc != 3) {
      std::cerr << "Usage: blaze <config_file> <las_file>" << std::endl;
      exit(1);
    }
    las_files.push_back(argv[1]);
  }

  ProgressBar progress_bar;
  run_with_config(config, las_files, ProgressTracker(&progress_bar));
}
