

# Class Grid

**template &lt;typename U&gt;**



[**ClassList**](annotated.md) **>** [**Grid**](classGrid.md)








Inherits the following classes: [GridData](classGridData.md)














## Public Types

| Type | Name |
| ---: | :--- |
| typedef T | [**value\_type**](#typedef-value_type)  <br> |








































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**Grid**](#function-grid-13) (size\_t width, size\_t height, int repeats=1) <br> |
|   | [**Grid**](#function-grid-23) (const [**Grid**](classGrid.md) & other) = default<br> |
|   | [**Grid**](#function-grid-33) ([**Grid**](classGrid.md) && other) noexcept<br> |
|  void | [**copy\_from**](#function-copy_from) (const [**Grid**](classGrid.md) & other) <br> |
|  void | [**draw\_circle**](#function-draw_circle) (const [**blaze::Point**](structblaze_1_1Point.md) & center, int radius, const [**RGBColor**](classRGBColor.md) & color, int thickness=-1) <br> |
|  void | [**draw\_polyline**](#function-draw_polyline) (const [**blaze::Point**](structblaze_1_1Point.md) \* points, int num\_points, bool closed, const [**RGBColor**](classRGBColor.md) & color, int thickness=1) <br> |
|  void | [**fill**](#function-fill) (const T & value) <br> |
|  void | [**fill\_from**](#function-fill_from-12) (const [**Grid**](classGrid.md) & other, const [**Coordinate2D**](classCoordinate2D.md)&lt; size\_t &gt; & top\_left={0, 0}) <br> |
|  void | [**fill\_from**](#function-fill_from-22) (const [**FlexGrid**](classFlexGrid.md) & other, const [**Coordinate2D**](classCoordinate2D.md)&lt; long long &gt; & top\_left={0, 0}) <br> |
|  std::pair&lt; T, T &gt; | [**get\_values**](#function-get_values) (const [**LineCoord2D**](classLineCoord2D.md)&lt; size\_t &gt; & coord) const<br> |
|  T | [**max\_value**](#function-max_value) () const<br> |
|  T | [**min\_value**](#function-min_value) () const<br> |
|  [**Grid**](classGrid.md) & | [**operator=**](#function-operator) (const [**Grid**](classGrid.md) & other) = default<br> |
|  [**Grid**](classGrid.md) & | [**operator=**](#function-operator_1) ([**Grid**](classGrid.md) && other) noexcept<br> |
|  T & | [**operator[]**](#function-operator_2) ([**Coordinate2D**](classCoordinate2D.md)&lt; size\_t &gt; coord) <br> |
|  const T & | [**operator[]**](#function-operator_3) ([**Coordinate2D**](classCoordinate2D.md)&lt; size\_t &gt; coord) const<br> |
|  void | [**resize\_to**](#function-resize_to) ([**Grid**](classGrid.md)&lt; [**RGBColor**](classRGBColor.md) &gt; & dst, const [**blaze::Size**](structblaze_1_1Size.md) & size, blaze::InterpolationMode mode=blaze::InterpolationMode::NEAREST) const<br> |
|  [**Grid**](classGrid.md)&lt; [**RGBColor**](classRGBColor.md) &gt; | [**slice\_rect**](#function-slice_rect) (const [**blaze::Rect**](structblaze_1_1Rect.md) & rect) const<br> |
|   | [**~Grid**](#function-grid) () = default<br> |


## Public Functions inherited from GridData

See [GridData](classGridData.md)

| Type | Name |
| ---: | :--- |
|   | [**GridData**](classGridData.md#function-griddata) (size\_t width, size\_t height) <br> |
|  size\_t | [**height**](classGridData.md#function-height) () const<br> |
|  bool | [**in\_bounds**](classGridData.md#function-in_bounds) (const [**Coordinate2D**](classCoordinate2D.md)&lt; size\_t &gt; & coord) const<br> |
|  size\_t | [**width**](classGridData.md#function-width) () const<br> |






## Protected Types

| Type | Name |
| ---: | :--- |
| typedef blaze::memory\_tracker::GridVector&lt; T &gt; | [**DataVector**](#typedef-datavector)  <br> |
| typedef std::conditional\_t&lt; std::is\_same\_v&lt; U, bool &gt;, [**BlazeBool**](structBlazeBool.md), U &gt; | [**T**](#typedef-t)  <br> |








## Protected Attributes

| Type | Name |
| ---: | :--- |
|  DataVector | [**m\_data**](#variable-m_data)  <br> |
|  int | [**m\_repeats**](#variable-m_repeats)  <br> |


## Protected Attributes inherited from GridData

See [GridData](classGridData.md)

| Type | Name |
| ---: | :--- |
|  size\_t | [**m\_height**](classGridData.md#variable-m_height)  <br> |
|  size\_t | [**m\_width**](classGridData.md#variable-m_width)  <br> |






































## Public Types Documentation




### typedef value\_type 

```C++
typedef T Grid< U >::value_type;
```




<hr>
## Public Functions Documentation




### function Grid [1/3]

```C++
inline Grid::Grid (
    size_t width,
    size_t height,
    int repeats=1
) 
```




<hr>



### function Grid [2/3]

```C++
Grid::Grid (
    const Grid & other
) = default
```




<hr>



### function Grid [3/3]

```C++
Grid::Grid (
    Grid && other
) noexcept
```




<hr>



### function copy\_from 

```C++
inline void Grid::copy_from (
    const Grid & other
) 
```




<hr>



### function draw\_circle 

```C++
inline void Grid::draw_circle (
    const blaze::Point & center,
    int radius,
    const RGBColor & color,
    int thickness=-1
) 
```




<hr>



### function draw\_polyline 

```C++
inline void Grid::draw_polyline (
    const blaze::Point * points,
    int num_points,
    bool closed,
    const RGBColor & color,
    int thickness=1
) 
```




<hr>



### function fill 

```C++
inline void Grid::fill (
    const T & value
) 
```




<hr>



### function fill\_from [1/2]

```C++
inline void Grid::fill_from (
    const Grid & other,
    const Coordinate2D < size_t > & top_left={0, 0}
) 
```




<hr>



### function fill\_from [2/2]

```C++
void Grid::fill_from (
    const FlexGrid & other,
    const Coordinate2D < long long > & top_left={0, 0}
) 
```




<hr>



### function get\_values 

```C++
inline std::pair< T, T > Grid::get_values (
    const LineCoord2D < size_t > & coord
) const
```




<hr>



### function max\_value 

```C++
inline T Grid::max_value () const
```




<hr>



### function min\_value 

```C++
inline T Grid::min_value () const
```




<hr>



### function operator= 

```C++
Grid & Grid::operator= (
    const Grid & other
) = default
```




<hr>



### function operator= 

```C++
Grid & Grid::operator= (
    Grid && other
) noexcept
```




<hr>



### function operator[] 

```C++
inline T & Grid::operator[] (
    Coordinate2D < size_t > coord
) 
```




<hr>



### function operator[] 

```C++
inline const T & Grid::operator[] (
    Coordinate2D < size_t > coord
) const
```




<hr>



### function resize\_to 

```C++
inline void Grid::resize_to (
    Grid < RGBColor > & dst,
    const blaze::Size & size,
    blaze::InterpolationMode mode=blaze::InterpolationMode::NEAREST
) const
```




<hr>



### function slice\_rect 

```C++
inline Grid < RGBColor > Grid::slice_rect (
    const blaze::Rect & rect
) const
```




<hr>



### function ~Grid 

```C++
Grid::~Grid () = default
```




<hr>
## Protected Types Documentation




### typedef DataVector 

```C++
using Grid< U >::DataVector =  blaze::memory_tracker::GridVector<T>;
```




<hr>



### typedef T 

```C++
using Grid< U >::T =  std::conditional_t<std::is_same_v<U, bool>, BlazeBool, U>;
```




<hr>
## Protected Attributes Documentation




### variable m\_data 

```C++
DataVector Grid< U >::m_data;
```




<hr>



### variable m\_repeats 

```C++
int Grid< U >::m_repeats;
```




<hr>## Friends Documentation





### friend operator&lt;&lt; 

```C++
inline std::ostream & Grid::operator<< (
    std::ostream & os,
    const Grid & grid
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/lib/grid/grid.hpp`

