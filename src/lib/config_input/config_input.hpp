#pragma once

#include <iostream>
#include <fstream>
#include "assert/assert.hpp"
#include "au/prefix.hh"
#include "au/io.hh"
#include "au/math.hh"
#include "au/quantity.hh"
#include "isom/colors.hpp"

#define JSON_DIAGNOSTICS 1
#include <nlohmann/json.hpp>

#include <au/units/meters.hh>
#include <au/units/inches.hh>
#include <au/units/unos.hh>
#include "utilities/filesystem.hpp"

using json=nlohmann::json;

struct GridConfig {
  const au::QuantityD<au::Meters> bin_resolution;
  const unsigned int downsample_factor;
};

namespace nlohmann
{
template <>
struct adl_serializer<GridConfig>
{
    static GridConfig from_json(const json& j)
    {
        return GridConfig{au::meters(j.value("bin_resolution", 1.0)), j.value("downsample_factor", 3u)};
    }

    static void to_json(json& j,GridConfig gc)
    {
        j["bin_resolution"] = gc.bin_resolution.in(au::meters);
        j["downsample_factor"] = gc.downsample_factor;
    }
};
}

struct GroundConfig {
  const au::QuantityD<au::Meters> outlier_removal_height_diff;
};

namespace nlohmann
{
template <>
struct adl_serializer<GroundConfig>
{
    static GroundConfig from_json(const json& j)
    {
        return GroundConfig{au::meters(j.value("outlier_removal_height_diff", 1.0))};
    }

    static void to_json(json& j,GroundConfig gc)
    {
        j["outlier_removal_height_diff"] = gc.outlier_removal_height_diff.in(au::meters);
    }
};
}


struct ContourConfig {
  const au::QuantityD<au::Meters> interval;
  const unsigned int min_points;
  const ColorVariant color;
  const au::QuantityD<au::Milli<au::Meters>> width;
};

namespace nlohmann
{
template <>
struct adl_serializer<RGBColor> {
    static RGBColor from_json(const json& j)
    {
        return RGBColor(j[0], j[1], j[2], j[3]);
    }

    static void to_json(json& j,RGBColor c)
    {
        j = {c.getRed(), c.getGreen(), c.getBlue(), c.getAlpha()};
    }
};

template <>
struct adl_serializer<CMYKColor> {
    static CMYKColor from_json(const json& j)
    {
        return CMYKColor(j[0], j[1], j[2], j[3]);
    }

    static void to_json(json& j,CMYKColor c)
    {
        j = {c.getCyan(), c.getMagenta(), c.getYellow(), c.getBlack()};
    }
};

template <>
struct adl_serializer<ColorVariant>
{
    static ColorVariant from_json(const json& j)
    {
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

    static void to_json(json& j,ColorVariant cv)
    {
      if (std::holds_alternative<RGBColor>(cv)) {
        j = json({{"rgb", std::get<RGBColor>(cv)}});
      } else {
        j = json({{"cmyk", std::get<CMYKColor>(cv)}});
      }
    }
};

template <>
struct adl_serializer<ContourConfig>
{
    static ContourConfig from_json(const json& j)
    {
        return ContourConfig{au::meters(j.value("interval", 1.0)), j.value("min_points", 5u),
          j.value("color", json({"brown"})).get<ColorVariant>(), au::milli(au::meters)(j.value("width", 0.14))};
    }

    static void to_json(json& j,ContourConfig cc)
    {
        j["interval"] = cc.interval.in(au::meters);
        j["min_points"] = cc.min_points;
        j["color"] = cc.color;
        j["width"] = cc.width.in(au::milli(au::meters));
    }
};
}

struct CanopyConfig {
  const au::QuantityD<au::Meters> min_height;
  const au::QuantityD<au::Meters> max_height;
  const double blocking_threshold;
};

namespace nlohmann
{
template <>
struct adl_serializer<CanopyConfig>
{
    static CanopyConfig from_json(const json& j)
    {
        return CanopyConfig{au::meters(j.value("min_height", 2.5)), au::meters(j.value("max_height", 100)), j.value("blocking_threshold", 0.1)};
    }

    static void to_json(json& j,CanopyConfig vc)
    {
        j["min_height"] = vc.min_height.in(au::meters);
        j["max_height"] = vc.max_height.in(au::meters);
        j["blocking_threshold"] = vc.blocking_threshold;
    }
};
}

struct BlockingThresholdColorPair {
  double blocking_threshold;
  ColorVariant color;
};

namespace nlohmann
{
template <>
struct adl_serializer<BlockingThresholdColorPair>
{
    static BlockingThresholdColorPair from_json(const json& j)
    {
        return BlockingThresholdColorPair{j.value("blocking_threshold", 0.1), j.value("color", json({"white"})).get<ColorVariant>()};
    }

    static void to_json(json& j,BlockingThresholdColorPair btc)
    {
        j["blocking_threshold"] = btc.blocking_threshold;
        j["color"] = btc.color;
    }
};
}

struct VegeHeightConfig {
   std::string label;
   au::QuantityD<au::Meters> min_height;
 au::QuantityD<au::Meters> max_height;
   std::vector<BlockingThresholdColorPair> colors;
};

namespace nlohmann
{
template <>
struct adl_serializer<VegeHeightConfig>
{
    static VegeHeightConfig from_json(const json& j)
    {
        return VegeHeightConfig{j.value("label", "Vegetation"), au::meters(j.value("min_height", 2.5)), au::meters(j.value("max_height", 100)), j.value("colors", json({})).get<std::vector<BlockingThresholdColorPair>>()};
    }

