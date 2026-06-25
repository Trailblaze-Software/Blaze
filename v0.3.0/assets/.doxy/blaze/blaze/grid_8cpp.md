

# File grid.cpp



[**FileList**](files.md) **>** [**grid**](dir_b440d1ddeab29faa8ab1c63476ee276f.md) **>** [**grid.cpp**](grid_8cpp.md)

[Go to the source code of this file](grid_8cpp_source.md)



* `#include "grid.hpp"`
* `#include <iostream>`
* `#include <span>`
* `#include "gdal_priv.h"`
* `#include "img_grid.hpp"`
* `#include "isom/colors.hpp"`
* `#include "las/las_point.hpp"`
* `#include "utilities/timer.hpp"`





































## Public Functions

| Type | Name |
| ---: | :--- |
|  T | [**interpolate\_value**](#function-interpolate_value) (const [**GeoGrid**](classGeo.md)&lt; T &gt; & grid, const [**Coordinate2D**](classCoordinate2D.md)&lt; double &gt; & projection\_coord) <br> |
|  template double | [**interpolate\_value**](#function-interpolate_value) (const [**GeoGrid**](classGeo.md)&lt; double &gt; & grid, const [**Coordinate2D**](classCoordinate2D.md)&lt; double &gt; & projection\_coord) <br> |
|  template float | [**interpolate\_value**](#function-interpolate_value) (const [**GeoGrid**](classGeo.md)&lt; float &gt; & grid, const [**Coordinate2D**](classCoordinate2D.md)&lt; double &gt; & projection\_coord) <br> |
|  [**Geo**](classGeo.md)&lt; GridT &gt; | [**same\_type\_different\_size**](#function-same_type_different_size) (const [**Geo**](classGeo.md)&lt; GridT &gt; & grid, size\_t new\_width, size\_t new\_height, const [**Coordinate2D**](classCoordinate2D.md)&lt; double &gt; & new\_top\_left) <br> |




























## Public Functions Documentation




### function interpolate\_value 

```C++
template<typename T>
T interpolate_value (
    const GeoGrid < T > & grid,
    const Coordinate2D < double > & projection_coord
) 
```




<hr>



### function interpolate\_value 

```C++
template double interpolate_value (
    const GeoGrid < double > & grid,
    const Coordinate2D < double > & projection_coord
) 
```




<hr>



### function interpolate\_value 

```C++
template float interpolate_value (
    const GeoGrid < float > & grid,
    const Coordinate2D < double > & projection_coord
) 
```




<hr>



### function same\_type\_different\_size 

```C++
template<typename GridT>
Geo < GridT > same_type_different_size (
    const Geo < GridT > & grid,
    size_t new_width,
    size_t new_height,
    const Coordinate2D < double > & new_top_left
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/lib/grid/grid.cpp`

