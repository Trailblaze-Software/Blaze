#include <filesystem>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <pdal/io/BufferReader.hpp>
#include <pdal/io/LasHeader.hpp>
#include <pdal/io/LasReader.hpp>
#include <pdal/pdal.hpp>
#include <pdal/util/Bounds.hpp>

#include "config_input/config_input.hpp"
#include "las/las_file.hpp"
#include "process.hpp"
#include "tif/tif.hpp"
#include "utilities/timer.hpp"

int main([[maybe_unused]] int argc, char *argv[]) {
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
            std::cerr << "Ignoring file " << entry.path() << " with extension "
                      << entry.path().extension() << std::endl;
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
          extract_borders(las_file, config.border_width.in(au::meters));
        }
        break;
      case ProcessingStep::Tiles:
        for (const fs::path &las_file : las_files) {
          process_las_file(las_file, config);
        }
        break;
      case ProcessingStep::Combine:
        for (const std::string filename : {"final_img.tif", "ground_intensity.tif", "buildings.tif",
                                           "slope.tif", "vege_color.tif", "hill_shade_multi.tif"}) {
          TimeFunction timer("Combining " + filename);
          std::vector<GeoGrid<RGBColor>> grids;

          pdal::BOX2D extent;
          std::optional<double> dx, dy;
          for (const fs::path &las_file : las_files) {
            fs::path output_dir = config.output_directory / las_file;
            fs::path img_path = output_dir / filename;
            if (!fs::exists(img_path)) {
              std::cerr << "Image " << img_path << " does not exist" << std::endl;
              continue;
            }
            grids.emplace_back(read_tif(img_path));
            extent.grow(grids.back().extent());
            std::cout << "Extent: " << grids.back().extent() << " grown: " << extent << std::endl;
            if (!dx.has_value()) {
              dx = grids.back().transform().dx();
              dy = grids.back().transform().dy();
            } else {
              if (dx != grids.back().transform().dx() || dy != grids.back().transform().dy()) {
                std::cerr << "dx or dy mismatch" << std::endl;
                exit(1);
              }
            }
          }

          GeoGrid<RGBColor> combined_grid((extent.maxx - extent.minx) / (*dx),
                                          (extent.maxy - extent.miny) / (std::abs(*dy)),
                                          GeoTransform(extent.minx, extent.maxy, *dx, *dy),
                                          GeoProjection(grids[0].projection()));
          for (const GeoGrid<RGBColor> &grid : grids) {
            combined_grid.fill_from(grid);
          }

          fs::create_directories(config.output_directory / "combined");
          write_to_tif(combined_grid, config.output_directory / "combined" / filename);
        }

        break;
    }
  }
}
