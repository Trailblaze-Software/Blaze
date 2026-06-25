

# File process.cpp

[**File List**](files.md) **>** [**src**](dir_68267d1309a1af8e8297ef4c3efbcdba.md) **>** [**process.cpp**](process_8cpp.md)

[Go to the documentation of this file](process_8cpp.md)


```C++
#include "process.hpp"

#include "cliff/cliff.hpp"
#include "contour/contour_gen.hpp"
#include "crt/crt.hpp"
#include "grid/grid_ops.hpp"
#include "grid/img_grid.hpp"
#include "io/gpkg.hpp"
#include "isom/colors.hpp"
#include "las/binned_points.hpp"
#include "las/las_file.hpp"
#include "las/las_point.hpp"
#include "lib/grid/grid.hpp"
#include "lib/vegetation/vegetation.hpp"
#include "methods/hill_shade/hill_shade.hpp"
#include "methods/water/water.hpp"
#include "tif/tif.hpp"
#include "utilities/progress_tracker.hpp"
#include "vegetation/vegetation_polygon.hpp"

enum class GroundMethod { LOWER_BOUND, LOWEST_POINT, INTERPOLATE };

GeoGrid<double> get_pixel_heights(const GeoGrid<std::optional<LASPoint>>& ground_points,
                                  GroundMethod method = GroundMethod::LOWEST_POINT) {
  GeoGrid<double> ground(ground_points.width(), ground_points.height(),
                         GeoTransform(ground_points.transform()),
                         GeoProjection(ground_points.projection()));
#pragma omp parallel for
  for (size_t i = 0; i < ground.height(); i++) {
    for (size_t j = 0; j < ground.width(); j++) {
      if (ground_points[{j, i}]) {
        if (method == GroundMethod::LOWEST_POINT) {
          ground[{j, i}] = ground_points[{j, i}]->z();
        } else {
          Fail("Not implemented");
        }
      } else {
        ground[{j, i}] = std::numeric_limits<double>::max();
      }
    }
  }
  return ground;
}

// Downsample a binary mask grid by `factor` using "any" aggregation: an output
// cell is set if any of the input sub-cells were set. Used to bring the
// buildings mask onto the same resolution as the smooth-ground DEM (slope,
// hill-shade, etc.) for export.
static GeoGrid<std::optional<std::byte>> downsample_mask_any(
    const GeoGrid<std::optional<std::byte>>& grid, size_t factor) {
  if (factor == 0) {
    Fail("downsample_mask_any factor must be > 0");
  }
  if (grid.transform().dx() != -grid.transform().dy()) {
    Fail("downsample_mask_any requires square pixels (dx == -dy)");
  }
  GeoGrid<std::optional<std::byte>> result(
      (grid.width() + factor - 1) / factor, (grid.height() + factor - 1) / factor,
      grid.transform().with_new_resolution(grid.transform().dx() * factor),
      GeoProjection(grid.projection()));
#pragma omp parallel for
  for (size_t i = 0; i < result.height(); i++) {
    for (size_t j = 0; j < result.width(); j++) {
      bool any_set = false;
      for (size_t k = 0; k < factor && i * factor + k < grid.height() && !any_set; k++) {
        for (size_t l = 0; l < factor && j * factor + l < grid.width(); l++) {
          if (grid[{j * factor + l, i * factor + k}]) {
            any_set = true;
            break;
          }
        }
      }
      result[{j, i}] = any_set ? std::optional<std::byte>{std::byte{0}} : std::nullopt;
    }
  }
  return result;
}

GeoGrid<double> adjust_ground_to_slope(const GeoGrid<double>& grid) {
  GeoGrid<double> result(grid.width(), grid.height(), GeoTransform(grid.transform()),
                         GeoProjection(grid.projection()));

  result.copy_from(grid);
  // Need at least one interior cell in each dimension to compute a central difference.
  // Skip adjustment for degenerate/tiny grids to avoid size_t underflow in the loop bounds.
  if (grid.width() < 3 || grid.height() < 3) {
    return result;
  }
  for (size_t i = 1; i < grid.height() - 1; i++) {
    for (size_t j = 1; j < grid.width() - 1; j++) {
      // The minimum point in each bin is at the downhill edge (half a bin away from center)
      // To correct from edge value to center value, we need to raise the edge value by the gradient
      // times the offset The correction accounts for the offset (half bin size) times the gradient
      result[{j, i}] = grid[{j, i}] + 0.25 * (std::abs(grid[{j + 1, i}] - grid[{j - 1, i}]) +
                                              std::abs(grid[{j, i + 1}] - grid[{j, i - 1}]));
    }
  }
  return result;
}

void process_las_file(const fs::path& las_filename, const Config& config,
                      ProgressTracker progress_tracker) {
  TimeFunction outer_timer("processing LAS file " + las_filename.string(), &progress_tracker);
  fs::path output_dir = config.output_path() / las_filename.stem();
  fs::create_directories(output_dir);

  LASData las_file =
      LASData::with_border(las_filename, config.border_width, progress_tracker.subtracker(0.0, 0.4),
                           config.override_crs);
  process_las_data(las_file, output_dir, config, progress_tracker.subtracker(0.4, 1.0));
}

void process_las_data(LASData& las_file, const fs::path& output_dir, const Config& config,
                      ProgressTracker progress_tracker) {
  const double bin_resolution = config.grid.bin_resolution;
  const unsigned int downsample_factor = config.grid.downsample_factor;
  BinnedPoints binned_points(las_file, bin_resolution, downsample_factor,
                             progress_tracker.subtracker(0.0, 0.5));
  // progress_tracker is now at 0.5 — mapped from BinnedPoints' internal set_proportion(1.0)

  // Export extent: midpoint between data and tile core, clipped to actual data.
  Extent2D data_ext = binned_points.data_extent().intersection(las_file.export_bounds());

  GeoGrid<std::optional<LASPoint>> ground_points(binned_points.width(), binned_points.height(),
                                                 GeoTransform(binned_points.transform()),
                                                 GeoProjection(las_file.projection()));

  GeoGrid<std::optional<std::byte>> buildings = GeoGrid<std::optional<std::byte>>(
      ground_points.width(), ground_points.height(), GeoTransform(ground_points.transform()),
      GeoProjection(ground_points.projection()));

  GeoGrid<RGBColor> ground_intensity_img(ground_points.width(), ground_points.height(),
                                         GeoTransform(ground_points.transform()),
                                         GeoProjection(las_file.projection()));

  GeoGrid<std::optional<std::byte>> water = GeoGrid<std::optional<std::byte>>(
      ground_points.width(), ground_points.height(), GeoTransform(ground_points.transform()),
      GeoProjection(ground_points.projection()));

  {
    bool only_classified_ground = true;
    TimeFunction timer("min finding", &progress_tracker);
#pragma omp parallel for
    for (size_t i = 0; i < binned_points.height(); i++) {
      for (size_t j = 0; j < binned_points.width(); j++) {
        bool is_building = false;
        bool is_water = false;
        double min = std::numeric_limits<double>::infinity();
        std::optional<LASPoint> min_point = std::nullopt;
        for (const LASPoint& las_point : binned_points[{j, i}]) {
          if (las_point.z() < min && (las_point.classification() == LASClassification::Ground ||
                                      !only_classified_ground)) {
            min = las_point.z();
            min_point = las_point;
            uint8_t intensity = std::clamp(
                (double)(las_point.intensity() - config.ground.min_ground_intensity) /
                    (config.ground.max_ground_intensity - config.ground.min_ground_intensity) *
                    255.0,
                0.0, 255.0);
            ground_intensity_img[{j, i}] = RGBColor(intensity, intensity, intensity);
          }
          if (las_point.classification() == LASClassification::Building) {
            is_building = true;
          } else if (las_point.classification() == LASClassification::Water) {
            is_water = true;
          }
        }
        ground_points[{j, i}] = min_point;
        buildings[{j, i}] = is_building ? std::optional<std::byte>{std::byte{0}} : std::nullopt;
        water[{j, i}] = is_water ? std::optional<std::byte>{std::byte{0}} : std::nullopt;
      }
    }
  }
  progress_tracker.set_proportion(0.6);

  GeoGrid<double> ground = get_pixel_heights(ground_points);

  write_to_tif(ground_intensity_img.slice(data_ext), output_dir / "ground_intensity.tif",
               progress_tracker.subtracker(0.62, 0.63));

  remove_outliers(ground, progress_tracker.subtracker(0.63, 0.64), bin_resolution);
  interpolate_holes(ground, progress_tracker.subtracker(0.64, 0.65));

  // Adjust ground estimate to account for bias from taking minimum point in each bin
  ground = adjust_ground_to_slope(ground);

  write_to_tif(ground.slice(data_ext), output_dir / "ground.tif",
               progress_tracker.subtracker(0.65, 0.66), /*include_vertical_crs=*/true);

  if (config.grid.export_fine_slope) {
    ProgressTracker fine_slope = progress_tracker.subtracker(0.66, 0.67);
    GeoGrid<double> fine_slope_grid = slope(ground, &fine_slope);
    write_to_image_tif(fine_slope_grid.slice(data_ext), output_dir / "fine_slope.tif",
                       fine_slope.subtracker(0.5, 1.0), std::optional<double>(std::numbers::pi / 2),
                       std::optional<double>(0.0));
  }

  // Export buildings.tif at the smooth-ground resolution (bin_resolution *
  // downsample_factor) to match slope.tif / hill_shade / smooth_ground.tif.
  // The internal `buildings` grid is kept at bin_resolution so that the
  // building_color raster drawn onto the final image preserves fine outlines.
  if (downsample_factor > 1) {
    GeoGrid<std::optional<std::byte>> buildings_export =
        downsample_mask_any(buildings, downsample_factor);
    write_to_tif(buildings_export.slice(data_ext), output_dir / "buildings.tif",
                 progress_tracker.subtracker(0.67, 0.68));
  } else {
    write_to_tif(buildings.slice(data_ext), output_dir / "buildings.tif",
                 progress_tracker.subtracker(0.67, 0.68));
  }
  write_to_tif(water.slice(data_ext), output_dir / "water.tif",
               progress_tracker.subtracker(0.68, 0.69));

  std::unique_ptr<GeoGrid<double>> downsampled_ground = std::make_unique<GeoGrid<double>>(
      downsample(ground, downsample_factor, progress_tracker.subtracker(0.69, 0.7)));
  remove_outliers(*downsampled_ground, progress_tracker.subtracker(0.7, 0.71),
                  bin_resolution * downsample_factor);
  GeoGrid<double> smooth_ground = *downsampled_ground;
  downsampled_ground.reset();

  write_to_tif(smooth_ground.slice(data_ext), output_dir / "smooth_ground.tif",
               progress_tracker.subtracker(0.72, 0.73), /*include_vertical_crs=*/true);

  {
    GeoGrid<double> slope_grid = slope(smooth_ground, &progress_tracker);
    // Scale absolutely with min=pi/2, max=0: flat terrain (slope≈0) → 255, vertical (slope≈pi/2) →
    // 0.
    write_to_image_tif(slope_grid.slice(data_ext), output_dir / "slope.tif",
                       progress_tracker.subtracker(0.74, 0.75),
                       std::optional<double>(std::numbers::pi / 2), std::optional<double>(0.0));
  }

  // Build the contour DEM by further downsampling the smooth ground DEM.
  // contour_downsample_factor() is the integer ratio between the requested
  // contour DEM resolution and the smooth-ground resolution (always >= 1).
  // When the factor is 1 the contour DEM is just the smooth ground.
  const unsigned int contour_factor = config.grid.contour_downsample_factor();
  GeoGrid<double> contour_dem = contour_factor > 1
                                    ? downsample(smooth_ground, contour_factor, ProgressTracker())
                                    : smooth_ground;

  const std::vector<Contour> contours =
      generate_contours(contour_dem, config.contours, progress_tracker.subtracker(0.75, 0.76));

  std::vector<Stream> stream_path =
      stream_paths(contour_dem, config.water, progress_tracker.subtracker(0.76, 0.77));

  std::vector<Coordinate2D<size_t>> sinks =
      identify_sinks(contour_dem, 10, 5000, &progress_tracker);
  GeoGrid<double> filled = fill_depressions(contour_dem, sinks, &progress_tracker);
  write_to_tif(filled.slice(data_ext), output_dir / "filled_dem.tif",
               /*progress_tracker=*/std::nullopt, /*include_vertical_crs=*/true);

  double contour_points_resolution = 20;
  GeoGrid<std::vector<std::shared_ptr<ContourPoint>>> contour_points(
      num_cells_by_distance(contour_dem.width_m(), contour_points_resolution) + 1,
      num_cells_by_distance(contour_dem.height_m(), contour_points_resolution) + 1,
      GeoTransform(contour_dem.transform().pixel_to_projection({0, 0}), contour_points_resolution),
      GeoProjection(las_file.projection()));

  std::vector<std::shared_ptr<ContourPoint>> all_contour_points;

  for (const Contour& contour : contours) {
    ContourPoint* last_point = nullptr;
    for (size_t i = 0; i < contour.points().size(); i++) {
      const Coordinate2D<double>& point = contour.points().at(i);
      std::shared_ptr<ContourPoint> contour_point =
          std::make_shared<ContourPoint>(point.x(), point.y(), contour.height());
      if (last_point) {
        contour_point->set_previous(last_point);
        last_point->set_next(contour_point.get());
      }
      contour_points[contour_points.transform().projection_to_pixel(point)].emplace_back(
          contour_point);
      all_contour_points.emplace_back(contour_point);
      last_point = contour_point.get();
    }
  }

#pragma omp parallel for
  for (size_t i = 0; i < contour_points.height(); i++) {
    for (size_t j = 0; j < contour_points.width(); j++) {
      std::vector<std::shared_ptr<ContourPoint>>& points = contour_points[{j, i}];
      for (std::shared_ptr<ContourPoint>& point : points) {
        point->find_up_down(contour_points);
      }
    }
  }

  const std::vector<Contour> trimmed_contours = trim_contours(contours, las_file.original_bounds());

  {
    std::vector<Contour> oriented_contours = contours;
#pragma omp parallel for
    for (size_t i = 0; i < oriented_contours.size(); i++) {
      oriented_contours[i].orient_consistent(contour_dem);
    }

    // Write contours to GPKG (always create file, even if empty)
    GPKGWriter writer((output_dir / "contours.gpkg").string(), las_file.projection().to_string(),
                      "Contour");
    for (const Contour& contour : oriented_contours) {
      if (contour.points().size() > 1) {
        writer.write_polyline(contour.to_polyline(config.contours),
                              {{"elevation", contour.height()}});
      }
    }
  }

  // Write trimmed contours to GPKG
  {
    std::vector<Contour> oriented_trimmed_contours = trimmed_contours;
#pragma omp parallel for
    for (size_t i = 0; i < oriented_trimmed_contours.size(); i++) {
      oriented_trimmed_contours[i].orient_consistent(contour_dem);
    }

    // Write trimmed contours to GPKG (always create file, even if empty)
    GPKGWriter writer((output_dir / "trimmed_contours.gpkg").string(),
                      las_file.projection().to_string(), "Contour");
    for (const Contour& contour : oriented_trimmed_contours) {
      if (contour.points().size() > 1) {
        writer.write_polyline(contour.to_polyline(config.contours),
                              {{"elevation", contour.height()}});
      }
    }
  }
  // crt name must match gpkg name (keeping for compatibility)
  write_to_crt(output_dir / "contours.crt", &progress_tracker);

  // Write streams to GPKG
  {
    GPKGWriter writer((output_dir / "streams.gpkg").string(), las_file.projection().to_string(),
                      "streams");
    for (const Stream& stream : stream_path) {
      writer.write_polyline(Polyline{.layer = "streams",
                                     .name = std::to_string(stream.catchment),
                                     .vertices = stream.coords},
                            {{"catchment", stream.catchment}});
    }
  }

  // VEGE
  // Vegetation maps are produced at vegetation_grid_resolution. We compute
  // blocked-proportion at the underlying bin_resolution (so each LiDAR point
  // contributes to the cell it actually falls in) and then aggregate to the
  // coarser vegetation grid via mean downsampling.
  const unsigned int veg_factor = config.grid.vegetation_aggregation_factor();
  std::map<std::string, GeoGrid<float>> vege_maps;
  {
    ProgressTracker vege_tracker = progress_tracker.subtracker(0.77, 0.78);
    const size_t vege_config_count = config.vege.height_configs.size();
    for (size_t vege_config_index = 0; vege_config_index < vege_config_count; ++vege_config_index) {
      const VegeHeightConfig& vege_config = config.vege.height_configs[vege_config_index];
      const double map_start =
          vege_config_count > 0 ? 0.55 * static_cast<double>(vege_config_index) / vege_config_count
                                : 0.0;
      const double map_end =
          vege_config_count > 0
              ? 0.55 * static_cast<double>(vege_config_index + 1) / vege_config_count
              : 0.55;
      ProgressTracker map_tracker = vege_tracker.subtracker(map_start, map_end);
      map_tracker.text_update("Vegetation map: " + vege_config.name);
      GeoGrid<std::optional<float>> blocked_proportion =
          get_blocked_proportion(binned_points, smooth_ground, vege_config, std::move(map_tracker));
      fs::create_directories(output_dir / "raw_vege");

      auto float01_to_byte_grid = [](const GeoGrid<float>& grid) {
        GeoGrid<std::byte> out(grid.width(), grid.height(), GeoTransform(grid.transform()),
                               GeoProjection(grid.projection()));
#pragma omp parallel for
        for (size_t i = 0; i < grid.height(); i++) {
          for (size_t j = 0; j < grid.width(); j++) {
            const float v = grid[{j, i}];
            if (!std::isfinite(v)) {
              out[{j, i}] = std::byte(0);
              continue;
            }
            const float clamped = std::clamp(v, 0.0f, 1.0f);
            const int scaled = static_cast<int>(std::lround(clamped * 255.0f));
            out[{j, i}] = static_cast<std::byte>(std::clamp(scaled, 0, 255));
          }
        }
        return out;
      };

      // Raw blocked-proportion (0..1) at vegetation resolution, exported as Byte.
      // We convert optional<float> to float with NaNs for nodata so downsample()
      // can ignore missing values (it only includes finite values in the mean).
      GeoGrid<float> raw_bp_float(blocked_proportion.width(), blocked_proportion.height(),
                                  GeoTransform(blocked_proportion.transform()),
                                  GeoProjection(blocked_proportion.projection()));
#pragma omp parallel for
      for (size_t i = 0; i < blocked_proportion.height(); i++) {
        for (size_t j = 0; j < blocked_proportion.width(); j++) {
          raw_bp_float[{j, i}] = blocked_proportion[{j, i}].has_value()
                                     ? *blocked_proportion[{j, i}]
                                     : std::numeric_limits<float>::quiet_NaN();
        }
      }
      GeoGrid<float> raw_vege_grid =
          veg_factor > 1
              ? downsample(raw_bp_float, veg_factor, ProgressTracker(), DownsampleMethod::MEAN)
              : std::move(raw_bp_float);
      write_to_tif(float01_to_byte_grid(raw_vege_grid).slice(data_ext),
                   output_dir / "raw_vege" / (vege_config.name + ".tif"));

      // Smoothed blocked-proportion (low-pass + aggregated) at vegetation resolution, exported as
      // Byte.
      GeoGrid<float> smooth_blocked_proportion = low_pass(blocked_proportion, 5);
      GeoGrid<float> vege_grid = veg_factor > 1
                                     ? downsample(smooth_blocked_proportion, veg_factor,
                                                  ProgressTracker(), DownsampleMethod::MEAN)
                                     : std::move(smooth_blocked_proportion);
      write_to_tif(float01_to_byte_grid(vege_grid).slice(data_ext),
                   output_dir / "raw_vege" / ("smoothed_" + vege_config.name + ".tif"));

      // Keep float vegetation grid for the coloring stage.
      vege_maps.emplace(vege_config.name, std::move(vege_grid));
    }

    // --- Vegetation polygon export ---
    vege_tracker.text_update("Polygonizing vegetation");
    std::vector<VegePolygon> vege_polygons =
        generate_vege_polygons(config.vege, vege_maps, vege_tracker.subtracker(0.55, 0.85));
    trim_vege_polygons_to_extent(vege_polygons, data_ext, {data_ext, las_file.original_bounds()},
                                 0.01, vege_tracker.subtracker(0.85, 0.92));
    if (!vege_polygons.empty()) {
      write_vege_polygons_gpkg(vege_polygons, output_dir / "vegetation.gpkg",
                               las_file.projection().to_string(),
                               vege_tracker.subtracker(0.92, 1.0));
      write_vegetation_crt(output_dir / "vegetation.crt", &vege_tracker);
    }
  }  // vege_tracker destructor advances progress to 0.78

  write_to_image_tif(hill_shade(smooth_ground, 315, 45, true, &progress_tracker).slice(data_ext),
                     output_dir / "hill_shade_multi.tif");

  // vege_color is at vegetation_grid_resolution (matching the aggregated
  // vege_maps), so its dimensions are the bin grid divided by veg_factor.
  const size_t vege_color_width = (binned_points.width() + veg_factor - 1) / veg_factor;
  const size_t vege_color_height = (binned_points.height() + veg_factor - 1) / veg_factor;
  GeoGrid<CMYKColor> vege_color(
      vege_color_width, vege_color_height,
      GeoTransform(binned_points.transform().with_new_resolution(bin_resolution * veg_factor)),
      GeoProjection(binned_points.projection()));

  GeoGrid<RGBColor> building_color(buildings.width(), buildings.height(),
                                   GeoTransform(buildings.transform()),
                                   GeoProjection(buildings.projection()));
  GeoGrid<RGBColor> water_color(water.width(), water.height(), GeoTransform(water.transform()),
                                GeoProjection(water.projection()));

#pragma omp parallel for
  for (size_t i = 0; i < vege_color.height(); i++) {
    for (size_t j = 0; j < vege_color.width(); j++) {
      vege_color[{j, i}] = to_cmyk(config.vege.background_color);
    }
  }
#pragma omp parallel for
  for (size_t i = 0; i < buildings.height(); i++) {
    for (size_t j = 0; j < buildings.width(); j++) {
      if (buildings[{j, i}]) building_color[{j, i}] = to_rgb(config.buildings.color);
      if (water[{j, i}]) water_color[{j, i}] = to_rgb(CMYKColor(100, 0, 0, 0));
    }
  }
  for (const VegeHeightConfig& vege_config : config.vege.height_configs) {
#pragma omp parallel for
    for (size_t i = 0; i < vege_maps.at(vege_config.name).height(); i++) {
      for (size_t j = 0; j < vege_maps.at(vege_config.name).width(); j++) {
        std::optional<ColorVariant> color =
            vege_config.pick_from_blocked_proportion(vege_maps.at(vege_config.name)[{j, i}]);
        if (color) {
          vege_color[{j, i}] = to_cmyk(color.value());
        }
      }
    }
  }
  write_to_tif(vege_color.slice(data_ext), output_dir / "vege_color.tif");

  constexpr double INCHES_PER_METER = 39.3701;
  double render_pixel_resolution = config.render.scale / config.render.dpi / INCHES_PER_METER;
  GeoImgGrid final_img(
      num_cells_by_distance(ground.width() * ground.transform().dx(), render_pixel_resolution),
      num_cells_by_distance(ground.height() * ground.transform().dy(), render_pixel_resolution),
      GeoTransform(vege_color.transform().with_new_resolution(render_pixel_resolution)),
      GeoProjection(vege_color.projection()));

  {
    TimeFunction timer("drawing vege", &progress_tracker);
    final_img.draw(GeoImgGrid(vege_color));
  }

  progress_tracker.set_proportion(0.8);
  {
    TimeFunction timer("drawing stuff", &progress_tracker);
    final_img.draw(GeoImgGrid(water_color));
  }

  {
    TimeFunction timer("drawing contours", &progress_tracker);
    for (const Contour& contour : contours) {
      if (config.contours.layer_name_from_height(contour.height()) == "Contour") continue;
      const ContourConfig& contour_config = config.contours.pick_from_height(contour.height());
      RGBColor color = to_rgb(contour_config.color);
      final_img.draw(contour, color, contour_config.width / 1000 * config.render.scale);
    }
  }

  {
    TimeFunction timer("drawing paths", &progress_tracker);
    for (const Stream& stream : stream_path) {
      const WaterConfig& water_config = config.water.config_from_catchment(stream.catchment);
      final_img.draw(stream.coords, water_config.color,
                     water_config.width / 1000 * config.render.scale);
    }
  }

  {
    TimeFunction timer("drawing stuff", &progress_tracker);
    final_img.draw(GeoImgGrid(building_color));
  }

  final_img.save_to(output_dir / "final_img.tif", data_ext);

  progress_tracker.set_proportion(0.9);

  for (const Contour& contour : contours) {
    if (config.contours.layer_name_from_height(contour.height()) != "Contour") continue;
    const ContourConfig& contour_config = config.contours.pick_from_height(contour.height());
    RGBColor color = to_rgb(contour_config.color);
    final_img.draw(contour, color, contour_config.width / 1000 * config.render.scale);
  }

  {
    TimeFunction timer("drawing paths", &progress_tracker);
    for (const Stream& stream : stream_path) {
      const WaterConfig& water_config = config.water.config_from_catchment(stream.catchment);
      final_img.draw(stream.coords, water_config.color,
                     water_config.width / 1000 * config.render.scale);
    }
  }

  final_img.draw(GeoImgGrid(building_color));

  for (const std::shared_ptr<ContourPoint>& point : all_contour_points) {
    if (point->slope() > 0.8) {
      final_img.draw_point(*point, RGBColor(0, 0, 0), 1.5);
    }
  }

  final_img.save_to(output_dir / "final_img_extra_contours.tif", data_ext);
}
```


