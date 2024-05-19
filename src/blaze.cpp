#include <filesystem>
#include <iostream>
#include <pdal/io/BufferReader.hpp>
#include <pdal/io/LasHeader.hpp>
#include <pdal/io/LasReader.hpp>
#include <pdal/pdal.hpp>
#include <opencv2/opencv.hpp>

#include "config_input/config_input.hpp"
#include "las/las_file.hpp"
#include "process.hpp"

int main([[maybe_unused]]int argc, char *argv[]) {

  Config config = Config::FromFile("config.json");
  std::cout << config << std::endl;

  std::vector<fs::path> las_files;
  if (config.las_files.size() == 0) {
    std::cerr << "No LAS files specified in config.json" << std::endl;
    if (argc != 2) {
      std::cerr << "Usage: blaze <las_file>" << std::endl;
      exit(1);
    }
    las_files.push_back(argv[1]);
  } else {
    for (const fs::path &las_file : config.las_files) {
      if (!fs::exists(las_file)) {
        std::cerr << "LAS file " << las_file << " does not exist" << std::endl;
        exit(1);
      } else if (fs::is_directory(las_file)) {
        for (const fs::directory_entry &entry : fs::directory_iterator(las_file)) {
          if (entry.path().extension() == ".las" || entry.path().extension() == ".laz") {
            las_files.push_back(entry.path());
          } else {
            std::cerr << "Ignoring file " << entry.path() << " with extension " << entry.path().extension() << std::endl;
          }
        }
      } else {
        las_files.push_back(las_file);
      }
    }
  }

  for (ProcessingStep step : config.processing_steps) {
    TimeFunction timer("processing step " + (std::string)json(step));
    switch (step) {
      case ProcessingStep::TmpBorders:
        for (const fs::path &las_file : las_files) {
          extract_borders(las_file, 100);
        }
        break;
      case ProcessingStep::Tiles:
        for (const fs::path &las_file : las_files) {
          process_las_file(las_file, config);
        }
        break;
      case ProcessingStep::Combine:
        std::cerr << "Combine processing step is not implemented" << std::endl;
        break;
    }
  }
}
