

# File config\_input.cpp

[**File List**](files.md) **>** [**config\_input**](dir_7e7c57be6e217d4e927a2ff8d648cb71.md) **>** [**config\_input.cpp**](config__input_8cpp.md)

[Go to the documentation of this file](config__input_8cpp.md)


```C++
#include "config_input.hpp"

#include <fstream>

#include "assert/assert.hpp"

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
                         j.value("color", json("brown")).get<ColorVariant>(),
                         j.value("width", 0.14)};
  }

  static void to_json(json& j, ContourConfig cc) {
    j["interval"] = cc.interval;
    j["min_points"] = cc.min_points;
    j["color"] = cc.color;
    j["width"] = cc.width;
  }
};

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

template <>
struct adl_serializer<BlockingThresholdColorPair> {
  static BlockingThresholdColorPair from_json(const json& j) {
    return BlockingThresholdColorPair{j.value("blocking_threshold", 0.1),
                                      j.value("color", json("white")).get<ColorVariant>()};
  }

  static void to_json(json& j, BlockingThresholdColorPair btc) {
    j["blocking_threshold"] = btc.blocking_threshold;
    j["color"] = btc.color;
  }
};
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

template <>
struct adl_serializer<VegeConfig> {
  static VegeConfig from_json(const json& j) {
    return VegeConfig{j.value("background_color", json("white")).get<ColorVariant>(),
                      j.value("height_configs", json({})).get<std::vector<VegeHeightConfig>>()};
  }

  static void to_json(json& j, VegeConfig vc) {
    j["background_color"] = vc.background_color;
    j["height_configs"] = vc.height_configs;
  }
};
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

template <>
struct adl_serializer<WaterConfig> {
  static WaterConfig from_json(const json& j) {
    return WaterConfig{.catchment = j.value("catchment", 0.05),
                       .color = j.value("color", json("blue")),
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

template <>
struct adl_serializer<ContourConfigs> {
  static ContourConfigs from_json(const json& j) {
    return ContourConfigs(j.get<std::map<std::string, ContourConfig>>());
  }

  static void to_json(json& j, ContourConfigs cc) { j = cc.configs; }
};

template <>
struct adl_serializer<BuildingsConfig> {
  static BuildingsConfig from_json(const json& j) {
    return BuildingsConfig{j.value("color", json("black")).get<ColorVariant>()};
  }

  static void to_json(json& j, BuildingsConfig bc) { j["color"] = bc.color; }
};

SERIALIZE_ENUM_STRICT(ProcessingStep, {
                                          {ProcessingStep::Tiles, "tiles"},
                                          {ProcessingStep::Combine, "combine"},
                                      })

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

std::ostream& operator<<(std::ostream& os, const Config& config) {
  os << "Config:\n";
  os << json(config).dump(4);
  return os;
}

void Config::write_to_file(const fs::path& filename) const {
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

Config Config::FromFile(const fs::path& filename) {
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

std::ostream& operator<<(std::ostream& os, const ProcessingStep& step) { return os << json(step); }
```


