

# Class BinnedPoints



[**ClassList**](annotated.md) **>** [**BinnedPoints**](classBinnedPoints.md)








Inherits the following classes: [Geo](classGeo.md)










































































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**BinnedPoints**](#function-binnedpoints) ([**LASData**](classLASData.md) & las\_file, double bin\_resolution, unsigned int downsample\_factor, [**ProgressTracker**](classProgressTracker.md) && progress\_tracker) <br> |
|  [**Extent2D**](structExtent2D.md) | [**data\_extent**](#function-data_extent) () const<br> |


## Public Functions inherited from Geo

See [Geo](classGeo.md)

| Type | Name |
| ---: | :--- |
|   | [**Geo**](classGeo.md#function-geo-13) (size\_t width, size\_t height, [**GeoTransform**](classGeoTransform.md) && transform, [**GeoProjection**](classGeoProjection.md) && projection) <br> |
|   | [**Geo**](classGeo.md#function-geo-23) ([**GeoTransform**](classGeoTransform.md) && transform, [**GeoProjection**](classGeoProjection.md) && projection, Args... args) <br> |
|   | [**Geo**](classGeo.md#function-geo-33) (const std::vector&lt; std::vector&lt; U &gt; &gt; & data, [**GeoTransform**](classGeoTransform.md) transform=[**GeoTransform**](classGeoTransform.md)(), [**GeoProjection**](classGeoProjection.md) projection=[**GeoProjection**](classGeoProjection.md)()) <br> |
|  void | [**draw**](classGeo.md#function-draw) (const [**Geo**](classGeo.md)&lt; [**Grid**](classGrid.md)&lt; [**RGBColor**](classRGBColor.md) &gt; &gt; & other, [**ProgressTracker**](classProgressTracker.md) && progress\_tracker, GeoGridCompositeMode composite\_mode=GeoGridCompositeMode::AlphaBlend, std::optional&lt; blaze::InterpolationMode &gt; interpolation={}) <br> |
|  void | [**draw\_contours**](classGeo.md#function-draw_contours) (const std::vector&lt; [**Contour**](classContour.md) &gt; & contours, const [**ContourConfigs**](structContourConfigs.md) & configs, double render\_scale, bool base\_layer\_only, [**ProgressTracker**](classProgressTracker.md) && progress\_tracker) <br> |
|  void | [**draw\_filled\_polygon**](classGeo.md#function-draw_filled_polygon) (const [**PolygonWithHoles**](structPolygonWithHoles.md) & poly, const ColorVariant & color) <br> |
|  void | [**draw\_point**](classGeo.md#function-draw_point) (const [**Coordinate2D**](classCoordinate2D.md)&lt; double &gt; & point, const ColorVariant & color, double size) <br> |
|  void | [**draw\_streams**](classGeo.md#function-draw_streams) (const std::vector&lt; [**Stream**](structStream.md) &gt; & streams, const [**WaterConfigs**](structWaterConfigs.md) & water, double render\_scale, [**ProgressTracker**](classProgressTracker.md) && progress\_tracker) <br> |
|  std::unique\_ptr&lt; [**Extent2D**](structExtent2D.md) &gt; | [**extent**](classGeo.md#function-extent) () const<br> |
|  void | [**fill\_from**](classGeo.md#function-fill_from-12) (const [**Geo**](classGeo.md)&lt; U &gt; & other) <br> |
|  void | [**fill\_from**](classGeo.md#function-fill_from-22) (const U & other) <br> |
|  double | [**height\_m**](classGeo.md#function-height_m) () const<br> |
|  [**Geo**](classGeo.md) | [**pad**](classGeo.md#function-pad) (U pad\_value={}) const<br> |
|  void | [**rasterize\_filled\_polygons**](classGeo.md#function-rasterize_filled_polygons) (const std::vector&lt; [**PolygonWithHoles**](structPolygonWithHoles.md) &gt; & polygons, const ColorVariant & color, [**ProgressTracker**](classProgressTracker.md) && progress\_tracker) <br> |
|  void | [**save\_to**](classGeo.md#function-save_to) (const fs::path & path, const [**Extent2D**](structExtent2D.md) & extent, [**ProgressTracker**](classProgressTracker.md) && progress\_tracker) <br> |
|  [**Geo**](classGeo.md) | [**slice**](classGeo.md#function-slice) (const [**Extent2D**](structExtent2D.md) & extent) <br> |
|  double | [**width\_m**](classGeo.md#function-width_m) () const<br> |


## Public Functions inherited from GeoGridData

See [GeoGridData](classGeoGridData.md)

| Type | Name |
| ---: | :--- |
|   | [**GeoGridData**](classGeoGridData.md#function-geogriddata) ([**GeoTransform**](classGeoTransform.md) && transform, [**GeoProjection**](classGeoProjection.md) && projection) <br> |
|  double | [**dx**](classGeoGridData.md#function-dx) () const<br> |
|  double | [**dy**](classGeoGridData.md#function-dy) () const<br> |
|  const [**GeoProjection**](classGeoProjection.md) & | [**projection**](classGeoGridData.md#function-projection) () const<br> |
|  const [**GeoTransform**](classGeoTransform.md) & | [**transform**](classGeoGridData.md#function-transform) () const<br> |




## Public Static Functions inherited from Geo

See [Geo](classGeo.md)

| Type | Name |
| ---: | :--- |
|  [**Geo**](classGeo.md) | [**FromPoints**](classGeo.md#function-frompoints) (const [**Geo**](classGeo.md) & grid) <br> |




















## Protected Attributes inherited from GeoGridData

See [GeoGridData](classGeoGridData.md)

| Type | Name |
| ---: | :--- |
|  [**GeoProjection**](classGeoProjection.md) | [**m\_projection**](classGeoGridData.md#variable-m_projection)  <br> |
|  [**GeoTransform**](classGeoTransform.md) | [**m\_transform**](classGeoGridData.md#variable-m_transform)  <br> |
























































## Public Functions Documentation




### function BinnedPoints 

```C++
inline BinnedPoints::BinnedPoints (
    LASData & las_file,
    double bin_resolution,
    unsigned int downsample_factor,
    ProgressTracker && progress_tracker
) 
```




<hr>



### function data\_extent 

```C++
inline Extent2D BinnedPoints::data_extent () const
```




<hr>

------------------------------
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/lib/las/binned_points.hpp`

