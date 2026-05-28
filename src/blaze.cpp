#include <exception>
#include <iostream>

#include "config_input/config_input.hpp"
#include "run.hpp"
#include "utilities/progress_tracker.hpp"

static bool is_las_file(const fs::path& p) {
  std::string ext = p.extension().string();
  for (char& c : ext) c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
  return ext == ".las" || ext == ".laz";
}

int main([[maybe_unused]] int argc, char* argv[]) {
  try {
    fs::path config_path = AssetRetriever::get_asset("default_config.json");
    std::vector<fs::path> las_files;

    if (argc == 2 && is_las_file(argv[1])) {
      // Single-file mode: blaze-cli file.laz
      las_files.push_back(argv[1]);
    } else {
      if (argc > 1) {
        config_path = argv[1];
      }
      if (argc > 2) {
        las_files.push_back(argv[2]);
      }
    }

    Config config = Config::FromFile(config_path);
    std::cout << config << std::endl;

    if (las_files.empty() && config.las_files.size() == 0) {
      std::cerr << "No LAS files specified." << std::endl;
      std::cerr << "Usage: blaze-cli <file.laz>" << std::endl;
      std::cerr << "       blaze-cli <config.json> <file.laz>" << std::endl;
      return 1;
    }

    ProgressBar progress_bar;
    run_with_config(config, las_files, ProgressTracker(&progress_bar));
  } catch (const std::exception& e) {
    std::cerr << "Error: " << e.what() << std::endl;
    return 1;
  } catch (...) {
    std::cerr << "Unknown error occurred" << std::endl;
    return 1;
  }
  return 0;
}
