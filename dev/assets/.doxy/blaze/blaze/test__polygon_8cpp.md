

# File test\_polygon.cpp



[**FileList**](files.md) **>** [**geometry**](dir_da4e387dad6145fce42efe284fbecf2d.md) **>** [**tests**](dir_36407adca9cc620e53261a1df3e1be68.md) **>** [**test\_polygon.cpp**](test__polygon_8cpp.md)

[Go to the source code of this file](test__polygon_8cpp_source.md)



* `#include <gtest/gtest.h>`
* `#include <algorithm>`
* `#include <cmath>`
* `#include <vector>`
* `#include "geometry/polygon.hpp"`
* `#include "geometry/polygon_subtract.hpp"`





































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**TEST**](#function-test) ([**SignedArea**](classCoordinate2D.md), [**CcwSquareIsPositive**](classCoordinate2D.md)) <br> |
|   | [**TEST**](#function-test) ([**SignedArea**](classCoordinate2D.md), [**CwSquareIsNegative**](classCoordinate2D.md)) <br> |
|   | [**TEST**](#function-test) ([**SignedArea**](classCoordinate2D.md), [**TooFewPointsIsZero**](classCoordinate2D.md)) <br> |
|   | [**TEST**](#function-test) ([**PointInRing**](classCoordinate2D.md), [**InsideSquare**](classCoordinate2D.md)) <br> |
|   | [**TEST**](#function-test) ([**PointInRing**](classCoordinate2D.md), [**OutsideSquare**](classCoordinate2D.md)) <br> |
|   | [**TEST**](#function-test) ([**PointInRing**](classCoordinate2D.md), [**TooFewPointsIsFalse**](classCoordinate2D.md)) <br> |
|   | [**TEST**](#function-test) ([**ReverseRing**](classCoordinate2D.md), [**NegatesSignedArea**](classCoordinate2D.md)) <br> |
|   | [**TEST**](#function-test) ([**NormalizePolygon**](classCoordinate2D.md), [**FixesExteriorAndHoleWinding**](classCoordinate2D.md)) <br> |
|   | [**TEST**](#function-test) ([**PolygonIntersection**](classCoordinate2D.md), [**FullContainment**](classCoordinate2D.md)) <br> |
|   | [**TEST**](#function-test) ([**PolygonIntersection**](classCoordinate2D.md), [**PartialOverlap**](classCoordinate2D.md)) <br> |
|   | [**TEST**](#function-test) ([**PolygonIntersection**](classCoordinate2D.md), [**NoOverlap**](classCoordinate2D.md)) <br> |
|   | [**TEST**](#function-test) ([**SubtractPolygon**](classCoordinate2D.md), [**NoCutouts**](classCoordinate2D.md)) <br> |
|   | [**TEST**](#function-test) ([**SubtractPolygonWithUnion**](classCoordinate2D.md), [**NullUnionReturnsHost**](classCoordinate2D.md)) <br> |
|   | [**TEST**](#function-test) ([**SubtractPolygon**](classCoordinate2D.md), [**CutoutOutsideHost**](classCoordinate2D.md)) <br> |
|   | [**TEST**](#function-test) ([**SubtractPolygon**](classCoordinate2D.md), [**CutoutFullyCoversHost**](classCoordinate2D.md)) <br> |
|   | [**TEST**](#function-test) ([**SubtractPolygon**](classCoordinate2D.md), [**SingleCutoutFullyContained**](classCoordinate2D.md)) <br> |
|   | [**TEST**](#function-test) ([**SubtractPolygon**](classCoordinate2D.md), [**TwoDisjointCutouts**](classCoordinate2D.md)) <br> |
|   | [**TEST**](#function-test) ([**SubtractPolygon**](classCoordinate2D.md), [**NestedCutoutsNotDoubleCut**](classCoordinate2D.md)) <br> |
|   | [**TEST**](#function-test) ([**SubtractPolygon**](classCoordinate2D.md), [**PartialOverlapClipsHost**](classCoordinate2D.md)) <br> |
|   | [**TEST**](#function-test) ([**SubtractPolygon**](classCoordinate2D.md), [**SplitsHostIntoTwo**](classCoordinate2D.md)) <br> |
|   | [**TEST**](#function-test) ([**SubtractPolygon**](classCoordinate2D.md), [**CutoutInsideExistingHole**](classCoordinate2D.md)) <br> |
|   | [**TEST**](#function-test) ([**SubtractPolygon**](classCoordinate2D.md), [**GreenDonutLeavesForestRing**](classCoordinate2D.md)) <br> |
|   | [**TEST**](#function-test) ([**SubtractPolygon**](classCoordinate2D.md), [**NetAreaConservedAcrossOperations**](classCoordinate2D.md)) <br> |
|   | [**TEST**](#function-test) ([**IntersectPolygon**](classCoordinate2D.md), [**ClipsExteriorToExtent**](classCoordinate2D.md)) <br> |
|   | [**TEST**](#function-test) ([**IntersectPolygon**](classCoordinate2D.md), [**RemovesPolygonOutsideExtent**](classCoordinate2D.md)) <br> |
|   | [**TEST**](#function-test) ([**IntersectPolygon**](classCoordinate2D.md), [**ClipsPolygonWithHole**](classCoordinate2D.md)) <br> |
|   | [**TEST**](#function-test) ([**ClipPolygonToExtent**](classCoordinate2D.md), [**MatchesGeosClipForSquare**](classCoordinate2D.md)) <br> |
|   | [**TEST**](#function-test) ([**ClipPolygonToExtent**](classCoordinate2D.md), [**ClipsPolygonWithHole**](classCoordinate2D.md)) <br> |
|   | [**TEST**](#function-test) ([**ClipPolygonToExtent**](classCoordinate2D.md), [**BisectedDonutDropsHole**](classCoordinate2D.md)) <br> |
|   | [**TEST**](#function-test) ([**UnionOverlappingPolygons**](classCoordinate2D.md), [**MergesOverlappingPolygons**](classCoordinate2D.md)) <br> |
|   | [**TEST**](#function-test) ([**UnionOverlappingPolygons**](classCoordinate2D.md), [**MergesTouchingEdges**](classCoordinate2D.md)) <br> |
|   | [**TEST**](#function-test) ([**UnionOverlappingPolygons**](classCoordinate2D.md), [**KeepsDisjointSeparate**](classCoordinate2D.md)) <br> |




























## Public Functions Documentation




### function TEST 

```C++
TEST (
    SignedArea,
    CcwSquareIsPositive
) 
```




<hr>



### function TEST 

```C++
TEST (
    SignedArea,
    CwSquareIsNegative
) 
```




<hr>



### function TEST 

```C++
TEST (
    SignedArea,
    TooFewPointsIsZero
) 
```




<hr>



### function TEST 

```C++
TEST (
    PointInRing,
    InsideSquare
) 
```




<hr>



### function TEST 

```C++
TEST (
    PointInRing,
    OutsideSquare
) 
```




<hr>



### function TEST 

```C++
TEST (
    PointInRing,
    TooFewPointsIsFalse
) 
```




<hr>



### function TEST 

```C++
TEST (
    ReverseRing,
    NegatesSignedArea
) 
```




<hr>



### function TEST 

```C++
TEST (
    NormalizePolygon,
    FixesExteriorAndHoleWinding
) 
```




<hr>



### function TEST 

```C++
TEST (
    PolygonIntersection,
    FullContainment
) 
```




<hr>



### function TEST 

```C++
TEST (
    PolygonIntersection,
    PartialOverlap
) 
```




<hr>



### function TEST 

```C++
TEST (
    PolygonIntersection,
    NoOverlap
) 
```




<hr>



### function TEST 

```C++
TEST (
    SubtractPolygon,
    NoCutouts
) 
```




<hr>



### function TEST 

```C++
TEST (
    SubtractPolygonWithUnion,
    NullUnionReturnsHost
) 
```




<hr>



### function TEST 

```C++
TEST (
    SubtractPolygon,
    CutoutOutsideHost
) 
```




<hr>



### function TEST 

```C++
TEST (
    SubtractPolygon,
    CutoutFullyCoversHost
) 
```




<hr>



### function TEST 

```C++
TEST (
    SubtractPolygon,
    SingleCutoutFullyContained
) 
```




<hr>



### function TEST 

```C++
TEST (
    SubtractPolygon,
    TwoDisjointCutouts
) 
```




<hr>



### function TEST 

```C++
TEST (
    SubtractPolygon,
    NestedCutoutsNotDoubleCut
) 
```




<hr>



### function TEST 

```C++
TEST (
    SubtractPolygon,
    PartialOverlapClipsHost
) 
```




<hr>



### function TEST 

```C++
TEST (
    SubtractPolygon,
    SplitsHostIntoTwo
) 
```




<hr>



### function TEST 

```C++
TEST (
    SubtractPolygon,
    CutoutInsideExistingHole
) 
```




<hr>



### function TEST 

```C++
TEST (
    SubtractPolygon,
    GreenDonutLeavesForestRing
) 
```




<hr>



### function TEST 

```C++
TEST (
    SubtractPolygon,
    NetAreaConservedAcrossOperations
) 
```




<hr>



### function TEST 

```C++
TEST (
    IntersectPolygon,
    ClipsExteriorToExtent
) 
```




<hr>



### function TEST 

```C++
TEST (
    IntersectPolygon,
    RemovesPolygonOutsideExtent
) 
```




<hr>



### function TEST 

```C++
TEST (
    IntersectPolygon,
    ClipsPolygonWithHole
) 
```




<hr>



### function TEST 

```C++
TEST (
    ClipPolygonToExtent,
    MatchesGeosClipForSquare
) 
```




<hr>



### function TEST 

```C++
TEST (
    ClipPolygonToExtent,
    ClipsPolygonWithHole
) 
```




<hr>



### function TEST 

```C++
TEST (
    ClipPolygonToExtent,
    BisectedDonutDropsHole
) 
```




<hr>



### function TEST 

```C++
TEST (
    UnionOverlappingPolygons,
    MergesOverlappingPolygons
) 
```




<hr>



### function TEST 

```C++
TEST (
    UnionOverlappingPolygons,
    MergesTouchingEdges
) 
```




<hr>



### function TEST 

```C++
TEST (
    UnionOverlappingPolygons,
    KeepsDisjointSeparate
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/lib/geometry/tests/test_polygon.cpp`

