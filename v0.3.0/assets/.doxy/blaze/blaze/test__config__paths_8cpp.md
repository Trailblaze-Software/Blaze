

# File test\_config\_paths.cpp



[**FileList**](files.md) **>** [**config\_input**](dir_7e7c57be6e217d4e927a2ff8d648cb71.md) **>** [**tests**](dir_7e4ff660e0fa82332112dfaa3eba02fe.md) **>** [**test\_config\_paths.cpp**](test__config__paths_8cpp.md)

[Go to the source code of this file](test__config__paths_8cpp_source.md)



* `#include <gtest/gtest.h>`
* `#include "config_input/config_input.hpp"`





































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**TEST**](#function-test) (ConfigPaths, OutputPathAbsolute) <br> |
|   | [**TEST**](#function-test) (ConfigPaths, OutputPathRelative) <br> |
|   | [**TEST**](#function-test) (ConfigPaths, SetOutputDirectory) <br> |
|   | [**TEST**](#function-test) (ConfigPaths, LasFilepathsAbsolute) <br> |
|   | [**TEST**](#function-test) (ConfigPaths, LasFilepathsRelative) <br> |
|   | [**TEST**](#function-test) (ConfigPaths, LasFilepathsEmpty) <br> |
|   | [**TEST**](#function-test) (ConfigPaths, LasFilepathsMixed) <br> |
|   | [**TEST**](#function-test) ([**ContourConfigs**](structContourConfigs.md), PickFromHeightNegative) <br> |
|   | [**TEST**](#function-test) ([**ContourConfigs**](structContourConfigs.md), MinimumIntervalStatic) <br> |
|   | [**TEST**](#function-test) ([**ContourConfigs**](structContourConfigs.md), LayerNameDefaultForUnknown) <br> |
|   | [**TEST**](#function-test) ([**WaterConfigs**](structWaterConfigs.md), ConfigFromCatchmentExact) <br> |



























## Macros

| Type | Name |
| ---: | :--- |
| define  | [**ABS\_CONFIG\_DIR**](test__config__paths_8cpp.md#define-abs_config_dir)  `"/some/config/dir"`<br> |
| define  | [**ABS\_CONFIG\_DIR2**](test__config__paths_8cpp.md#define-abs_config_dir2)  `"/config/dir"`<br> |
| define  | [**ABS\_FILE1**](test__config__paths_8cpp.md#define-abs_file1)  `"/absolute/file1.las"`<br> |
| define  | [**ABS\_FILE2**](test__config__paths_8cpp.md#define-abs_file2)  `"/absolute/file2.laz"`<br> |
| define  | [**ABS\_OUTPUT**](test__config__paths_8cpp.md#define-abs_output)  `"/absolute/output"`<br> |

## Public Functions Documentation




### function TEST 

```C++
TEST (
    ConfigPaths,
    OutputPathAbsolute
) 
```




<hr>



### function TEST 

```C++
TEST (
    ConfigPaths,
    OutputPathRelative
) 
```




<hr>



### function TEST 

```C++
TEST (
    ConfigPaths,
    SetOutputDirectory
) 
```




<hr>



### function TEST 

```C++
TEST (
    ConfigPaths,
    LasFilepathsAbsolute
) 
```




<hr>



### function TEST 

```C++
TEST (
    ConfigPaths,
    LasFilepathsRelative
) 
```




<hr>



### function TEST 

```C++
TEST (
    ConfigPaths,
    LasFilepathsEmpty
) 
```




<hr>



### function TEST 

```C++
TEST (
    ConfigPaths,
    LasFilepathsMixed
) 
```




<hr>



### function TEST 

```C++
TEST (
    ContourConfigs,
    PickFromHeightNegative
) 
```




<hr>



### function TEST 

```C++
TEST (
    ContourConfigs,
    MinimumIntervalStatic
) 
```




<hr>



### function TEST 

```C++
TEST (
    ContourConfigs,
    LayerNameDefaultForUnknown
) 
```




<hr>



### function TEST 

```C++
TEST (
    WaterConfigs,
    ConfigFromCatchmentExact
) 
```




<hr>
## Macro Definition Documentation





### define ABS\_CONFIG\_DIR 

```C++
#define ABS_CONFIG_DIR `"/some/config/dir"`
```




<hr>



### define ABS\_CONFIG\_DIR2 

```C++
#define ABS_CONFIG_DIR2 `"/config/dir"`
```




<hr>



### define ABS\_FILE1 

```C++
#define ABS_FILE1 `"/absolute/file1.las"`
```




<hr>



### define ABS\_FILE2 

```C++
#define ABS_FILE2 `"/absolute/file2.laz"`
```




<hr>



### define ABS\_OUTPUT 

```C++
#define ABS_OUTPUT `"/absolute/output"`
```




<hr>

------------------------------
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/lib/config_input/tests/test_config_paths.cpp`

