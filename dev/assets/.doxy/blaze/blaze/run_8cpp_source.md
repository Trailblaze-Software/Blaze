

# File run.cpp

[**File List**](files.md) **>** [**src**](dir_68267d1309a1af8e8297ef4c3efbcdba.md) **>** [**run.cpp**](run_8cpp.md)

[Go to the documentation of this file](run_8cpp.md)


```C++
#include "run.hpp"

#include <omp.h>

#include <array>
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
#include "utilities/trace_recorder.hpp"
#include "vegetation/vegetation_polygon.hpp"

void run_with_config(const Config& config, const std::vector<fs::path>& additional_las_files,
                     ProgressTracker&& progress_tracker_param) {
  blaze::trace::RecordTrace timing_trace(config.output_path() / "timing_trace.json");
  ProgressTracker progress_tracker = SUBTRACKER_HIDDEN(0.0, 1.0, progress_tracker_param);
  START_TRACKER(to_string("Using ", omp_get_max_threads(), " threads for processing."));
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

  // Fraction of the overall progress budget allotted to the initial
  // "load input extents" pass; the rest is split across processing steps.
  constexpr double LOAD_EXTENTS_TIME = 0.001;

  std::vector<double> time_ratios;
  double total_time = LOAD_EXTENTS_TIME;
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
                         SUBTRACKER_HIDDEN(0.0, LOAD_EXTENTS_TIME / total_time));
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
    progress_tracker.text_update(
        to_string("Planned ", tiles.size(), " tiles over extent ", overall, " in output CRS."));
  } else {
    tiles = tiles_per_file(tile_input_extents);
  }

  // Collected during the Tiles step; deleted after all steps complete so that
  // a subsequent Combine step can still read from them.
  std::vector<fs::path> processed_tile_dirs;

  double current_time = LOAD_EXTENTS_TIME / total_time;
  int idx = 0;
  for (ProcessingStep step : config.processing_steps) {
    ProgressTracker step_tracker = SUBTRACKER_HIDDEN(
        current_time, current_time + time_ratios[idx] / total_time, progress_tracker);
    START_TRACKER(step_tracker,
                  step == ProcessingStep::Tiles ? "processing tiles" : "combining tiles");
    current_time += time_ratios[idx++] / total_time;
    switch (step) {
      case ProcessingStep::Tiles: {
        for (size_t i = 0; i < tiles.size(); i++) {
          const Tile& tile = tiles[i];
          const std::string tile_name =
              to_string("tile ", i + 1, "/", tiles.size(), ": ", tile.output_name());
          ProgressTracker tile_tracker =
              SUBTRACKER_VISIBLE(static_cast<double>(i) / tiles.size(),
                                 static_cast<double>(i + 1) / tiles.size(), step_tracker);
          START_TRACKER(tile_tracker, tile_name);

          LASData tile_data =
              read_tile_from_inputs(tile.extent, config.border_width, tile_input_extents,
                                    tile_output_crs_wkt, SUBTRACKER_HIDDEN(0.0, 0.5, tile_tracker));
          if (tile_data.n_points() == 0) {
            step_tracker.text_update("Tile " + tile.output_name() + " has no points; skipping.");
            continue;
          }
          // Only create the output directory once we know the tile has points.
          // Otherwise the Combine step below would pick up an empty directory
          // and emit spurious "Image ... does not exist" warnings.
          fs::path output_dir = config.output_path() / tile.output_name();
          fs::create_directories(output_dir);
          process_las_data(tile_data, output_dir, config,
                           SUBTRACKER_HIDDEN(0.5, 1.0, tile_tracker));
          processed_tile_dirs.push_back(output_dir);
        }
        break;
      }
      case ProcessingStep::Combine: {
        std::optional<std::string> projection;

        std::vector<fs::path> combine_dirs;
        combine_dirs.reserve(tiles.size());
        for (const Tile& t : tiles) {
          fs::path d = config.output_path() / t.output_name();
          if (fs::exists(d)) combine_dirs.push_back(d);
        }

        // Combine TIFs
        fs::create_directories(config.output_path() / "combined" / "raw_vege");
        static constexpr std::array<const char*, 15> COMBINE_TIFS = {
            {"final_img.tif", "final_img_extra_contours.tif", "ground_intensity.tif",
             "buildings.tif", "slope.tif", "fine_slope.tif", "vege_color.tif",
             "hill_shade_multi.tif", "ground.tif", "smooth_ground.tif", "filled_dem.tif",
             "raw_vege/canopy.tif", "raw_vege/green.tif", "raw_vege/smoothed_green.tif",
             "raw_vege/smoothed_canopy.tif"}};
        for (size_t fi = 0; fi < COMBINE_TIFS.size(); ++fi) {
          const std::string filename = COMBINE_TIFS[fi];
          ProgressTracker file_tracker = step_tracker.subtracker(
              0.9 * static_cast<double>(fi) / COMBINE_TIFS.size(),
              0.9 * static_cast<double>(fi + 1) / COMBINE_TIFS.size(), filename);

          std::vector<Geo<MultiBand<FlexGrid>>> grids;

          Extent2D extent;
          std::optional<double> dx, dy;
          const size_t dir_count = combine_dirs.size();
          for (size_t dir_idx = 0; dir_idx < dir_count; ++dir_idx) {
            const fs::path img_path = combine_dirs[dir_idx] / filename;
            if (!fs::exists(img_path)) {
              std::cerr << "Image " << img_path << " does not exist" << std::endl;
              continue;
            }
            grids.emplace_back(read_tif(
                img_path,
                SUBTRACKER(0.5 * static_cast<double>(dir_idx) / dir_count,
                           0.5 * static_cast<double>(dir_idx + 1) / dir_count, file_tracker)));
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
          step_tracker.text_update(to_string("Creating combined grid with dimensions ", width, "x",
                                             height, " requiring ", required_memory / 1e9, " GB"));
          if (required_memory > 16e9) {
            step_tracker.text_update("Skipping " + filename + " due to memory requirements");
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
                       SUBTRACKER(0.5, 0.85, file_tracker),
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
                         SUBTRACKER(0.85, 0.92, file_tracker),
                         /*include_vertical_crs=*/true);

            std::vector<Stream> stream_path =
                stream_paths(filled_dem, config.water, SUBTRACKER_HIDDEN(0.92, 1.0, file_tracker));

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

        // Combine vector outputs (contours, vegetation, map GPKG)
        {
          ProgressTracker gpkg_tracker = step_tracker.subtracker(0.9, 1.0, "combine vectors");

          std::map<double, std::vector<Contour>> contours_by_height;
          std::vector<Contour> joined_contours;
          {
            ProgressTracker contour_tracker =
                gpkg_tracker.subtracker(0.0, 0.35, "combine contours");

            const size_t dir_count = combine_dirs.size();
            for (size_t dir_idx = 0; dir_idx < dir_count; ++dir_idx) {
              const fs::path gpkg_path = combine_dirs[dir_idx] / "trimmed_contours.gpkg";
              if (!fs::exists(gpkg_path)) {
                std::cerr << "GPKG " << gpkg_path << " does not exist" << std::endl;
                continue;
              }

              contour_tracker.text_update("Reading " + gpkg_path.filename().string());
              std::vector<Contour> contours = read_gpkg(
                  gpkg_path,
                  SUBTRACKER(0.15 * static_cast<double>(dir_idx) / dir_count,
                             0.15 * static_cast<double>(dir_idx + 1) / dir_count, contour_tracker));
              for (Contour& contour : contours) {
                contours_by_height[contour.height()].push_back(contour);
              }
            }

            const size_t height_band_count = contours_by_height.size();
            size_t height_band_index = 0;
            contour_tracker.text_update("Joining contours");
            for (const auto& [height, contours] : contours_by_height) {
              std::vector<Contour> jc =
                  join_contours(contours, 5 * config.grid.contour_dem_resolution);
              for (Contour& contour : jc) {
                joined_contours.emplace_back(contour);
              }
              ++height_band_index;
              if (height_band_count > 0) {
                contour_tracker.set_proportion(
                    0.15 + 0.40 * static_cast<double>(height_band_index) / height_band_count);
              }
              (void)height;
            }

            contour_tracker.text_update("Writing combined contours GPKG");
            GPKGWriter writer((config.output_path() / "combined" / "contours.gpkg").string(),
                              projection.value(), "Contour");
            const size_t write_stride = std::max<size_t>(1, joined_contours.size() / 20);
            for (size_t i = 0; i < joined_contours.size(); i++) {
              const Contour& contour = joined_contours[i];
              writer.write_polyline(contour.to_polyline(config.contours),
                                    {{"elevation", contour.height()}});
              if (i % write_stride == 0 || i + 1 == joined_contours.size()) {
                contour_tracker.set_proportion(0.55 + 0.45 * static_cast<double>(i + 1) /
                                                          joined_contours.size());
              }
            }
          }

          write_to_crt(config.output_path() / "combined" / "contours.crt",
                       SUBTRACKER(0.35, 0.36, gpkg_tracker));

          combine_vege_gpkgs(combine_dirs, config.output_path() / "combined", projection.value(),
                             SUBTRACKER(0.36, 0.64, gpkg_tracker));
          write_vegetation_crt(config.output_path() / "combined" / "vegetation.crt",
                               SUBTRACKER(0.64, 0.65, gpkg_tracker));

          {
            const fs::path combined_dir = config.output_path() / "combined";
            std::vector<fs::path> map_sources = {combined_dir / "contours.gpkg",
                                                 combined_dir / "streams.gpkg",
                                                 combined_dir / "vegetation.gpkg"};
            ProgressTracker map_tracker = SUBTRACKER(0.65, 1.0, gpkg_tracker);
            if (projection.has_value()) {
              combine_gpkgs(map_sources, combined_dir / "map.gpkg", projection.value(),
                            SUBTRACKER(0.0, 0.99, map_tracker));
            } else {
              combine_gpkgs(map_sources, combined_dir / "map.gpkg", "",
                            SUBTRACKER(0.0, 0.99, map_tracker));
            }
            if (fs::exists(combined_dir / "map.gpkg")) {
              write_to_crt(combined_dir / "map.crt", SUBTRACKER(0.99, 1.0, map_tracker));
            }
          }
        }

        break;
      }
    }
  }

  if (config.delete_tile_folders && config.processing_steps.count(ProcessingStep::Combine) > 0 &&
      !processed_tile_dirs.empty()) {
    progress_tracker.text_update("Deleting tile folders...");
    for (const fs::path& dir : processed_tile_dirs) {
      std::error_code ec;
      fs::remove_all(dir, ec);
      if (ec) {
        std::cerr << "Warning: failed to delete tile folder " << dir << ": " << ec.message()
                  << std::endl;
      } else {
        progress_tracker.text_update("Deleted tile folder: " + dir.string());
      }
    }
  }
}
```


