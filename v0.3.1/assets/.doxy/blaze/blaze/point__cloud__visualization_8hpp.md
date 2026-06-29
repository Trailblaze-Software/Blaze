

# File point\_cloud\_visualization.hpp



[**FileList**](files.md) **>** [**gui**](dir_99d0482cf009f9d97a0877749b817f19.md) **>** [**point\_cloud\_visualization.hpp**](point__cloud__visualization_8hpp.md)

[Go to the source code of this file](point__cloud__visualization_8hpp_source.md)



* `#include <array>`
* `#include <cstdint>`
* `#include <string>`















## Classes

| Type | Name |
| ---: | :--- |
| struct | [**ClassificationStyle**](structClassificationStyle.md) <br> |


## Public Types

| Type | Name |
| ---: | :--- |
| enum  | [**PointColorMode**](#enum-pointcolormode)  <br> |




## Public Attributes

| Type | Name |
| ---: | :--- |
|  constexpr std::array&lt; [**ClassificationStyle**](structClassificationStyle.md), 9 &gt; | [**CLASSIFICATION\_STYLES**](#variable-classification_styles)   = `/* multi line expression */`<br> |
|  constexpr std::array&lt; uint8\_t, 3 &gt; | [**DEFAULT\_CLASSIFICATION\_COLOR**](#variable-default_classification_color)   = `{{200, 200, 200}}`<br> |
















## Public Functions

| Type | Name |
| ---: | :--- |
|  std::array&lt; uint8\_t, 3 &gt; | [**classification\_color**](#function-classification_color) (uint8\_t classification) <br> |
|  std::string | [**classification\_color\_glsl**](#function-classification_color_glsl) () <br> |




























## Public Types Documentation




### enum PointColorMode 

```C++
enum PointColorMode {
    File,
    Classification,
    Fixed
};
```




<hr>
## Public Attributes Documentation




### variable CLASSIFICATION\_STYLES 

```C++
constexpr std::array<ClassificationStyle, 9> CLASSIFICATION_STYLES;
```




<hr>



### variable DEFAULT\_CLASSIFICATION\_COLOR 

```C++
constexpr std::array<uint8_t, 3> DEFAULT_CLASSIFICATION_COLOR;
```




<hr>
## Public Functions Documentation




### function classification\_color 

```C++
inline std::array< uint8_t, 3 > classification_color (
    uint8_t classification
) 
```




<hr>



### function classification\_color\_glsl 

```C++
inline std::string classification_color_glsl () 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/gui/point_cloud_visualization.hpp`

