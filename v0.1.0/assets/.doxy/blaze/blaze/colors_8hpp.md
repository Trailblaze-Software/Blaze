

# File colors.hpp



[**FileList**](files.md) **>** [**isom**](dir_95e71238802b7f0c2279a9a971eb5146.md) **>** [**colors.hpp**](colors_8hpp.md)

[Go to the source code of this file](colors_8hpp_source.md)



* `#include <array>`
* `#include <map>`
* `#include <ostream>`
* `#include <variant>`













## Namespaces

| Type | Name |
| ---: | :--- |
| namespace | [**cv**](namespacecv.md) <br> |


## Classes

| Type | Name |
| ---: | :--- |
| class | [**CMYKColor**](classCMYKColor.md) <br> |
| class | [**Color**](classColor.md) <br> |
| class | [**RGBColor**](classRGBColor.md) <br> |


## Public Types

| Type | Name |
| ---: | :--- |
| typedef std::variant&lt; [**RGBColor**](classRGBColor.md), [**CMYKColor**](classCMYKColor.md) &gt; | [**ColorVariant**](#typedef-colorvariant)  <br> |




## Public Attributes

| Type | Name |
| ---: | :--- |
|  std::map&lt; std::string, ColorVariant &gt; | [**COLOR\_MAP**](#variable-color_map)  <br> |
















## Public Functions

| Type | Name |
| ---: | :--- |
|  [**CMYKColor**](classCMYKColor.md) | [**to\_cmyk**](#function-to_cmyk) ([**const**](classCoordinate2D.md) ColorVariant & cv) <br> |
|  [**RGBColor**](classRGBColor.md) | [**to\_rgb**](#function-to_rgb) ([**const**](classCoordinate2D.md) ColorVariant & cv) <br> |




























## Public Types Documentation




### typedef ColorVariant 

```C++
typedef std::variant<RGBColor, CMYKColor> ColorVariant;
```




<hr>
## Public Attributes Documentation




### variable COLOR\_MAP 

```C++
std::map<std::string, ColorVariant> COLOR_MAP;
```




<hr>
## Public Functions Documentation




### function to\_cmyk 

```C++
inline CMYKColor to_cmyk (
    const ColorVariant & cv
) 
```




<hr>



### function to\_rgb 

```C++
inline RGBColor to_rgb (
    const ColorVariant & cv
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/lib/isom/colors.hpp`

