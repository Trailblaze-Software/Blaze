

# File water.hpp

[**File List**](files.md) **>** [**methods**](dir_0525f968218f30056a0344f59b10bbbb.md) **>** [**water**](dir_9906ac72c69ac5c4da1443f27a433c13.md) **>** [**water.hpp**](water_8hpp.md)

[Go to the documentation of this file](water_8hpp.md)


```C++
#pragma once

#include <cstddef>
#include <vector>

#include "grid/forward_grid.hpp"
#include "utilities/coordinate.hpp"

struct WaterConfigs;
class ProgressTracker;

struct Stream {
  std::vector<Coordinate2D<double>> coords;
  double catchment;
};

GeoGrid<double> fill_depressions(const GeoGrid<double>& grid,
                                 const std::vector<Coordinate2D<size_t>>& sinks = {});

std::vector<Coordinate2D<size_t>> identify_sinks(const GeoGrid<double>& grid, double depth = 10,
                                                 double min_area = 5000);

std::vector<Stream> stream_paths(const GeoGrid<double>& grid, const WaterConfigs& config,
                                 ProgressTracker progress_tracker, bool already_filled = false);
```


