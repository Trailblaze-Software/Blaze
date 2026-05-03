

# Class GeoImgGrid



[**ClassList**](annotated.md) **>** [**GeoImgGrid**](classGeoImgGrid.md)








Inherits the following classes: [ImgGrid](classImgGrid.md),  [GeoGridData](classGeoGridData.md)






























































































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**GeoImgGrid**](#function-geoimggrid-12) ([**size\_t**](classCoordinate2D.md) width, [**size\_t**](classCoordinate2D.md) height, [**GeoTransform**](classGeoTransform.md) && transform, [**GeoProjection**](classGeoProjection.md) && projection) <br> |
|   | [**GeoImgGrid**](#function-geoimggrid-22) ([**const**](classCoordinate2D.md) [**GeoGrid**](classGeo.md)&lt; [**ColorT**](classCoordinate2D.md) &gt; & grid) <br> |
|  [**void**](classCoordinate2D.md) | [**draw**](#function-draw-13) ([**const**](classCoordinate2D.md) [**GeoImgGrid**](classGeoImgGrid.md) & other, std::optional&lt; [**int**](classCoordinate2D.md) &gt; interpolation={}) <br> |
|  [**void**](classCoordinate2D.md) | [**draw**](#function-draw-23) ([**const**](classCoordinate2D.md) [**Contour**](classContour.md) & contour, [**const**](classCoordinate2D.md) ColorVariant & color, [**double**](classCoordinate2D.md) width) <br> |
|  [**void**](classCoordinate2D.md) | [**draw**](#function-draw-33) ([**const**](classCoordinate2D.md) std::vector&lt; [**Coordinate2D**](classCoordinate2D.md)&lt; [**double**](classCoordinate2D.md) &gt; &gt; & in\_points, [**const**](classCoordinate2D.md) ColorVariant & color, [**double**](classCoordinate2D.md) width) <br> |
|  [**void**](classCoordinate2D.md) | [**draw\_point**](#function-draw_point) ([**const**](classCoordinate2D.md) [**Coordinate2D**](classCoordinate2D.md)&lt; [**double**](classCoordinate2D.md) &gt; & point, [**const**](classCoordinate2D.md) ColorVariant & color, [**double**](classCoordinate2D.md) size) <br> |
|  [**void**](classCoordinate2D.md) | [**save\_to**](#function-save_to) ([**const**](classCoordinate2D.md) fs::path & path, [**const**](classCoordinate2D.md) [**Extent2D**](structExtent2D.md) & extent) <br> |


## Public Functions inherited from ImgGrid

See [ImgGrid](classImgGrid.md)

| Type | Name |
| ---: | :--- |
|   | [**ImgGrid**](classImgGrid.md#function-imggrid) ([**size\_t**](classCoordinate2D.md) height, [**size\_t**](classCoordinate2D.md) width, std::optional&lt; [**int**](classCoordinate2D.md) &gt; type={}) <br> |
|  [**RGBColor**](classRGBColor.md) | [**get\_rgb\_color**](classImgGrid.md#function-get_rgb_color) ([**size\_t**](classCoordinate2D.md) row, [**size\_t**](classCoordinate2D.md) col) const<br> |
|  [**void**](classCoordinate2D.md) | [**save\_to**](classImgGrid.md#function-save_to) ([**const**](classCoordinate2D.md) fs::path & path) <br> |
|   | [**~ImgGrid**](classImgGrid.md#function-imggrid) () <br> |


## Public Functions inherited from GridData

See [GridData](classGridData.md)

| Type | Name |
| ---: | :--- |
|   | [**GridData**](classGridData.md#function-griddata) ([**size\_t**](classCoordinate2D.md) width, [**size\_t**](classCoordinate2D.md) height) <br> |
|  [**size\_t**](classCoordinate2D.md) | [**height**](classGridData.md#function-height) () const<br> |
|  [**bool**](classCoordinate2D.md) | [**in\_bounds**](classGridData.md#function-in_bounds) ([**const**](classCoordinate2D.md) [**Coordinate2D**](classCoordinate2D.md)&lt; [**size\_t**](classCoordinate2D.md) &gt; & coord) const<br> |
|  [**size\_t**](classCoordinate2D.md) | [**width**](classGridData.md#function-width) () const<br> |


## Public Functions inherited from GeoGridData

See [GeoGridData](classGeoGridData.md)

| Type | Name |
| ---: | :--- |
|   | [**GeoGridData**](classGeoGridData.md#function-geogriddata) ([**GeoTransform**](classGeoTransform.md) && transform, [**GeoProjection**](classGeoProjection.md) && projection) <br> |
|  [**double**](classCoordinate2D.md) | [**dx**](classGeoGridData.md#function-dx) () const<br> |
|  [**double**](classCoordinate2D.md) | [**dy**](classGeoGridData.md#function-dy) () const<br> |
|  [**const**](classCoordinate2D.md) [**GeoProjection**](classGeoProjection.md) & | [**projection**](classGeoGridData.md#function-projection) () const<br> |
|  [**const**](classCoordinate2D.md) [**GeoTransform**](classGeoTransform.md) & | [**transform**](classGeoGridData.md#function-transform) () const<br> |




























## Protected Attributes inherited from ImgGrid

See [ImgGrid](classImgGrid.md)

| Type | Name |
| ---: | :--- |
|  std::unique\_ptr&lt; cv::Mat &gt; | [**m\_img**](classImgGrid.md#variable-m_img)  <br> |


## Protected Attributes inherited from GridData

See [GridData](classGridData.md)

| Type | Name |
| ---: | :--- |
|  [**size\_t**](classCoordinate2D.md) | [**m\_height**](classGridData.md#variable-m_height)  <br> |
|  [**size\_t**](classCoordinate2D.md) | [**m\_width**](classGridData.md#variable-m_width)  <br> |


## Protected Attributes inherited from GeoGridData

See [GeoGridData](classGeoGridData.md)

| Type | Name |
| ---: | :--- |
|  [**GeoProjection**](classGeoProjection.md) | [**m\_projection**](classGeoGridData.md#variable-m_projection)  <br> |
|  [**GeoTransform**](classGeoTransform.md) | [**m\_transform**](classGeoGridData.md#variable-m_transform)  <br> |










































































## Public Functions Documentation




### function GeoImgGrid [1/2]

```C++
inline GeoImgGrid::GeoImgGrid (
    size_t width,
    size_t height,
    GeoTransform && transform,
    GeoProjection && projection
) 
```




<hr>



### function GeoImgGrid [2/2]

```C++
template<typename  ColorT, typename>
explicit GeoImgGrid::GeoImgGrid (
    const  GeoGrid < ColorT > & grid
) 
```




<hr>



### function draw [1/3]

```C++
void GeoImgGrid::draw (
    const  GeoImgGrid & other,
    std::optional< int > interpolation={}
) 
```




<hr>



### function draw [2/3]

```C++
void GeoImgGrid::draw (
    const  Contour & contour,
    const ColorVariant & color,
    double width
) 
```




<hr>



### function draw [3/3]

```C++
void GeoImgGrid::draw (
    const std::vector< Coordinate2D < double > > & in_points,
    const ColorVariant & color,
    double width
) 
```




<hr>



### function draw\_point 

```C++
void GeoImgGrid::draw_point (
    const  Coordinate2D < double > & point,
    const ColorVariant & color,
    double size
) 
```




<hr>



### function save\_to 

```C++
void GeoImgGrid::save_to (
    const fs::path & path,
    const  Extent2D & extent
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/lib/grid/img_grid.hpp`

