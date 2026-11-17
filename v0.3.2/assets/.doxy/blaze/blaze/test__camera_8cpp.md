

# File test\_camera.cpp



[**FileList**](files.md) **>** [**gui**](dir_99d0482cf009f9d97a0877749b817f19.md) **>** [**tests**](dir_f2e26a16b2cc77b57a8a23b2e82761a0.md) **>** [**test\_camera.cpp**](test__camera_8cpp.md)

[Go to the source code of this file](test__camera_8cpp_source.md)



* `#include <gtest/gtest.h>`
* `#include <QPointF>`
* `#include <QVector3D>`
* `#include <cmath>`
* `#include "gui/camera.hpp"`





































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**TEST**](#function-test) ([**Camera**](classCamera.md), PanToTargetMovesFocalPointToTarget) <br> |
|   | [**TEST**](#function-test) ([**Camera**](classCamera.md), PanToTargetNoOpWhenAlreadyCentered) <br> |
|   | [**TEST**](#function-test) ([**Camera**](classCamera.md), LookAtTargetReorientsWithoutMovingPosition) <br> |
|   | [**TEST**](#function-test) ([**Camera**](classCamera.md), ProjectWorldToScreenRoundTripsWithUnproject) <br> |
|   | [**TEST**](#function-test) ([**Camera**](classCamera.md), ProjectWorldToScreenBehindCameraReturnsSentinel) <br> |




























## Public Functions Documentation




### function TEST 

```C++
TEST (
    Camera,
    PanToTargetMovesFocalPointToTarget
) 
```




<hr>



### function TEST 

```C++
TEST (
    Camera,
    PanToTargetNoOpWhenAlreadyCentered
) 
```




<hr>



### function TEST 

```C++
TEST (
    Camera,
    LookAtTargetReorientsWithoutMovingPosition
) 
```




<hr>



### function TEST 

```C++
TEST (
    Camera,
    ProjectWorldToScreenRoundTripsWithUnproject
) 
```




<hr>



### function TEST 

```C++
TEST (
    Camera,
    ProjectWorldToScreenBehindCameraReturnsSentinel
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/gui/tests/test_camera.cpp`

