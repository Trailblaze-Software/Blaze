#include "run.hpp"

#include <iostream>

#include "config_input/config_input.hpp"
#include "contour/contour.hpp"
#include "contour/contour_gen.hpp"
#include "dxf/dxf.hpp"
#include "grid/grid.hpp"
#include "las/las_file.hpp"
#include "printing/to_string.hpp"
#include "process.hpp"
#include "tif/tif.hpp"
#include "utilities/filesystem.hpp"
#include "utilities/progress_tracker.hpp"
#include "utilities/timer.hpp"

void run_with_config(const Config &config, const std::vector<fs::path> &additional_las_files,
                     ProgressTracker &&tracker) {
  std::vector<fs::path> las_files = additional_las_files;
  for (const fs::path &las_file : config.las_filepaths()) {
    if (!fs::exists(las_file)) {
      Fail("LAS file " + las_file.string() + " does not exist");
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

  std::vector<double> time_ratios;
  double total_time = 0;
  for (ProcessingStep step : config.processing_steps) {
    switch (step) {
      case ProcessingStep::TmpBorders:
        time_ratios.push_back(0.2);
        break;
      case ProcessingStep::Tiles:
        time_ratios.push_back(0.9);
        break;
      case ProcessingStep::Combine:
        time_ratios.push_back(0.1);
        break;
    }
    total_time += time_ratios.back();
  }

  double current_time = 0;
  int idx = 0;
  for (ProcessingStep step : config.processing_steps) {
    TimeFunction timer(to_string("processing step ", step));
    tracker.text_update(to_string("Processing step ", step));
    ProgressTracker step_tracker =
        tracker.subtracker(current_time, current_time + time_ratios[idx] / total_time);
    current_time += time_ratios[idx++] / total_time;
    switch (step) {
      case ProcessingStep::TmpBorders:
        for (size_t i = 0; i < las_files.size(); i++) {
          step_tracker.set_proportion((double)i / las_files.size());
          step_tracker.text_update("Extracting borders " + std::to_string(i + 1) + " of " +
                                   std::to_string(las_files.size()) + ": " +
                                   las_files[i].filename().string());
          extract_borders(las_files[i], config.border_width.in(au::meters));
        }
        break;
      case ProcessingStep::Tiles:
        for (size_t i = 0; i < las_files.size(); i++) {
          step_tracker.text_update("Processing tile " + std::to_string(i + 1) + " of " +
                                   std::to_string(las_files.size()) + ": " +
                                   las_files[i].filename().string());
          process_las_file(las_files[i], config,
                           step_tracker.subtracker((double)i / las_files.size(),
                                                   (double)(i + 1) / las_files.size()));
        }
        break;
      case ProcessingStep::Combine:
        // Combine contours
        std::map<double, std::vector<Contour>> contours_by_height;
        for (const fs::path &las_file : las_files) {
          fs::path output_dir = config.output_path() / las_file.stem();
          fs::path dxf_path = output_dir / "trimmed_contours.dxf";
          if (!fs::exists(dxf_path)) {
            std::cerr << "DXF " << dxf_path << " does not exist" << std::endl;
            continue;
          }

          std::vector<Contour> contours = read_dxf(dxf_path);
          for (Contour &contour : contours) {
            contours_by_height[contour.height()].push_back(contour);
          }
        }
        std::vector<Contour> joined_contours;
        for (const auto &[height, contours] : contours_by_height) {
          std::vector<Contour> jc = join_contours(contours);
          for (Contour &contour : jc) {
            joined_contours.emplace_back(contour);
          }
        }
        write_to_dxf(joined_contours, config.output_path() / "combined" / "contours.dxf",
                     config.contours);
        write_to_crt(config.output_path() / "combined" / "contours.crt");

        // Combine TIFs
        for (const std::string filename :
             {"final_img.tif", "final_img_extra_contours.tif", "ground_intensity.tif",
              "buildings.tif", "slope.tif", "vege_color.tif", "hill_shade_multi.tif",
              "filled_dem.tif"}) {
          TimeFunction combining_timer("Combining " + filename);

          std::vector<Geo<MultiBand<FlexGrid>>> grids;

          pdal::BOX2D extent;
          std::optional<double> dx, dy;
          for (const fs::path &las_file : las_files) {
            fs::path output_dir = config.output_path() / las_file.stem();
            fs::path img_path = output_dir / filename;
            if (!fs::exists(img_path)) {
              std::cerr << "Image " << img_path << " does not exist" << std::endl;
              continue;
            }
            grids.emplace_back(read_tif(img_path));
            extent.grow(grids.back().extent());
            if (!dx.has_value()) {
              dx = grids.back().transform().dx();
              dy = grids.back().transform().dy();
            } else {
              if (dx != grids.back().transform().dx() || dy != grids.back().transform().dy()) {
                Fail("dx or dy mismatch");
              }
            }
          }

          AssertGE(grids.size(), 1);
          AssertGE(grids[0].size(), 1);

          Geo<MultiBand<FlexGrid>> combined_grid(
              GeoTransform(extent.minx, extent.maxy, *dx, *dy),
              GeoProjection(grids[0].projection()), grids[0].size(),
              (extent.maxx - extent.minx) / (*dx), (extent.maxy - extent.miny) / (std::abs(*dy)),
              grids[0][0].n_bytes(), grids[0][0].data_type());

          for (const auto &grid : grids) {
            combined_grid.fill_from(grid);
          }

          fs::create_directories(config.output_path() / "combined");
          write_to_tif(combined_grid, config.output_path() / "combined" / filename);

          if (filename == "filled_dem.tif") {
            GeoGrid<double> filled_dem(combined_grid.width(), combined_grid.height(),
                                       GeoTransform(combined_grid.transform()),
                                       GeoProjection(combined_grid.projection()));
            filled_dem.fill_from(combined_grid[0]);
            std::vector<Stream> stream_path = stream_paths(filled_dem, config.water, true);
            write_to_dxf(stream_path, config.output_path() / "combined" / "streams.dxf", "streams");
          }
        }
        break;
    }
  }
}
