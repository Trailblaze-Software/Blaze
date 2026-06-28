

# File forward\_grid.hpp

[**File List**](files.md) **>** [**grid**](dir_b440d1ddeab29faa8ab1c63476ee276f.md) **>** [**forward\_grid.hpp**](forward__grid_8hpp.md)

[Go to the documentation of this file](forward__grid_8hpp.md)


```C++
#pragma once

#include <cstddef>

namespace blaze {

enum class InterpolationMode;
struct Point;
struct Rect;
struct Size;

}  // namespace blaze

class Contour;
class GDALDataset;
class RGBColor;
class CMYKColor;

template <typename T>
class Coordinate2D;

struct Extent2D;

struct ContourConfigs;
struct WaterConfigs;
struct Stream;

class GridData;
class GeoTransform;
class GeoProjection;
class GeoGridData;
class FlexGrid;
struct BlazeBool;

template <typename U>
class Grid;

template <typename GridT>
class Geo;

template <typename GridT>
class MultiBand;

template <typename T>
class GridGraph;

template <typename T>
using GeoGrid = Geo<Grid<T>>;

using GeoImgGrid = GeoGrid<RGBColor>;
using GeoFlexGrid = Geo<FlexGrid>;

size_t num_cells_by_distance(double x, double dx);

template <typename T>
T interpolate_value(const GeoGrid<T>& grid, const Coordinate2D<double>& projection_coord);
```


