

# File grid\_ops.hpp



[**FileList**](files.md) **>** [**grid**](dir_b440d1ddeab29faa8ab1c63476ee276f.md) **>** [**grid\_ops.hpp**](grid__ops_8hpp.md)

[Go to the source code of this file](grid__ops_8hpp_source.md)



* `#include <cmath>`
* `#include <limits>`
* `#include <map>`
* `#include <numeric>`
* `#include <optional>`
* `#include "grid.hpp"`
* `#include "utilities/coordinate.hpp"`
* `#include "utilities/timer.hpp"`

















## Public Types

| Type | Name |
| ---: | :--- |
| enum  | [**DownsampleMethod**](#enum-downsamplemethod)  <br> |




















## Public Functions

| Type | Name |
| ---: | :--- |
|  [**GeoGrid**](classGeo.md)&lt; std::optional&lt; std::byte &gt; &gt; | [**bool\_grid**](#function-bool_grid) ([**const**](classCoordinate2D.md) [**GeoGrid**](classGeo.md)&lt; T &gt; & grid, T threshold) <br> |
|  [**GeoGrid**](classGeo.md)&lt; T &gt; | [**downsample**](#function-downsample) ([**const**](classCoordinate2D.md) [**GeoGrid**](classGeo.md)&lt; T &gt; & grid, [**size\_t**](classCoordinate2D.md) factor, [**ProgressTracker**](classProgressTracker.md) && progress\_tracker, DownsampleMethod method=DownsampleMethod::MEDIAN) <br> |
|  [**void**](classCoordinate2D.md) | [**interpolate\_holes**](#function-interpolate_holes) ([**GeoGrid**](classGeo.md)&lt; T &gt; & grid, [**ProgressTracker**](classProgressTracker.md) progress\_tracker) <br> |
|  [**void**](classCoordinate2D.md) | [**remove\_outliers**](#function-remove_outliers) ([**GeoGrid**](classGeo.md)&lt; T &gt; & grid, [**ProgressTracker**](classProgressTracker.md) progress\_tracker, [**double**](classCoordinate2D.md) z\_threshold=1, [**bool**](classCoordinate2D.md) z\_only=[**false**](classCoordinate2D.md)) <br> |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  [**bool**](classCoordinate2D.md) | [**has\_value**](#function-has_value) ([**double**](classCoordinate2D.md) value) <br> |

























## Macros

| Type | Name |
| ---: | :--- |
| define  | [**SQ**](grid__ops_8hpp.md#define-sq) (x) `((x) \* (x))`<br> |

## Public Types Documentation




### enum DownsampleMethod 

```C++
enum DownsampleMethod {
    MEAN,
    MEDIAN
};
```




<hr>
## Public Functions Documentation




### function bool\_grid 

```C++
template<typename T>
GeoGrid < std::optional< std::byte > > bool_grid (
    const  GeoGrid < T > & grid,
    T threshold
) 
```




<hr>



### function downsample 

```C++
template<typename T>
GeoGrid < T > downsample (
    const  GeoGrid < T > & grid,
    size_t factor,
    ProgressTracker && progress_tracker,
    DownsampleMethod method=DownsampleMethod::MEDIAN
) 
```




<hr>



### function interpolate\_holes 

```C++
template<typename T>
void interpolate_holes (
    GeoGrid < T > & grid,
    ProgressTracker progress_tracker
) 
```




<hr>



### function remove\_outliers 

```C++
template<typename T>
void remove_outliers (
    GeoGrid < T > & grid,
    ProgressTracker progress_tracker,
    double z_threshold=1,
    bool z_only=false
) 
```




<hr>
## Public Static Functions Documentation




### function has\_value 

```C++
static inline bool has_value (
    double value
) 
```




<hr>
## Macro Definition Documentation





### define SQ 

```C++
#define SQ (
    x
) `((x) * (x))`
```




<hr>

------------------------------
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/lib/grid/grid_ops.hpp`

