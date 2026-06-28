

# File forward\_grid.hpp



[**FileList**](files.md) **>** [**grid**](dir_b440d1ddeab29faa8ab1c63476ee276f.md) **>** [**forward\_grid.hpp**](forward__grid_8hpp.md)

[Go to the source code of this file](forward__grid_8hpp_source.md)



* `#include <cstddef>`













## Namespaces

| Type | Name |
| ---: | :--- |
| namespace | [**blaze**](namespaceblaze.md) <br> |




## Public Types

| Type | Name |
| ---: | :--- |
| typedef [**Geo**](classGeo.md)&lt; [**FlexGrid**](classFlexGrid.md) &gt; | [**GeoFlexGrid**](#typedef-geoflexgrid)  <br> |
| typedef [**Geo**](classGeo.md)&lt; [**Grid**](classGrid.md)&lt; T &gt; &gt; | [**GeoGrid**](#typedef-geogrid)  <br> |
| typedef [**GeoGrid**](classGeo.md)&lt; [**RGBColor**](classRGBColor.md) &gt; | [**GeoImgGrid**](#typedef-geoimggrid)  <br> |




















## Public Functions

| Type | Name |
| ---: | :--- |
|  T | [**interpolate\_value**](#function-interpolate_value) (const [**GeoGrid**](classGeo.md)&lt; T &gt; & grid, const [**Coordinate2D**](classCoordinate2D.md)&lt; double &gt; & projection\_coord) <br> |
|  size\_t | [**num\_cells\_by\_distance**](#function-num_cells_by_distance) (double x, double dx) <br> |




























## Public Types Documentation




### typedef GeoFlexGrid 

```C++
using GeoFlexGrid =  Geo<FlexGrid>;
```




<hr>



### typedef GeoGrid 

```C++
using GeoGrid =  Geo<Grid<T> >;
```




<hr>



### typedef GeoImgGrid 

```C++
using GeoImgGrid =  GeoGrid<RGBColor>;
```




<hr>
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



### function num\_cells\_by\_distance 

```C++
inline size_t num_cells_by_distance (
    double x,
    double dx
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/lib/grid/forward_grid.hpp`

