

# File water.cpp



[**FileList**](files.md) **>** [**methods**](dir_0525f968218f30056a0344f59b10bbbb.md) **>** [**water**](dir_9906ac72c69ac5c4da1443f27a433c13.md) **>** [**water.cpp**](water_8cpp.md)

[Go to the source code of this file](water_8cpp_source.md)



* `#include "water.hpp"`
* `#include <queue>`
* `#include "config_input/config_input.hpp"`
* `#include "grid/grid.hpp"`
* `#include "utilities/coordinate.hpp"`
* `#include "utilities/progress_tracker.hpp"`















## Classes

| Type | Name |
| ---: | :--- |
| struct | [**PriorityPoint**](structPriorityPoint.md) <br> |






















## Public Functions

| Type | Name |
| ---: | :--- |
|  [**GeoGrid**](classGeo.md)&lt; double &gt; | [**catchment\_size**](#function-catchment_size) (const [**GeoGrid**](classGeo.md)&lt; double &gt; & filled, [**ProgressTracker**](classProgressTracker.md) && progress\_tracker) <br> |
|  [**GeoGrid**](classGeo.md)&lt; double &gt; | [**fill\_depressions**](#function-fill_depressions) (const [**GeoGrid**](classGeo.md)&lt; double &gt; & grid, [**ProgressTracker**](classProgressTracker.md) && progress\_tracker, const std::vector&lt; [**Coordinate2D**](classCoordinate2D.md)&lt; size\_t &gt; &gt; & sinks) <br> |
|  std::optional&lt; [**Coordinate2D**](classCoordinate2D.md)&lt; size\_t &gt; &gt; | [**flows\_to**](#function-flows_to) (const [**GeoGrid**](classGeo.md)&lt; double &gt; & grid, const [**Coordinate2D**](classCoordinate2D.md)&lt; size\_t &gt; & coord) <br> |
|  std::vector&lt; [**Coordinate2D**](classCoordinate2D.md)&lt; size\_t &gt; &gt; | [**identify\_sinks**](#function-identify_sinks) (const [**GeoGrid**](classGeo.md)&lt; double &gt; & grid, const double depth, const double min\_area, [**ProgressTracker**](classProgressTracker.md) && progress\_tracker) <br> |
|  std::vector&lt; [**Coordinate2D**](classCoordinate2D.md)&lt; double &gt; &gt; | [**smoothify**](#function-smoothify) (const std::vector&lt; [**Coordinate2D**](classCoordinate2D.md)&lt; double &gt; &gt; & path) <br> |
|  std::vector&lt; [**Coordinate2D**](classCoordinate2D.md)&lt; size\_t &gt; &gt; | [**stream\_path**](#function-stream_path) (const [**GeoGrid**](classGeo.md)&lt; bool &gt; & stream, [**GeoGrid**](classGeo.md)&lt; bool &gt; & visited, const [**GeoGrid**](classGeo.md)&lt; double &gt; & heights, std::vector&lt; [**Coordinate2D**](classCoordinate2D.md)&lt; size\_t &gt; &gt; && start, std::queue&lt; std::vector&lt; [**Coordinate2D**](classCoordinate2D.md)&lt; size\_t &gt; &gt; &gt; & queue\_of\_starts) <br> |
|  std::vector&lt; [**Stream**](structStream.md) &gt; | [**stream\_paths**](#function-stream_paths) (const [**GeoGrid**](classGeo.md)&lt; double &gt; & grid, const [**WaterConfigs**](structWaterConfigs.md) & config, [**ProgressTracker**](classProgressTracker.md) && progress\_tracker, const bool already\_filled) <br> |
|  [**GeoGrid**](classGeo.md)&lt; bool &gt; | [**streams**](#function-streams) (const [**GeoGrid**](classGeo.md)&lt; double &gt; & filled\_ground, const [**GeoGrid**](classGeo.md)&lt; double &gt; & catchment, const double minimum\_catchment, [**ProgressTracker**](classProgressTracker.md) && progress\_tracker) <br> |



























## Macros

| Type | Name |
| ---: | :--- |
| define  | [**SQ**](water_8cpp.md#define-sq) (x) `((x) \* (x))`<br> |

## Public Functions Documentation




### function catchment\_size 

```C++
GeoGrid < double > catchment_size (
    const GeoGrid < double > & filled,
    ProgressTracker && progress_tracker
) 
```




<hr>



### function fill\_depressions 

```C++
GeoGrid < double > fill_depressions (
    const GeoGrid < double > & grid,
    ProgressTracker && progress_tracker,
    const std::vector< Coordinate2D < size_t > > & sinks
) 
```




<hr>



### function flows\_to 

```C++
std::optional< Coordinate2D < size_t > > flows_to (
    const GeoGrid < double > & grid,
    const Coordinate2D < size_t > & coord
) 
```




<hr>



### function identify\_sinks 

```C++
std::vector< Coordinate2D < size_t > > identify_sinks (
    const GeoGrid < double > & grid,
    const double depth,
    const double min_area,
    ProgressTracker && progress_tracker
) 
```




<hr>



### function smoothify 

```C++
std::vector< Coordinate2D < double > > smoothify (
    const std::vector< Coordinate2D < double > > & path
) 
```




<hr>



### function stream\_path 

```C++
std::vector< Coordinate2D < size_t > > stream_path (
    const GeoGrid < bool > & stream,
    GeoGrid < bool > & visited,
    const GeoGrid < double > & heights,
    std::vector< Coordinate2D < size_t > > && start,
    std::queue< std::vector< Coordinate2D < size_t > > > & queue_of_starts
) 
```




<hr>



### function stream\_paths 

```C++
std::vector< Stream > stream_paths (
    const GeoGrid < double > & grid,
    const WaterConfigs & config,
    ProgressTracker && progress_tracker,
    const bool already_filled
) 
```




<hr>



### function streams 

```C++
GeoGrid < bool > streams (
    const GeoGrid < double > & filled_ground,
    const GeoGrid < double > & catchment,
    const double minimum_catchment,
    ProgressTracker && progress_tracker
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
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/methods/water/water.cpp`