    static void to_json(json& j,VegeHeightConfig vhc)
    {
        j["label"] = vhc.label;
        j["min_height"] = vhc.min_height.in(au::meters);
        j["max_height"] = vhc.max_height.in(au::meters);
        j["colors"] = vhc.colors;
    }
};
}

struct VegeConfig {
  const ColorVariant background_color;
  const std::vector<std::unique_ptr<VegeHeightConfig>> height_configs;
};

namespace nlohmann
{
template <>
struct adl_serializer<VegeConfig>
{
    static VegeConfig from_json(const json& j)
    {
        return VegeConfig{j.value("background_color", json({"white"})).get<ColorVariant>(), j.value("height_configs", json({})).get<std::vector<VegeHeightConfig>>()};
    }

    static void to_json(json& j,VegeConfig vc)
    {
      j["background_color"] = vc.background_color;
      j["height_configs"] = vc.height_configs;
    }
};
}

struct RenderConfig {
  const double scale;
  const au::QuantityD<au::UnitPowerT<au::Inches, -1>> dpi;
};

namespace nlohmann
{
template <>
struct adl_serializer<RenderConfig>
{
    static RenderConfig from_json(const json& j)
    {
        return RenderConfig{j.value("scale", 10000.0), (au::inverse(au::inches))(j.value("dpi", 600.0))};
    }

    static void to_json(json& j,RenderConfig rc)
    {
        j["scale"] = rc.scale;
        j["dpi"] = rc.dpi.in(au::inverse(au::inches));
    }
};
}

struct ContourConfigs {
  const std::map<std::string, ContourConfig> configs;
  const au::QuantityD<au::Meters> min_interval;

  static au::QuantityD<au::Meters> minimum_interval(const std::map<std::string, ContourConfig>& configs) {
    au::QuantityD<au::Meters> min_interval = std::numeric_limits<au::QuantityD<au::Meters>>::max();
    for (const auto& [_, config] : configs) {
      min_interval = std::min(min_interval, config.interval);
    }
    return min_interval;
  }

  explicit ContourConfigs(std::map<std::string, ContourConfig> in_configs)
      : configs(std::move(in_configs)), min_interval(minimum_interval(configs)) {}

  const ContourConfig& operator[](const std::string& key) const {
    return configs.at(key);
  }

  const ContourConfig& pick_from_height(double height) const {
    double max_valid_interval = std::numeric_limits<double>::min();
    const ContourConfig* config_to_return = nullptr;
    for (const auto& [_, config] : configs) {
      if (config.interval > au::meters(max_valid_interval) && std::fmod(std::abs(height), config.interval.in(au::meters)) < 1e-8) {
        max_valid_interval = config.interval.in(au::meters);
        config_to_return = &config;
      }
    }
    return *config_to_return;
  }
};

namespace nlohmann
{
template <>
struct adl_serializer<ContourConfigs>
{
    static ContourConfigs from_json(const json& j)
    {
        return ContourConfigs(j.get<std::map<std::string, ContourConfig>>());
    }

    static void to_json(json& j,ContourConfigs cc)
    {
        j = cc.configs;
    }
};
}

struct Config {
  const GridConfig grid;
  const GroundConfig ground;
  const ContourConfigs contours;
  const VegeConfig vege;
  const RenderConfig render;

  static Config FromFile(const fs::path& filename);

  friend std::ostream& operator<<(std::ostream& os, const Config& config);
};

namespace nlohmann
{
template <>
struct adl_serializer<Config>
{
    static Config from_json(const json& j)
    {
      return Config{j.value("grid", json({})).get<GridConfig>(), j.value("ground", json({})).get<GroundConfig>(), j.value("contours", json({})).get<ContourConfigs>(), j.value("vege", json({})).get<VegeConfig>(), j.value("render", json({})).get<RenderConfig>()};
    }

    static void to_json(json& j,Config gc)
    {
      j["grid"] = gc.grid;
      j["ground"] = gc.ground;
      j["contours"] = gc.contours;
      j["vege"] = gc.vege;
      j["render"] = gc.render;
      j["colors"] = json({{"primitive", COLOR_MAP}});
    }
};
}


inline Config Config::FromFile(const fs::path& filename) {
  std::ifstream file(filename);
  if (!file.is_open()) {
    std::cerr << "Failed to open file\n";
    throw std::filesystem::filesystem_error("Failed to open file", std::make_error_code(std::errc::io_error));
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
  } for (const auto& color : j["colors"]["composite"].items()) {
    CMYKColor composite;
    for (const auto& component : color.value().items()) {
      composite = composite + to_cmyk(COLOR_MAP.at(component.key())) * component.value().get<double>();
    }
    COLOR_MAP[color.key()] = composite;
  }
  return j.get<Config>();
}

inline std::ostream& operator<<(std::ostream& os, const Config& config)
{
  os << "Config:\n";
  os << json(config).dump(4);
  return os;
}
