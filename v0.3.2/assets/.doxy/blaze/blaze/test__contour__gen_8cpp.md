

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
* `#include "utilities/progress_tracker.hpp"`





































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**TEST**](#function-test) (ContourGen, ContourGen) <br> |
|   | [**TEST**](#function-test) (ContourGen, ContourGen2) <br> |
|   | [**TEST**](#function-test) (IdentifyContoursAtHeights, SingleHeightCrossing) <br> |
|   | [**TEST**](#function-test) (IdentifyContoursAtHeights, NoCrossing) <br> |
|   | [**TEST**](#function-test) (IdentifyContoursAtHeights, MultipleHeights) <br> |
|   | [**TEST**](#function-test) (IdentifyContoursAtHeights, ExactThresholdValue) <br> |
|   | [**TEST**](#function-test) (IdentifyContoursAtHeights, MinExactlyAtThreshold) <br> |
|   | [**TEST**](#function-test) (GenerateContoursAtHeights, SinglePeakClosedLoop) <br> |
|   | [**TEST**](#function-test) (GenerateContoursAtHeights, EdgeContoursAreClosed) <br> |
|   | [**TEST**](#function-test) (GenerateContoursAtHeights, MultipleDisjointPatches) <br> |
|   | [**TEST**](#function-test) (GenerateContoursAtHeights, AllZerosNoContours) <br> |
|   | [**TEST**](#function-test) (GenerateContoursAtHeights, MultipleHeights) <br> |
|   | [**TEST**](#function-test) (GenerateContoursAtHeights, FilteredByMinPoints) <br> |
|   | [**TEST**](#function-test) (GenerateContoursAtHeights, OrientsDonutRings) <br> |
|   | [**TEST**](#function-test) (GenerateContoursAtHeights, SaddleConfigA\_AlwaysOutside) <br> |
|   | [**TEST**](#function-test) (GenerateContoursAtHeights, SaddleConfigA\_AlwaysInside) <br> |
|   | [**TEST**](#function-test) (GenerateContoursAtHeights, SaddleConfigA\_ByHeight) <br> |
|   | [**TEST**](#function-test) (GenerateContoursAtHeights, SaddleConfigA\_ByHeightAboveMerges) <br> |
|   | [**TEST**](#function-test) (GenerateContoursAtHeights, SaddleConfigB\_AlwaysOutside) <br> |
|   | [**TEST**](#function-test) (GenerateContoursAtHeights, SaddleConfigB\_AlwaysInside) <br> |
|   | [**TEST**](#function-test) (GenerateContoursAtHeights, SaddleConfigB\_ByHeight) <br> |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  void | [**check\_saddle\_2x2**](#function-check_saddle_2x2) (const std::vector&lt; std::vector&lt; float &gt; &gt; & data, float threshold, SaddlePolicy policy, size\_t expected\_contours, const std::vector&lt; size\_t &gt; & expected\_point\_counts) <br> |


























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



### function TEST 

```C++
TEST (
    GenerateContoursAtHeights,
    SaddleConfigA_AlwaysOutside
) 
```




<hr>



### function TEST 

```C++
TEST (
    GenerateContoursAtHeights,
    SaddleConfigA_AlwaysInside
) 
```




<hr>



### function TEST 

```C++
TEST (
    GenerateContoursAtHeights,
    SaddleConfigA_ByHeight
) 
```




<hr>



### function TEST 

```C++
TEST (
    GenerateContoursAtHeights,
    SaddleConfigA_ByHeightAboveMerges
) 
```




<hr>



### function TEST 

```C++
TEST (
    GenerateContoursAtHeights,
    SaddleConfigB_AlwaysOutside
) 
```




<hr>



### function TEST 

```C++
TEST (
    GenerateContoursAtHeights,
    SaddleConfigB_AlwaysInside
) 
```




<hr>



### function TEST 

```C++
TEST (
    GenerateContoursAtHeights,
    SaddleConfigB_ByHeight
) 
```




<hr>
## Public Static Functions Documentation




### function check\_saddle\_2x2 

```C++
static void check_saddle_2x2 (
    const std::vector< std::vector< float > > & data,
    float threshold,
    SaddlePolicy policy,
    size_t expected_contours,
    const std::vector< size_t > & expected_point_counts
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/lib/contour/tests/test_contour_gen.cpp`

