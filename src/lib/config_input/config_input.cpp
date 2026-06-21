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

namespace {

template <typename T>
T json_number_or(const json& j, const char* key, T default_value) {
  if (!j.contains(key) || j[key].is_null()) {
    return default_value;
  }
  return j[key].get<T>();
}

}  // namespace

template <>
struct adl_serializer<GridConfig> {
  static GridConfig from_json(const json& j) {
    // Defaults for fresh configs.
    constexpr double kDefaultBinRes = 0.5;
    constexpr unsigned int kDefaultDownsample = 3u;
    constexpr double kDefaultVegRes = 3.0;
    constexpr double kDefaultContourRes = 9.0;

    const double bin_res = json_number_or(j, "bin_resolution", kDefaultBinRes);
    const unsigned int downsample = json_number_or(j, "downsample_factor", kDefaultDownsample);

    // Vegetation / contour resolutions are independent of bin/downsample.
    // For backward compatibility, configs that omit these but provide the
    // legacy bin_resolution / downsample_factor keys get the legacy
    // behaviour: vegetation at bin_resolution, contour DEM at the smooth-
    // ground resolution (bin_resolution * downsample_factor). Configs that
    // omit everything get the new defaults.
    const bool has_legacy_only = !j.contains("vegetation_grid_resolution") &&
                                 !j.contains("contour_dem_resolution") &&
                                 (j.contains("bin_resolution") || j.contains("downsample_factor"));

    double veg_res = kDefaultVegRes;
    double contour_res = kDefaultContourRes;
    if (has_legacy_only) {
      veg_res = bin_res;
      contour_res = bin_res * static_cast<double>(downsample);
    }
    veg_res = json_number_or(j, "vegetation_grid_resolution", veg_res);
    contour_res = json_number_or(j, "contour_dem_resolution", contour_res);

    return GridConfig{bin_res, downsample, veg_res, contour_res};
  }

  static void to_json(json& j, GridConfig gc) {
    j["bin_resolution"] = gc.bin_resolution;
    j["downsample_factor"] = gc.downsample_factor;
    j["vegetation_grid_resolution"] = gc.vegetation_grid_resolution;
    j["contour_dem_resolution"] = gc.contour_dem_resolution;
  }
};

template <>
struct adl_serializer<GroundConfig> {
  static GroundConfig from_json(const json& j) {
    return GroundConfig{static_cast<int>(json_number_or(j, "min_ground_intensity", 100)),
                        static_cast<int>(json_number_or(j, "max_ground_intensity", 1000))};
  }

  static void to_json(json& j, GroundConfig gc) {
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
    return BlockingThresholdColorPair{
        json_number_or(j, "blocking_threshold", 0.1),
        j.value("color", json("white")).get<ColorVariant>(), j.value("layer", std::string{}),
        json_number_or(j, "min_area_m2", 0.0), json_number_or(j, "min_hole_area_m2", 0.0)};
  }

  static void to_json(json& j, BlockingThresholdColorPair btc) {
    j["blocking_threshold"] = btc.blocking_threshold;
    j["color"] = btc.color;
    if (!btc.layer.empty()) {
      j["layer"] = btc.layer;
    }
    if (btc.min_area_m2 > 0) {
      j["min_area_m2"] = btc.min_area_m2;
    }
    if (btc.min_hole_area_m2 > 0) {
      j["min_hole_area_m2"] = btc.min_hole_area_m2;
    }
  }
};
template <>
struct adl_serializer<VegeHeightConfig> {
  static VegeHeightConfig from_json(const json& j) {
    return VegeHeightConfig{
        j.value("name", "Vegetation"), json_number_or(j, "min_height", 2.5),
        json_number_or(j, "max_height", 100.0),
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
    return RenderConfig{json_number_or(j, "scale", 10000.0), json_number_or(j, "dpi", 600.0)};
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
    config.tile_size = j.value("tile_size", 0.0);
    config.override_crs = j.value("override_crs", std::string{});
    config.delete_tile_folders = j.value("delete_tile_folders", false);
    config.relative_path_to_config = "";
    return config;
  }

  static void to_json(json& j, const Config& gc) {
    j["grid"] = gc.grid;
    j["ground"] = gc.ground;
    j["contours"] = gc.contours;
    j["water"] = gc.water;
    j["vege"] = gc.vege;
    j["render"] = gc.render;
    j["colors"] = json({{"primitive", COLOR_MAP}});
    j["buildings"] = gc.buildings;
    j["las_files"] = gc.las_files;
    j["steps"] = gc.processing_steps;
    j["output_directory"] = gc.output_directory;
    j["border_width"] = gc.border_width;
    if (gc.tile_size > 0.0) {
      j["tile_size"] = gc.tile_size;
    }
    if (!gc.override_crs.empty()) {
      j["override_crs"] = gc.override_crs;
    }
    if (gc.delete_tile_folders) {
      j["delete_tile_folders"] = gc.delete_tile_folders;
    }
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
  if (j.contains("colors")) {
    if (j["colors"].contains("primitive")) {
      for (const auto& color : j["colors"]["primitive"].items()) {
        COLOR_MAP[color.key()] = color.value().get<ColorVariant>();
      }
    }
    if (j["colors"].contains("composite")) {
      for (const auto& color : j["colors"]["composite"].items()) {
        CMYKColor composite;
        for (const auto& component : color.value().items()) {
          composite =
              composite + to_cmyk(COLOR_MAP.at(component.key())) * component.value().get<double>();
        }
        COLOR_MAP[color.key()] = composite;
      }
    }
  }
  Config c = j.get<Config>();
  c.relative_path_to_config = filename.parent_path();
  return c;
}

std::ostream& operator<<(std::ostream& os, const ProcessingStep& step) { return os << json(step); }
