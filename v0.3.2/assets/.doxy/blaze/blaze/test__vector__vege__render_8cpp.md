

# File test\_vector\_vege\_render.cpp



[**FileList**](files.md) **>** [**lib**](dir_c85d3e3c5052e9ad9ce18c6863244a25.md) **>** [**vegetation**](dir_b743e47c5a2b15e05ebb68ed1bfc6ebf.md) **>** [**tests**](dir_f363110a8f8d8c62b28512efb8187aa9.md) **>** [**test\_vector\_vege\_render.cpp**](test__vector__vege__render_8cpp.md)

[Go to the source code of this file](test__vector__vege__render_8cpp_source.md)



* `#include <gtest/gtest.h>`
* `#include <cmath>`
* `#include <filesystem>`
* `#include <vector>`
* `#include "grid/grid.hpp"`
* `#include "grid/img_grid.hpp"`
* `#include "isom/colors.hpp"`
* `#include "testing/output_dir.hpp"`
* `#include "tif/tif.hpp"`
* `#include "utilities/progress_tracker.hpp"`
* `#include "vegetation/vector_vege_render.hpp"`
* `#include "vegetation/vegetation_polygon.hpp"`





































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**TEST**](#function-test) (VectorVegeRender, BackgroundFillWithoutPolygons) <br> |
|   | [**TEST**](#function-test) (VectorVegeRender, HigherPriorityGreenCoversForest) <br> |
|   | [**TEST**](#function-test) (VectorVegeRender, OpenLandUsesBackgroundColor) <br> |
|   | [**TEST**](#function-test) (VectorVegeRender, UnknownLayerIsSkipped) <br> |
|   | [**TEST**](#function-test) (VectorVegeRender, AllGreenLayersRenderDistinctColors) <br> |
|   | [**TEST**](#function-test) (VectorVegeRender, PolygonHoleLeavesBackgroundInterior) <br> |
|   | [**TEST**](#function-test) (VectorVegeRender, DefaultLayerNamesMapFromConfig) <br> |
|   | [**TEST**](#function-test) (VectorVegeTif, SaveAndReadPreservesRenderedColors) <br> |
|   | [**TEST**](#function-test) (VectorVegeOverlay, TransparentOverlayPreservesVectorBackground) <br> |
|   | [**TEST**](#function-test) (VectorVegeOverlay, OpaqueOverlayPixelReplacesBackground) <br> |
|   | [**TEST**](#function-test) (VectorVegeOverlay, DrawWithTransparentForegroundDoesNotTintBackground) <br> |




























## Public Functions Documentation




### function TEST 

```C++
TEST (
    VectorVegeRender,
    BackgroundFillWithoutPolygons
) 
```




<hr>



### function TEST 

```C++
TEST (
    VectorVegeRender,
    HigherPriorityGreenCoversForest
) 
```




<hr>



### function TEST 

```C++
TEST (
    VectorVegeRender,
    OpenLandUsesBackgroundColor
) 
```




<hr>



### function TEST 

```C++
TEST (
    VectorVegeRender,
    UnknownLayerIsSkipped
) 
```




<hr>



### function TEST 

```C++
TEST (
    VectorVegeRender,
    AllGreenLayersRenderDistinctColors
) 
```




<hr>



### function TEST 

```C++
TEST (
    VectorVegeRender,
    PolygonHoleLeavesBackgroundInterior
) 
```




<hr>



### function TEST 

```C++
TEST (
    VectorVegeRender,
    DefaultLayerNamesMapFromConfig
) 
```




<hr>



### function TEST 

```C++
TEST (
    VectorVegeTif,
    SaveAndReadPreservesRenderedColors
) 
```




<hr>



### function TEST 

```C++
TEST (
    VectorVegeOverlay,
    TransparentOverlayPreservesVectorBackground
) 
```




<hr>



### function TEST 

```C++
TEST (
    VectorVegeOverlay,
    OpaqueOverlayPixelReplacesBackground
) 
```




<hr>



### function TEST 

```C++
TEST (
    VectorVegeOverlay,
    DrawWithTransparentForegroundDoesNotTintBackground
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/lib/vegetation/tests/test_vector_vege_render.cpp`

