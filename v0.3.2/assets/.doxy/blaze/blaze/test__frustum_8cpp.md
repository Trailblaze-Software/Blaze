

# File test\_frustum.cpp



[**FileList**](files.md) **>** [**gui**](dir_99d0482cf009f9d97a0877749b817f19.md) **>** [**tests**](dir_f2e26a16b2cc77b57a8a23b2e82761a0.md) **>** [**test\_frustum.cpp**](test__frustum_8cpp.md)

[Go to the source code of this file](test__frustum_8cpp_source.md)



* `#include <gtest/gtest.h>`
* `#include <QMatrix4x4>`
* `#include "gui/frustum.hpp"`





































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**TEST**](#function-test) ([**Frustum**](structFrustum.md), IntersectsFullyInsideAABB) <br> |
|   | [**TEST**](#function-test) ([**Frustum**](structFrustum.md), RejectsAABBBehindNearPlane) <br> |
|   | [**TEST**](#function-test) ([**Frustum**](structFrustum.md), IntersectsPartiallyVisibleAABB) <br> |
|   | [**TEST**](#function-test) ([**Frustum**](structFrustum.md), RejectsAABBToTheLeft) <br> |
|   | [**TEST**](#function-test) ([**Frustum**](structFrustum.md), IntersectsAABBAtFrustumEdge) <br> |
|   | [**TEST**](#function-test) ([**Frustum**](structFrustum.md), HandlesZeroSizeAABB) <br> |
|   | [**TEST**](#function-test) ([**Frustum**](structFrustum.md), ConservativeTestIncludesPartialOverlap) <br> |




























## Public Functions Documentation




### function TEST 

```C++
TEST (
    Frustum,
    IntersectsFullyInsideAABB
) 
```




<hr>



### function TEST 

```C++
TEST (
    Frustum,
    RejectsAABBBehindNearPlane
) 
```




<hr>



### function TEST 

```C++
TEST (
    Frustum,
    IntersectsPartiallyVisibleAABB
) 
```




<hr>



### function TEST 

```C++
TEST (
    Frustum,
    RejectsAABBToTheLeft
) 
```




<hr>



### function TEST 

```C++
TEST (
    Frustum,
    IntersectsAABBAtFrustumEdge
) 
```




<hr>



### function TEST 

```C++
TEST (
    Frustum,
    HandlesZeroSizeAABB
) 
```




<hr>



### function TEST 

```C++
TEST (
    Frustum,
    ConservativeTestIncludesPartialOverlap
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/gui/tests/test_frustum.cpp`

