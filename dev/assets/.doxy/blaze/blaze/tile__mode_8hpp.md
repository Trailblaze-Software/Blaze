

# File tile\_mode.hpp



[**FileList**](files.md) **>** [**las**](dir_50e4ddd575fc604ec1609997d931fab5.md) **>** [**tile\_mode.hpp**](tile__mode_8hpp.md)

[Go to the source code of this file](tile__mode_8hpp_source.md)



* `#include <ogr_spatialref.h>`
* `#include <algorithm>`
* `#include <cmath>`
* `#include <memory>`
* `#include <optional>`
* `#include <string>`
* `#include <unordered_map>`
* `#include <vector>`
* `#include "assert/assert.hpp"`
* `#include "io/crs.hpp"`
* `#include "las/las_file.hpp"`
* `#include "printing/to_string.hpp"`
* `#include "utilities/coordinate.hpp"`
* `#include "utilities/filesystem.hpp"`
* `#include "utilities/progress_tracker.hpp"`















## Classes

| Type | Name |
| ---: | :--- |
| struct | [**LASFileExtent**](structLASFileExtent.md) <br> |
| struct | [**Tile**](structTile.md) <br> |
| struct | [**TileModeInfo**](structTileModeInfo.md) <br> |






















## Public Functions

| Type | Name |
| ---: | :--- |
|  [**TileModeInfo**](structTileModeInfo.md) | [**analyze\_extents**](#function-analyze_extents) (std::vector&lt; [**LASFileExtent**](structLASFileExtent.md) &gt; & extents, const std::string & override\_wkt="") <br> |
|  std::vector&lt; [**Tile**](structTile.md) &gt; | [**compute\_tiles**](#function-compute_tiles) (const [**Extent2D**](structExtent2D.md) & overall, double tile\_size, const std::vector&lt; [**LASFileExtent**](structLASFileExtent.md) &gt; & extents={}) <br> |
|  [**TileModeInfo**](structTileModeInfo.md) | [**detect\_tile\_mode\_needed**](#function-detect_tile_mode_needed) (const std::vector&lt; [**LASFileExtent**](structLASFileExtent.md) &gt; & extents) <br> |
|  std::vector&lt; [**LASFileExtent**](structLASFileExtent.md) &gt; | [**load\_input\_extents**](#function-load_input_extents) (const std::vector&lt; fs::path &gt; & files, const std::string & override\_crs, std::string & output\_crs\_wkt, [**ProgressTracker**](classProgressTracker.md) progress) <br> |
|  [**LASData**](classLASData.md) | [**read\_tile\_from\_inputs**](#function-read_tile_from_inputs) (const [**Extent2D**](structExtent2D.md) & tile\_extent, double border\_width, const std::vector&lt; [**LASFileExtent**](structLASFileExtent.md) &gt; & all\_extents, const std::string & output\_crs\_wkt, [**ProgressTracker**](classProgressTracker.md) progress) <br> |
|  [**Extent2D**](structExtent2D.md) | [**reproject\_extent**](#function-reproject_extent) (const [**Extent2D**](structExtent2D.md) & extent, const std::string & src\_wkt, const std::string & dst\_wkt) <br> |
|  double | [**snap\_down**](#function-snap_down) (double value, double step) <br> |
|  double | [**snap\_up**](#function-snap_up) (double value, double step) <br> |
|  std::vector&lt; [**Tile**](structTile.md) &gt; | [**tiles\_per\_file**](#function-tiles_per_file) (const std::vector&lt; [**LASFileExtent**](structLASFileExtent.md) &gt; & extents) <br> |
|  [**Extent2D**](structExtent2D.md) | [**union\_extent**](#function-union_extent) (const std::vector&lt; [**LASFileExtent**](structLASFileExtent.md) &gt; & extents) <br> |




























## Public Functions Documentation




### function analyze\_extents 

```C++
inline TileModeInfo analyze_extents (
    std::vector< LASFileExtent > & extents,
    const std::string & override_wkt=""
) 
```




<hr>



### function compute\_tiles 

```C++
inline std::vector< Tile > compute_tiles (
    const Extent2D & overall,
    double tile_size,
    const std::vector< LASFileExtent > & extents={}
) 
```




<hr>



### function detect\_tile\_mode\_needed 

```C++
inline TileModeInfo detect_tile_mode_needed (
    const std::vector< LASFileExtent > & extents
) 
```




<hr>



### function load\_input\_extents 

```C++
inline std::vector< LASFileExtent > load_input_extents (
    const std::vector< fs::path > & files,
    const std::string & override_crs,
    std::string & output_crs_wkt,
    ProgressTracker progress
) 
```




<hr>



### function read\_tile\_from\_inputs 

```C++
inline LASData read_tile_from_inputs (
    const Extent2D & tile_extent,
    double border_width,
    const std::vector< LASFileExtent > & all_extents,
    const std::string & output_crs_wkt,
    ProgressTracker progress
) 
```




<hr>



### function reproject\_extent 

```C++
inline Extent2D reproject_extent (
    const Extent2D & extent,
    const std::string & src_wkt,
    const std::string & dst_wkt
) 
```




<hr>



### function snap\_down 

```C++
inline double snap_down (
    double value,
    double step
) 
```




<hr>



### function snap\_up 

```C++
inline double snap_up (
    double value,
    double step
) 
```




<hr>



### function tiles\_per\_file 

```C++
inline std::vector< Tile > tiles_per_file (
    const std::vector< LASFileExtent > & extents
) 
```




<hr>



### function union\_extent 

```C++
inline Extent2D union_extent (
    const std::vector< LASFileExtent > & extents
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/lib/las/tile_mode.hpp`

