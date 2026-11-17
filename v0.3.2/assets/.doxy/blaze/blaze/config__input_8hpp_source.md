

# File config\_input.hpp

[**File List**](files.md) **>** [**config\_input**](dir_7e7c57be6e217d4e927a2ff8d648cb71.md) **>** [**config\_input.hpp**](config__input_8hpp.md)

[Go to the documentation of this file](config__input_8hpp.md)


```C++
#pragma once

#include <cmath>
#include <iostream>
#include <optional>
#include <set>
#include <vector>

#include "isom/colors.hpp"
#include "utilities/filesystem.hpp"
#include "utilities/resources.hpp"

// Policy for resolving marching-squares saddle-point ambiguity.
enum class SaddlePolicy {
  ByHeight,       // Bilinear centre: above threshold → merge, below → separate.
  AlwaysInside,   // Always connect above corners (merge adjacent regions).
  AlwaysOutside,  // Always separate above corners (keep regions distinct).
};

inline SaddlePolicy opposite_saddle_policy(SaddlePolicy p) {
  switch (p) {
    case SaddlePolicy::AlwaysInside:
      return SaddlePolicy::AlwaysOutside;
    case SaddlePolicy::AlwaysOutside:
      return SaddlePolicy::AlwaysInside;
    case SaddlePolicy::ByHeight:
      return SaddlePolicy::ByHeight;
  }
  return SaddlePolicy::ByHeight;
}

struct GridConfig {
  // Resolution (m) at which raw LiDAR points are binned. This is the
  // underlying working grid: ground / building / water / intensity rasters
  // are produced at this resolution.
  double bin_resolution = 0.5;
  // Integer factor by which the binned grid is downsampled to obtain the
  // smoothed ground DEM. The smoothed DEM is what slope, hill-shade and the
  // smooth_ground.tif raster are computed from. Effective smooth-DEM
  // resolution = bin_resolution * downsample_factor.
  unsigned int downsample_factor = 3;
  // Resolution (m) of the vegetation/canopy maps. Vegetation point counts
  // are aggregated to this resolution; final vege_color and raw_vege rasters
  // are written at this resolution. Should be >= bin_resolution.
  double vegetation_grid_resolution = 3.0;
  // Resolution (m) of the DEM used for contour generation, stream extraction,
  // depression filling and contour orientation. Should be >= the smooth DEM
  // resolution (bin_resolution * downsample_factor). Larger values produce
  // smoother contours but lose fine terrain detail.
  double contour_dem_resolution = 9.0;
  // When true, write fine_slope.tif from ground.tif (bin resolution) in addition to
  // slope.tif from smooth_ground.tif.
  bool export_fine_slope = true;

  // Integer factor used to aggregate the bin grid into the vegetation grid.
  // Always >= 1.
  unsigned int vegetation_aggregation_factor() const {
    if (bin_resolution <= 0.0) return 1u;
    long rounded = std::lround(vegetation_grid_resolution / bin_resolution);
    if (rounded < 1) rounded = 1;
    return static_cast<unsigned int>(rounded);
  }

  // Integer factor used to further downsample the smooth ground DEM into the
  // contour DEM. Always >= 1.
  unsigned int contour_downsample_factor() const {
    const double smooth_res = bin_resolution * static_cast<double>(downsample_factor);
    if (smooth_res <= 0.0) return 1u;
    long rounded = std::lround(contour_dem_resolution / smooth_res);
    if (rounded < 1) rounded = 1;
    return static_cast<unsigned int>(rounded);
  }
};

#define SERIALIZE_ENUM_STRICT(ENUM_TYPE, ...)                                                    \
  template <typename BasicJsonType>                                                              \
  inline void to_json(BasicJsonType& j, const ENUM_TYPE& e) {                                    \
    static_assert(std::is_enum<ENUM_TYPE>::value, #ENUM_TYPE " must be an enum!");               \
    static const std::pair<ENUM_TYPE, BasicJsonType> m[] = __VA_ARGS__;                          \
    auto it = std::find_if(std::begin(m), std::end(m),                                           \
                           [e](const std::pair<ENUM_TYPE, BasicJsonType>& ej_pair) -> bool {     \
                             return ej_pair.first == e;                                          \
                           });                                                                   \
    if (it == std::end(m)) throw std::invalid_argument("unknown enum value");                    \
    j = it->second;                                                                              \
  }                                                                                              \
  template <typename BasicJsonType>                                                              \
  inline void from_json(const BasicJsonType& j, ENUM_TYPE& e) {                                  \
    static_assert(std::is_enum<ENUM_TYPE>::value, #ENUM_TYPE " must be an enum!");               \
    static const std::pair<ENUM_TYPE, BasicJsonType> m[] = __VA_ARGS__;                          \
    auto it = std::find_if(std::begin(m), std::end(m),                                           \
                           [&j](const std::pair<ENUM_TYPE, BasicJsonType>& ej_pair) -> bool {    \
                             return ej_pair.second == j;                                         \
                           });                                                                   \
    if (it == std::end(m)) throw std::invalid_argument("unknown json value: " + std::string(j)); \
    e = it->first;                                                                               \
  }

struct GroundConfig {
  int min_ground_intensity = 100;
  int max_ground_intensity = 1000;
  // When true, only LAS points classified as ground are used for the DEM minimum.
  bool use_only_ground_class = true;
  // Vertical threshold (m) for spike removal. <= 0 uses bin_resolution (and scales with
  // downsample_factor on the smooth ground DEM).
  double outlier_threshold_m = 0.0;
};

struct ContourConfig {
  double interval;
  unsigned int min_points;
  ColorVariant color;
  double width;
};

struct BlockingThresholdColorPair {
  double blocking_threshold;
  ColorVariant color;
  std::string
      layer;  // CRT layer name, e.g. "405_Forest". Empty → default from config name + threshold.
  double min_area_m2 = 0;       // minimum polygon area in m²; smaller polygons are dropped
  double min_hole_area_m2 = 0;  // minimum hole area in m²; smaller holes are filled
};

struct VegeHeightConfig {
  std::string name;
  double min_height = 2.5;
  double max_height = 100.0;
  // Low-pass filter radius in vegetation-grid cells applied before polygonization.
  int smooth_radius = 3;
  std::vector<BlockingThresholdColorPair> colors;

  std::optional<ColorVariant> pick_from_blocked_proportion(double bp) const {
    std::optional<ColorVariant> color;
    for (const BlockingThresholdColorPair& btc : colors) {
      if (bp >= btc.blocking_threshold) {
        color = btc.color;
      }
    }
    return color;
  }
};

struct VegeConfig {
  ColorVariant background_color;
  std::vector<VegeHeightConfig> height_configs;
  SaddlePolicy saddle_policy = SaddlePolicy::AlwaysOutside;
};

struct RenderConfig {
  double scale = 10000.0;
  double dpi = 600.0;
};

struct WaterConfig {
  double catchment;
  ColorVariant color;
  double width;
};

struct WaterConfigs {
  std::map<std::string, WaterConfig> configs;
  // Color for LAS-classified water cells on the final map overlay.
  ColorVariant classified_overlay_color = ColorVariant(CMYKColor(100, 0, 0, 0));
  // Minimum depression area (m²) to treat as a sink when filling the DEM for streams.
  double sink_min_area_m2 = 5000.0;
  // Minimum depth (m) below the filled surface for a cell to belong to a sink region.
  double sink_depth_m = 10.0;

  const WaterConfig& config_from_catchment(double catchment) const {
    const WaterConfig* max_valid_config = nullptr;
    for (const auto& [_, config] : configs) {
      if (config.catchment <= catchment &&
          (max_valid_config == nullptr || config.catchment > max_valid_config->catchment))
        max_valid_config = &config;
    }
    return *max_valid_config;
  }

  double minimum_catchment() const {
    double min_catchment = std::numeric_limits<double>::max();
    for (const auto& [_, config] : configs) {
      min_catchment = std::min(config.catchment, min_catchment);
    }
    return min_catchment;
  }
};

struct ContourConfigs {
  std::map<std::string, ContourConfig> configs;
  double min_interval;

  static double minimum_interval(const std::map<std::string, ContourConfig>& configs) {
    double min_interval = std::numeric_limits<double>::max();
    for (const auto& [_, config] : configs) {
      min_interval = std::min(min_interval, config.interval);
    }
    return min_interval;
  }

  ContourConfigs() : min_interval(std::numeric_limits<double>::max()) {}

  explicit ContourConfigs(std::map<std::string, ContourConfig> in_configs)
      : configs(std::move(in_configs)), min_interval(minimum_interval(configs)) {}

  const ContourConfig& operator[](const std::string& key) const { return configs.at(key); }

  const ContourConfig& pick_from_height(double height) const {
    auto max_valid_interval = std::numeric_limits<double>::min();
    const ContourConfig* config_to_return = nullptr;
    for (const auto& [_, config] : configs) {
      if (config.interval > max_valid_interval &&
          std::fmod(std::abs(height), config.interval) < 1e-8) {
        max_valid_interval = config.interval;
        config_to_return = &config;
      }
    }
    return *config_to_return;
  }

  std::string layer_name_from_height(double height) const {
    auto max_valid_interval = std::numeric_limits<double>::min();
    std::string layer_name = "Contour";
    for (const auto& [name, config] : configs) {
      if (config.interval > max_valid_interval &&
          std::fmod(std::abs(height), config.interval) < 1e-8) {
        if (name == "form_line" || name == "formline") {
          layer_name = "103_Form_Line";
        } else if (name == "index") {
          layer_name = "102_Index_Contour";
        } else if (name == "normal") {
          layer_name = "101_Contour";
        }
        max_valid_interval = config.interval;
      }
    }
    return layer_name;
  }
};

struct BuildingsConfig {
  ColorVariant color;
};

enum class ProcessingStep {
  Tiles,
  Combine,
};

std::ostream& operator<<(std::ostream& os, const ProcessingStep& step);

struct Config {
  GridConfig grid;
  GroundConfig ground;
  ContourConfigs contours;
  WaterConfigs water;
  VegeConfig vege;
  RenderConfig render;
  BuildingsConfig buildings;
  std::vector<fs::path> las_files;
  std::set<ProcessingStep> processing_steps;
  fs::path output_directory;
  double border_width;
  // When > 0, enables tiled processing mode. Blaze divides the union of all
  // input files' extents (in the output CRS) into a regular grid of tiles
  // with this side length (meters) and processes each tile independently,
  // pulling and reprojecting points from every input LAS/LAZ file that
  // overlaps the tile+border. Required when input files overlap each other
  // or use different CRSes.
  double tile_size = 0.0;
  // Overrides the CRS of any input LAS/LAZ file regardless of whether the file
  // embeds a projection. Useful for older ACT government datasets that ship
  // with no projection at all, and for correcting files that embed the wrong
  // CRS. When set, a warning is emitted if the embedded CRS (if any) disagrees
  // with this value. Accepts anything OGRSpatialReference::SetFromUserInput
  // understands, e.g. "EPSG:28355", a WKT string, or a proj.4 string. Empty
  // string = use whatever the file embeds (error out if it embeds nothing).
  std::string override_crs;
  // When true, each per-tile output directory is removed after all tiles have
  // been processed. Useful for freeing disk space once the Combine step has
  // merged the individual tile outputs into the combined/ directory.
  bool delete_tile_folders = false;
  fs::path relative_path_to_config;

  void set_output_directory(const fs::path& output_dir) { output_directory = output_dir; }

  fs::path output_path() const {
    if (output_directory.is_absolute()) {
      return output_directory;
    }
    return relative_path_to_config / output_directory;
  }

  std::vector<fs::path> las_filepaths() const {
    std::vector<fs::path> las_filepaths;
    for (const fs::path& las_file : las_files) {
      if (las_file.is_absolute()) {
        las_filepaths.push_back(las_file);
      } else {
        las_filepaths.push_back(relative_path_to_config / las_file);
      }
    }
    return las_filepaths;
  }

  std::vector<fs::path> get_las_files(const fs::path& las_path) const {
    std::vector<fs::path> file_list;
    fs::path actual_path = las_path.is_absolute() ? las_path : relative_path_to_config / las_path;
    if (fs::exists(actual_path)) {
      if (fs::is_directory(actual_path)) {
        for (const fs::directory_entry& entry : fs::directory_iterator(actual_path)) {
          if (entry.path().extension() == ".las" || entry.path().extension() == ".laz") {
            file_list.push_back(entry.path());
          }
        }
      } else if (actual_path.extension() == ".las" || actual_path.extension() == ".laz") {
        file_list.push_back(actual_path);
      }
    }
    return file_list;
  }

  static Config FromFile(const fs::path& filename);

  void write_to_file(const fs::path& filename) const;

  static Config Default() {
    Config c = FromFile(AssetRetriever::get_asset("default_config.json"));
    // The asset directory may be read-only (e.g. inside a mounted DMG or an
    // installed .app bundle). Redirect any relative output path to a writable
    // per-user data directory so the first run doesn't hit a read-only error.
    if (!c.output_directory.is_absolute()) {
      c.output_directory = LocalDataRetriever::get_local_data(c.output_directory);
    }
    return c;
  }

  Config& operator=(const Config& config) = default;
  Config(const Config& config) = delete;
  Config(Config&& config) = default;
  Config() = default;

  friend std::ostream& operator<<(std::ostream& os, const Config& config);
};
```


