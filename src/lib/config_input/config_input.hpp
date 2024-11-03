#pragma once

#include <cmath>
#include <iostream>
#include <optional>
#include <set>
#include <vector>

#include "isom/colors.hpp"
#include "utilities/filesystem.hpp"
#include "utilities/resources.hpp"

#ifdef _MSC_VER
#pragma warning(push, 0)
#endif
#include <au/units/inches.hh>
#include <au/units/meters.hh>
#include <au/units/unos.hh>

#include "au/prefix.hh"
#include "au/quantity.hh"
#include "au/unit_of_measure.hh"
#ifdef _MSC_VER
#pragma warning(pop)
#endif

struct GridConfig {
  au::QuantityD<au::Meters> bin_resolution;
  unsigned int downsample_factor;
};

struct GroundConfig {
  au::QuantityD<au::Meters> outlier_removal_height_diff;
  int min_ground_intensity;
  int max_ground_intensity;
};

struct ContourConfig {
  au::QuantityD<au::Meters> interval;
  unsigned int min_points;
  ColorVariant color;
  au::QuantityD<au::Milli<au::Meters>> width;
};

struct CanopyConfig {
  au::QuantityD<au::Meters> min_height;
  au::QuantityD<au::Meters> max_height;
  double blocking_threshold;
};

struct BlockingThresholdColorPair {
  double blocking_threshold;
  ColorVariant color;
};

struct VegeHeightConfig {
  std::string name;
  au::QuantityD<au::Meters> min_height;
  au::QuantityD<au::Meters> max_height;
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
};

struct RenderConfig {
  double scale;
  au::QuantityD<au::UnitPowerT<au::Inches, -1>> dpi;
};

struct WaterConfig {
  au::QuantityD<au::UnitPowerT<au::Kilo<au::Meters>, 2>> catchment;
  ColorVariant color;
  au::QuantityD<au::Milli<au::Meters>> width;
};

struct WaterConfigs {
  std::map<std::string, WaterConfig> configs;

  const WaterConfig& config_from_catchment(double catchment) const {
    const WaterConfig* max_valid_config = nullptr;
    for (const auto& [_, config] : configs) {
      if (config.catchment <= au::pow<2>(au::meters)(catchment) &&
          (max_valid_config == nullptr || config.catchment > max_valid_config->catchment))
        max_valid_config = &config;
    }
    return *max_valid_config;
  }

  double minimum_catchment() const {
    double min_catchment = std::numeric_limits<double>::max();
    for (const auto& [_, config] : configs) {
      min_catchment =
          std::min(config.catchment.in(au::pow<2>(au::kilo(au::meters))), min_catchment);
    }
    return min_catchment;
  }
};

struct ContourConfigs {
  std::map<std::string, ContourConfig> configs;
  au::QuantityD<au::Meters> min_interval;

  static au::QuantityD<au::Meters> minimum_interval(
      const std::map<std::string, ContourConfig>& configs) {
    au::QuantityD<au::Meters> min_interval = au::meters(std::numeric_limits<double>::max());
    for (const auto& [_, config] : configs) {
      min_interval = std::min(min_interval, config.interval);
    }
    return min_interval;
  }

  ContourConfigs() : min_interval(au::meters(std::numeric_limits<double>::max())) {}

  explicit ContourConfigs(std::map<std::string, ContourConfig> in_configs)
      : configs(std::move(in_configs)), min_interval(minimum_interval(configs)) {}

  const ContourConfig& operator[](const std::string& key) const { return configs.at(key); }

  const ContourConfig& pick_from_height(double height) const {
    auto max_valid_interval = au::meters(std::numeric_limits<double>::min());
    const ContourConfig* config_to_return = nullptr;
    for (const auto& [_, config] : configs) {
      if (config.interval > max_valid_interval &&
          std::fmod(std::abs(height), config.interval.in(au::meters)) < 1e-8) {
        max_valid_interval = config.interval;
        config_to_return = &config;
      }
    }
    return *config_to_return;
  }

  std::string layer_name_from_height(double height) const {
    auto max_valid_interval = au::meters(std::numeric_limits<double>::min());
    std::string layer_name = "Contour";
    for (const auto& [name, config] : configs) {
      if (config.interval > max_valid_interval &&
          std::fmod(std::abs(height), config.interval.in(au::meters)) < 1e-8) {
        if (name == "form_line") {
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
  TmpBorders,
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
  au::QuantityD<au::Meters> border_width;
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

  static Config FromFile(const fs::path& filename);

  void write_to_file(const fs::path& filename) const;

  static Config Default() { return FromFile(AssetRetriever::get_asset("default_config.json")); }

  Config& operator=(const Config& config) = default;
  Config(const Config& config) = delete;
  Config(Config&& config) = default;
  Config() = default;

  friend std::ostream& operator<<(std::ostream& os, const Config& config);
};
