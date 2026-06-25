

# Namespace octree\_las\_detail



[**Namespace List**](namespaces.md) **>** [**octree\_las\_detail**](namespaceoctree__las__detail.md)




















## Classes

| Type | Name |
| ---: | :--- |
| struct | [**BenchTimer**](structoctree__las__detail_1_1BenchTimer.md) <br> |
| class | [**MonotonicProgress**](classoctree__las__detail_1_1MonotonicProgress.md) <br> |


## Public Types

| Type | Name |
| ---: | :--- |
| typedef std::function&lt; void(const std::vector&lt; [**OctreePoint**](structOctreePoint.md) &gt; &preview, size\_t points\_loaded, const [**Extent3D**](structExtent3D.md) &bounds)&gt; | [**PreviewCallback**](#typedef-previewcallback)  <br> |






## Public Static Attributes

| Type | Name |
| ---: | :--- |
|  constexpr size\_t | [**MAX\_PREVIEW\_POINTS**](#variable-max_preview_points)   = `500'000`<br> |














## Public Functions

| Type | Name |
| ---: | :--- |
|  [**OctreePoint**](structOctreePoint.md) | [**convert\_las\_point**](#function-convert_las_point) (const LasPt & pt, const laspp::LASHeader & header, OGRCoordinateTransformation \* coord\_transform, const [**Coordinate3D**](classCoordinate3D.md)&lt; double &gt; & origin) <br> |
|  uint8\_t | [**las\_point\_classification**](#function-las_point_classification) (const LasPt & pt) <br> |
|  void | [**las\_point\_file\_color**](#function-las_point_file_color) (const LasPt & pt, [**OctreePoint**](structOctreePoint.md) & out) <br> |
|  bool | [**las\_point\_format\_has\_rgb**](#function-las_point_format_has_rgb) (uint8\_t point\_format) <br> |
|  void | [**load\_points\_dispatch**](#function-load_points_dispatch) (laspp::LASReader & reader, OGRCoordinateTransformation \* coord\_transform, const [**Coordinate3D**](classCoordinate3D.md)&lt; double &gt; & origin, size\_t preview\_stride, std::vector&lt; [**OctreePoint**](structOctreePoint.md) &gt; & converted, std::vector&lt; [**OctreePoint**](structOctreePoint.md) &gt; & preview, [**Extent3D**](structExtent3D.md) & bounds, [**ProgressTracker**](classProgressTracker.md) & tracker, const PreviewCallback & publish\_preview, const std::atomic&lt; bool &gt; \* cancel=nullptr) <br> |
|  void | [**load\_points\_parallel**](#function-load_points_parallel) (laspp::LASReader & reader, OGRCoordinateTransformation \* coord\_transform, const [**Coordinate3D**](classCoordinate3D.md)&lt; double &gt; & origin, size\_t preview\_stride, std::vector&lt; [**OctreePoint**](structOctreePoint.md) &gt; & converted, std::vector&lt; [**OctreePoint**](structOctreePoint.md) &gt; & preview, [**Extent3D**](structExtent3D.md) & bounds, [**ProgressTracker**](classProgressTracker.md) & tracker, const PreviewCallback & publish\_preview, const std::atomic&lt; bool &gt; \* cancel=nullptr) <br> |




























## Public Types Documentation




### typedef PreviewCallback 

```C++
using octree_las_detail::PreviewCallback = typedef std::function<void(const std::vector<OctreePoint>& preview, size_t points_loaded, const Extent3D& bounds)>;
```




<hr>
## Public Static Attributes Documentation




### variable MAX\_PREVIEW\_POINTS 

```C++
constexpr size_t octree_las_detail::MAX_PREVIEW_POINTS;
```




<hr>
## Public Functions Documentation




### function convert\_las\_point 

```C++
template<typename LasPt>
OctreePoint octree_las_detail::convert_las_point (
    const LasPt & pt,
    const laspp::LASHeader & header,
    OGRCoordinateTransformation * coord_transform,
    const Coordinate3D < double > & origin
) 
```




<hr>



### function las\_point\_classification 

```C++
template<typename LasPt>
uint8_t octree_las_detail::las_point_classification (
    const LasPt & pt
) 
```




<hr>



### function las\_point\_file\_color 

```C++
template<typename LasPt>
void octree_las_detail::las_point_file_color (
    const LasPt & pt,
    OctreePoint & out
) 
```




<hr>



### function las\_point\_format\_has\_rgb 

```C++
inline bool octree_las_detail::las_point_format_has_rgb (
    uint8_t point_format
) 
```




<hr>



### function load\_points\_dispatch 

```C++
inline void octree_las_detail::load_points_dispatch (
    laspp::LASReader & reader,
    OGRCoordinateTransformation * coord_transform,
    const Coordinate3D < double > & origin,
    size_t preview_stride,
    std::vector< OctreePoint > & converted,
    std::vector< OctreePoint > & preview,
    Extent3D & bounds,
    ProgressTracker & tracker,
    const PreviewCallback & publish_preview,
    const std::atomic< bool > * cancel=nullptr
) 
```




<hr>



### function load\_points\_parallel 

```C++
template<typename LasPt>
inline void octree_las_detail::load_points_parallel (
    laspp::LASReader & reader,
    OGRCoordinateTransformation * coord_transform,
    const Coordinate3D < double > & origin,
    size_t preview_stride,
    std::vector< OctreePoint > & converted,
    std::vector< OctreePoint > & preview,
    Extent3D & bounds,
    ProgressTracker & tracker,
    const PreviewCallback & publish_preview,
    const std::atomic< bool > * cancel=nullptr
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/gui/octree_las_data.hpp`

