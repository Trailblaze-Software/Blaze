#pragma once

#include <fstream>
#include <iostream>
#include <set>

#include "assert/assert.hpp"
#include "isom/colors.hpp"
#include "utilities/filesystem.hpp"
#include "utilities/resources.hpp"

#define JSON_DIAGNOSTICS 1
#ifdef _MSC_VER
#pragma warning(push, 0)
#endif
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Warray-bounds"
#include <nlohmann/json.hpp>
#pragma GCC diagnostic pop
#ifdef _MSC_VER
#pragma warning(pop)
#endif

using json = nlohmann::json;

struct GridConfig {
  double bin_resolution;
  unsigned int downsample_factor;
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

namespace nlohmann {
template <>
struct adl_serializer<GridConfig> {
  static GridConfig from_json(const json& j) {
    return GridConfig{j.value("bin_resolution", 1.0), j.value("downsample_factor", 3u)};
  }

  static void to_json(json& j, GridConfig gc) {
    j["bin_resolution"] = gc.bin_resolution;
    j["downsample_factor"] = gc.downsample_factor;
  }
};
}  // namespace nlohmann

struct GroundConfig {
  double outlier_removal_height_diff;
  int min_ground_intensity;
  int max_ground_intensity;
};

namespace nlohmann {
template <>
struct adl_serializer<GroundConfig> {
  static GroundConfig from_json(const json& j) {
    return GroundConfig{j.value("outlier_removal_height_diff", 1.0),
                        j.value("min_ground_intensity", 100),
                        j.value("max_ground_intensity", 1000)};
  }

  static void to_json(json& j, GroundConfig gc) {
    j["outlier_removal_height_diff"] = gc.outlier_removal_height_diff;
    j["min_ground_intensity"] = gc.min_ground_intensity;
    j["max_ground_intensity"] = gc.max_ground_intensity;
  }
};
}  // namespace nlohmann

struct ContourConfig {
  double interval;
  unsigned int min_points;
  ColorVariant color;
  double width;
};

namespace nlohmann {
template <>
struct adl_serializer<RGBColor> {
  static RGBColor from_json(const json& j) { return RGBColor(j[0], j[1], j[2], j[3]); }

  static void to_json(json& j, RGBColor c) {
    j = {c.getRed(), c.getGreen(), c.getBlue(), c.getAlpha()};
  }
};

template <>
struct adl_serializer<CMYKColor> {
  static CMYKColor from_json(const json& j) { return CMYKColor(j[0], j[1], j[2], j[3]); }

  static void to_json(json& j, CMYKColor c) {
    j = {c.getCyan(), c.getMagenta(), c.getYellow(), c.getBlack()};
  }
};

template <>
struct adl_serializer<ColorVariant> {
  static ColorVariant from_json(const json& j) {
    if (j.is_string()) {
      return COLOR_MAP.at(j.get<std::string>());
    } else {
      const auto& color = j.items().begin();
      if (color.key() == "rgb") {
        return color.value().get<RGBColor>();
      } else {
        Assert(color.key() == "cmyk", "Invalid color type");
        return color.value().get<CMYKColor>();
      }
    }
  }

  static void to_json(json& j, ColorVariant cv) {
    if (std::holds_alternative<RGBColor>(cv)) {
      j = json({{"rgb", std::get<RGBColor>(cv)}});
    } else {
      j = json({{"cmyk", std::get<CMYKColor>(cv)}});
    }
  }
};

template <>
struct adl_serializer<ContourConfig> {
  static ContourConfig from_json(const json& j) {
    return ContourConfig{j.value("interval", 1.0), j.value("min_points", 5u),
                         j.value("color", json({"brown"})).get<ColorVariant>(),
                         j.value("width", 0.14)};
  }

  static void to_json(json& j, ContourConfig cc) {
    j["interval"] = cc.interval;
    j["min_points"] = cc.min_points;
    j["color"] = cc.color;
    j["width"] = cc.width;
  }
};
}  // namespace nlohmann

struct CanopyConfig {
  double min_height;
  double max_height;
  double blocking_threshold;
};

namespace nlohmann {
template <>
struct adl_serializer<CanopyConfig> {
  static CanopyConfig from_json(const json& j) {
    return CanopyConfig{j.value("min_height", 2.5), j.value("max_height", 100.0),
                        j.value("blocking_threshold", 0.1)};
  }

