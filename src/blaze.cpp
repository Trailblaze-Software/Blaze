#include <iostream>

#include "config_input/config_input.hpp"
#include "run.hpp"
#include "utilities/progress_tracker.hpp"

int main([[maybe_unused]] int argc, char *argv[]) {
  fs::path config_path = AssetRetriever::get_asset("default_config.json");
  if (argc > 1) {
    config_path = argv[1];
  }
  Config config = Config::FromFile(config_path);
  std::cout << config << std::endl;

  std::vector<fs::path> las_files;
  if (argc > 2) {
    las_files.push_back(argv[2]);
  } else if (config.las_files.size() == 0) {
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
