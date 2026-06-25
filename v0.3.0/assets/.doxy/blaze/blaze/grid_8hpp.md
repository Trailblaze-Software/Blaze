

# File grid.hpp



[**FileList**](files.md) **>** [**grid**](dir_b440d1ddeab29faa8ab1c63476ee276f.md) **>** [**grid.hpp**](grid_8hpp.md)

[Go to the source code of this file](grid_8hpp_source.md)



* `#include <algorithm>`
* `#include <cmath>`
* `#include <cstddef>`
* `#include <cstring>`
* `#include <limits>`
* `#include <memory>`
* `#include <stdexcept>`
* `#include <string>`
* `#include <type_traits>`
* `#include <vector>`
* `#include "assert/assert.hpp"`
* `#include "utilities/coordinate.hpp"`















## Classes

| Type | Name |
| ---: | :--- |
| struct | [**BlazeBool**](structBlazeBool.md) <br> |
| class | [**FlexGrid**](classFlexGrid.md) <br> |
| class | [**Geo**](classGeo.md) &lt;typename GridT&gt;<br> |
| class | [**GeoGridData**](classGeoGridData.md) <br> |
| class | [**GeoProjection**](classGeoProjection.md) <br> |
| class | [**GeoTransform**](classGeoTransform.md) <br> |
| class | [**Grid**](classGrid.md) &lt;typename U&gt;<br> |
| class | [**GridData**](classGridData.md) <br> |
| class | [**GridGraph**](classGridGraph.md) &lt;typename T&gt;<br> |
| class | [**MultiBand**](classMultiBand.md) &lt;typename GridT&gt;<br> |
| struct | [**is\_specialization**](structis__specialization.md) &lt;typename Test, Ref&gt;<br> |
| struct | [**is\_specialization&lt; Ref&lt; Args... &gt;, Ref &gt;**](structis__specialization_3_01Ref_3_01Args_8_8_8_01_4_00_01Ref_01_4.md) &lt;Ref, Args&gt;<br> |


## Public Types

| Type | Name |
| ---: | :--- |
| typedef [**Geo**](classGeo.md)&lt; [**FlexGrid**](classFlexGrid.md) &gt; | [**GeoFlexGrid**](#typedef-geoflexgrid)  <br> |
| typedef [**Geo**](classGeo.md)&lt; [**Grid**](classGrid.md)&lt; T &gt; &gt; | [**GeoGrid**](#typedef-geogrid)  <br> |




## Public Attributes

| Type | Name |
| ---: | :--- |
|  constexpr bool | [**IS\_SPECIALIZATION\_V**](#variable-is_specialization_v)   = `[**is\_specialization**](structis__specialization.md)&lt;Type, Template&gt;::value`<br> |
















## Public Functions

| Type | Name |
| ---: | :--- |
|  T | [**interpolate\_value**](#function-interpolate_value) (const [**GeoGrid**](classGeo.md)&lt; T &gt; & grid, const [**Coordinate2D**](classCoordinate2D.md)&lt; double &gt; & projection\_coord) <br> |
|  size\_t | [**num\_cells\_by\_distance**](#function-num_cells_by_distance) (double x, double dx) <br> |




























## Public Types Documentation




### typedef GeoFlexGrid 

```C++
typedef Geo<FlexGrid> GeoFlexGrid;
```




<hr>



### typedef GeoGrid 

```C++
using GeoGrid =  Geo<Grid<T> >;
```




<hr>
## Public Attributes Documentation




### variable IS\_SPECIALIZATION\_V 

```C++
constexpr bool IS_SPECIALIZATION_V;
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
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/lib/grid/grid.hpp`