  static void to_json(json& j, CanopyConfig vc) {
    j["min_height"] = vc.min_height;
    j["max_height"] = vc.max_height;
    j["blocking_threshold"] = vc.blocking_threshold;
  }
};
}  // namespace nlohmann

struct BlockingThresholdColorPair {
  double blocking_threshold;
  ColorVariant color;
};

namespace nlohmann {
template <>
struct adl_serializer<BlockingThresholdColorPair> {
  static BlockingThresholdColorPair from_json(const json& j) {
    return BlockingThresholdColorPair{j.value("blocking_threshold", 0.1),
                                      j.value("color", json({"white"})).get<ColorVariant>()};
  }

  static void to_json(json& j, BlockingThresholdColorPair btc) {
    j["blocking_threshold"] = btc.blocking_threshold;
    j["color"] = btc.color;
  }
};
}  // namespace nlohmann

struct VegeHeightConfig {
  std::string name;
  double min_height;
  double max_height;
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

namespace nlohmann {
template <>
struct adl_serializer<VegeHeightConfig> {
  static VegeHeightConfig from_json(const json& j) {
    return VegeHeightConfig{
        j.value("name", "Vegetation"), j.value("min_height", 2.5), j.value("max_height", 100.0),
        j.value("colors", json({})).get<std::vector<BlockingThresholdColorPair>>()};
  }

  static void to_json(json& j, VegeHeightConfig vhc) {
    j["name"] = vhc.name;
    j["min_height"] = vhc.min_height;
    j["max_height"] = vhc.max_height;
    j["colors"] = vhc.colors;
  }
};
}  // namespace nlohmann

struct VegeConfig {
  ColorVariant background_color;
  std::vector<VegeHeightConfig> height_configs;
};

namespace nlohmann {
template <>
struct adl_serializer<VegeConfig> {
  static VegeConfig from_json(const json& j) {
    return VegeConfig{j.value("background_color", json({"white"})).get<ColorVariant>(),
                      j.value("height_configs", json({})).get<std::vector<VegeHeightConfig>>()};
  }

  static void to_json(json& j, VegeConfig vc) {
    j["background_color"] = vc.background_color;
    j["height_configs"] = vc.height_configs;
  }
};
}  // namespace nlohmann

struct RenderConfig {
  double scale;
  double dpi;
};

namespace nlohmann {
template <>
struct adl_serializer<RenderConfig> {
  static RenderConfig from_json(const json& j) {
    return RenderConfig{j.value("scale", 10000.0), j.value("dpi", 600.0)};
  }

  static void to_json(json& j, RenderConfig rc) {
    j["scale"] = rc.scale;
    j["dpi"] = rc.dpi;
  }
};
}  // namespace nlohmann

struct WaterConfig {
  double catchment;
  ColorVariant color;
  double width;
};

struct WaterConfigs {
  std::map<std::string, WaterConfig> configs;

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

namespace nlohmann {
template <>
struct adl_serializer<WaterConfig> {
  static WaterConfig from_json(const json& j) {
    return WaterConfig{.catchment = (j.value("catchment", 0.05)),
                       .color = j.value("color", json({"blue"})),
                       .width = j.value("width", 0.18)};
  }

  static void to_json(json& j, WaterConfig cc) {
    j["catchment"] = cc.catchment;
    j["color"] = cc.color;
    j["width"] = cc.width;
  }
};

template <>
struct adl_serializer<WaterConfigs> {
  static WaterConfigs from_json(const json& j) {
    return WaterConfigs{j.get<std::map<std::string, WaterConfig>>()};
  }

  static void to_json(json& j, WaterConfigs cc) { j = cc.configs; }
};
}  // namespace nlohmann

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

namespace nlohmann {
template <>
struct adl_serializer<ContourConfigs> {
  static ContourConfigs from_json(const json& j) {
    return ContourConfigs(j.get<std::map<std::string, ContourConfig>>());
  }

