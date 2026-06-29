

# Class Geo

**template &lt;typename GridT&gt;**



[**ClassList**](annotated.md) **>** [**Geo**](classGeo.md)








Inherits the following classes: GridT,  [GeoGridData](classGeoGridData.md)






















































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**Geo**](#function-geo-13) (size\_t width, size\_t height, [**GeoTransform**](classGeoTransform.md) && transform, [**GeoProjection**](classGeoProjection.md) && projection) <br> |
|   | [**Geo**](#function-geo-23) ([**GeoTransform**](classGeoTransform.md) && transform, [**GeoProjection**](classGeoProjection.md) && projection, Args... args) <br> |
|   | [**Geo**](#function-geo-33) (const std::vector&lt; std::vector&lt; U &gt; &gt; & data, [**GeoTransform**](classGeoTransform.md) transform=[**GeoTransform**](classGeoTransform.md)(), [**GeoProjection**](classGeoProjection.md) projection=[**GeoProjection**](classGeoProjection.md)()) <br> |
|  void | [**draw**](#function-draw) (const [**Geo**](classGeo.md)&lt; [**Grid**](classGrid.md)&lt; [**RGBColor**](classRGBColor.md) &gt; &gt; & other, [**ProgressTracker**](classProgressTracker.md) && progress\_tracker, GeoGridCompositeMode composite\_mode=GeoGridCompositeMode::AlphaBlend, std::optional&lt; blaze::InterpolationMode &gt; interpolation={}) <br> |
|  void | [**draw\_contours**](#function-draw_contours) (const std::vector&lt; [**Contour**](classContour.md) &gt; & contours, const [**ContourConfigs**](structContourConfigs.md) & configs, double render\_scale, bool base\_layer\_only, [**ProgressTracker**](classProgressTracker.md) && progress\_tracker) <br> |
|  void | [**draw\_filled\_polygon**](#function-draw_filled_polygon) (const [**PolygonWithHoles**](structPolygonWithHoles.md) & poly, const ColorVariant & color) <br> |
|  void | [**draw\_point**](#function-draw_point) (const [**Coordinate2D**](classCoordinate2D.md)&lt; double &gt; & point, const ColorVariant & color, double size) <br> |
|  void | [**draw\_streams**](#function-draw_streams) (const std::vector&lt; [**Stream**](structStream.md) &gt; & streams, const [**WaterConfigs**](structWaterConfigs.md) & water, double render\_scale, [**ProgressTracker**](classProgressTracker.md) && progress\_tracker) <br> |
|  std::unique\_ptr&lt; [**Extent2D**](structExtent2D.md) &gt; | [**extent**](#function-extent) () const<br> |
|  void | [**fill\_from**](#function-fill_from-12) (const [**Geo**](classGeo.md)&lt; U &gt; & other) <br> |
|  void | [**fill\_from**](#function-fill_from-22) (const U & other) <br> |
|  double | [**height\_m**](#function-height_m) () const<br> |
|  [**Geo**](classGeo.md) | [**pad**](#function-pad) (U pad\_value={}) const<br> |
|  void | [**rasterize\_filled\_polygons**](#function-rasterize_filled_polygons) (const std::vector&lt; [**PolygonWithHoles**](structPolygonWithHoles.md) &gt; & polygons, const ColorVariant & color, [**ProgressTracker**](classProgressTracker.md) && progress\_tracker) <br> |
|  void | [**save\_to**](#function-save_to) (const fs::path & path, const [**Extent2D**](structExtent2D.md) & extent, [**ProgressTracker**](classProgressTracker.md) && progress\_tracker) <br> |
|  [**Geo**](classGeo.md) | [**slice**](#function-slice) (const [**Extent2D**](structExtent2D.md) & extent) <br> |
|  double | [**width\_m**](#function-width_m) () const<br> |


## Public Functions inherited from GeoGridData

See [GeoGridData](classGeoGridData.md)

| Type | Name |
| ---: | :--- |
|   | [**GeoGridData**](classGeoGridData.md#function-geogriddata) ([**GeoTransform**](classGeoTransform.md) && transform, [**GeoProjection**](classGeoProjection.md) && projection) <br> |
|  double | [**dx**](classGeoGridData.md#function-dx) () const<br> |
|  double | [**dy**](classGeoGridData.md#function-dy) () const<br> |
|  const [**GeoProjection**](classGeoProjection.md) & | [**projection**](classGeoGridData.md#function-projection) () const<br> |
|  const [**GeoTransform**](classGeoTransform.md) & | [**transform**](classGeoGridData.md#function-transform) () const<br> |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  [**Geo**](classGeo.md) | [**FromPoints**](#function-frompoints) (const [**Geo**](classGeo.md) & grid) <br> |














## Protected Attributes inherited from GeoGridData

See [GeoGridData](classGeoGridData.md)

| Type | Name |
| ---: | :--- |
|  [**GeoProjection**](classGeoProjection.md) | [**m\_projection**](classGeoGridData.md#variable-m_projection)  <br> |
|  [**GeoTransform**](classGeoTransform.md) | [**m\_transform**](classGeoGridData.md#variable-m_transform)  <br> |






































## Public Functions Documentation




### function Geo [1/3]

```C++
inline Geo::Geo (
    size_t width,
    size_t height,
    GeoTransform && transform,
    GeoProjection && projection
) 
```




<hr>



### function Geo [2/3]

```C++
template<typename... Args>
inline Geo::Geo (
    GeoTransform && transform,
    GeoProjection && projection,
    Args... args
) 
```




<hr>



### function Geo [3/3]

```C++
template<typename U>
inline Geo::Geo (
    const std::vector< std::vector< U > > & data,
    GeoTransform transform=GeoTransform (),
    GeoProjection projection=GeoProjection ()
) 
```




<hr>



### function draw 

```C++
inline void Geo::draw (
    const Geo < Grid < RGBColor > > & other,
    ProgressTracker && progress_tracker,
    GeoGridCompositeMode composite_mode=GeoGridCompositeMode::AlphaBlend,
    std::optional< blaze::InterpolationMode > interpolation={}
) 
```




<hr>



### function draw\_contours 

```C++
inline void Geo::draw_contours (
    const std::vector< Contour > & contours,
    const ContourConfigs & configs,
    double render_scale,
    bool base_layer_only,
    ProgressTracker && progress_tracker
) 
```




<hr>



### function draw\_filled\_polygon 

```C++
inline void Geo::draw_filled_polygon (
    const PolygonWithHoles & poly,
    const ColorVariant & color
) 
```




<hr>



### function draw\_point 

```C++
inline void Geo::draw_point (
    const Coordinate2D < double > & point,
    const ColorVariant & color,
    double size
) 
```




<hr>



### function draw\_streams 

```C++
inline void Geo::draw_streams (
    const std::vector< Stream > & streams,
    const WaterConfigs & water,
    double render_scale,
    ProgressTracker && progress_tracker
) 
```




<hr>



### function extent 

```C++
std::unique_ptr< Extent2D > Geo::extent () const
```




<hr>



### function fill\_from [1/2]

```C++
template<typename U>
inline void Geo::fill_from (
    const Geo < U > & other
) 
```




<hr>



### function fill\_from [2/2]

```C++
template<typename U>
inline void Geo::fill_from (
    const U & other
) 
```




<hr>



### function height\_m 

```C++
inline double Geo::height_m () const
```




<hr>



### function pad 

```C++
template<typename U>
inline Geo Geo::pad (
    U pad_value={}
) const
```




<hr>



### function rasterize\_filled\_polygons 

```C++
inline void Geo::rasterize_filled_polygons (
    const std::vector< PolygonWithHoles > & polygons,
    const ColorVariant & color,
    ProgressTracker && progress_tracker
) 
```




<hr>



### function save\_to 

```C++
inline void Geo::save_to (
    const fs::path & path,
    const Extent2D & extent,
    ProgressTracker && progress_tracker
) 
```




<hr>



### function slice 

```C++
Geo Geo::slice (
    const Extent2D & extent
) 
```




<hr>



### function width\_m 

```C++
inline double Geo::width_m () const
```




<hr>
## Public Static Functions Documentation




### function FromPoints 

```C++
template<typename U>
static inline Geo Geo::FromPoints (
    const Geo & grid
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/lib/grid/grid.hpp`

