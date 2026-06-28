#pragma once

#include <cstddef>
#include <vector>

#include "grid/forward_grid.hpp"
#include "utilities/coordinate.hpp"
#include "utilities/progress_tracker.hpp"

struct WaterConfigs;

struct Stream {
  std::vector<Coordinate2D<double>> coords;
  double catchment;
};

GeoGrid<double> fill_depressions(const GeoGrid<double>& grid, ProgressTracker&& progress_tracker,
                                 const std::vector<Coordinate2D<size_t>>& sinks = {});

std::vector<Coordinate2D<size_t>> identify_sinks(const GeoGrid<double>& grid, double depth,
                                                 double min_area,
                                                 ProgressTracker&& progress_tracker);

std::vector<Stream> stream_paths(const GeoGrid<double>& grid, const WaterConfigs& config,
                                 ProgressTracker&& progress_tracker, bool already_filled = false);
