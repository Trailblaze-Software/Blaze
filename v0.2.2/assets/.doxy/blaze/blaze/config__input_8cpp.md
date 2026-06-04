

# File config\_input.cpp



[**FileList**](files.md) **>** [**config\_input**](dir_7e7c57be6e217d4e927a2ff8d648cb71.md) **>** [**config\_input.cpp**](config__input_8cpp.md)

[Go to the source code of this file](config__input_8cpp_source.md)



* `#include "config_input.hpp"`
* `#include <fstream>`
* `#include "assert/assert.hpp"`
* `#include <nlohmann/json.hpp>`













## Namespaces

| Type | Name |
| ---: | :--- |
| namespace | [**nlohmann**](namespacenlohmann.md) <br> |


## Classes

| Type | Name |
| ---: | :--- |
| struct | [**adl\_serializer&lt; BlockingThresholdColorPair &gt;**](structnlohmann_1_1adl__serializer_3_01BlockingThresholdColorPair_01_4.md) &lt;&gt;<br> |
| struct | [**adl\_serializer&lt; BuildingsConfig &gt;**](structnlohmann_1_1adl__serializer_3_01BuildingsConfig_01_4.md) &lt;&gt;<br> |
| struct | [**adl\_serializer&lt; CMYKColor &gt;**](structnlohmann_1_1adl__serializer_3_01CMYKColor_01_4.md) &lt;&gt;<br> |
| struct | [**adl\_serializer&lt; CanopyConfig &gt;**](structnlohmann_1_1adl__serializer_3_01CanopyConfig_01_4.md) &lt;&gt;<br> |
| struct | [**adl\_serializer&lt; ColorVariant &gt;**](structnlohmann_1_1adl__serializer_3_01ColorVariant_01_4.md) &lt;&gt;<br> |
| struct | [**adl\_serializer&lt; ContourConfig &gt;**](structnlohmann_1_1adl__serializer_3_01ContourConfig_01_4.md) &lt;&gt;<br> |
| struct | [**adl\_serializer&lt; ContourConfigs &gt;**](structnlohmann_1_1adl__serializer_3_01ContourConfigs_01_4.md) &lt;&gt;<br> |
| struct | [**adl\_serializer&lt; GridConfig &gt;**](structnlohmann_1_1adl__serializer_3_01GridConfig_01_4.md) &lt;&gt;<br> |
| struct | [**adl\_serializer&lt; GroundConfig &gt;**](structnlohmann_1_1adl__serializer_3_01GroundConfig_01_4.md) &lt;&gt;<br> |
| struct | [**adl\_serializer&lt; RGBColor &gt;**](structnlohmann_1_1adl__serializer_3_01RGBColor_01_4.md) &lt;&gt;<br> |
| struct | [**adl\_serializer&lt; RenderConfig &gt;**](structnlohmann_1_1adl__serializer_3_01RenderConfig_01_4.md) &lt;&gt;<br> |
| struct | [**adl\_serializer&lt; VegeConfig &gt;**](structnlohmann_1_1adl__serializer_3_01VegeConfig_01_4.md) &lt;&gt;<br> |
| struct | [**adl\_serializer&lt; VegeHeightConfig &gt;**](structnlohmann_1_1adl__serializer_3_01VegeHeightConfig_01_4.md) &lt;&gt;<br> |
| struct | [**adl\_serializer&lt; WaterConfig &gt;**](structnlohmann_1_1adl__serializer_3_01WaterConfig_01_4.md) &lt;&gt;<br> |
| struct | [**adl\_serializer&lt; WaterConfigs &gt;**](structnlohmann_1_1adl__serializer_3_01WaterConfigs_01_4.md) &lt;&gt;<br> |


## Public Types

| Type | Name |
| ---: | :--- |
| typedef nlohmann::json | [**json**](#typedef-json)  <br> |




















## Public Functions

| Type | Name |
| ---: | :--- |
|  std::ostream & | [**operator&lt;&lt;**](#function-operator) (std::ostream & os, [**const**](classCoordinate2D.md) [**Config**](structConfig.md) & config) <br> |
|  std::ostream & | [**operator&lt;&lt;**](#function-operator_1) (std::ostream & os, [**const**](classCoordinate2D.md) ProcessingStep & step) <br> |



























## Macros

| Type | Name |
| ---: | :--- |
| define  | [**JSON\_DIAGNOSTICS**](config__input_8cpp.md#define-json_diagnostics)  `1`<br> |
| define  | [**SERIALIZE\_ENUM\_STRICT**](config__input_8cpp.md#define-serialize_enum_strict) (ENUM\_TYPE, ...) `/* multi line expression */`<br> |

## Public Types Documentation




### typedef json 

```C++
using json =  nlohmann::json;
```




<hr>
## Public Functions Documentation




### function operator&lt;&lt; 

```C++
std::ostream & operator<< (
    std::ostream & os,
    const  Config & config
) 
```




<hr>



### function operator&lt;&lt; 

```C++
std::ostream & operator<< (
    std::ostream & os,
    const ProcessingStep & step
) 
```




<hr>
## Macro Definition Documentation





### define JSON\_DIAGNOSTICS 

```C++
#define JSON_DIAGNOSTICS `1`
```




<hr>



### define SERIALIZE\_ENUM\_STRICT 

```C++
#define SERIALIZE_ENUM_STRICT (
    ENUM_TYPE,
    ...
) `/* multi line expression */`
```




<hr>

------------------------------
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/lib/config_input/config_input.cpp`

