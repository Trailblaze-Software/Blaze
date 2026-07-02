

# File grid\_ops.hpp



[**FileList**](files.md) **>** [**grid**](dir_b440d1ddeab29faa8ab1c63476ee276f.md) **>** [**grid\_ops.hpp**](grid__ops_8hpp.md)

[Go to the source code of this file](grid__ops_8hpp_source.md)



* `#include <cmath>`
* `#include <cstdint>`
* `#include <deque>`
* `#include <limits>`
* `#include <map>`
* `#include <numeric>`
* `#include <optional>`
* `#include "grid.hpp"`
* `#include "utilities/coordinate.hpp"`
* `#include "utilities/progress_tracker.hpp"`

















## Public Types

| Type | Name |
| ---: | :--- |
| enum  | [**DownsampleMethod**](#enum-downsamplemethod)  <br> |




















## Public Functions

| Type | Name |
| ---: | :--- |
|  void | [**apply\_coverage\_mask**](#function-apply_coverage_mask) ([**GeoGrid**](classGeo.md)&lt; T &gt; & grid, const [**GeoGrid**](classGeo.md)&lt; bool &gt; & coverage) <br> |
|  [**GeoGrid**](classGeo.md)&lt; std::optional&lt; std::byte &gt; &gt; | [**bool\_grid**](#function-bool_grid) (const [**GeoGrid**](classGeo.md)&lt; T &gt; & grid, T threshold, [**ProgressTracker**](classProgressTracker.md) && progress\_tracker) <br> |
|  [**GeoGrid**](classGeo.md)&lt; bool &gt; | [**compute\_lidar\_coverage\_mask**](#function-compute_lidar_coverage_mask) (size\_t width, size\_t height, const [**GeoTransform**](classGeoTransform.md) & transform, const [**GeoProjection**](classGeoProjection.md) & projection, IsEmptyFn && is\_empty, [**ProgressTracker**](classProgressTracker.md) && progress\_tracker) <br> |
|  [**Extent2D**](structExtent2D.md) | [**coverage\_extent**](#function-coverage_extent) (const [**GeoGrid**](classGeo.md)&lt; bool &gt; & coverage) <br> |
|  [**GeoGrid**](classGeo.md)&lt; T &gt; | [**downsample**](#function-downsample) (const [**GeoGrid**](classGeo.md)&lt; T &gt; & grid, size\_t factor, [**ProgressTracker**](classProgressTracker.md) && progress\_tracker, DownsampleMethod method=DownsampleMethod::MEDIAN) <br> |
|  void | [**enforce\_downsample\_nodata**](#function-enforce_downsample_nodata) ([**GeoGrid**](classGeo.md)&lt; T &gt; & coarse, const [**GeoGrid**](classGeo.md)&lt; T &gt; & fine, size\_t factor) <br> |
|  void | [**fill\_grid\_from\_coverage**](#function-fill_grid_from_coverage) ([**GeoGrid**](classGeo.md)&lt; T &gt; & dest, const [**GeoGrid**](classGeo.md)&lt; bool &gt; & coverage, const T & data\_value, const T & nodata\_value) <br> |
|  void | [**interpolate\_holes**](#function-interpolate_holes) ([**GeoGrid**](classGeo.md)&lt; T &gt; & grid, [**ProgressTracker**](classProgressTracker.md) && progress\_tracker) <br> |
|  void | [**mask\_outside\_coverage**](#function-mask_outside_coverage) ([**GeoGrid**](classGeo.md)&lt; T &gt; & dest, const [**GeoGrid**](classGeo.md)&lt; bool &gt; & coverage, const T & nodata\_value) <br> |
|  void | [**remove\_outliers**](#function-remove_outliers) ([**GeoGrid**](classGeo.md)&lt; T &gt; & grid, [**ProgressTracker**](classProgressTracker.md) && progress\_tracker, double z\_threshold=1, bool z\_only=false) <br> |
|  bool | [**sample\_coverage\_at\_pixel**](#function-sample_coverage_at_pixel) (const [**GeoGrid**](classGeo.md)&lt; bool &gt; & coverage, const [**GeoTransform**](classGeoTransform.md) & dest\_transform, size\_t col, size\_t row) <br> |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  bool | [**has\_value**](#function-has_value) (double value) <br> |

























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




### function apply\_coverage\_mask 

```C++
template<typename T>
void apply_coverage_mask (
    GeoGrid < T > & grid,
    const GeoGrid < bool > & coverage
) 
```




<hr>



### function bool\_grid 

```C++
template<typename T>
GeoGrid < std::optional< std::byte > > bool_grid (
    const GeoGrid < T > & grid,
    T threshold,
    ProgressTracker && progress_tracker
) 
```




<hr>



### function compute\_lidar\_coverage\_mask 

```C++
template<typename IsEmptyFn>
GeoGrid < bool > compute_lidar_coverage_mask (
    size_t width,
    size_t height,
    const GeoTransform & transform,
    const GeoProjection & projection,
    IsEmptyFn && is_empty,
    ProgressTracker && progress_tracker
) 
```




<hr>



### function coverage\_extent 

```C++
inline Extent2D coverage_extent (
    const GeoGrid < bool > & coverage
) 
```




<hr>



### function downsample 

```C++
template<typename T>
GeoGrid < T > downsample (
    const GeoGrid < T > & grid,
    size_t factor,
    ProgressTracker && progress_tracker,
    DownsampleMethod method=DownsampleMethod::MEDIAN
) 
```




<hr>



### function enforce\_downsample\_nodata 

```C++
template<typename T>
void enforce_downsample_nodata (
    GeoGrid < T > & coarse,
    const GeoGrid < T > & fine,
    size_t factor
) 
```




<hr>



### function fill\_grid\_from\_coverage 

```C++
template<typename T>
void fill_grid_from_coverage (
    GeoGrid < T > & dest,
    const GeoGrid < bool > & coverage,
    const T & data_value,
    const T & nodata_value
) 
```




<hr>



### function interpolate\_holes 

```C++
template<typename T>
void interpolate_holes (
    GeoGrid < T > & grid,
    ProgressTracker && progress_tracker
) 
```




<hr>



### function mask\_outside\_coverage 

```C++
template<typename T>
void mask_outside_coverage (
    GeoGrid < T > & dest,
    const GeoGrid < bool > & coverage,
    const T & nodata_value
) 
```




<hr>



### function remove\_outliers 

```C++
template<typename T>
void remove_outliers (
    GeoGrid < T > & grid,
    ProgressTracker && progress_tracker,
    double z_threshold=1,
    bool z_only=false
) 
```




<hr>



### function sample\_coverage\_at\_pixel 

```C++
inline bool sample_coverage_at_pixel (
    const GeoGrid < bool > & coverage,
    const GeoTransform & dest_transform,
    size_t col,
    size_t row
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

