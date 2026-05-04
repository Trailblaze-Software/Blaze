

# File test\_las\_file.cpp



[**FileList**](files.md) **>** [**las**](dir_50e4ddd575fc604ec1609997d931fab5.md) **>** [**tests**](dir_cbe4df00df7a61fa7e328fcb8d7dc5eb.md) **>** [**test\_las\_file.cpp**](test__las__file_8cpp.md)

[Go to the source code of this file](test__las__file_8cpp_source.md)



* `#include <gtest/gtest.h>`
* `#include <cmath>`
* `#include <limits>`
* `#include <sstream>`
* `#include <string>`
* `#include "las/las_file.hpp"`





































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**TEST**](#function-test) (BorderType, [**StreamOutput**](classCoordinate2D.md)) <br> |
|   | [**TEST**](#function-test) ([**BorderRanges**](classCoordinate2D.md), [**North**](classCoordinate2D.md)) <br> |
|   | [**TEST**](#function-test) ([**BorderRanges**](classCoordinate2D.md), [**South**](classCoordinate2D.md)) <br> |
|   | [**TEST**](#function-test) ([**BorderRanges**](classCoordinate2D.md), [**East**](classCoordinate2D.md)) <br> |
|   | [**TEST**](#function-test) ([**BorderRanges**](classCoordinate2D.md), [**West**](classCoordinate2D.md)) <br> |
|   | [**TEST**](#function-test) ([**BorderRanges**](classCoordinate2D.md), [**NorthEast**](classCoordinate2D.md)) <br> |
|   | [**TEST**](#function-test) ([**BorderRanges**](classCoordinate2D.md), [**SouthWest**](classCoordinate2D.md)) <br> |
|   | [**TEST**](#function-test) ([**BorderRanges**](classCoordinate2D.md), [**SouthEast**](classCoordinate2D.md)) <br> |
|   | [**TEST**](#function-test) ([**BorderRanges**](classCoordinate2D.md), [**NorthWest**](classCoordinate2D.md)) <br> |
|   | [**TEST**](#function-test) ([**ExternalBorderRanges**](classCoordinate2D.md), [**North**](classCoordinate2D.md)) <br> |
|   | [**TEST**](#function-test) ([**ExternalBorderRanges**](classCoordinate2D.md), [**South**](classCoordinate2D.md)) <br> |
|   | [**TEST**](#function-test) ([**ExternalBorderRanges**](classCoordinate2D.md), [**East**](classCoordinate2D.md)) <br> |
|   | [**TEST**](#function-test) ([**ExternalBorderRanges**](classCoordinate2D.md), [**West**](classCoordinate2D.md)) <br> |
|   | [**TEST**](#function-test) ([**ExternalBorderRanges**](classCoordinate2D.md), [**Corners**](classCoordinate2D.md)) <br> |
|   | [**TEST**](#function-test) ([**LASRound**](classCoordinate2D.md), [**BasicRounding**](classCoordinate2D.md)) <br> |
|   | [**TEST**](#function-test) ([**LASRound**](classCoordinate2D.md), [**WithResolution**](classCoordinate2D.md)) <br> |
|   | [**TEST**](#function-test) ([**LASRound**](classCoordinate2D.md), [**WithSmallResolution**](classCoordinate2D.md)) <br> |
|   | [**TEST**](#function-test) ([**Average**](classCoordinate2D.md), [**Integers**](classCoordinate2D.md)) <br> |
|   | [**TEST**](#function-test) ([**Average**](classCoordinate2D.md), [**Doubles**](classCoordinate2D.md)) <br> |
|   | [**TEST**](#function-test) ([**UniqueCoordName**](classCoordinate2D.md), [**BasicOutput**](classCoordinate2D.md)) <br> |
|   | [**TEST**](#function-test) ([**UniqueCoordName**](classCoordinate2D.md), [**DifferentBoxesProduceDifferentNames**](classCoordinate2D.md)) <br> |
|   | [**TEST**](#function-test) ([**UniqueCoordName**](classCoordinate2D.md), [**SameBoxProducesSameName**](classCoordinate2D.md)) <br> |
|   | [**TEST**](#function-test) ([**LASData**](classLASData.md), [**ConstructFromExtent**](classCoordinate2D.md)) <br> |
|   | [**TEST**](#function-test) ([**LASData**](classLASData.md), [**InsertAndAccess**](classCoordinate2D.md)) <br> |
|   | [**TEST**](#function-test) ([**LASData**](classLASData.md), [**InsertUpdatesBounds**](classCoordinate2D.md)) <br> |
|   | [**TEST**](#function-test) ([**LASData**](classLASData.md), [**IntensityRange**](classCoordinate2D.md)) <br> |
|   | [**TEST**](#function-test) ([**LASData**](classLASData.md), [**Iterator**](classCoordinate2D.md)) <br> |
|   | [**TEST**](#function-test) ([**LASData**](classLASData.md), [**PushBack**](classCoordinate2D.md)) <br> |
|   | [**TEST**](#function-test) ([**LASData**](classLASData.md), [**MutableAccess**](classCoordinate2D.md)) <br> |
|   | [**TEST**](#function-test) ([**LASFile**](classLASFile.md), [**TopLeft**](classCoordinate2D.md)) <br> |
|   | [**TEST**](#function-test) ([**LASFile**](classLASFile.md), [**WidthHeight**](classCoordinate2D.md)) <br> |
|   | [**TEST**](#function-test) ([**LASFile**](classLASFile.md), [**HeightRange**](classCoordinate2D.md)) <br> |
|   | [**TEST**](#function-test) ([**LASFile**](classLASFile.md), [**ExportBounds**](classCoordinate2D.md)) <br> |
|   | [**TEST**](#function-test) ([**LASFile**](classLASFile.md), [**Projection**](classCoordinate2D.md)) <br> |




























## Public Functions Documentation




### function TEST 

```C++
TEST (
    BorderType,
    StreamOutput
) 
```




<hr>



### function TEST 

```C++
TEST (
    BorderRanges,
    North
) 
```




<hr>



### function TEST 

```C++
TEST (
    BorderRanges,
    South
) 
```




<hr>



### function TEST 

```C++
TEST (
    BorderRanges,
    East
) 
```




<hr>



### function TEST 

```C++
TEST (
    BorderRanges,
    West
) 
```




<hr>



### function TEST 

```C++
TEST (
    BorderRanges,
    NorthEast
) 
```




<hr>



### function TEST 

```C++
TEST (
    BorderRanges,
    SouthWest
) 
```




<hr>



### function TEST 

```C++
TEST (
    BorderRanges,
    SouthEast
) 
```




<hr>



### function TEST 

```C++
TEST (
    BorderRanges,
    NorthWest
) 
```




<hr>



### function TEST 

```C++
TEST (
    ExternalBorderRanges,
    North
) 
```




<hr>



### function TEST 

```C++
TEST (
    ExternalBorderRanges,
    South
) 
```




<hr>



### function TEST 

```C++
TEST (
    ExternalBorderRanges,
    East
) 
```




<hr>



### function TEST 

```C++
TEST (
    ExternalBorderRanges,
    West
) 
```




<hr>



### function TEST 

```C++
TEST (
    ExternalBorderRanges,
    Corners
) 
```




<hr>



### function TEST 

```C++
TEST (
    LASRound,
    BasicRounding
) 
```




<hr>



### function TEST 

```C++
TEST (
    LASRound,
    WithResolution
) 
```




<hr>



### function TEST 

```C++
TEST (
    LASRound,
    WithSmallResolution
) 
```




<hr>



### function TEST 

```C++
TEST (
    Average,
    Integers
) 
```




<hr>



### function TEST 

```C++
TEST (
    Average,
    Doubles
) 
```




<hr>



### function TEST 

```C++
TEST (
    UniqueCoordName,
    BasicOutput
) 
```




<hr>



### function TEST 

```C++
TEST (
    UniqueCoordName,
    DifferentBoxesProduceDifferentNames
) 
```




<hr>



### function TEST 

```C++
TEST (
    UniqueCoordName,
    SameBoxProducesSameName
) 
```




<hr>



### function TEST 

```C++
TEST (
    LASData,
    ConstructFromExtent
) 
```




<hr>



### function TEST 

```C++
TEST (
    LASData,
    InsertAndAccess
) 
```




<hr>



### function TEST 

```C++
TEST (
    LASData,
    InsertUpdatesBounds
) 
```




<hr>



### function TEST 

```C++
TEST (
    LASData,
    IntensityRange
) 
```




<hr>



### function TEST 

```C++
TEST (
    LASData,
    Iterator
) 
```




<hr>



### function TEST 

```C++
TEST (
    LASData,
    PushBack
) 
```




<hr>



### function TEST 

```C++
TEST (
    LASData,
    MutableAccess
) 
```




<hr>



### function TEST 

```C++
TEST (
    LASFile,
    TopLeft
) 
```




<hr>



### function TEST 

```C++
TEST (
    LASFile,
    WidthHeight
) 
```




<hr>



### function TEST 

```C++
TEST (
    LASFile,
    HeightRange
) 
```




<hr>



### function TEST 

```C++
TEST (
    LASFile,
    ExportBounds
) 
```




<hr>



### function TEST 

```C++
TEST (
    LASFile,
    Projection
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/lib/las/tests/test_las_file.cpp`

