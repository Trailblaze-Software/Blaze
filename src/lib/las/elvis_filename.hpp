#pragma once

#include <optional>
#include <regex>
#include <string>

#include "grid/grid.hpp"
#include "utilities/filesystem.hpp"

// Infers the CRS of a tile from its ELVIS (Geoscience Australia / NSW Spatial
// Services) file name, for files that have no embedded CRS, e.g.
//   Oberon201311-PHO3-C0-AHD_7606234_55_0002_0002.laz
//   <project><year>[month]-..._<easting km><northing km>_<MGA zone>_<width km>_<height km>
// The name gives the MGA zone but not the datum, so tiles captured from 2020
// use GDA2020 (EPSG:78zz) and older ones GDA94 (EPSG:283zz). The name is only
// trusted if `bounds` lie within the tile footprint it describes. Returns the
// EPSG code, or nullopt.
inline std::optional<int> elvis_filename_epsg(const fs::path& path, const Extent2D& bounds) {
  static const std::regex pattern(
      R"(^[^0-9]*((?:19|20)\d\d).*_(\d{3})(\d{4})_(\d{2})_(\d{4})_(\d{4})$)");
  const std::string stem = path.stem().string();
  std::smatch m;
  if (!std::regex_match(stem, m, pattern)) return std::nullopt;
  const int year = std::stoi(m[1]);
  const double minx = std::stod(m[2]) * 1000.0;
  const double miny = std::stod(m[3]) * 1000.0;
  const int zone = std::stoi(m[4]);
  const double maxx = minx + std::stod(m[5]) * 1000.0;
  const double maxy = miny + std::stod(m[6]) * 1000.0;
  if (zone < 49 || zone > 56) return std::nullopt;

  constexpr double tolerance_m = 10.0;
  if (bounds.minx < minx - tolerance_m || bounds.maxx > maxx + tolerance_m ||
      bounds.miny < miny - tolerance_m || bounds.maxy > maxy + tolerance_m) {
    return std::nullopt;
  }
  return (year >= 2020 ? 7800 : 28300) + zone;
}
