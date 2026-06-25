

# File vegetation\_polygon.hpp



[**FileList**](files.md) **>** [**lib**](dir_c85d3e3c5052e9ad9ce18c6863244a25.md) **>** [**vegetation**](dir_b743e47c5a2b15e05ebb68ed1bfc6ebf.md) **>** [**vegetation\_polygon.hpp**](vegetation__polygon_8hpp.md)

[Go to the source code of this file](vegetation__polygon_8hpp_source.md)



* `#include <ogrsf_frmts.h>`
* `#include <algorithm>`
* `#include <cmath>`
* `#include <limits>`
* `#include <map>`
* `#include <memory>`
* `#include <set>`
* `#include <string>`
* `#include <vector>`
* `#include "assert/assert.hpp"`
* `#include "config_input/config_input.hpp"`
* `#include "contour/contour.hpp"`
* `#include "contour/contour_gen.hpp"`
* `#include "geometry/polygon.hpp"`
* `#include "geometry/polygon_subtract.hpp"`
* `#include "grid/grid.hpp"`
* `#include "io/gdal_init.hpp"`
* `#include "io/gpkg.hpp"`
* `#include "printing/to_string.hpp"`
* `#include "utilities/coordinate.hpp"`
* `#include "utilities/filesystem.hpp"`
* `#include "utilities/progress_tracker.hpp"`
* `#include "utilities/timer.hpp"`















## Classes

| Type | Name |
| ---: | :--- |
| struct | [**VegePolygon**](structVegePolygon.md) <br> |






















## Public Functions

