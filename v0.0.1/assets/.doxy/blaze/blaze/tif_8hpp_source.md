

# File tif.hpp

[**File List**](files.md) **>** [**lib**](dir_c85d3e3c5052e9ad9ce18c6863244a25.md) **>** [**tif**](dir_ca784dd9e8c063f2791dae69e4495085.md) **>** [**tif.hpp**](tif_8hpp.md)

[Go to the documentation of this file](tif_8hpp.md)


```C++
#pragma once

#include "lib/grid/grid.hpp"
#include "utilities/filesystem.hpp"
#include "utilities/progress_tracker.hpp"

template <typename GridT>
void write_to_tif(const Geo<GridT>& grid, const fs::path& filename,
                  std::optional<ProgressTracker> progress_tracker = {});

Geo<MultiBand<FlexGrid>> read_tif(const fs::path& filename);

template <typename T>
void write_to_image_tif(const GeoGrid<T>& grid, const fs::path& filename,
                        std::optional<ProgressTracker> progress_tracker = {});
```


