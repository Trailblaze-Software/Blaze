

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
|  std::vector&lt; [**PolygonWithHoles**](structPolygonWithHoles.md) &gt; | [**clip\_polygon\_hole\_free\_to\_extent**](#function-clip_polygon_hole_free_to_extent) (const [**PolygonWithHoles**](structPolygonWithHoles.md) & poly, const [**Extent2D**](structExtent2D.md) & bounds) <br> |
|  void | [**dedupe\_consecutive\_ring\_vertices**](#function-dedupe_consecutive_ring_vertices) (std::vector&lt; [**Coordinate2D**](classCoordinate2D.md)&lt; double &gt; &gt; & ring, double tolerance=1e-9) <br> |
|  bool | [**extent\_contains**](#function-extent_contains) (const [**Extent2D**](structExtent2D.md) & outer, const [**Extent2D**](structExtent2D.md) & inner) <br> |
|  std::vector&lt; [**Coordinate2D**](classCoordinate2D.md)&lt; double &gt; &gt; | [**intersect\_polygons**](#function-intersect_polygons) (const std::vector&lt; [**Coordinate2D**](classCoordinate2D.md)&lt; double &gt; &gt; & subject, const std::vector&lt; [**Coordinate2D**](classCoordinate2D.md)&lt; double &gt; &gt; & clip) <br> |
|  bool | [**is\_left\_of**](#function-is_left_of) (const [**Coordinate2D**](classCoordinate2D.md)&lt; double &gt; & from, const [**Coordinate2D**](classCoordinate2D.md)&lt; double &gt; & to, const [**Coordinate2D**](classCoordinate2D.md)&lt; double &gt; & point) <br> |
|  void | [**normalize\_polygon**](#function-normalize_polygon) ([**PolygonWithHoles**](structPolygonWithHoles.md) & poly) <br> |
|  bool | [**point\_in\_polygon\_with\_holes**](#function-point_in_polygon_with_holes) (const [**Coordinate2D**](classCoordinate2D.md)&lt; double &gt; & point, const [**PolygonWithHoles**](structPolygonWithHoles.md) & poly) <br> |
|  bool | [**point\_in\_ring**](#function-point_in_ring) (const [**Coordinate2D**](classCoordinate2D.md)&lt; double &gt; & point, const std::vector&lt; [**Coordinate2D**](classCoordinate2D.md)&lt; double &gt; &gt; & ring) <br> |
|  [**PolygonWithHoles**](structPolygonWithHoles.md) | [**polygon\_from\_extent**](#function-polygon_from_extent) (const [**Extent2D**](structExtent2D.md) & extent) <br> |
|  std::vector&lt; [**Coordinate2D**](classCoordinate2D.md)&lt; double &gt; &gt; | [**reverse\_ring**](#function-reverse_ring) (const std::vector&lt; [**Coordinate2D**](classCoordinate2D.md)&lt; double &gt; &gt; & ring) <br> |
|  [**Extent2D**](structExtent2D.md) | [**ring\_extent**](#function-ring_extent) (const std::vector&lt; [**Coordinate2D**](classCoordinate2D.md)&lt; double &gt; &gt; & ring) <br> |
|  bool | [**segment\_intersection**](#function-segment_intersection) (const [**Coordinate2D**](classCoordinate2D.md)&lt; double &gt; & a1, const [**Coordinate2D**](classCoordinate2D.md)&lt; double &gt; & a2, const [**Coordinate2D**](classCoordinate2D.md)&lt; double &gt; & b1, const [**Coordinate2D**](classCoordinate2D.md)&lt; double &gt; & b2, [**Coordinate2D**](classCoordinate2D.md)&lt; double &gt; & out) <br> |
|  double | [**signed\_area**](#function-signed_area) (const std::vector&lt; [**Coordinate2D**](classCoordinate2D.md)&lt; double &gt; &gt; & ring) <br> |
|  void | [**snap\_polygon\_to\_extents**](#function-snap_polygon_to_extents) ([**PolygonWithHoles**](structPolygonWithHoles.md) & poly, const std::vector&lt; [**Extent2D**](structExtent2D.md) &gt; & extents, double tolerance) <br> |
|  void | [**snap\_ring\_to\_extent**](#function-snap_ring_to_extent) (std::vector&lt; [**Coordinate2D**](classCoordinate2D.md)&lt; double &gt; &gt; & ring, const [**Extent2D**](structExtent2D.md) & extent, double tolerance) <br> |




























## Public Functions Documentation




### function clip\_polygon\_hole\_free\_to\_extent 

```C++
inline std::vector< PolygonWithHoles > clip_polygon_hole_free_to_extent (
    const PolygonWithHoles & poly,
    const Extent2D & bounds
) 
```




<hr>



### function dedupe\_consecutive\_ring\_vertices 

```C++
inline void dedupe_consecutive_ring_vertices (
    std::vector< Coordinate2D < double > > & ring,
    double tolerance=1e-9
) 
```




<hr>



### function extent\_contains 

```C++
inline bool extent_contains (
    const Extent2D & outer,
    const Extent2D & inner
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
    const Coordinate2D < double > & from,
    const Coordinate2D < double > & to,
    const Coordinate2D < double > & point
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



### function point\_in\_polygon\_with\_holes 

```C++
inline bool point_in_polygon_with_holes (
    const Coordinate2D < double > & point,
    const PolygonWithHoles & poly
) 
```




<hr>



### function point\_in\_ring 

```C++
inline bool point_in_ring (
    const Coordinate2D < double > & point,
    const std::vector< Coordinate2D < double > > & ring
) 
```




<hr>



### function polygon\_from\_extent 

```C++
inline PolygonWithHoles polygon_from_extent (
    const Extent2D & extent
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
    const Coordinate2D < double > & a1,
    const Coordinate2D < double > & a2,
    const Coordinate2D < double > & b1,
    const Coordinate2D < double > & b2,
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



### function snap\_polygon\_to\_extents 

```C++
inline void snap_polygon_to_extents (
    PolygonWithHoles & poly,
    const std::vector< Extent2D > & extents,
    double tolerance
) 
```




<hr>



### function snap\_ring\_to\_extent 

```C++
inline void snap_ring_to_extent (
    std::vector< Coordinate2D < double > > & ring,
    const Extent2D & extent,
    double tolerance
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/lib/geometry/polygon.hpp`

