

# File blaze.cpp

[**File List**](files.md) **>** [**src**](dir_68267d1309a1af8e8297ef4c3efbcdba.md) **>** [**blaze.cpp**](blaze_8cpp.md)

[Go to the documentation of this file](blaze_8cpp.md)


```C++
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
    fs::path config_path;
    std::vector<fs::path> las_files;
    bool use_default_config = true;

    if (argc == 2 && is_las_file(argv[1])) {
      // Single-file mode: blaze-cli file.laz
      las_files.push_back(argv[1]);
    } else {
      if (argc > 1) {
        config_path = argv[1];
        use_default_config = false;
      }
      if (argc > 2) {
        las_files.push_back(argv[2]);
      }
    }

    // Use Config::Default() when no explicit config is given so the output
    // directory resolves to a writable location even when the default config
    // lives inside a read-only bundle or mounted DMG.
    Config config = use_default_config ? Config::Default() : Config::FromFile(config_path);
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
```


