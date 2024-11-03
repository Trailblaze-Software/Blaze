#pragma once

#include <cstddef>
#include <vector>

#include "grid/forward_grid.hpp"
#include "utilities/coordinate.hpp"

class WaterConfigs;

struct Stream {
  std::vector<Coordinate2D<double>> coords;
  double catchment;
};

GeoGrid<double> fill_depressions(const GeoGrid<double>& grid,
                                 const std::vector<Coordinate2D<size_t>>& sinks = {});

std::vector<Coordinate2D<size_t>> identify_sinks(const GeoGrid<double>& grid, double depth = 3,
                                                 double min_area = 500);

std::vector<Stream> stream_paths(const GeoGrid<double>& grid, const WaterConfigs& config,
                                 bool already_filled = false);
