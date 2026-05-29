

# File water.hpp



[**FileList**](files.md) **>** [**methods**](dir_0525f968218f30056a0344f59b10bbbb.md) **>** [**water**](dir_9906ac72c69ac5c4da1443f27a433c13.md) **>** [**water.hpp**](water_8hpp.md)

[Go to the source code of this file](water_8hpp_source.md)



* `#include <cstddef>`
* `#include <vector>`
* `#include "grid/forward_grid.hpp"`
* `#include "utilities/coordinate.hpp"`















## Classes

| Type | Name |
| ---: | :--- |
| struct | [**Stream**](structStream.md) <br> |






















## Public Functions

| Type | Name |
| ---: | :--- |
|  [**GeoGrid**](classGeo.md)&lt; [**double**](classCoordinate2D.md) &gt; | [**fill\_depressions**](#function-fill_depressions) ([**const**](classCoordinate2D.md) [**GeoGrid**](classGeo.md)&lt; [**double**](classCoordinate2D.md) &gt; & grid, [**const**](classCoordinate2D.md) std::vector&lt; [**Coordinate2D**](classCoordinate2D.md)&lt; [**size\_t**](classCoordinate2D.md) &gt; &gt; & sinks={}) <br> |
|  std::vector&lt; [**Coordinate2D**](classCoordinate2D.md)&lt; [**size\_t**](classCoordinate2D.md) &gt; &gt; | [**identify\_sinks**](#function-identify_sinks) ([**const**](classCoordinate2D.md) [**GeoGrid**](classGeo.md)&lt; [**double**](classCoordinate2D.md) &gt; & grid, [**double**](classCoordinate2D.md) depth=10, [**double**](classCoordinate2D.md) min\_area=5000) <br> |
|  std::vector&lt; [**Stream**](structStream.md) &gt; | [**stream\_paths**](#function-stream_paths) ([**const**](classCoordinate2D.md) [**GeoGrid**](classGeo.md)&lt; [**double**](classCoordinate2D.md) &gt; & grid, [**const**](classCoordinate2D.md) [**WaterConfigs**](structWaterConfigs.md) & config, [**ProgressTracker**](classProgressTracker.md) progress\_tracker, [**bool**](classCoordinate2D.md) already\_filled=[**false**](classCoordinate2D.md)) <br> |




























## Public Functions Documentation




### function fill\_depressions 

```C++
GeoGrid < double > fill_depressions (
    const  GeoGrid < double > & grid,
    const std::vector< Coordinate2D < size_t > > & sinks={}
) 
```




<hr>



### function identify\_sinks 

```C++
std::vector< Coordinate2D < size_t > > identify_sinks (
    const  GeoGrid < double > & grid,
    double depth=10,
    double min_area=5000
) 
```




<hr>



### function stream\_paths 

```C++
std::vector< Stream > stream_paths (
    const  GeoGrid < double > & grid,
    const  WaterConfigs & config,
    ProgressTracker progress_tracker,
    bool already_filled=false
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/methods/water/water.hpp`

