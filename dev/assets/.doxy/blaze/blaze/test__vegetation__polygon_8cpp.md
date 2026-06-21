

# File test\_vegetation\_polygon.cpp



[**FileList**](files.md) **>** [**lib**](dir_c85d3e3c5052e9ad9ce18c6863244a25.md) **>** [**vegetation**](dir_b743e47c5a2b15e05ebb68ed1bfc6ebf.md) **>** [**tests**](dir_f363110a8f8d8c62b28512efb8187aa9.md) **>** [**test\_vegetation\_polygon.cpp**](test__vegetation__polygon_8cpp.md)

[Go to the source code of this file](test__vegetation__polygon_8cpp_source.md)



* `#include <gtest/gtest.h>`
* `#include <algorithm>`
* `#include <cmath>`
* `#include <map>`
* `#include <set>`
* `#include <vector>`
* `#include "config_input/config_input.hpp"`
* `#include "contour/contour.hpp"`
* `#include "contour/contour_gen.hpp"`
* `#include "geometry/polygon.hpp"`
* `#include "grid/grid.hpp"`
* `#include "vegetation/vegetation_polygon.hpp"`





































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**TEST**](#function-test) ([**ExtractThresholdLayers**](classCoordinate2D.md), [**UsesDefaultLayerName**](classCoordinate2D.md)) <br> |
|   | [**TEST**](#function-test) ([**ExtractThresholdLayers**](classCoordinate2D.md), [**SortedByThreshold**](classCoordinate2D.md)) <br> |
|   | [**TEST**](#function-test) ([**ExtractThresholdLayers**](classCoordinate2D.md), [**EmptyConfig**](classCoordinate2D.md)) <br> |
|   | [**TEST**](#function-test) ([**ContoursToPolygons**](classCoordinate2D.md), [**SingleThresholdNoHoles**](classCoordinate2D.md)) <br> |
|   | [**TEST**](#function-test) ([**ContoursToPolygons**](classCoordinate2D.md), [**NestedContoursAreIndependent**](classCoordinate2D.md)) <br> |
|   | [**TEST**](#function-test) ([**ContoursToPolygons**](classCoordinate2D.md), [**DetectsOuterRingVsHole**](classCoordinate2D.md)) <br> |
|   | [**TEST**](#function-test) ([**ContoursToPolygons**](classCoordinate2D.md), [**CwOnlyRingProducesNoPolygon**](classCoordinate2D.md)) <br> |
|   | [**TEST**](#function-test) ([**TrimVegePolygons**](classCoordinate2D.md), [**ClipsToExportExtent**](classCoordinate2D.md)) <br> |
|   | [**TEST**](#function-test) ([**TrimVegePolygons**](classCoordinate2D.md), [**RemovesPolygonOutsideExtent**](classCoordinate2D.md)) <br> |
|   | [**TEST**](#function-test) ([**ContoursToPolygons**](classCoordinate2D.md), [**DeepNestedPolygonInHoleInPolygon**](classCoordinate2D.md)) <br> |
|   | [**TEST**](#function-test) ([**ContoursToPolygons**](classCoordinate2D.md), [**TwoSeparatePeaks**](classCoordinate2D.md)) <br> |
|   | [**TEST**](#function-test) ([**ContoursToPolygons**](classCoordinate2D.md), [**LayerAssignmentFromThreshold**](classCoordinate2D.md)) <br> |
|   | [**TEST**](#function-test) ([**FilterByMinArea**](classCoordinate2D.md), [**RemovesSmallPolygons**](classCoordinate2D.md)) <br> |
|   | [**TEST**](#function-test) ([**FilterByMinArea**](classCoordinate2D.md), [**KeepsAllWhenNoThreshold**](classCoordinate2D.md)) <br> |
|   | [**TEST**](#function-test) ([**FilterByMinArea**](classCoordinate2D.md), [**RespectsDifferentLimits**](classCoordinate2D.md)) <br> |
|   | [**TEST**](#function-test) ([**FilterByMinArea**](classCoordinate2D.md), [**UsesNetAreaNotExterior**](classCoordinate2D.md)) <br> |
|   | [**TEST**](#function-test) ([**FilterSmallHoles**](classCoordinate2D.md), [**RemovesTinyHoles**](classCoordinate2D.md)) <br> |
|   | [**TEST**](#function-test) ([**FilterSmallHoles**](classCoordinate2D.md), [**NoFilterWhenZero**](classCoordinate2D.md)) <br> |
|   | [**TEST**](#function-test) ([**FilterSmallHoles**](classCoordinate2D.md), [**DifferentPerLayer**](classCoordinate2D.md)) <br> |
|   | [**TEST**](#function-test) ([**SubtractFromPolygon**](classCoordinate2D.md), [**PreservesLayerMetadata**](classCoordinate2D.md)) <br> |
|   | [**TEST**](#function-test) ([**SubtractFromPolygon**](classCoordinate2D.md), [**GreenDonutLeavesForestRing**](classCoordinate2D.md)) <br> |
|   | [**TEST**](#function-test) ([**SubtractFromPolygon**](classCoordinate2D.md), [**SmallHolesRemovedByPostSubtractFilter**](classCoordinate2D.md)) <br> |
|   | [**TEST**](#function-test) ([**GenerateVegePolygons**](classCoordinate2D.md), [**RoughOpenLandHolesMatchRemainingForest**](classCoordinate2D.md)) <br> |
|   | [**TEST**](#function-test) ([**GenerateVegePolygons**](classCoordinate2D.md), [**RoughOpenLandHasNoTinySpeckleHoles**](classCoordinate2D.md)) <br> |
|   | [**TEST**](#function-test) ([**GenerateVegePolygons**](classCoordinate2D.md), [**GreenDonutCutLeavesForestRing**](classCoordinate2D.md)) <br> |
|   | [**TEST**](#function-test) ([**ContoursToPolygons**](classCoordinate2D.md), [**NestedHoles**](classCoordinate2D.md)) <br> |
|   | [**TEST**](#function-test) ([**ContoursToPolygons**](classCoordinate2D.md), [**BigGrid**](classCoordinate2D.md)) <br> |
|  std::vector&lt; [**VegePolygon**](structVegePolygon.md) &gt; | [**forest\_contours\_polygonize**](#function-forest_contours_polygonize) ([**const**](classCoordinate2D.md) [**GeoGrid**](classGeo.md)&lt; [**float**](classCoordinate2D.md) &gt; & grid) <br> |




























## Public Functions Documentation




### function TEST 

```C++
TEST (
    ExtractThresholdLayers,
    UsesDefaultLayerName
) 
```




<hr>



### function TEST 

```C++
TEST (
    ExtractThresholdLayers,
    SortedByThreshold
) 
```




<hr>



### function TEST 

```C++
TEST (
    ExtractThresholdLayers,
    EmptyConfig
) 
```




<hr>



### function TEST 

```C++
TEST (
    ContoursToPolygons,
    SingleThresholdNoHoles
) 
```




<hr>



### function TEST 

```C++
TEST (
    ContoursToPolygons,
    NestedContoursAreIndependent
) 
```




<hr>



### function TEST 

```C++
TEST (
    ContoursToPolygons,
    DetectsOuterRingVsHole
) 
```




<hr>



### function TEST 

```C++
TEST (
    ContoursToPolygons,
    CwOnlyRingProducesNoPolygon
) 
```




<hr>



### function TEST 

```C++
TEST (
    TrimVegePolygons,
    ClipsToExportExtent
) 
```




<hr>



### function TEST 

```C++
TEST (
    TrimVegePolygons,
    RemovesPolygonOutsideExtent
) 
```




<hr>



### function TEST 

```C++
TEST (
    ContoursToPolygons,
    DeepNestedPolygonInHoleInPolygon
) 
```




<hr>



### function TEST 

```C++
TEST (
    ContoursToPolygons,
    TwoSeparatePeaks
) 
```




<hr>



### function TEST 

```C++
TEST (
    ContoursToPolygons,
    LayerAssignmentFromThreshold
) 
```




<hr>



### function TEST 

```C++
TEST (
    FilterByMinArea,
    RemovesSmallPolygons
) 
```




<hr>



### function TEST 

```C++
TEST (
    FilterByMinArea,
    KeepsAllWhenNoThreshold
) 
```




<hr>



### function TEST 

```C++
TEST (
    FilterByMinArea,
    RespectsDifferentLimits
) 
```




<hr>



### function TEST 

```C++
TEST (
    FilterByMinArea,
    UsesNetAreaNotExterior
) 
```




<hr>



### function TEST 

```C++
TEST (
    FilterSmallHoles,
    RemovesTinyHoles
) 
```




<hr>



### function TEST 

```C++
TEST (
    FilterSmallHoles,
    NoFilterWhenZero
) 
```




<hr>



### function TEST 

```C++
TEST (
    FilterSmallHoles,
    DifferentPerLayer
) 
```




<hr>



### function TEST 

```C++
TEST (
    SubtractFromPolygon,
    PreservesLayerMetadata
) 
```




<hr>



### function TEST 

```C++
TEST (
    SubtractFromPolygon,
    GreenDonutLeavesForestRing
) 
```




<hr>



### function TEST 

```C++
TEST (
    SubtractFromPolygon,
    SmallHolesRemovedByPostSubtractFilter
) 
```




<hr>



### function TEST 

```C++
TEST (
    GenerateVegePolygons,
    RoughOpenLandHolesMatchRemainingForest
) 
```




<hr>



### function TEST 

```C++
TEST (
    GenerateVegePolygons,
    RoughOpenLandHasNoTinySpeckleHoles
) 
```




<hr>



### function TEST 

```C++
TEST (
    GenerateVegePolygons,
    GreenDonutCutLeavesForestRing
) 
```




<hr>



### function TEST 

```C++
TEST (
    ContoursToPolygons,
    NestedHoles
) 
```




<hr>



### function TEST 

```C++
TEST (
    ContoursToPolygons,
    BigGrid
) 
```




<hr>



### function forest\_contours\_polygonize 

```C++
std::vector< VegePolygon > forest_contours_polygonize (
    const  GeoGrid < float > & grid
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/lib/vegetation/tests/test_vegetation_polygon.cpp`

