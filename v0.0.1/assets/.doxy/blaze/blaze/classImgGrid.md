

# Class ImgGrid



[**ClassList**](annotated.md) **>** [**ImgGrid**](classImgGrid.md)








Inherits the following classes: [GridData](classGridData.md)


Inherited by the following classes: [GeoImgGrid](classGeoImgGrid.md)




















































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**ImgGrid**](#function-imggrid) ([**size\_t**](classCoordinate2D.md) height, [**size\_t**](classCoordinate2D.md) width, std::optional&lt; [**int**](classCoordinate2D.md) &gt; type={}) <br> |
|  [**RGBColor**](classRGBColor.md) | [**get\_rgb\_color**](#function-get_rgb_color) ([**size\_t**](classCoordinate2D.md) row, [**size\_t**](classCoordinate2D.md) col) const<br> |
|  [**void**](classCoordinate2D.md) | [**save\_to**](#function-save_to) ([**const**](classCoordinate2D.md) fs::path & path) <br> |
|   | [**~ImgGrid**](#function-imggrid) () <br> |


## Public Functions inherited from GridData

See [GridData](classGridData.md)

| Type | Name |
| ---: | :--- |
|   | [**GridData**](classGridData.md#function-griddata) ([**size\_t**](classCoordinate2D.md) width, [**size\_t**](classCoordinate2D.md) height) <br> |
|  [**size\_t**](classCoordinate2D.md) | [**height**](classGridData.md#function-height) () const<br> |
|  [**bool**](classCoordinate2D.md) | [**in\_bounds**](classGridData.md#function-in_bounds) ([**const**](classCoordinate2D.md) [**Coordinate2D**](classCoordinate2D.md)&lt; [**size\_t**](classCoordinate2D.md) &gt; & coord) const<br> |
|  [**size\_t**](classCoordinate2D.md) | [**width**](classGridData.md#function-width) () const<br> |














## Protected Attributes

| Type | Name |
| ---: | :--- |
|  std::unique\_ptr&lt; cv::Mat &gt; | [**m\_img**](#variable-m_img)  <br> |


## Protected Attributes inherited from GridData

See [GridData](classGridData.md)

| Type | Name |
| ---: | :--- |
|  [**size\_t**](classCoordinate2D.md) | [**m\_height**](classGridData.md#variable-m_height)  <br> |
|  [**size\_t**](classCoordinate2D.md) | [**m\_width**](classGridData.md#variable-m_width)  <br> |






































## Public Functions Documentation




### function ImgGrid 

```C++
ImgGrid::ImgGrid (
    size_t height,
    size_t width,
    std::optional< int > type={}
) 
```




<hr>



### function get\_rgb\_color 

```C++
RGBColor ImgGrid::get_rgb_color (
    size_t row,
    size_t col
) const
```




<hr>



### function save\_to 

```C++
void ImgGrid::save_to (
    const fs::path & path
) 
```




<hr>



### function ~ImgGrid 

```C++
ImgGrid::~ImgGrid () 
```




<hr>
## Protected Attributes Documentation




### variable m\_img 

```C++
std::unique_ptr<cv::Mat> ImgGrid::m_img;
```




<hr>

------------------------------
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/lib/grid/img_grid.hpp`

