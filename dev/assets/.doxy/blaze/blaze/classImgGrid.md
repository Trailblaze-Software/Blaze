

# Class ImgGrid



[**ClassList**](annotated.md) **>** [**ImgGrid**](classImgGrid.md)








Inherits the following classes: [GridData](classGridData.md)


Inherited by the following classes: [GeoImgGrid](classGeoImgGrid.md)




















































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**ImgGrid**](#function-imggrid) (size\_t width, size\_t height) <br> |
|  [**RGBColor**](classRGBColor.md) | [**get\_rgb\_color**](#function-get_rgb_color) (size\_t row, size\_t col) const<br> |
|  void | [**save\_to**](#function-save_to) (const fs::path & path) <br> |
|   | [**~ImgGrid**](#function-imggrid) () <br> |


## Public Functions inherited from GridData

See [GridData](classGridData.md)

| Type | Name |
| ---: | :--- |
|   | [**GridData**](classGridData.md#function-griddata) (size\_t width, size\_t height) <br> |
|  size\_t | [**height**](classGridData.md#function-height) () const<br> |
|  bool | [**in\_bounds**](classGridData.md#function-in_bounds) (const [**Coordinate2D**](classCoordinate2D.md)&lt; size\_t &gt; & coord) const<br> |
|  size\_t | [**width**](classGridData.md#function-width) () const<br> |














## Protected Attributes

| Type | Name |
| ---: | :--- |
|  std::unique\_ptr&lt; [**blaze::Image**](classblaze_1_1Image.md) &gt; | [**m\_img**](#variable-m_img)  <br> |


## Protected Attributes inherited from GridData

See [GridData](classGridData.md)

| Type | Name |
| ---: | :--- |
|  size\_t | [**m\_height**](classGridData.md#variable-m_height)  <br> |
|  size\_t | [**m\_width**](classGridData.md#variable-m_width)  <br> |






































## Public Functions Documentation




### function ImgGrid 

```C++
ImgGrid::ImgGrid (
    size_t width,
    size_t height
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
std::unique_ptr<blaze::Image> ImgGrid::m_img;
```




<hr>

------------------------------
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/lib/grid/img_grid.hpp`