  static void to_json(json& j, ContourConfigs cc) { j = cc.configs; }
};
}  // namespace nlohmann

struct BuildingsConfig {
  ColorVariant color;
};

namespace nlohmann {
template <>
struct adl_serializer<BuildingsConfig> {
  static BuildingsConfig from_json(const json& j) {
    return BuildingsConfig{j.value("color", json({"black"})).get<ColorVariant>()};
  }

  static void to_json(json& j, BuildingsConfig bc) { j["color"] = bc.color; }
};
}  // namespace nlohmann

enum class ProcessingStep {
  TmpBorders,
  Tiles,
  Combine,
};

SERIALIZE_ENUM_STRICT(ProcessingStep, {
                                          {ProcessingStep::TmpBorders, "tmp_borders"},
                                          {ProcessingStep::Tiles, "tiles"},
                                          {ProcessingStep::Combine, "combine"},
                                      })

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
  fs::path relative_path_to_config;

  friend nlohmann::adl_serializer<Config>;

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

namespace nlohmann {
template <>
struct adl_serializer<Config> {
  static Config from_json(const json& j) {
    Config config;
    config.grid = j.value("grid", json({})).get<GridConfig>();
    config.ground = j.value("ground", json({})).get<GroundConfig>();
    config.contours = j.value("contours", json({})).get<ContourConfigs>();
    config.water = j.value("water", json({})).get<WaterConfigs>();
    config.vege = j.value("vege", json({})).get<VegeConfig>();
    config.render = j.value("render", json({})).get<RenderConfig>();
    config.buildings = j.value("buildings", json({})).get<BuildingsConfig>();
    config.las_files =
        j.value("las_files", json(std::vector<std::string>())).get<std::vector<fs::path>>();
    config.processing_steps = j.value("steps", json({"tiles"})).get<std::set<ProcessingStep>>();
    config.output_directory = j.value("output_directory", "out");
    config.border_width = j.value("border_width", 100.0);
    config.relative_path_to_config = "";
    return config;
  }

  static void to_json(json& j, const Config& gc) {
    j["grid"] = gc.grid;
    j["ground"] = gc.ground;
    j["contours"] = gc.contours;
    j["vege"] = gc.vege;
    j["render"] = gc.render;
    j["colors"] = json({{"primitive", COLOR_MAP}});
    j["buildings"] = gc.buildings;
    j["las_files"] = gc.las_files;
    j["steps"] = gc.processing_steps;
    j["output_directory"] = gc.output_directory;
    j["border_width"] = gc.border_width;
  }
};
}  // namespace nlohmann

inline Config Config::FromFile(const fs::path& filename) {
  std::ifstream file(filename);
  if (!file.is_open()) {
    std::cerr << "Failed to open config file " << filename << std::endl;
    throw std::filesystem::filesystem_error("Failed to open config file " + filename.string(),
                                            std::make_error_code(std::errc::io_error));
  }
  json j;
  try {
    j = json::parse(file, nullptr, true, true);
  } catch (const json::exception& e) {
    std::cerr << "JSON parsing error: " << e.what() << "\n";
    throw e;
  }
  file.close();
  for (const auto& color : j["colors"]["primitive"].items()) {
    COLOR_MAP[color.key()] = color.value().get<ColorVariant>();
  }
  for (const auto& color : j["colors"]["composite"].items()) {
    CMYKColor composite;
    for (const auto& component : color.value().items()) {
      composite =
          composite + to_cmyk(COLOR_MAP.at(component.key())) * component.value().get<double>();
    }
    COLOR_MAP[color.key()] = composite;
  }
  Config c = j.get<Config>();
  c.relative_path_to_config = filename.parent_path();
  return c;
}

inline std::ostream& operator<<(std::ostream& os, const Config& config) {
  os << "Config:\n";
  os << json(config).dump(4);
  return os;
}

inline void Config::write_to_file(const fs::path& filename) const {
  std::ofstream file(filename);
  if (!file.is_open()) {
    std::cerr << "Failed to open config file " << filename << std::endl;
    throw std::filesystem::filesystem_error("Failed to open config file " + filename.string(),
                                            std::make_error_code(std::errc::io_error));
  }
  json j = *this;
  j.erase("relative_path_to_config");
  file << j.dump(4);
  file.close();
}
