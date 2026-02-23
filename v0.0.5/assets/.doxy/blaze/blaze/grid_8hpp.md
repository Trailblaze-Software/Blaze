

# File grid.hpp



[**FileList**](files.md) **>** [**grid**](dir_b440d1ddeab29faa8ab1c63476ee276f.md) **>** [**grid.hpp**](grid_8hpp.md)

[Go to the source code of this file](grid_8hpp_source.md)



* `#include <algorithm>`
* `#include <cstddef>`
* `#include <cstring>`
* `#include <memory>`
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
| class | [**Geo**](classGeo.md) &lt;[**typename**](classCoordinate2D.md) GridT&gt;<br> |
| class | [**GeoGridData**](classGeoGridData.md) <br> |
| class | [**GeoProjection**](classGeoProjection.md) <br> |
| class | [**GeoTransform**](classGeoTransform.md) <br> |
| class | [**Grid**](classGrid.md) &lt;[**typename**](classCoordinate2D.md) [**U**](classCoordinate2D.md)&gt;<br> |
| class | [**GridData**](classGridData.md) <br> |
| class | [**GridGraph**](classGridGraph.md) &lt;[**typename**](classCoordinate2D.md) T&gt;<br> |
| class | [**MultiBand**](classMultiBand.md) &lt;[**typename**](classCoordinate2D.md) GridT&gt;<br> |
| struct | [**is\_specialization**](structis__specialization.md) &lt;[**typename**](classCoordinate2D.md) [**Test**](classCoordinate2D.md), Ref&gt;<br> |
| struct | [**is\_specialization&lt; Ref&lt; Args... &gt;, Ref &gt;**](structis__specialization_3_01Ref_3_01Args_8_8_8_01_4_00_01Ref_01_4.md) &lt;Ref, Args&gt;<br> |


## Public Types

| Type | Name |
| ---: | :--- |
| typedef [**Geo**](classGeo.md)&lt; [**FlexGrid**](classFlexGrid.md) &gt; | [**GeoFlexGrid**](#typedef-geoflexgrid)  <br> |
| typedef [**Geo**](classGeo.md)&lt; [**Grid**](classGrid.md)&lt; T &gt; &gt; | [**GeoGrid**](#typedef-geogrid)  <br> |




## Public Attributes

| Type | Name |
| ---: | :--- |
|  [**constexpr**](classCoordinate2D.md) [**bool**](classCoordinate2D.md) | [**is\_specialization\_v**](#variable-is_specialization_v)   = `[**is\_specialization**](structis__specialization.md)&lt;[**Type**](classCoordinate2D.md), [**Template**](classCoordinate2D.md)&gt;::value`<br> |
















## Public Functions

| Type | Name |
| ---: | :--- |
|  T | [**interpolate\_value**](#function-interpolate_value) ([**const**](classCoordinate2D.md) [**GeoGrid**](classGeo.md)&lt; T &gt; & grid, [**const**](classCoordinate2D.md) [**Coordinate2D**](classCoordinate2D.md)&lt; [**double**](classCoordinate2D.md) &gt; & projection\_coord) <br> |




























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




### variable is\_specialization\_v 

```C++
constexpr bool is_specialization_v;
```




<hr>
## Public Functions Documentation




### function interpolate\_value 

```C++
template<typename T>
T interpolate_value (
    const  GeoGrid < T > & grid,
    const  Coordinate2D < double > & projection_coord
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/lib/grid/grid.hpp`

