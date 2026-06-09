

# File config\_input.hpp



[**FileList**](files.md) **>** [**config\_input**](dir_7e7c57be6e217d4e927a2ff8d648cb71.md) **>** [**config\_input.hpp**](config__input_8hpp.md)

[Go to the source code of this file](config__input_8hpp_source.md)



* `#include <cmath>`
* `#include <iostream>`
* `#include <optional>`
* `#include <set>`
* `#include <vector>`
* `#include "isom/colors.hpp"`
* `#include "utilities/filesystem.hpp"`
* `#include "utilities/resources.hpp"`















## Classes

| Type | Name |
| ---: | :--- |
| struct | [**BlockingThresholdColorPair**](structBlockingThresholdColorPair.md) <br> |
| struct | [**BuildingsConfig**](structBuildingsConfig.md) <br> |
| struct | [**CanopyConfig**](structCanopyConfig.md) <br> |
| struct | [**Config**](structConfig.md) <br> |
| struct | [**ContourConfig**](structContourConfig.md) <br> |
| struct | [**ContourConfigs**](structContourConfigs.md) <br> |
| struct | [**GridConfig**](structGridConfig.md) <br> |
| struct | [**GroundConfig**](structGroundConfig.md) <br> |
| struct | [**RenderConfig**](structRenderConfig.md) <br> |
| struct | [**VegeConfig**](structVegeConfig.md) <br> |
| struct | [**VegeHeightConfig**](structVegeHeightConfig.md) <br> |
| struct | [**WaterConfig**](structWaterConfig.md) <br> |
| struct | [**WaterConfigs**](structWaterConfigs.md) <br> |


## Public Types

| Type | Name |
| ---: | :--- |
| enum  | [**ProcessingStep**](#enum-processingstep)  <br> |




















## Public Functions

| Type | Name |
| ---: | :--- |
|  std::ostream & | [**operator&lt;&lt;**](#function-operator) (std::ostream & os, [**const**](classCoordinate2D.md) ProcessingStep & step) <br> |



























## Macros

| Type | Name |
| ---: | :--- |
| define  | [**SERIALIZE\_ENUM\_STRICT**](config__input_8hpp.md#define-serialize_enum_strict) (ENUM\_TYPE, ...) `/* multi line expression */`<br> |

## Public Types Documentation




### enum ProcessingStep 

```C++
enum ProcessingStep {
    Tiles,
    Combine
};
```




<hr>
## Public Functions Documentation




### function operator&lt;&lt; 

```C++
std::ostream & operator<< (
    std::ostream & os,
    const ProcessingStep & step
) 
```




<hr>
## Macro Definition Documentation





### define SERIALIZE\_ENUM\_STRICT 

```C++
#define SERIALIZE_ENUM_STRICT (
    ENUM_TYPE,
    ...
) `/* multi line expression */`
```




<hr>

------------------------------
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/lib/config_input/config_input.hpp`

