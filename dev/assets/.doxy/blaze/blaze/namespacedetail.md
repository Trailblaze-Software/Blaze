

# Namespace detail



[**Namespace List**](namespaces.md) **>** [**detail**](namespacedetail.md)




















## Classes

| Type | Name |
| ---: | :--- |
| class | [**ExtentSpatialIndex**](classdetail_1_1ExtentSpatialIndex.md) <br> |






















## Public Functions

| Type | Name |
| ---: | :--- |
|  [**void**](classCoordinate2D.md) | [**append\_ogr\_polygons**](#function-append_ogr_polygons) ([**const**](classCoordinate2D.md) [**OGRGeometry**](classCoordinate2D.md) \* geometry, std::vector&lt; std::unique\_ptr&lt; [**OGRGeometry**](classCoordinate2D.md) &gt; &gt; & out) <br> |
|  [**void**](classCoordinate2D.md) | [**append\_polygons\_from\_ogr**](#function-append_polygons_from_ogr) ([**const**](classCoordinate2D.md) [**OGRGeometry**](classCoordinate2D.md) \* geometry, std::vector&lt; [**PolygonWithHoles**](structPolygonWithHoles.md) &gt; & out) <br> |
|  std::unique\_ptr&lt; [**OGRGeometry**](classCoordinate2D.md) &gt; | [**build\_cutout\_union**](#function-build_cutout_union) ([**const**](classCoordinate2D.md) std::vector&lt; [**PolygonWithHoles**](structPolygonWithHoles.md) &gt; & cutouts) <br> |
|  [**void**](classCoordinate2D.md) | [**fill\_ogr\_ring**](#function-fill_ogr_ring) ([**OGRLinearRing**](classCoordinate2D.md) & ring, [**const**](classCoordinate2D.md) std::vector&lt; [**Coordinate2D**](classCoordinate2D.md)&lt; [**double**](classCoordinate2D.md) &gt; &gt; & vertices) <br> |
|  [**GridGraph**](classGridGraph.md)&lt; std::set&lt; [**double**](classCoordinate2D.md) &gt; &gt; | [**identify\_contour\_crossings**](#function-identify_contour_crossings) ([**const**](classCoordinate2D.md) [**GeoGrid**](classGeo.md)&lt; T &gt; & grid, [**EdgeHeightsFn**](classCoordinate2D.md) edge\_heights) <br> |
|  [**double**](classCoordinate2D.md) | [**min\_contour\_loop\_area\_m2**](#function-min_contour_loop_area_m2) ([**const**](classCoordinate2D.md) [**GeoGrid**](classGeo.md)&lt; T &gt; & grid) <br> |
|  [**PolygonWithHoles**](structPolygonWithHoles.md) | [**polygon\_from\_ogr**](#function-polygon_from_ogr) ([**const**](classCoordinate2D.md) [**OGRPolygon**](classCoordinate2D.md) \* ogr\_poly) <br> |
|  std::unique\_ptr&lt; [**OGRGeometry**](classCoordinate2D.md) &gt; | [**polygon\_to\_ogr**](#function-polygon_to_ogr) ([**const**](classCoordinate2D.md) [**PolygonWithHoles**](structPolygonWithHoles.md) & poly) <br> |
|  std::unique\_ptr&lt; [**OGRGeometry**](classCoordinate2D.md) &gt; | [**ring\_to\_ogr**](#function-ring_to_ogr) ([**const**](classCoordinate2D.md) std::vector&lt; [**Coordinate2D**](classCoordinate2D.md)&lt; [**double**](classCoordinate2D.md) &gt; &gt; & exterior\_ring) <br> |
|  [**void**](classCoordinate2D.md) | [**trace\_contours**](#function-trace_contours) ([**const**](classCoordinate2D.md) [**GeoGrid**](classGeo.md)&lt; T &gt; & grid, [**GridGraph**](classGridGraph.md)&lt; std::set&lt; [**double**](classCoordinate2D.md) &gt; &gt; & contour\_heights, [**AcceptFn**](classCoordinate2D.md) accept, [**EmitFn**](classCoordinate2D.md) emit) <br> |
|  [**const**](classCoordinate2D.md) [**GeoGrid**](classGeo.md)&lt; T &gt; & | [**work\_grid\_for\_contours**](#function-work_grid_for_contours) ([**const**](classCoordinate2D.md) [**GeoGrid**](classGeo.md)&lt; T &gt; & grid, std::optional&lt; T &gt; pad\_value, std::optional&lt; [**GeoGrid**](classGeo.md)&lt; T &gt; &gt; & padded\_out) <br> |




























## Public Functions Documentation




### function append\_ogr\_polygons 

```C++
inline void detail::append_ogr_polygons (
    const  OGRGeometry * geometry,
    std::vector< std::unique_ptr< OGRGeometry > > & out
) 
```




<hr>



### function append\_polygons\_from\_ogr 

```C++
inline void detail::append_polygons_from_ogr (
    const  OGRGeometry * geometry,
    std::vector< PolygonWithHoles > & out
) 
```




<hr>



### function build\_cutout\_union 

```C++
inline std::unique_ptr< OGRGeometry > detail::build_cutout_union (
    const std::vector< PolygonWithHoles > & cutouts
) 
```




<hr>



### function fill\_ogr\_ring 

```C++
inline void detail::fill_ogr_ring (
    OGRLinearRing & ring,
    const std::vector< Coordinate2D < double > > & vertices
) 
```




<hr>



### function identify\_contour\_crossings 

```C++
template<typename T, typename  EdgeHeightsFn>
GridGraph < std::set< double > > detail::identify_contour_crossings (
    const  GeoGrid < T > & grid,
    EdgeHeightsFn edge_heights
) 
```




<hr>



### function min\_contour\_loop\_area\_m2 

```C++
template<typename T>
double detail::min_contour_loop_area_m2 (
    const  GeoGrid < T > & grid
) 
```




<hr>



### function polygon\_from\_ogr 

```C++
inline PolygonWithHoles detail::polygon_from_ogr (
    const  OGRPolygon * ogr_poly
) 
```




<hr>



### function polygon\_to\_ogr 

```C++
inline std::unique_ptr< OGRGeometry > detail::polygon_to_ogr (
    const  PolygonWithHoles & poly
) 
```




<hr>



### function ring\_to\_ogr 

```C++
inline std::unique_ptr< OGRGeometry > detail::ring_to_ogr (
    const std::vector< Coordinate2D < double > > & exterior_ring
) 
```




<hr>



### function trace\_contours 

```C++
template<typename T, typename  AcceptFn, typename  EmitFn>
void detail::trace_contours (
    const  GeoGrid < T > & grid,
    GridGraph < std::set< double > > & contour_heights,
    AcceptFn accept,
    EmitFn emit
) 
```




<hr>



### function work\_grid\_for\_contours 

```C++
template<typename T>
const  GeoGrid < T > & detail::work_grid_for_contours (
    const  GeoGrid < T > & grid,
    std::optional< T > pad_value,
    std::optional< GeoGrid < T > > & padded_out
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/lib/contour/contour_gen.hpp`

