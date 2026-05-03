

# File test\_vegetation.cpp



[**FileList**](files.md) **>** [**lib**](dir_c85d3e3c5052e9ad9ce18c6863244a25.md) **>** [**vegetation**](dir_b743e47c5a2b15e05ebb68ed1bfc6ebf.md) **>** [**tests**](dir_f363110a8f8d8c62b28512efb8187aa9.md) **>** [**test\_vegetation.cpp**](test__vegetation_8cpp.md)

[Go to the source code of this file](test__vegetation_8cpp_source.md)



* `#include <gtest/gtest.h>`
* `#include <cmath>`
* `#include "grid/grid.hpp"`
* `#include "vegetation/vegetation.hpp"`





































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**TEST**](#function-test) ([**Vegetation**](classCoordinate2D.md), [**LowPassUniformGrid**](classCoordinate2D.md)) <br> |
|   | [**TEST**](#function-test) ([**Vegetation**](classCoordinate2D.md), [**LowPassSmoothing**](classCoordinate2D.md)) <br> |
|   | [**TEST**](#function-test) ([**Vegetation**](classCoordinate2D.md), [**LowPassSmallDelta**](classCoordinate2D.md)) <br> |
|   | [**TEST**](#function-test) ([**Vegetation**](classCoordinate2D.md), [**LowPassOptionalUniform**](classCoordinate2D.md)) <br> |
|   | [**TEST**](#function-test) ([**Vegetation**](classCoordinate2D.md), [**LowPassOptionalWithNulls**](classCoordinate2D.md)) <br> |
|   | [**TEST**](#function-test) ([**Vegetation**](classCoordinate2D.md), [**LowPassOptionalAllNull**](classCoordinate2D.md)) <br> |
|   | [**TEST**](#function-test) ([**Vegetation**](classCoordinate2D.md), [**LowPassPreservesGridDimensions**](classCoordinate2D.md)) <br> |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  [**GeoGrid**](classGeo.md)&lt; [**float**](classCoordinate2D.md) &gt; | [**make\_float\_grid**](#function-make_float_grid) ([**const**](classCoordinate2D.md) std::vector&lt; std::vector&lt; [**float**](classCoordinate2D.md) &gt; &gt; & data) <br> |
|  [**GeoGrid**](classGeo.md)&lt; std::optional&lt; [**float**](classCoordinate2D.md) &gt; &gt; | [**make\_opt\_float\_grid**](#function-make_opt_float_grid) ([**const**](classCoordinate2D.md) std::vector&lt; std::vector&lt; std::optional&lt; [**float**](classCoordinate2D.md) &gt; &gt; &gt; & data) <br> |


























## Public Functions Documentation




### function TEST 

```C++
TEST (
    Vegetation,
    LowPassUniformGrid
) 
```




<hr>



### function TEST 

```C++
TEST (
    Vegetation,
    LowPassSmoothing
) 
```




<hr>



### function TEST 

```C++
TEST (
    Vegetation,
    LowPassSmallDelta
) 
```




<hr>



### function TEST 

```C++
TEST (
    Vegetation,
    LowPassOptionalUniform
) 
```




<hr>



### function TEST 

```C++
TEST (
    Vegetation,
    LowPassOptionalWithNulls
) 
```




<hr>



### function TEST 

```C++
TEST (
    Vegetation,
    LowPassOptionalAllNull
) 
```




<hr>



### function TEST 

```C++
TEST (
    Vegetation,
    LowPassPreservesGridDimensions
) 
```




<hr>
## Public Static Functions Documentation




### function make\_float\_grid 

```C++
static GeoGrid < float > make_float_grid (
    const std::vector< std::vector< float > > & data
) 
```




<hr>



### function make\_opt\_float\_grid 

```C++
static GeoGrid < std::optional< float > > make_opt_float_grid (
    const std::vector< std::vector< std::optional< float > > > & data
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/lib/vegetation/tests/test_vegetation.cpp`

