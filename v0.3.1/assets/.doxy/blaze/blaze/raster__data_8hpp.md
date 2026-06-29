

# File raster\_data.hpp



[**FileList**](files.md) **>** [**gui**](dir_99d0482cf009f9d97a0877749b817f19.md) **>** [**raster\_data.hpp**](raster__data_8hpp.md)

[Go to the source code of this file](raster__data_8hpp_source.md)



* `#include <gdal.h>`
* `#include <algorithm>`
* `#include <atomic>`
* `#include <cmath>`
* `#include <future>`
* `#include <mutex>`
* `#include <optional>`
* `#include <vector>`
* `#include "grid/grid.hpp"`
* `#include "io/crs.hpp"`
* `#include "io/gdal_init.hpp"`
* `#include "tif/tif.hpp"`
* `#include "utilities/progress_tracker.hpp"`















## Classes

| Type | Name |
| ---: | :--- |
| class | [**AsyncRasterData**](classAsyncRasterData.md) <br> |
| struct | [**DemMeshData**](structDemMeshData.md) <br> |
| struct | [**TifMetadata**](structTifMetadata.md) <br> |






















## Public Functions

| Type | Name |
| ---: | :--- |
|  [**DemMeshData**](structDemMeshData.md) | [**build\_dem\_mesh**](#function-build_dem_mesh) (const [**Geo**](classGeo.md)&lt; [**MultiBand**](classMultiBand.md)&lt; [**FlexGrid**](classFlexGrid.md) &gt; &gt; & grid, int stride=1, const [**Geo**](classGeo.md)&lt; [**MultiBand**](classMultiBand.md)&lt; [**FlexGrid**](classFlexGrid.md) &gt; &gt; \* texture=nullptr) <br> |
|  [**DemMeshData**](structDemMeshData.md) | [**build\_flat\_cell\_dem\_mesh**](#function-build_flat_cell_dem_mesh) (const [**Geo**](classGeo.md)&lt; [**MultiBand**](classMultiBand.md)&lt; [**FlexGrid**](classFlexGrid.md) &gt; &gt; & grid, int stride=1) <br> |
|  [**DemMeshData**](structDemMeshData.md) | [**build\_slope\_colored\_mesh**](#function-build_slope_colored_mesh) (const [**Geo**](classGeo.md)&lt; [**MultiBand**](classMultiBand.md)&lt; [**FlexGrid**](classFlexGrid.md) &gt; &gt; & slope\_grid, const [**Geo**](classGeo.md)&lt; [**MultiBand**](classMultiBand.md)&lt; [**FlexGrid**](classFlexGrid.md) &gt; &gt; & dem\_grid, int stride=1) <br> |
|  [**DemMeshData**](structDemMeshData.md) | [**build\_textured\_dem\_mesh**](#function-build_textured_dem_mesh) (const [**Geo**](classGeo.md)&lt; [**MultiBand**](classMultiBand.md)&lt; [**FlexGrid**](classFlexGrid.md) &gt; &gt; & dem\_grid, const [**Geo**](classGeo.md)&lt; [**MultiBand**](classMultiBand.md)&lt; [**FlexGrid**](classFlexGrid.md) &gt; &gt; & texture\_grid, int stride=1, OGRCoordinateTransformation \* coord\_transform=nullptr) <br> |
|  void | [**compute\_mesh\_normals**](#function-compute_mesh_normals) ([**DemMeshData**](structDemMeshData.md) & mesh) <br> |
|  void | [**compute\_terrain\_normals\_from\_dem**](#function-compute_terrain_normals_from_dem) ([**DemMeshData**](structDemMeshData.md) & mesh, const [**Geo**](classGeo.md)&lt; [**MultiBand**](classMultiBand.md)&lt; [**FlexGrid**](classFlexGrid.md) &gt; &gt; & dem\_grid, int stride, size\_t cols, size\_t rows) <br> |
|  double | [**flex\_grid\_value**](#function-flex_grid_value) (const [**FlexGrid**](classFlexGrid.md) & band, size\_t x, size\_t y) <br> |
|  bool | [**is\_valid\_elevation**](#function-is_valid_elevation) (double value) <br> |
|  std::array&lt; size\_t, 2 &gt; | [**read\_tif\_dimensions**](#function-read_tif_dimensions) (const fs::path & path) <br> |
|  [**TifMetadata**](structTifMetadata.md) | [**read\_tif\_metadata**](#function-read_tif_metadata) (const fs::path & path) <br> |
|  void | [**reproject\_dem\_mesh\_horizontal**](#function-reproject_dem_mesh_horizontal) ([**DemMeshData**](structDemMeshData.md) & mesh, OGRCoordinateTransformation \* ct) <br> |
|  double | [**sample\_grid\_bilinear**](#function-sample_grid_bilinear) (const [**FlexGrid**](classFlexGrid.md) & band, double px, double py) <br> |
|  std::pair&lt; float, float &gt; | [**texture\_uv\_from\_projection**](#function-texture_uv_from_projection) (const [**GeoTransform**](classGeoTransform.md) & texture\_transform, size\_t texture\_width, size\_t texture\_height, const [**Coordinate2D**](classCoordinate2D.md)&lt; double &gt; & coord) <br> |




























## Public Functions Documentation




### function build\_dem\_mesh 

```C++
inline DemMeshData build_dem_mesh (
    const Geo < MultiBand < FlexGrid > > & grid,
    int stride=1,
    const Geo < MultiBand < FlexGrid > > * texture=nullptr
) 
```




<hr>



### function build\_flat\_cell\_dem\_mesh 

```C++
inline DemMeshData build_flat_cell_dem_mesh (
    const Geo < MultiBand < FlexGrid > > & grid,
    int stride=1
) 
```




<hr>



### function build\_slope\_colored\_mesh 

```C++
inline DemMeshData build_slope_colored_mesh (
    const Geo < MultiBand < FlexGrid > > & slope_grid,
    const Geo < MultiBand < FlexGrid > > & dem_grid,
    int stride=1
) 
```




<hr>



### function build\_textured\_dem\_mesh 

```C++
inline DemMeshData build_textured_dem_mesh (
    const Geo < MultiBand < FlexGrid > > & dem_grid,
    const Geo < MultiBand < FlexGrid > > & texture_grid,
    int stride=1,
    OGRCoordinateTransformation * coord_transform=nullptr
) 
```




<hr>



### function compute\_mesh\_normals 

```C++
inline void compute_mesh_normals (
    DemMeshData & mesh
) 
```




<hr>



### function compute\_terrain\_normals\_from\_dem 

```C++
inline void compute_terrain_normals_from_dem (
    DemMeshData & mesh,
    const Geo < MultiBand < FlexGrid > > & dem_grid,
    int stride,
    size_t cols,
    size_t rows
) 
```




<hr>



### function flex\_grid\_value 

```C++
inline double flex_grid_value (
    const FlexGrid & band,
    size_t x,
    size_t y
) 
```




<hr>



### function is\_valid\_elevation 

```C++
inline bool is_valid_elevation (
    double value
) 
```




<hr>



### function read\_tif\_dimensions 

```C++
inline std::array< size_t, 2 > read_tif_dimensions (
    const fs::path & path
) 
```




<hr>



### function read\_tif\_metadata 

```C++
inline TifMetadata read_tif_metadata (
    const fs::path & path
) 
```




<hr>



### function reproject\_dem\_mesh\_horizontal 

```C++
inline void reproject_dem_mesh_horizontal (
    DemMeshData & mesh,
    OGRCoordinateTransformation * ct
) 
```




<hr>



### function sample\_grid\_bilinear 

```C++
inline double sample_grid_bilinear (
    const FlexGrid & band,
    double px,
    double py
) 
```




<hr>



### function texture\_uv\_from\_projection 

```C++
inline std::pair< float, float > texture_uv_from_projection (
    const GeoTransform & texture_transform,
    size_t texture_width,
    size_t texture_height,
    const Coordinate2D < double > & coord
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/gui/raster_data.hpp`

