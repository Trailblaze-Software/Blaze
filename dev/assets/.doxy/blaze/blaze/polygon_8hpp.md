

# File polygon.hpp



[**FileList**](files.md) **>** [**geometry**](dir_da4e387dad6145fce42efe284fbecf2d.md) **>** [**polygon.hpp**](polygon_8hpp.md)

[Go to the source code of this file](polygon_8hpp_source.md)



* `#include <cmath>`
* `#include <optional>`
* `#include <vector>`
* `#include "assert/assert.hpp"`
* `#include "utilities/coordinate.hpp"`















## Classes

| Type | Name |
| ---: | :--- |
| struct | [**PolygonWithHoles**](structPolygonWithHoles.md) <br> |






















## Public Functions

| Type | Name |
| ---: | :--- |
|  std::vector&lt; [**PolygonWithHoles**](structPolygonWithHoles.md) &gt; | [**clip\_polygon\_hole\_free\_to\_extent**](#function-clip_polygon_hole_free_to_extent) ([**const**](classCoordinate2D.md) [**PolygonWithHoles**](structPolygonWithHoles.md) & poly, [**const**](classCoordinate2D.md) [**Extent2D**](structExtent2D.md) & bounds) <br> |
|  [**bool**](classCoordinate2D.md) | [**extent\_contains**](#function-extent_contains) ([**const**](classCoordinate2D.md) [**Extent2D**](structExtent2D.md) & outer, [**const**](classCoordinate2D.md) [**Extent2D**](structExtent2D.md) & inner) <br> |
|  std::vector&lt; [**Coordinate2D**](classCoordinate2D.md)&lt; [**double**](classCoordinate2D.md) &gt; &gt; | [**intersect\_polygons**](#function-intersect_polygons) ([**const**](classCoordinate2D.md) std::vector&lt; [**Coordinate2D**](classCoordinate2D.md)&lt; [**double**](classCoordinate2D.md) &gt; &gt; & subject, [**const**](classCoordinate2D.md) std::vector&lt; [**Coordinate2D**](classCoordinate2D.md)&lt; [**double**](classCoordinate2D.md) &gt; &gt; & clip) <br> |
|  [**bool**](classCoordinate2D.md) | [**is\_left\_of**](#function-is_left_of) ([**const**](classCoordinate2D.md) [**Coordinate2D**](classCoordinate2D.md)&lt; [**double**](classCoordinate2D.md) &gt; & from, [**const**](classCoordinate2D.md) [**Coordinate2D**](classCoordinate2D.md)&lt; [**double**](classCoordinate2D.md) &gt; & to, [**const**](classCoordinate2D.md) [**Coordinate2D**](classCoordinate2D.md)&lt; [**double**](classCoordinate2D.md) &gt; & point) <br> |
|  [**void**](classCoordinate2D.md) | [**normalize\_polygon**](#function-normalize_polygon) ([**PolygonWithHoles**](structPolygonWithHoles.md) & poly) <br> |
|  [**bool**](classCoordinate2D.md) | [**point\_in\_ring**](#function-point_in_ring) ([**const**](classCoordinate2D.md) [**Coordinate2D**](classCoordinate2D.md)&lt; [**double**](classCoordinate2D.md) &gt; & point, [**const**](classCoordinate2D.md) std::vector&lt; [**Coordinate2D**](classCoordinate2D.md)&lt; [**double**](classCoordinate2D.md) &gt; &gt; & ring) <br> |
|  [**PolygonWithHoles**](structPolygonWithHoles.md) | [**polygon\_from\_extent**](#function-polygon_from_extent) ([**const**](classCoordinate2D.md) [**Extent2D**](structExtent2D.md) & extent) <br> |
|  std::vector&lt; [**Coordinate2D**](classCoordinate2D.md)&lt; [**double**](classCoordinate2D.md) &gt; &gt; | [**reverse\_ring**](#function-reverse_ring) ([**const**](classCoordinate2D.md) std::vector&lt; [**Coordinate2D**](classCoordinate2D.md)&lt; [**double**](classCoordinate2D.md) &gt; &gt; & ring) <br> |
|  [**Extent2D**](structExtent2D.md) | [**ring\_extent**](#function-ring_extent) ([**const**](classCoordinate2D.md) std::vector&lt; [**Coordinate2D**](classCoordinate2D.md)&lt; [**double**](classCoordinate2D.md) &gt; &gt; & ring) <br> |
|  [**bool**](classCoordinate2D.md) | [**segment\_intersection**](#function-segment_intersection) ([**const**](classCoordinate2D.md) [**Coordinate2D**](classCoordinate2D.md)&lt; [**double**](classCoordinate2D.md) &gt; & a1, [**const**](classCoordinate2D.md) [**Coordinate2D**](classCoordinate2D.md)&lt; [**double**](classCoordinate2D.md) &gt; & a2, [**const**](classCoordinate2D.md) [**Coordinate2D**](classCoordinate2D.md)&lt; [**double**](classCoordinate2D.md) &gt; & b1, [**const**](classCoordinate2D.md) [**Coordinate2D**](classCoordinate2D.md)&lt; [**double**](classCoordinate2D.md) &gt; & b2, [**Coordinate2D**](classCoordinate2D.md)&lt; [**double**](classCoordinate2D.md) &gt; & out) <br> |
|  [**double**](classCoordinate2D.md) | [**signed\_area**](#function-signed_area) ([**const**](classCoordinate2D.md) std::vector&lt; [**Coordinate2D**](classCoordinate2D.md)&lt; [**double**](classCoordinate2D.md) &gt; &gt; & ring) <br> |




























## Public Functions Documentation




### function clip\_polygon\_hole\_free\_to\_extent 

```C++
inline std::vector< PolygonWithHoles > clip_polygon_hole_free_to_extent (
    const  PolygonWithHoles & poly,
    const  Extent2D & bounds
) 
```




<hr>



### function extent\_contains 

```C++
inline bool extent_contains (
    const  Extent2D & outer,
    const  Extent2D & inner
) 
```




<hr>



### function intersect\_polygons 

```C++
inline std::vector< Coordinate2D < double > > intersect_polygons (
    const std::vector< Coordinate2D < double > > & subject,
    const std::vector< Coordinate2D < double > > & clip
) 
```




<hr>



### function is\_left\_of 

```C++
inline bool is_left_of (
    const  Coordinate2D < double > & from,
    const  Coordinate2D < double > & to,
    const  Coordinate2D < double > & point
) 
```




<hr>



### function normalize\_polygon 

```C++
inline void normalize_polygon (
    PolygonWithHoles & poly
) 
```




<hr>



### function point\_in\_ring 

```C++
inline bool point_in_ring (
    const  Coordinate2D < double > & point,
    const std::vector< Coordinate2D < double > > & ring
) 
```




<hr>



### function polygon\_from\_extent 

```C++
inline PolygonWithHoles polygon_from_extent (
    const  Extent2D & extent
) 
```




<hr>



### function reverse\_ring 

```C++
inline std::vector< Coordinate2D < double > > reverse_ring (
    const std::vector< Coordinate2D < double > > & ring
) 
```




<hr>



### function ring\_extent 

```C++
inline Extent2D ring_extent (
    const std::vector< Coordinate2D < double > > & ring
) 
```




<hr>



### function segment\_intersection 

```C++
inline bool segment_intersection (
    const  Coordinate2D < double > & a1,
    const  Coordinate2D < double > & a2,
    const  Coordinate2D < double > & b1,
    const  Coordinate2D < double > & b2,
    Coordinate2D < double > & out
) 
```




<hr>



### function signed\_area 

```C++
inline double signed_area (
    const std::vector< Coordinate2D < double > > & ring
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/lib/geometry/polygon.hpp`

