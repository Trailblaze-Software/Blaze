

# Namespace detail



[**Namespace List**](namespaces.md) **>** [**detail**](namespacedetail.md)




















## Classes

| Type | Name |
| ---: | :--- |
| class | [**ExtentSpatialIndex**](classdetail_1_1ExtentSpatialIndex.md) <br> |






















## Public Functions

| Type | Name |
| ---: | :--- |
|  void | [**append\_ogr\_polygons**](#function-append_ogr_polygons) (const OGRGeometry \* geometry, std::vector&lt; std::unique\_ptr&lt; OGRGeometry &gt; &gt; & out) <br> |
|  void | [**append\_polygons\_from\_ogr**](#function-append_polygons_from_ogr) (const OGRGeometry \* geometry, std::vector&lt; [**PolygonWithHoles**](structPolygonWithHoles.md) &gt; & out) <br> |
|  int | [**blaze\_output\_score**](#function-blaze_output_score) (const [**BlazeOutputSet**](structBlazeOutputSet.md) & outputs) <br> |
|  std::unique\_ptr&lt; OGRGeometry &gt; | [**build\_cutout\_union**](#function-build_cutout_union) (const std::vector&lt; [**PolygonWithHoles**](structPolygonWithHoles.md) &gt; & cutouts) <br> |
|  void | [**collect\_locations\_with\_outputs**](#function-collect_locations_with_outputs) (const fs::path & directory, std::vector&lt; fs::path &gt; & locations) <br> |
|  void | [**collect\_search\_roots**](#function-collect_search_roots) (const fs::path & directory, std::vector&lt; fs::path &gt; & roots) <br> |
|  [**BlazeOutputSet**](structBlazeOutputSet.md) | [**discover\_in\_root**](#function-discover_in_root) (const fs::path & root) <br> |
|  void | [**fill\_ogr\_ring**](#function-fill_ogr_ring) (OGRLinearRing & ring, const std::vector&lt; [**Coordinate2D**](classCoordinate2D.md)&lt; double &gt; &gt; & vertices) <br> |
|  std::optional&lt; fs::path &gt; | [**find\_in\_root**](#function-find_in_root) (const fs::path & root, const std::vector&lt; std::string &gt; & names) <br> |
|  bool | [**has\_importable\_outputs**](#function-has_importable_outputs) (const [**BlazeOutputSet**](structBlazeOutputSet.md) & outputs) <br> |
|  [**GridGraph**](classGridGraph.md)&lt; std::set&lt; double &gt; &gt; | [**identify\_contour\_crossings**](#function-identify_contour_crossings) (const [**GeoGrid**](classGeo.md)&lt; T &gt; & grid, EdgeHeightsFn edge\_heights) <br> |
|  bool | [**is\_blaze\_output\_filename**](#function-is_blaze_output_filename) (const std::string & name) <br> |
|  bool | [**is\_combined\_root**](#function-is_combined_root) (const fs::path & root) <br> |
|  double | [**min\_contour\_loop\_area\_m2**](#function-min_contour_loop_area_m2) (const [**GeoGrid**](classGeo.md)&lt; T &gt; & grid) <br> |
|  [**PolygonWithHoles**](structPolygonWithHoles.md) | [**polygon\_from\_ogr**](#function-polygon_from_ogr) (const OGRPolygon \* ogr\_poly) <br> |
|  std::unique\_ptr&lt; OGRGeometry &gt; | [**polygon\_to\_ogr**](#function-polygon_to_ogr) (const [**PolygonWithHoles**](structPolygonWithHoles.md) & poly) <br> |
|  std::unique\_ptr&lt; OGRGeometry &gt; | [**repair\_ogr\_geometry**](#function-repair_ogr_geometry) (std::unique\_ptr&lt; OGRGeometry &gt; geom) <br> |
|  std::unique\_ptr&lt; OGRGeometry &gt; | [**ring\_to\_ogr**](#function-ring_to_ogr) (const std::vector&lt; [**Coordinate2D**](classCoordinate2D.md)&lt; double &gt; &gt; & exterior\_ring) <br> |
|  void | [**trace\_contours**](#function-trace_contours) (const [**GeoGrid**](classGeo.md)&lt; T &gt; & grid, [**GridGraph**](classGridGraph.md)&lt; std::set&lt; double &gt; &gt; & contour\_heights, AcceptFn accept, EmitFn emit) <br> |
|  const [**GeoGrid**](classGeo.md)&lt; T &gt; & | [**work\_grid\_for\_contours**](#function-work_grid_for_contours) (const [**GeoGrid**](classGeo.md)&lt; T &gt; & grid, std::optional&lt; T &gt; pad\_value, std::optional&lt; [**GeoGrid**](classGeo.md)&lt; T &gt; &gt; & padded\_out) <br> |




























## Public Functions Documentation




### function append\_ogr\_polygons 

```C++
inline void detail::append_ogr_polygons (
    const OGRGeometry * geometry,
    std::vector< std::unique_ptr< OGRGeometry > > & out
) 
```




<hr>



### function append\_polygons\_from\_ogr 

```C++
inline void detail::append_polygons_from_ogr (
    const OGRGeometry * geometry,
    std::vector< PolygonWithHoles > & out
) 
```




<hr>



### function blaze\_output\_score 

```C++
inline int detail::blaze_output_score (
    const BlazeOutputSet & outputs
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



### function collect\_locations\_with\_outputs 

```C++
inline void detail::collect_locations_with_outputs (
    const fs::path & directory,
    std::vector< fs::path > & locations
) 
```




<hr>



### function collect\_search\_roots 

```C++
inline void detail::collect_search_roots (
    const fs::path & directory,
    std::vector< fs::path > & roots
) 
```




<hr>



### function discover\_in\_root 

```C++
inline BlazeOutputSet detail::discover_in_root (
    const fs::path & root
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



### function find\_in\_root 

```C++
inline std::optional< fs::path > detail::find_in_root (
    const fs::path & root,
    const std::vector< std::string > & names
) 
```




<hr>



### function has\_importable\_outputs 

```C++
inline bool detail::has_importable_outputs (
    const BlazeOutputSet & outputs
) 
```




<hr>



### function identify\_contour\_crossings 

```C++
template<typename T, typename EdgeHeightsFn>
GridGraph < std::set< double > > detail::identify_contour_crossings (
    const GeoGrid < T > & grid,
    EdgeHeightsFn edge_heights
) 
```




<hr>



### function is\_blaze\_output\_filename 

```C++
inline bool detail::is_blaze_output_filename (
    const std::string & name
) 
```




<hr>



### function is\_combined\_root 

```C++
inline bool detail::is_combined_root (
    const fs::path & root
) 
```




<hr>



### function min\_contour\_loop\_area\_m2 

```C++
template<typename T>
double detail::min_contour_loop_area_m2 (
    const GeoGrid < T > & grid
) 
```




<hr>



### function polygon\_from\_ogr 

```C++
inline PolygonWithHoles detail::polygon_from_ogr (
    const OGRPolygon * ogr_poly
) 
```




<hr>



### function polygon\_to\_ogr 

```C++
inline std::unique_ptr< OGRGeometry > detail::polygon_to_ogr (
    const PolygonWithHoles & poly
) 
```




<hr>



### function repair\_ogr\_geometry 

```C++
inline std::unique_ptr< OGRGeometry > detail::repair_ogr_geometry (
    std::unique_ptr< OGRGeometry > geom
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
template<typename T, typename AcceptFn, typename EmitFn>
void detail::trace_contours (
    const GeoGrid < T > & grid,
    GridGraph < std::set< double > > & contour_heights,
    AcceptFn accept,
    EmitFn emit
) 
```




<hr>



### function work\_grid\_for\_contours 

```C++
template<typename T>
const GeoGrid < T > & detail::work_grid_for_contours (
    const GeoGrid < T > & grid,
    std::optional< T > pad_value,
    std::optional< GeoGrid < T > > & padded_out
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/gui/blaze_output_loader.hpp`

