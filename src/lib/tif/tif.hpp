#pragma once

#include "lib/grid/grid.hpp"
#include "utilities/filesystem.hpp"
#include "utilities/progress_tracker.hpp"

template <typename GridT>
void write_to_tif(const Geo<GridT>& grid, const fs::path& filename,
                  std::optional<ProgressTracker> progress_tracker = {},
                  bool include_vertical_crs = false);

Geo<MultiBand<FlexGrid>> read_tif(const fs::path& filename,
                                  ProgressTracker* progress_tracker = nullptr);

template <typename T>
void write_to_image_tif(const GeoGrid<T>& grid, const fs::path& filename,
                        std::optional<ProgressTracker> progress_tracker = {},
                        std::optional<T> min_val = {}, std::optional<T> max_val = {});
