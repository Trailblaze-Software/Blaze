

# Class AsyncOctreeLASData



[**ClassList**](annotated.md) **>** [**AsyncOctreeLASData**](classAsyncOctreeLASData.md)




























## Public Static Attributes

| Type | Name |
| ---: | :--- |
|  constexpr size\_t | [**MAX\_PREVIEW\_POINTS**](#variable-max_preview_points)   = `500'000`<br> |














## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**AsyncOctreeLASData**](#function-asyncoctreelasdata) (const fs::path & filename, [**AsyncProgressTracker**](classAsyncProgressTracker.md) progress\_tracker, std::vector&lt; std::function&lt; void()&gt; &gt; callbacks={}, const std::string & target\_crs\_wkt={}) <br> |
|  [**Extent3D**](structExtent3D.md) | [**bounds**](#function-bounds) () const<br> |
|  const [**Coordinate3D**](classCoordinate3D.md)&lt; double &gt; & | [**coordinate\_origin**](#function-coordinate_origin) () const<br> |
|  bool | [**has\_rgb\_data**](#function-has_rgb_data) () const<br> |
|  bool | [**load\_complete**](#function-load_complete) () const<br> |
|  const [**GeoProjection**](classGeoProjection.md) & | [**native\_projection**](#function-native_projection) () const<br> |
|  bool | [**point\_format\_has\_rgb**](#function-point_format_has_rgb) () const<br> |
|  size\_t | [**points\_loaded**](#function-points_loaded) () const<br> |
|  const [**GeoProjection**](classGeoProjection.md) & | [**projection**](#function-projection) () const<br> |
|  std::shared\_ptr&lt; const [**LasRenderSnapshot**](structLasRenderSnapshot.md) &gt; | [**snapshot**](#function-snapshot) () const<br> |
|  size\_t | [**total\_points**](#function-total_points) () const<br> |
|   | [**~AsyncOctreeLASData**](#function-asyncoctreelasdata) () <br> |




























## Public Static Attributes Documentation




### variable MAX\_PREVIEW\_POINTS 

```C++
constexpr size_t AsyncOctreeLASData::MAX_PREVIEW_POINTS;
```




<hr>
## Public Functions Documentation




### function AsyncOctreeLASData 

```C++
inline AsyncOctreeLASData::AsyncOctreeLASData (
    const fs::path & filename,
    AsyncProgressTracker progress_tracker,
    std::vector< std::function< void()> > callbacks={},
    const std::string & target_crs_wkt={}
) 
```




<hr>



### function bounds 

```C++
inline Extent3D AsyncOctreeLASData::bounds () const
```




<hr>



### function coordinate\_origin 

```C++
inline const Coordinate3D < double > & AsyncOctreeLASData::coordinate_origin () const
```




<hr>



### function has\_rgb\_data 

```C++
inline bool AsyncOctreeLASData::has_rgb_data () const
```




<hr>



### function load\_complete 

```C++
inline bool AsyncOctreeLASData::load_complete () const
```




<hr>



### function native\_projection 

```C++
inline const GeoProjection & AsyncOctreeLASData::native_projection () const
```




<hr>



### function point\_format\_has\_rgb 

```C++
inline bool AsyncOctreeLASData::point_format_has_rgb () const
```




<hr>



### function points\_loaded 

```C++
inline size_t AsyncOctreeLASData::points_loaded () const
```




<hr>



### function projection 

```C++
inline const GeoProjection & AsyncOctreeLASData::projection () const
```




<hr>



### function snapshot 

```C++
inline std::shared_ptr< const LasRenderSnapshot > AsyncOctreeLASData::snapshot () const
```




<hr>



### function total\_points 

```C++
inline size_t AsyncOctreeLASData::total_points () const
```




<hr>



### function ~AsyncOctreeLASData 

```C++
inline AsyncOctreeLASData::~AsyncOctreeLASData () 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/gui/octree_las_data.hpp`

