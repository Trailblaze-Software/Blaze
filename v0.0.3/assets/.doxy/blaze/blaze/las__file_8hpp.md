

# File las\_file.hpp



[**FileList**](files.md) **>** [**las**](dir_50e4ddd575fc604ec1609997d931fab5.md) **>** [**las\_file.hpp**](las__file_8hpp.md)

[Go to the source code of this file](las__file_8hpp_source.md)



* `#include <cstdint>`
* `#include <fstream>`
* `#include <future>`
* `#include <iostream>`
* `#include <limits>`
* `#include <mutex>`
* `#include "ogr_spatialref.h"`
* `#include "spatial_index.hpp"`
* `#include "las_reader.hpp"`
* `#include "las_writer.hpp"`
* `#include <string>`
* `#include <vector>`
* `#include "grid/grid.hpp"`
* `#include "las_point.hpp"`
* `#include "utilities/filesystem.hpp"`
* `#include "utilities/progress_tracker.hpp"`
* `#include "utilities/resources.hpp"`
* `#include "utilities/timer.hpp"`















## Classes

| Type | Name |
| ---: | :--- |
| class | [**AsyncLASData**](classAsyncLASData.md) <br> |
| class | [**LASData**](classLASData.md) <br> |
| class | [**LASFile**](classLASFile.md) <br> |


## Public Types

| Type | Name |
| ---: | :--- |
| enum  | [**BorderType**](#enum-bordertype)  <br> |




















## Public Functions

| Type | Name |
| ---: | :--- |
|  T | [**average**](#function-average) (T a, T b) <br> |
|  [**Extent2D**](structExtent2D.md) | [**border\_ranges**](#function-border_ranges) ([**const**](classCoordinate2D.md) [**Extent2D**](structExtent2D.md) & box, BorderType border\_type, [**double**](classCoordinate2D.md) border\_width) <br> |
|  std::string | [**convert\_geo\_keys\_to\_wkt**](#function-convert_geo_keys_to_wkt) ([**const**](classCoordinate2D.md) laspp::LASGeoKeys & geo\_keys) <br> |
|  [**void**](classCoordinate2D.md) | [**copy\_from**](#function-copy_from) ([**LASPoint**](classLASPoint.md) & point, [**const**](classCoordinate2D.md) laspp::LASPointFormat0 & data) <br> |
|  [**void**](classCoordinate2D.md) | [**copy\_from**](#function-copy_from) ([**LASPoint**](classLASPoint.md) & point, [**const**](classCoordinate2D.md) laspp::LASPointFormat6 & data) <br> |
|  [**void**](classCoordinate2D.md) | [**copy\_from**](#function-copy_from) (laspp::LASPointFormat0 & data, [**const**](classCoordinate2D.md) [**LASPoint**](classLASPoint.md) & point) <br> |
|  [**Extent2D**](structExtent2D.md) | [**external\_border\_ranges**](#function-external_border_ranges) ([**const**](classCoordinate2D.md) [**Extent2D**](structExtent2D.md) & box, BorderType border\_type, [**double**](classCoordinate2D.md) border\_width) <br> |
|  [**void**](classCoordinate2D.md) | [**extract\_borders**](#function-extract_borders) ([**const**](classCoordinate2D.md) fs::path & las\_filename, [**double**](classCoordinate2D.md) border\_width, [**ProgressTracker**](classProgressTracker.md) progress\_tracker) <br> |
|  std::ostream & | [**operator&lt;&lt;**](#function-operator) (std::ostream & os, BorderType border\_type) <br> |
|  [**long**](classCoordinate2D.md) [**int**](classCoordinate2D.md) | [**round**](#function-round) ([**double**](classCoordinate2D.md) x, [**double**](classCoordinate2D.md) resolution=1.0) <br> |
|  std::string | [**unique\_coord\_name**](#function-unique_coord_name) ([**const**](classCoordinate2D.md) [**Extent2D**](structExtent2D.md) & box) <br> |




























## Public Types Documentation




### enum BorderType 

```C++
enum BorderType {
    N,
    NE,
    E,
    SE,
    S,
    SW,
    W,
    NW
};
```




<hr>
## Public Functions Documentation




### function average 

```C++
template<typename T>
inline T average (
    T a,
    T b
) 
```




<hr>



### function border\_ranges 

```C++
inline Extent2D border_ranges (
    const  Extent2D & box,
    BorderType border_type,
    double border_width
) 
```




<hr>



### function convert\_geo\_keys\_to\_wkt 

```C++
inline std::string convert_geo_keys_to_wkt (
    const laspp::LASGeoKeys & geo_keys
) 
```




<hr>



### function copy\_from 

```C++
inline void copy_from (
    LASPoint & point,
    const laspp::LASPointFormat0 & data
) 
```




<hr>



### function copy\_from 

```C++
inline void copy_from (
    LASPoint & point,
    const laspp::LASPointFormat6 & data
) 
```




<hr>



### function copy\_from 

```C++
inline void copy_from (
    laspp::LASPointFormat0 & data,
    const  LASPoint & point
) 
```




<hr>



### function external\_border\_ranges 

```C++
inline Extent2D external_border_ranges (
    const  Extent2D & box,
    BorderType border_type,
    double border_width
) 
```




<hr>



### function extract\_borders 

```C++
inline void extract_borders (
    const fs::path & las_filename,
    double border_width,
    ProgressTracker progress_tracker
) 
```




<hr>



### function operator&lt;&lt; 

```C++
inline std::ostream & operator<< (
    std::ostream & os,
    BorderType border_type
) 
```




<hr>



### function round 

```C++
inline long  int round (
    double x,
    double resolution=1.0
) 
```




<hr>



### function unique\_coord\_name 

```C++
inline std::string unique_coord_name (
    const  Extent2D & box
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/lib/las/las_file.hpp`

