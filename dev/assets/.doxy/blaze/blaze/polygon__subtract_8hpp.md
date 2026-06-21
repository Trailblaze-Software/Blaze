

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
|  std::vector&lt; [**PolygonWithHoles**](structPolygonWithHoles.md) &gt; | [**clip\_polygon\_to\_extent**](#function-clip_polygon_to_extent) ([**const**](classCoordinate2D.md) [**PolygonWithHoles**](structPolygonWithHoles.md) & poly, [**const**](classCoordinate2D.md) [**Extent2D**](structExtent2D.md) & bounds) <br> |
|  std::vector&lt; [**PolygonWithHoles**](structPolygonWithHoles.md) &gt; | [**intersect\_polygon**](#function-intersect_polygon) ([**const**](classCoordinate2D.md) [**PolygonWithHoles**](structPolygonWithHoles.md) & host, [**const**](classCoordinate2D.md) [**PolygonWithHoles**](structPolygonWithHoles.md) & clip) <br> |
|  std::vector&lt; [**PolygonWithHoles**](structPolygonWithHoles.md) &gt; | [**subtract\_polygon**](#function-subtract_polygon) ([**const**](classCoordinate2D.md) [**PolygonWithHoles**](structPolygonWithHoles.md) & host, [**const**](classCoordinate2D.md) std::vector&lt; [**PolygonWithHoles**](structPolygonWithHoles.md) &gt; & cutouts) <br> |
|  std::vector&lt; [**PolygonWithHoles**](structPolygonWithHoles.md) &gt; | [**subtract\_polygon\_with\_union**](#function-subtract_polygon_with_union) ([**const**](classCoordinate2D.md) [**PolygonWithHoles**](structPolygonWithHoles.md) & host, [**const**](classCoordinate2D.md) [**OGRGeometry**](classCoordinate2D.md) \* cut\_union) <br> |
|  std::vector&lt; [**PolygonWithHoles**](structPolygonWithHoles.md) &gt; | [**union\_overlapping\_polygons**](#function-union_overlapping_polygons) ([**const**](classCoordinate2D.md) std::vector&lt; [**PolygonWithHoles**](structPolygonWithHoles.md) &gt; & polygons) <br> |




























## Public Functions Documentation




### function clip\_polygon\_to\_extent 

```C++
inline std::vector< PolygonWithHoles > clip_polygon_to_extent (
    const  PolygonWithHoles & poly,
    const  Extent2D & bounds
) 
```




<hr>



### function intersect\_polygon 

```C++
inline std::vector< PolygonWithHoles > intersect_polygon (
    const  PolygonWithHoles & host,
    const  PolygonWithHoles & clip
) 
```




<hr>



### function subtract\_polygon 

```C++
inline std::vector< PolygonWithHoles > subtract_polygon (
    const  PolygonWithHoles & host,
    const std::vector< PolygonWithHoles > & cutouts
) 
```




<hr>



### function subtract\_polygon\_with\_union 

```C++
inline std::vector< PolygonWithHoles > subtract_polygon_with_union (
    const  PolygonWithHoles & host,
    const  OGRGeometry * cut_union
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

