

# File process.cpp



[**FileList**](files.md) **>** [**src**](dir_68267d1309a1af8e8297ef4c3efbcdba.md) **>** [**process.cpp**](process_8cpp.md)

[Go to the source code of this file](process_8cpp_source.md)



* `#include "process.hpp"`
* `#include "cliff/cliff.hpp"`
* `#include "contour/contour_gen.hpp"`
* `#include "crt/crt.hpp"`
* `#include "grid/grid_ops.hpp"`
* `#include "grid/img_grid.hpp"`
* `#include "io/gpkg.hpp"`
* `#include "isom/colors.hpp"`
* `#include "las/las_file.hpp"`
* `#include "las/las_point.hpp"`
* `#include "lib/grid/grid.hpp"`
* `#include "lib/vegetation/vegetation.hpp"`
* `#include "methods/hill_shade/hill_shade.hpp"`
* `#include "methods/water/water.hpp"`
* `#include "tif/tif.hpp"`
* `#include "utilities/progress_tracker.hpp"`

















## Public Types

| Type | Name |
| ---: | :--- |
| enum  | [**GroundMethod**](#enum-groundmethod)  <br> |




## Public Attributes

| Type | Name |
| ---: | :--- |
|  [**constexpr**](classCoordinate2D.md) [**bool**](classCoordinate2D.md) | [**OUT\_LAS**](#variable-out_las)   = `[**false**](classCoordinate2D.md)`<br> |
















## Public Functions

| Type | Name |
| ---: | :--- |
|  [**GeoGrid**](classGeo.md)&lt; [**double**](classCoordinate2D.md) &gt; | [**adjust\_ground\_to\_slope**](#function-adjust_ground_to_slope) ([**const**](classCoordinate2D.md) [**GeoGrid**](classGeo.md)&lt; [**double**](classCoordinate2D.md) &gt; & grid, [**double**](classCoordinate2D.md) original\_resolution) <br> |
|  [**GeoGrid**](classGeo.md)&lt; [**double**](classCoordinate2D.md) &gt; | [**get\_pixel\_heights**](#function-get_pixel_heights) ([**const**](classCoordinate2D.md) [**GeoGrid**](classGeo.md)&lt; std::optional&lt; [**LASPoint**](classLASPoint.md) &gt; &gt; & ground\_points, GroundMethod method=GroundMethod::LOWEST\_POINT) <br> |
|  [**void**](classCoordinate2D.md) | [**process\_las\_data**](#function-process_las_data) ([**LASData**](classLASData.md) & las\_file, [**const**](classCoordinate2D.md) fs::path & output\_dir, [**const**](classCoordinate2D.md) [**Config**](structConfig.md) & config, [**ProgressTracker**](classProgressTracker.md) progress\_tracker) <br> |
|  [**void**](classCoordinate2D.md) | [**process\_las\_file**](#function-process_las_file) ([**const**](classCoordinate2D.md) fs::path & las\_filename, [**const**](classCoordinate2D.md) [**Config**](structConfig.md) & config, [**ProgressTracker**](classProgressTracker.md) progress\_tracker) <br> |




























## Public Types Documentation




### enum GroundMethod 

```C++
enum GroundMethod {
    LOWER_BOUND,
    LOWEST_POINT,
    INTERPOLATE
};
```




<hr>
## Public Attributes Documentation




### variable OUT\_LAS 

```C++
constexpr bool OUT_LAS;
```




<hr>
## Public Functions Documentation




### function adjust\_ground\_to\_slope 

```C++
GeoGrid < double > adjust_ground_to_slope (
    const  GeoGrid < double > & grid,
    double original_resolution
) 
```




<hr>



### function get\_pixel\_heights 

```C++
GeoGrid < double > get_pixel_heights (
    const  GeoGrid < std::optional< LASPoint > > & ground_points,
    GroundMethod method=GroundMethod::LOWEST_POINT
) 
```




<hr>



### function process\_las\_data 

```C++
void process_las_data (
    LASData & las_file,
    const fs::path & output_dir,
    const  Config & config,
    ProgressTracker progress_tracker
) 
```




<hr>



### function process\_las\_file 

```C++
void process_las_file (
    const fs::path & las_filename,
    const  Config & config,
    ProgressTracker progress_tracker
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/process.cpp`

