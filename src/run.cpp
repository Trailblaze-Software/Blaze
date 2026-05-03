#include "run.hpp"

#include <omp.h>

#include <filesystem>
#include <iostream>

#include "config_input/config_input.hpp"
#include "contour/contour.hpp"
#include "contour/contour_gen.hpp"
#include "crt/crt.hpp"
#include "grid/grid.hpp"
#include "io/gpkg.hpp"
#include "las/las_file.hpp"
#include "las/tile_mode.hpp"
#include "methods/water/water.hpp"
#include "printing/to_string.hpp"
#include "process.hpp"
#include "tif/tif.hpp"
#include "utilities/coordinate.hpp"
#include "utilities/filesystem.hpp"
#include "utilities/progress_tracker.hpp"
#include "utilities/timer.hpp"

void run_with_config(const Config& config, const std::vector<fs::path>& additional_las_files,
                     ProgressTracker&& tracker) {
  std::cout << "Using " << omp_get_max_threads() << " threads for processing." << std::endl;
  std::vector<fs::path> las_files = additional_las_files;
  for (const fs::path& las_file : config.las_filepaths()) {
    if (!fs::exists(las_file)) {
      Fail("LAS file " + las_file.string() + " does not exist");
    } else if (fs::is_directory(las_file)) {
      for (const fs::directory_entry& entry : fs::directory_iterator(las_file)) {
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
  double total_time = 0.01;
  for (ProcessingStep step : config.processing_steps) {
    switch (step) {
      case ProcessingStep::Tiles:
        time_ratios.push_back(0.9);
        break;
      case ProcessingStep::Combine:
        time_ratios.push_back(0.1);
        break;
    }
    total_time += time_ratios.back();
  }

  const bool tiled_mode = config.tile_size > 0.0;
  std::string tile_output_crs_wkt;
  std::vector<LASFileExtent> tile_input_extents =
      load_input_extents(las_files, config.override_crs, tile_output_crs_wkt,
                         tracker.subtracker(0.0, 0.01 / total_time));
  const TileModeInfo tile_info = detect_tile_mode_needed(tile_input_extents);
  if (tile_info.any_overlap) {
    std::cerr << "Info: Input files overlap; tile reads will pull from every overlapping input."
              << std::endl;
  }
  if (tile_info.crs_mismatch) {
    std::cerr << "Info: Input files use different CRSes; points will be reprojected into the "
              << "output CRS." << std::endl;
  }
  if (tile_info.required() && !tiled_mode) {
    std::cerr << "WARNING: overlapping / mixed-CRS inputs are being processed one-tile-per-file."
              << " For correct handling of the overlap regions, enable tiled mode by setting"
              << " 'tile_size' in the config (meters)." << std::endl;
  }

  std::vector<Tile> tiles;
  if (tiled_mode) {
    Extent2D overall = union_extent(tile_input_extents);
    tiles = compute_tiles(overall, config.tile_size, tile_input_extents);
    tracker.text_update(
        to_string("Planned ", tiles.size(), " tiles over extent ", overall, " in output CRS."));
  } else {
    tiles = tiles_per_file(tile_input_extents);
  }

  double current_time = 0.01 / total_time;
  int idx = 0;
  for (ProcessingStep step : config.processing_steps) {
    TimeFunction timer(to_string("processing step ", step));
    tracker.text_update(to_string("Processing step ", step));
    ProgressTracker step_tracker =
        tracker.subtracker(current_time, current_time + time_ratios[idx] / total_time);
    current_time += time_ratios[idx++] / total_time;
    switch (step) {
      case ProcessingStep::Tiles:
        for (size_t i = 0; i < tiles.size(); i++) {
          const Tile& tile = tiles[i];
          step_tracker.text_update("Processing tile " + std::to_string(i + 1) + " of " +
                                   std::to_string(tiles.size()) + ": " + tile.output_name());

          ProgressTracker progress_tracker =
              step_tracker.subtracker((double)i / tiles.size(), (double)(i + 1) / tiles.size());

          LASData tile_data =
              read_tile_from_inputs(tile.extent, config.border_width, tile_input_extents,
                                    tile_output_crs_wkt, progress_tracker.subtracker(0.0, 0.4));
          if (tile_data.n_points() == 0) {
            step_tracker.text_update("Tile " + tile.output_name() + " has no points; skipping.");
            continue;
          }
          // Only create the output directory once we know the tile has points.
          // Otherwise the Combine step below would pick up an empty directory
          // and emit spurious "Image ... does not exist" warnings.
          fs::path output_dir = config.output_path() / tile.output_name();
          fs::create_directories(output_dir);
          process_las_data(tile_data, output_dir, config, progress_tracker.subtracker(0.4, 1.0));
        }
        break;
      case ProcessingStep::Combine:
        std::optional<std::string> projection;

        std::vector<fs::path> combine_dirs;
        combine_dirs.reserve(tiles.size());
        for (const Tile& t : tiles) {
          fs::path d = config.output_path() / t.output_name();
          if (fs::exists(d)) combine_dirs.push_back(d);
        }

        // Combine TIFs
        fs::create_directories(config.output_path() / "combined" / "raw_vege");
        for (const std::string filename :
             {"final_img.tif", "final_img_extra_contours.tif", "ground_intensity.tif",
              "buildings.tif", "slope.tif", "vege_color.tif", "hill_shade_multi.tif",
              "filled_dem.tif", "raw_vege/canopy.tif", "raw_vege/green.tif",
              "raw_vege/smoothed_green.tif", "raw_vege/smoothed_canopy.tif"}) {
          // for (const std::string filename :
          //{"filled_dem.tif"}) {
          TimeFunction combining_timer("Combining " + filename);

          std::vector<Geo<MultiBand<FlexGrid>>> grids;

          Extent2D extent;
          std::optional<double> dx, dy;
          for (const fs::path& output_dir : combine_dirs) {
            fs::path img_path = output_dir / filename;
            if (!fs::exists(img_path)) {
              std::cerr << "Image " << img_path << " does not exist" << std::endl;
              continue;
            }
            grids.emplace_back(read_tif(img_path));
            if (!projection.has_value()) {
              projection = grids.back().projection().to_string();
            } else {
              AssertEQ(projection, grids.back().projection().to_string());
            }
            extent.grow(*grids.back().extent());
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

          size_t width = (extent.maxx - extent.minx) / (*dx);
          size_t height = (extent.maxy - extent.miny) / (std::abs(*dy));

          size_t required_memory = width * height * grids[0].size() * grids[0][0].n_bytes();
          std::cout << "Creating combined grid with dimensions " << width << "x" << height
                    << " requiring " << (double)required_memory / 1e9 << " GB" << std::endl;
          if (required_memory > 16e9) {
            std::cout << "Skipping " << filename << " due to memory requirements" << std::endl;
            continue;
          }
          Geo<MultiBand<FlexGrid>> combined_grid(
              GeoTransform(extent.minx, extent.maxy, *dx, *dy),
              GeoProjection(grids[0].projection()), grids[0].size(),
              (extent.maxx - extent.minx) / (*dx), (extent.maxy - extent.miny) / (std::abs(*dy)),
              grids[0][0].n_bytes(), grids[0][0].data_type());

          for (const auto& grid : grids) {
            combined_grid.fill_from(grid);
          }

          fs::create_directories((config.output_path() / "combined" / filename).parent_path());
          const bool is_dem = filename == "filled_dem.tif" || filename == "ground.tif" ||
                              filename == "smooth_ground.tif";
          write_to_tif(combined_grid, config.output_path() / "combined" / filename,
                       /*progress_tracker=*/std::nullopt,
                       /*include_vertical_crs=*/is_dem);

          if (filename == "filled_dem.tif") {
            GeoGrid<double> filled_dem(combined_grid.width(), combined_grid.height(),
                                       GeoTransform(combined_grid.transform()),
                                       GeoProjection(combined_grid.projection()));
            filled_dem.fill_from(combined_grid[0]);

#pragma omp parallel for
            for (size_t i = 0; i < filled_dem.height(); i++) {
              for (size_t j = 0; j < filled_dem.width(); j++) {
                if (!std::isfinite(filled_dem[{j, i}])) {
                  filled_dem[{j, i}] = 0;
                }
              }
            }

            write_to_tif(filled_dem, config.output_path() / "combined" / "filled_filled_dem.tif",
                         /*progress_tracker=*/std::nullopt, /*include_vertical_crs=*/true);

            std::vector<Stream> stream_path =
                stream_paths(filled_dem, config.water, step_tracker.subtracker(0.8, 0.9), false);

            {
              GPKGWriter writer((config.output_path() / "combined" / "streams.gpkg").string(),
                                projection.value(), "streams");
              for (const Stream& stream : stream_path) {
                writer.write_polyline(Polyline{.layer = "streams",
                                               .name = std::to_string(stream.catchment),
                                               .vertices = stream.coords},
                                      {{"catchment", stream.catchment}});
              }
            }
          }
        }

        // Combine contours
        std::map<double, std::vector<Contour>> contours_by_height;
        for (const fs::path& output_dir : combine_dirs) {
          fs::path gpkg_path = output_dir / "trimmed_contours.gpkg";
          if (!fs::exists(gpkg_path)) {
            std::cerr << "GPKG " << gpkg_path << " does not exist" << std::endl;
            continue;
          }

          std::vector<Contour> contours = read_gpkg(gpkg_path);
          for (Contour& contour : contours) {
            contours_by_height[contour.height()].push_back(contour);
          }
        }
        std::vector<Contour> joined_contours;
        for (const auto& [height, contours] : contours_by_height) {
          std::vector<Contour> jc = join_contours(contours, 5 * config.grid.contour_dem_resolution);
          for (Contour& contour : jc) {
            joined_contours.emplace_back(contour);
          }
        }
        {
          GPKGWriter writer((config.output_path() / "combined" / "contours.gpkg").string(),
                            projection.value(), "Contour");
          for (const Contour& contour : joined_contours) {
            writer.write_polyline(contour.to_polyline(config.contours),
                                  {{"elevation", contour.height()}});
          }
        }

        write_to_crt(config.output_path() / "combined" / "contours.crt");

        break;
    }
  }
}
