

# File test\_colors.cpp



[**FileList**](files.md) **>** [**isom**](dir_95e71238802b7f0c2279a9a971eb5146.md) **>** [**tests**](dir_fd4bfd50a894f2f8cc4c88d12f7e8a3a.md) **>** [**test\_colors.cpp**](test__colors_8cpp.md)

[Go to the source code of this file](test__colors_8cpp_source.md)



* `#include <gtest/gtest.h>`
* `#include "isom/colors.hpp"`





































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**TEST**](#function-test) ([**RGBColor**](classRGBColor.md), [**Construction**](classCoordinate2D.md)) <br> |
|   | [**TEST**](#function-test) ([**RGBColor**](classRGBColor.md), [**ConstructionWithAlpha**](classCoordinate2D.md)) <br> |
|   | [**TEST**](#function-test) ([**RGBColor**](classRGBColor.md), [**DefaultConstruction**](classCoordinate2D.md)) <br> |
|   | [**TEST**](#function-test) ([**RGBColor**](classRGBColor.md), [**IndexOperator**](classCoordinate2D.md)) <br> |
|   | [**TEST**](#function-test) ([**CMYKColor**](classCMYKColor.md), [**Construction**](classCoordinate2D.md)) <br> |
|   | [**TEST**](#function-test) ([**CMYKColor**](classCMYKColor.md), [**DefaultConstruction**](classCoordinate2D.md)) <br> |
|   | [**TEST**](#function-test) ([**CMYKColor**](classCMYKColor.md), [**Addition**](classCoordinate2D.md)) <br> |
|   | [**TEST**](#function-test) ([**CMYKColor**](classCMYKColor.md), [**AdditionClamping**](classCoordinate2D.md)) <br> |
|   | [**TEST**](#function-test) ([**CMYKColor**](classCMYKColor.md), [**Multiply**](classCoordinate2D.md)) <br> |
|   | [**TEST**](#function-test) ([**ColorConversion**](classCoordinate2D.md), [**CMYKToRGB\_Black**](classCoordinate2D.md)) <br> |
|   | [**TEST**](#function-test) ([**ColorConversion**](classCoordinate2D.md), [**CMYKToRGB\_White**](classCoordinate2D.md)) <br> |
|   | [**TEST**](#function-test) ([**ColorConversion**](classCoordinate2D.md), [**CMYKToRGB\_Red**](classCoordinate2D.md)) <br> |
|   | [**TEST**](#function-test) ([**ColorConversion**](classCoordinate2D.md), [**CMYKToRGB\_Green**](classCoordinate2D.md)) <br> |
|   | [**TEST**](#function-test) ([**ColorConversion**](classCoordinate2D.md), [**CMYKToRGB\_Blue**](classCoordinate2D.md)) <br> |
|   | [**TEST**](#function-test) ([**ColorConversion**](classCoordinate2D.md), [**RGBToCMYK\_Black**](classCoordinate2D.md)) <br> |
|   | [**TEST**](#function-test) ([**ColorConversion**](classCoordinate2D.md), [**RGBToCMYK\_White**](classCoordinate2D.md)) <br> |
|   | [**TEST**](#function-test) ([**ColorConversion**](classCoordinate2D.md), [**RGBToCMYK\_Red**](classCoordinate2D.md)) <br> |
|   | [**TEST**](#function-test) ([**ColorConversion**](classCoordinate2D.md), [**RGBToCMYK\_Green**](classCoordinate2D.md)) <br> |
|   | [**TEST**](#function-test) ([**ColorConversion**](classCoordinate2D.md), [**RGBToCMYK\_Blue**](classCoordinate2D.md)) <br> |
|   | [**TEST**](#function-test) ([**ColorConversion**](classCoordinate2D.md), [**RoundTripRGBToCMYKToRGB**](classCoordinate2D.md)) <br> |
|   | [**TEST**](#function-test) (ColorVariant, [**ToRGB**](classCoordinate2D.md)) <br> |
|   | [**TEST**](#function-test) (ColorVariant, [**ToCMYK**](classCoordinate2D.md)) <br> |




























## Public Functions Documentation




### function TEST 

```C++
TEST (
    RGBColor,
    Construction
) 
```




<hr>



### function TEST 

```C++
TEST (
    RGBColor,
    ConstructionWithAlpha
) 
```




<hr>



### function TEST 

```C++
TEST (
    RGBColor,
    DefaultConstruction
) 
```




<hr>



### function TEST 

```C++
TEST (
    RGBColor,
    IndexOperator
) 
```




<hr>



### function TEST 

```C++
TEST (
    CMYKColor,
    Construction
) 
```




<hr>



### function TEST 

```C++
TEST (
    CMYKColor,
    DefaultConstruction
) 
```




<hr>



### function TEST 

```C++
TEST (
    CMYKColor,
    Addition
) 
```




<hr>



### function TEST 

```C++
TEST (
    CMYKColor,
    AdditionClamping
) 
```




<hr>



### function TEST 

```C++
TEST (
    CMYKColor,
    Multiply
) 
```




<hr>



### function TEST 

```C++
TEST (
    ColorConversion,
    CMYKToRGB_Black
) 
```




<hr>



### function TEST 

```C++
TEST (
    ColorConversion,
    CMYKToRGB_White
) 
```




<hr>



### function TEST 

```C++
TEST (
    ColorConversion,
    CMYKToRGB_Red
) 
```




<hr>



### function TEST 

```C++
TEST (
    ColorConversion,
    CMYKToRGB_Green
) 
```




<hr>



### function TEST 

```C++
TEST (
    ColorConversion,
    CMYKToRGB_Blue
) 
```




<hr>



### function TEST 

```C++
TEST (
    ColorConversion,
    RGBToCMYK_Black
) 
```




<hr>



### function TEST 

```C++
TEST (
    ColorConversion,
    RGBToCMYK_White
) 
```




<hr>



### function TEST 

```C++
TEST (
    ColorConversion,
    RGBToCMYK_Red
) 
```




<hr>



### function TEST 

```C++
TEST (
    ColorConversion,
    RGBToCMYK_Green
) 
```




<hr>



### function TEST 

```C++
TEST (
    ColorConversion,
    RGBToCMYK_Blue
) 
```




<hr>



### function TEST 

```C++
TEST (
    ColorConversion,
    RoundTripRGBToCMYKToRGB
) 
```




<hr>



### function TEST 

```C++
TEST (
    ColorVariant,
    ToRGB
) 
```




<hr>



### function TEST 

```C++
TEST (
    ColorVariant,
    ToCMYK
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/lib/isom/tests/test_colors.cpp`

