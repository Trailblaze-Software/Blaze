

# File polygon\_subtract.hpp



[**FileList**](files.md) **>** [**geometry**](dir_da4e387dad6145fce42efe284fbecf2d.md) **>** [**polygon\_subtract.hpp**](polygon__subtract_8hpp.md)

[Go to the source code of this file](polygon__subtract_8hpp_source.md)



* `#include <ogrsf_frmts.h>`
* `#include <algorithm>`
* `#include <cmath>`
* `#include <memory>`
* `#include <unordered_map>`
* `#include <vector>`
* `#include "geometry/polygon.hpp"`
* `#include "io/gdal_init.hpp"`













## Namespaces

| Type | Name |
| ---: | :--- |
| namespace | [**detail**](namespacedetail.md) <br> |


## Classes

| Type | Name |
| ---: | :--- |
| class | [**ExtentSpatialIndex**](classdetail_1_1ExtentSpatialIndex.md) <br> |






















## Public Functions

| Type | Name |
| ---: | :--- |
|  std::vector&lt; [**PolygonWithHoles**](structPolygonWithHoles.md) &gt; | [**clip\_polygon\_to\_extent**](#function-clip_polygon_to_extent) (const [**PolygonWithHoles**](structPolygonWithHoles.md) & poly, const [**Extent2D**](structExtent2D.md) & bounds) <br> |
|  std::vector&lt; [**PolygonWithHoles**](structPolygonWithHoles.md) &gt; | [**finalize\_polygon\_with\_holes**](#function-finalize_polygon_with_holes) ([**PolygonWithHoles**](structPolygonWithHoles.md) poly, const std::vector&lt; [**Extent2D**](structExtent2D.md) &gt; & snap\_extents={}, double snap\_tolerance=0.01) <br> |
|  std::vector&lt; [**PolygonWithHoles**](structPolygonWithHoles.md) &gt; | [**intersect\_polygon**](#function-intersect_polygon) (const [**PolygonWithHoles**](structPolygonWithHoles.md) & host, const [**PolygonWithHoles**](structPolygonWithHoles.md) & clip) <br> |
|  std::vector&lt; [**PolygonWithHoles**](structPolygonWithHoles.md) &gt; | [**subtract\_polygon**](#function-subtract_polygon) (const [**PolygonWithHoles**](structPolygonWithHoles.md) & host, const std::vector&lt; [**PolygonWithHoles**](structPolygonWithHoles.md) &gt; & cutouts) <br> |
|  std::vector&lt; [**PolygonWithHoles**](structPolygonWithHoles.md) &gt; | [**subtract\_polygon\_with\_union**](#function-subtract_polygon_with_union) (const [**PolygonWithHoles**](structPolygonWithHoles.md) & host, const OGRGeometry \* cut\_union) <br> |
|  std::vector&lt; [**PolygonWithHoles**](structPolygonWithHoles.md) &gt; | [**union\_overlapping\_polygons**](#function-union_overlapping_polygons) (const std::vector&lt; [**PolygonWithHoles**](structPolygonWithHoles.md) &gt; & polygons) <br> |




























## Public Functions Documentation




### function clip\_polygon\_to\_extent 

```C++
inline std::vector< PolygonWithHoles > clip_polygon_to_extent (
    const PolygonWithHoles & poly,
    const Extent2D & bounds
) 
```




<hr>



### function finalize\_polygon\_with\_holes 

```C++
inline std::vector< PolygonWithHoles > finalize_polygon_with_holes (
    PolygonWithHoles poly,
    const std::vector< Extent2D > & snap_extents={},
    double snap_tolerance=0.01
) 
```




<hr>



### function intersect\_polygon 

```C++
inline std::vector< PolygonWithHoles > intersect_polygon (
    const PolygonWithHoles & host,
    const PolygonWithHoles & clip
) 
```




<hr>



### function subtract\_polygon 

```C++
inline std::vector< PolygonWithHoles > subtract_polygon (
    const PolygonWithHoles & host,
    const std::vector< PolygonWithHoles > & cutouts
) 
```




<hr>



### function subtract\_polygon\_with\_union 

```C++
inline std::vector< PolygonWithHoles > subtract_polygon_with_union (
    const PolygonWithHoles & host,
    const OGRGeometry * cut_union
) 
```




<hr>



### function union\_overlapping\_polygons 

```C++
inline std::vector< PolygonWithHoles > union_overlapping_polygons (
    const std::vector< PolygonWithHoles > & polygons
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/lib/geometry/polygon_subtract.hpp`

