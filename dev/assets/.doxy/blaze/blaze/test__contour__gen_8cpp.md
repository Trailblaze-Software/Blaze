

# File test\_contour\_gen.cpp



[**FileList**](files.md) **>** [**contour**](dir_168d7404e8aa1148a0abea8bd7ba0546.md) **>** [**tests**](dir_af1ec3f63b3290d3c0b6a16b438b915c.md) **>** [**test\_contour\_gen.cpp**](test__contour__gen_8cpp.md)

[Go to the source code of this file](test__contour__gen_8cpp_source.md)



* `#include <gtest/gtest.h>`
* `#include <algorithm>`
* `#include <set>`
* `#include <vector>`
* `#include "config_input/config_input.hpp"`
* `#include "contour/contour.hpp"`
* `#include "contour/contour_gen.hpp"`
* `#include "geometry/polygon.hpp"`
* `#include "isom/colors.hpp"`
* `#include "lib/grid/grid.hpp"`





































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**TEST**](#function-test) ([**ContourGen**](classCoordinate2D.md), [**ContourGen**](classCoordinate2D.md)) <br> |
|   | [**TEST**](#function-test) ([**ContourGen**](classCoordinate2D.md), [**ContourGen2**](classCoordinate2D.md)) <br> |
|   | [**TEST**](#function-test) ([**IdentifyContoursAtHeights**](classCoordinate2D.md), [**SingleHeightCrossing**](classCoordinate2D.md)) <br> |
|   | [**TEST**](#function-test) ([**IdentifyContoursAtHeights**](classCoordinate2D.md), [**NoCrossing**](classCoordinate2D.md)) <br> |
|   | [**TEST**](#function-test) ([**IdentifyContoursAtHeights**](classCoordinate2D.md), [**MultipleHeights**](classCoordinate2D.md)) <br> |
|   | [**TEST**](#function-test) ([**IdentifyContoursAtHeights**](classCoordinate2D.md), [**ExactThresholdValue**](classCoordinate2D.md)) <br> |
|   | [**TEST**](#function-test) ([**IdentifyContoursAtHeights**](classCoordinate2D.md), [**MinExactlyAtThreshold**](classCoordinate2D.md)) <br> |
|   | [**TEST**](#function-test) ([**GenerateContoursAtHeights**](classCoordinate2D.md), [**SinglePeakClosedLoop**](classCoordinate2D.md)) <br> |
|   | [**TEST**](#function-test) ([**GenerateContoursAtHeights**](classCoordinate2D.md), [**EdgeContoursAreClosed**](classCoordinate2D.md)) <br> |
|   | [**TEST**](#function-test) ([**GenerateContoursAtHeights**](classCoordinate2D.md), [**MultipleDisjointPatches**](classCoordinate2D.md)) <br> |
|   | [**TEST**](#function-test) ([**GenerateContoursAtHeights**](classCoordinate2D.md), [**AllZerosNoContours**](classCoordinate2D.md)) <br> |
|   | [**TEST**](#function-test) ([**GenerateContoursAtHeights**](classCoordinate2D.md), [**MultipleHeights**](classCoordinate2D.md)) <br> |
|   | [**TEST**](#function-test) ([**GenerateContoursAtHeights**](classCoordinate2D.md), [**FilteredByMinPoints**](classCoordinate2D.md)) <br> |
|   | [**TEST**](#function-test) ([**GenerateContoursAtHeights**](classCoordinate2D.md), [**OrientsDonutRings**](classCoordinate2D.md)) <br> |




























## Public Functions Documentation




### function TEST 

```C++
TEST (
    ContourGen,
    ContourGen
) 
```




<hr>



### function TEST 

```C++
TEST (
    ContourGen,
    ContourGen2
) 
```




<hr>



### function TEST 

```C++
TEST (
    IdentifyContoursAtHeights,
    SingleHeightCrossing
) 
```




<hr>



### function TEST 

```C++
TEST (
    IdentifyContoursAtHeights,
    NoCrossing
) 
```




<hr>



### function TEST 

```C++
TEST (
    IdentifyContoursAtHeights,
    MultipleHeights
) 
```




<hr>



### function TEST 

```C++
TEST (
    IdentifyContoursAtHeights,
    ExactThresholdValue
) 
```




<hr>



### function TEST 

```C++
TEST (
    IdentifyContoursAtHeights,
    MinExactlyAtThreshold
) 
```




<hr>



### function TEST 

```C++
TEST (
    GenerateContoursAtHeights,
    SinglePeakClosedLoop
) 
```




<hr>



### function TEST 

```C++
TEST (
    GenerateContoursAtHeights,
    EdgeContoursAreClosed
) 
```




<hr>



### function TEST 

```C++
TEST (
    GenerateContoursAtHeights,
    MultipleDisjointPatches
) 
```




<hr>



### function TEST 

```C++
TEST (
    GenerateContoursAtHeights,
    AllZerosNoContours
) 
```




<hr>



### function TEST 

```C++
TEST (
    GenerateContoursAtHeights,
    MultipleHeights
) 
```




<hr>



### function TEST 

```C++
TEST (
    GenerateContoursAtHeights,
    FilteredByMinPoints
) 
```




<hr>



### function TEST 

```C++
TEST (
    GenerateContoursAtHeights,
    OrientsDonutRings
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/lib/contour/tests/test_contour_gen.cpp`

