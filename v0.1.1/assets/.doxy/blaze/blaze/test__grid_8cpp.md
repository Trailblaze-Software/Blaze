

# File test\_grid.cpp



[**FileList**](files.md) **>** [**grid**](dir_b440d1ddeab29faa8ab1c63476ee276f.md) **>** [**tests**](dir_7abe1d2e6c271935b6731dcf9a13a0e9.md) **>** [**test\_grid.cpp**](test__grid_8cpp.md)

[Go to the source code of this file](test__grid_8cpp_source.md)



* `#include <gtest/gtest.h>`
* `#include <cmath>`
* `#include <limits>`
* `#include "grid/grid.hpp"`
* `#include "grid/grid_ops.hpp"`





































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**TEST**](#function-test) ([**GeoTransform**](classGeoTransform.md), [**DefaultConstruction**](classCoordinate2D.md)) <br> |
|   | [**TEST**](#function-test) ([**GeoTransform**](classGeoTransform.md), [**ConstructionWithValues**](classCoordinate2D.md)) <br> |
|   | [**TEST**](#function-test) ([**GeoTransform**](classGeoTransform.md), [**ConstructionFromCoordinate**](classCoordinate2D.md)) <br> |
|   | [**TEST**](#function-test) ([**GeoTransform**](classGeoTransform.md), [**PixelToProjection**](classCoordinate2D.md)) <br> |
|   | [**TEST**](#function-test) ([**GeoTransform**](classGeoTransform.md), [**PixelToProjectionWithOffset**](classCoordinate2D.md)) <br> |
|   | [**TEST**](#function-test) ([**GeoTransform**](classGeoTransform.md), [**ProjectionToPixel**](classCoordinate2D.md)) <br> |
|   | [**TEST**](#function-test) ([**GeoTransform**](classGeoTransform.md), [**PixelProjectionRoundTrip**](classCoordinate2D.md)) <br> |
|   | [**TEST**](#function-test) ([**GeoTransform**](classGeoTransform.md), [**WithNewResolution**](classCoordinate2D.md)) <br> |
|   | [**TEST**](#function-test) ([**Grid**](classGrid.md), [**ConstructionAndAccess**](classCoordinate2D.md)) <br> |
|   | [**TEST**](#function-test) ([**Grid**](classGrid.md), [**Fill**](classCoordinate2D.md)) <br> |
|   | [**TEST**](#function-test) ([**Grid**](classGrid.md), [**MinMax**](classCoordinate2D.md)) <br> |
|   | [**TEST**](#function-test) ([**Grid**](classGrid.md), [**CopyFrom**](classCoordinate2D.md)) <br> |
|   | [**TEST**](#function-test) ([**Grid**](classGrid.md), [**InBounds**](classCoordinate2D.md)) <br> |
|   | [**TEST**](#function-test) ([**Grid**](classGrid.md), [**FillFrom**](classCoordinate2D.md)) <br> |
|   | [**TEST**](#function-test) ([**GeoGrid**](classGeo.md), [**Extent**](classCoordinate2D.md)) <br> |
|   | [**TEST**](#function-test) ([**InterpolateValue**](classCoordinate2D.md), [**CenterOfCell**](classCoordinate2D.md)) <br> |
|   | [**TEST**](#function-test) ([**InterpolateValue**](classCoordinate2D.md), [**MidpointBetweenCells**](classCoordinate2D.md)) <br> |
|   | [**TEST**](#function-test) ([**GridGraph**](classGridGraph.md), [**ConstructionAndAccess**](classCoordinate2D.md)) <br> |
|   | [**TEST**](#function-test) ([**GridGraph**](classGridGraph.md), [**InBounds**](classCoordinate2D.md)) <br> |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  [**Coordinate2D**](classCoordinate2D.md)&lt; [**size\_t**](classCoordinate2D.md) &gt; | [**coord**](#function-coord) ([**size\_t**](classCoordinate2D.md) x, [**size\_t**](classCoordinate2D.md) y) <br> |


























## Public Functions Documentation




### function TEST 

```C++
TEST (
    GeoTransform,
    DefaultConstruction
) 
```




<hr>



### function TEST 

```C++
TEST (
    GeoTransform,
    ConstructionWithValues
) 
```




<hr>



### function TEST 

```C++
TEST (
    GeoTransform,
    ConstructionFromCoordinate
) 
```




<hr>



### function TEST 

```C++
TEST (
    GeoTransform,
    PixelToProjection
) 
```




<hr>



### function TEST 

```C++
TEST (
    GeoTransform,
    PixelToProjectionWithOffset
) 
```




<hr>



### function TEST 

```C++
TEST (
    GeoTransform,
    ProjectionToPixel
) 
```




<hr>



### function TEST 

```C++
TEST (
    GeoTransform,
    PixelProjectionRoundTrip
) 
```




<hr>



### function TEST 

```C++
TEST (
    GeoTransform,
    WithNewResolution
) 
```




<hr>



### function TEST 

```C++
TEST (
    Grid,
    ConstructionAndAccess
) 
```




<hr>



### function TEST 

```C++
TEST (
    Grid,
    Fill
) 
```




<hr>



### function TEST 

```C++
TEST (
    Grid,
    MinMax
) 
```




<hr>



### function TEST 

```C++
TEST (
    Grid,
    CopyFrom
) 
```




<hr>



### function TEST 

```C++
TEST (
    Grid,
    InBounds
) 
```




<hr>



### function TEST 

```C++
TEST (
    Grid,
    FillFrom
) 
```




<hr>



### function TEST 

```C++
TEST (
    GeoGrid,
    Extent
) 
```




<hr>



### function TEST 

```C++
TEST (
    InterpolateValue,
    CenterOfCell
) 
```




<hr>



### function TEST 

```C++
TEST (
    InterpolateValue,
    MidpointBetweenCells
) 
```




<hr>



### function TEST 

```C++
TEST (
    GridGraph,
    ConstructionAndAccess
) 
```




<hr>



### function TEST 

```C++
TEST (
    GridGraph,
    InBounds
) 
```




<hr>
## Public Static Functions Documentation




### function coord 

```C++
static Coordinate2D < size_t > coord (
    size_t x,
    size_t y
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/lib/grid/tests/test_grid.cpp`