| Type | Name |
| ---: | :--- |
|  void | [**combine\_vege\_gpkgs**](#function-combine_vege_gpkgs) (const std::vector&lt; fs::path &gt; & tile\_dirs, const fs::path & combined\_dir, const std::string & projection, [**ProgressTracker**](classProgressTracker.md) progress\_tracker=[**ProgressTracker**](classProgressTracker.md)()) <br> |
|  std::vector&lt; [**VegePolygon**](structVegePolygon.md) &gt; | [**contours\_to\_polygons**](#function-contours_to_polygons) (const std::map&lt; double, std::vector&lt; [**Contour**](classContour.md) &gt; &gt; & contours\_by\_height, const std::map&lt; double, std::string &gt; & height\_to\_layer) <br> |
|  std::map&lt; double, std::string &gt; | [**extract\_threshold\_layers**](#function-extract_threshold_layers) (const [**VegeHeightConfig**](structVegeHeightConfig.md) & config) <br> |
|  void | [**filter\_by\_min\_area**](#function-filter_by_min_area) (std::vector&lt; [**VegePolygon**](structVegePolygon.md) &gt; & polygons, const std::map&lt; std::string, double &gt; & min\_areas) <br> |
|  void | [**filter\_small\_holes**](#function-filter_small_holes) (std::vector&lt; [**VegePolygon**](structVegePolygon.md) &gt; & polygons, const std::map&lt; std::string, double &gt; & min\_hole\_areas) <br> |
|  std::vector&lt; [**VegePolygon**](structVegePolygon.md) &gt; | [**generate\_vege\_polygons**](#function-generate_vege_polygons) (const [**VegeConfig**](structVegeConfig.md) & vege\_config, const std::map&lt; std::string, [**GeoGrid**](classGeo.md)&lt; float &gt; &gt; & vege\_maps, [**ProgressTracker**](classProgressTracker.md) && progress\_tracker=[**ProgressTracker**](classProgressTracker.md)()) <br> |
|  std::string | [**layer\_number**](#function-layer_number) (const std::string & layer) <br> |
|  double | [**polygon\_net\_area\_m2**](#function-polygon_net_area_m2) (const [**VegePolygon**](structVegePolygon.md) & poly) <br> |
|  std::vector&lt; [**VegePolygon**](structVegePolygon.md) &gt; | [**read\_vege\_polygons**](#function-read_vege_polygons) (const fs::path & gpkg\_path) <br> |
|  std::vector&lt; [**VegePolygon**](structVegePolygon.md) &gt; | [**subtract\_from\_polygon**](#function-subtract_from_polygon) (const [**VegePolygon**](structVegePolygon.md) & host, const std::vector&lt; [**VegePolygon**](structVegePolygon.md) &gt; & cutouts) <br> |
|  std::vector&lt; [**VegePolygon**](structVegePolygon.md) &gt; | [**subtract\_from\_polygon**](#function-subtract_from_polygon) (const [**VegePolygon**](structVegePolygon.md) & host, const OGRGeometry \* cut\_union) <br> |
|  std::string | [**threshold\_layer\_name**](#function-threshold_layer_name) (const [**VegeHeightConfig**](structVegeHeightConfig.md) & config, const [**BlockingThresholdColorPair**](structBlockingThresholdColorPair.md) & btc) <br> |
|  void | [**trim\_vege\_polygons\_to\_extent**](#function-trim_vege_polygons_to_extent) (std::vector&lt; [**VegePolygon**](structVegePolygon.md) &gt; & polygons, const [**Extent2D**](structExtent2D.md) & bounds, const std::vector&lt; [**Extent2D**](structExtent2D.md) &gt; & snap\_extents={}, double snap\_tolerance=0.01, [**ProgressTracker**](classProgressTracker.md) && progress\_tracker=[**ProgressTracker**](classProgressTracker.md)()) <br> |
|  void | [**write\_vege\_polygons\_gpkg**](#function-write_vege_polygons_gpkg) (const std::vector&lt; [**VegePolygon**](structVegePolygon.md) &gt; & polygons, const fs::path & gpkg\_path, const std::string & projection, [**ProgressTracker**](classProgressTracker.md) && progress\_tracker=[**ProgressTracker**](classProgressTracker.md)()) <br> |




























## Public Functions Documentation




### function combine\_vege\_gpkgs 

```C++
inline void combine_vege_gpkgs (
    const std::vector< fs::path > & tile_dirs,
    const fs::path & combined_dir,
    const std::string & projection,
    ProgressTracker progress_tracker=ProgressTracker ()
) 
```




<hr>



### function contours\_to\_polygons 

```C++
inline std::vector< VegePolygon > contours_to_polygons (
    const std::map< double, std::vector< Contour > > & contours_by_height,
    const std::map< double, std::string > & height_to_layer
) 
```




<hr>



### function extract\_threshold\_layers 

```C++
inline std::map< double, std::string > extract_threshold_layers (
    const VegeHeightConfig & config
) 
```




<hr>



### function filter\_by\_min\_area 

```C++
inline void filter_by_min_area (
    std::vector< VegePolygon > & polygons,
    const std::map< std::string, double > & min_areas
) 
```




<hr>



### function filter\_small\_holes 

```C++
inline void filter_small_holes (
    std::vector< VegePolygon > & polygons,
    const std::map< std::string, double > & min_hole_areas
) 
```




<hr>



### function generate\_vege\_polygons 

```C++
inline std::vector< VegePolygon > generate_vege_polygons (
    const VegeConfig & vege_config,
    const std::map< std::string, GeoGrid < float > > & vege_maps,
    ProgressTracker && progress_tracker=ProgressTracker ()
) 
```




<hr>



### function layer\_number 

```C++
inline std::string layer_number (
    const std::string & layer
) 
```




<hr>



### function polygon\_net\_area\_m2 

```C++
inline double polygon_net_area_m2 (
    const VegePolygon & poly
) 
```




<hr>



### function read\_vege\_polygons 

```C++
inline std::vector< VegePolygon > read_vege_polygons (
    const fs::path & gpkg_path
) 
```




<hr>



### function subtract\_from\_polygon 

```C++
inline std::vector< VegePolygon > subtract_from_polygon (
    const VegePolygon & host,
    const std::vector< VegePolygon > & cutouts
) 
```




<hr>



### function subtract\_from\_polygon 

```C++
inline std::vector< VegePolygon > subtract_from_polygon (
    const VegePolygon & host,
    const OGRGeometry * cut_union
) 
```




<hr>



### function threshold\_layer\_name 

```C++
inline std::string threshold_layer_name (
    const VegeHeightConfig & config,
    const BlockingThresholdColorPair & btc
) 
```




<hr>



### function trim\_vege\_polygons\_to\_extent 

```C++
inline void trim_vege_polygons_to_extent (
    std::vector< VegePolygon > & polygons,
    const Extent2D & bounds,
    const std::vector< Extent2D > & snap_extents={},
    double snap_tolerance=0.01,
    ProgressTracker && progress_tracker=ProgressTracker ()
) 
```




<hr>



### function write\_vege\_polygons\_gpkg 

```C++
inline void write_vege_polygons_gpkg (
    const std::vector< VegePolygon > & polygons,
    const fs::path & gpkg_path,
    const std::string & projection,
    ProgressTracker && progress_tracker=ProgressTracker ()
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/lib/vegetation/vegetation_polygon.hpp`

