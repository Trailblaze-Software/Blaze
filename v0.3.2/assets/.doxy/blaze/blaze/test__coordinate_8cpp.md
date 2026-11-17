

# File test\_coordinate.cpp



[**FileList**](files.md) **>** [**lib**](dir_c85d3e3c5052e9ad9ce18c6863244a25.md) **>** [**utilities**](dir_f68f3bc40609949e989ead5b0b6dedfd.md) **>** [**tests**](dir_61cbaf6f69b3ff38c8740f6eb1724d7a.md) **>** [**test\_coordinate.cpp**](test__coordinate_8cpp.md)

[Go to the source code of this file](test__coordinate_8cpp_source.md)



* `#include <gtest/gtest.h>`
* `#include <cmath>`
* `#include <limits>`
* `#include "utilities/coordinate.hpp"`





































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**TEST**](#function-test) ([**Coordinate2D**](classCoordinate2D.md), Construction) <br> |
|   | [**TEST**](#function-test) ([**Coordinate2D**](classCoordinate2D.md), DefaultConstruction) <br> |
|   | [**TEST**](#function-test) ([**Coordinate2D**](classCoordinate2D.md), Addition) <br> |
|   | [**TEST**](#function-test) ([**Coordinate2D**](classCoordinate2D.md), Subtraction) <br> |
|   | [**TEST**](#function-test) ([**Coordinate2D**](classCoordinate2D.md), Equality) <br> |
|   | [**TEST**](#function-test) ([**Coordinate2D**](classCoordinate2D.md), MagnitudeSquared) <br> |
|   | [**TEST**](#function-test) ([**Coordinate2D**](classCoordinate2D.md), Magnitude) <br> |
|   | [**TEST**](#function-test) ([**Coordinate2D**](classCoordinate2D.md), MagnitudeUnit) <br> |
|   | [**TEST**](#function-test) ([**Coordinate2D**](classCoordinate2D.md), OffsetToCenter) <br> |
|   | [**TEST**](#function-test) ([**Coordinate2D**](classCoordinate2D.md), AddDirection) <br> |
|   | [**TEST**](#function-test) ([**Coordinate2D**](classCoordinate2D.md), TypeConversion) <br> |
|   | [**TEST**](#function-test) ([**Coordinate2D**](classCoordinate2D.md), OrthogonalNeighbors) <br> |
|   | [**TEST**](#function-test) ([**Direction2D**](classDirection2D.md), DxDy) <br> |
|   | [**TEST**](#function-test) ([**Direction2D**](classDirection2D.md), Opposite) <br> |
|   | [**TEST**](#function-test) ([**Direction2D**](classDirection2D.md), OrthogonalDirs) <br> |
|   | [**TEST**](#function-test) ([**Direction2D**](classDirection2D.md), OrthogonalTo) <br> |
|   | [**TEST**](#function-test) ([**Extent2D**](structExtent2D.md), DefaultConstruction) <br> |
|   | [**TEST**](#function-test) ([**Extent2D**](structExtent2D.md), Contains) <br> |
|   | [**TEST**](#function-test) ([**Extent2D**](structExtent2D.md), Grow) <br> |
|   | [**TEST**](#function-test) ([**Extent2D**](structExtent2D.md), GrowNonOverlapping) <br> |
|   | [**TEST**](#function-test) ([**Extent3D**](structExtent3D.md), GrowByPoint) <br> |
|   | [**TEST**](#function-test) ([**Extent3D**](structExtent3D.md), GrowByBorder) <br> |
|   | [**TEST**](#function-test) ([**Extent3D**](structExtent3D.md), GrowByExtent) <br> |
|   | [**TEST**](#function-test) ([**Extent3D**](structExtent3D.md), Intersects) <br> |
|   | [**TEST**](#function-test) ([**Extent3D**](structExtent3D.md), IntersectsEdge) <br> |
|   | [**TEST**](#function-test) ([**Extent3D**](structExtent3D.md), Center) <br> |
|   | [**TEST**](#function-test) ([**Extent3D**](structExtent3D.md), MaxExtent) <br> |
|   | [**TEST**](#function-test) ([**Extent3D**](structExtent3D.md), Intersection) <br> |
|   | [**TEST**](#function-test) ([**Extent3D**](structExtent3D.md), NotEqual) <br> |
|   | [**TEST**](#function-test) ([**Extent3D**](structExtent3D.md), SubtractOffset) <br> |
|   | [**TEST**](#function-test) ([**LineCoord2D**](classLineCoord2D.md), StartEnd) <br> |
|   | [**TEST**](#function-test) ([**Coordinate3D**](classCoordinate3D.md), Construction) <br> |




























## Public Functions Documentation




### function TEST 

```C++
TEST (
    Coordinate2D,
    Construction
) 
```




<hr>



### function TEST 

```C++
TEST (
    Coordinate2D,
    DefaultConstruction
) 
```




<hr>



### function TEST 

```C++
TEST (
    Coordinate2D,
    Addition
) 
```




<hr>



### function TEST 

```C++
TEST (
    Coordinate2D,
    Subtraction
) 
```




<hr>



### function TEST 

```C++
TEST (
    Coordinate2D,
    Equality
) 
```




<hr>



### function TEST 

```C++
TEST (
    Coordinate2D,
    MagnitudeSquared
) 
```




<hr>



### function TEST 

```C++
TEST (
    Coordinate2D,
    Magnitude
) 
```




<hr>



### function TEST 

```C++
TEST (
    Coordinate2D,
    MagnitudeUnit
) 
```




<hr>



### function TEST 

```C++
TEST (
    Coordinate2D,
    OffsetToCenter
) 
```




<hr>



### function TEST 

```C++
TEST (
    Coordinate2D,
    AddDirection
) 
```




<hr>



### function TEST 

```C++
TEST (
    Coordinate2D,
    TypeConversion
) 
```




<hr>



### function TEST 

```C++
TEST (
    Coordinate2D,
    OrthogonalNeighbors
) 
```




<hr>



### function TEST 

```C++
TEST (
    Direction2D,
    DxDy
) 
```




<hr>



### function TEST 

```C++
TEST (
    Direction2D,
    Opposite
) 
```




<hr>



### function TEST 

```C++
TEST (
    Direction2D,
    OrthogonalDirs
) 
```




<hr>



### function TEST 

```C++
TEST (
    Direction2D,
    OrthogonalTo
) 
```




<hr>



### function TEST 

```C++
TEST (
    Extent2D,
    DefaultConstruction
) 
```




<hr>



### function TEST 

```C++
TEST (
    Extent2D,
    Contains
) 
```




<hr>



### function TEST 

```C++
TEST (
    Extent2D,
    Grow
) 
```




<hr>



### function TEST 

```C++
TEST (
    Extent2D,
    GrowNonOverlapping
) 
```




<hr>



### function TEST 

```C++
TEST (
    Extent3D,
    GrowByPoint
) 
```




<hr>



### function TEST 

```C++
TEST (
    Extent3D,
    GrowByBorder
) 
```




<hr>



### function TEST 

```C++
TEST (
    Extent3D,
    GrowByExtent
) 
```




<hr>



### function TEST 

```C++
TEST (
    Extent3D,
    Intersects
) 
```




<hr>



### function TEST 

```C++
TEST (
    Extent3D,
    IntersectsEdge
) 
```




<hr>



### function TEST 

```C++
TEST (
    Extent3D,
    Center
) 
```




<hr>



### function TEST 

```C++
TEST (
    Extent3D,
    MaxExtent
) 
```




<hr>



### function TEST 

```C++
TEST (
    Extent3D,
    Intersection
) 
```




<hr>



### function TEST 

```C++
TEST (
    Extent3D,
    NotEqual
) 
```




<hr>



### function TEST 

```C++
TEST (
    Extent3D,
    SubtractOffset
) 
```




<hr>



### function TEST 

```C++
TEST (
    LineCoord2D,
    StartEnd
) 
```




<hr>



### function TEST 

```C++
TEST (
    Coordinate3D,
    Construction
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/lib/utilities/tests/test_coordinate.cpp`

