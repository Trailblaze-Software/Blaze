

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
|   | [**TEST**](#function-test) (SignedArea, CcwSquareIsPositive) <br> |
|   | [**TEST**](#function-test) (SignedArea, CwSquareIsNegative) <br> |
|   | [**TEST**](#function-test) (SignedArea, TooFewPointsIsZero) <br> |
|   | [**TEST**](#function-test) (PointInRing, InsideSquare) <br> |
|   | [**TEST**](#function-test) (PointInRing, OutsideSquare) <br> |
|   | [**TEST**](#function-test) (PointInRing, TooFewPointsIsFalse) <br> |
|   | [**TEST**](#function-test) (ReverseRing, NegatesSignedArea) <br> |
|   | [**TEST**](#function-test) (NormalizePolygon, FixesExteriorAndHoleWinding) <br> |
|   | [**TEST**](#function-test) (PolygonIntersection, FullContainment) <br> |
|   | [**TEST**](#function-test) (PolygonIntersection, PartialOverlap) <br> |
|   | [**TEST**](#function-test) (PolygonIntersection, NoOverlap) <br> |
|   | [**TEST**](#function-test) (SubtractPolygon, NoCutouts) <br> |
|   | [**TEST**](#function-test) (SubtractPolygonWithUnion, NullUnionReturnsHost) <br> |
|   | [**TEST**](#function-test) (SubtractPolygon, CutoutOutsideHost) <br> |
|   | [**TEST**](#function-test) (SubtractPolygon, CutoutFullyCoversHost) <br> |
|   | [**TEST**](#function-test) (SubtractPolygon, SingleCutoutFullyContained) <br> |
|   | [**TEST**](#function-test) (SubtractPolygon, TwoDisjointCutouts) <br> |
|   | [**TEST**](#function-test) (SubtractPolygon, NestedCutoutsNotDoubleCut) <br> |
|   | [**TEST**](#function-test) (SubtractPolygon, PartialOverlapClipsHost) <br> |
|   | [**TEST**](#function-test) (SubtractPolygon, SplitsHostIntoTwo) <br> |
|   | [**TEST**](#function-test) (SubtractPolygon, CutoutInsideExistingHole) <br> |
|   | [**TEST**](#function-test) (SubtractPolygon, GreenDonutLeavesForestRing) <br> |
|   | [**TEST**](#function-test) (SubtractPolygon, NetAreaConservedAcrossOperations) <br> |
|   | [**TEST**](#function-test) (IntersectPolygon, ClipsExteriorToExtent) <br> |
|   | [**TEST**](#function-test) (IntersectPolygon, RemovesPolygonOutsideExtent) <br> |
|   | [**TEST**](#function-test) (IntersectPolygon, ClipsPolygonWithHole) <br> |
|   | [**TEST**](#function-test) (ClipPolygonToExtent, MatchesGeosClipForSquare) <br> |
|   | [**TEST**](#function-test) (ClipPolygonToExtent, ClipsPolygonWithHole) <br> |
|   | [**TEST**](#function-test) (ClipPolygonToExtent, BisectedDonutDropsHole) <br> |
|   | [**TEST**](#function-test) (UnionOverlappingPolygons, MergesOverlappingPolygons) <br> |
|   | [**TEST**](#function-test) (UnionOverlappingPolygons, MergesTouchingEdges) <br> |
|   | [**TEST**](#function-test) (UnionOverlappingPolygons, KeepsDisjointSeparate) <br> |
|   | [**TEST**](#function-test) (UnionOverlappingPolygons, RepairsSelfIntersectingInputs) <br> |
|   | [**TEST**](#function-test) (SnapRingToExtent, SnapsNearBoundaryVertices) <br> |
|   | [**TEST**](#function-test) (FinalizePolygonWithHoles, RepairsSelfIntersectingBowtie) <br> |
|   | [**TEST**](#function-test) (FinalizePolygonWithHoles, SnapsToTileSeamBeforeRepair) <br> |




























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



### function TEST 

```C++
TEST (
    UnionOverlappingPolygons,
    RepairsSelfIntersectingInputs
) 
```




<hr>



### function TEST 

```C++
TEST (
    SnapRingToExtent,
    SnapsNearBoundaryVertices
) 
```




<hr>



### function TEST 

```C++
TEST (
    FinalizePolygonWithHoles,
    RepairsSelfIntersectingBowtie
) 
```




<hr>



### function TEST 

```C++
TEST (
    FinalizePolygonWithHoles,
    SnapsToTileSeamBeforeRepair
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/lib/geometry/tests/test_polygon.cpp`

