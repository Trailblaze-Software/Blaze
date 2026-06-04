

# Class Grid

**template &lt;[**typename**](classCoordinate2D.md) [**U**](classCoordinate2D.md)&gt;**



[**ClassList**](annotated.md) **>** [**Grid**](classGrid.md)








Inherits the following classes: [GridData](classGridData.md)














## Public Types

| Type | Name |
| ---: | :--- |
| typedef T | [**value\_type**](#typedef-value_type)  <br> |








































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**Grid**](#function-grid) ([**size\_t**](classCoordinate2D.md) width, [**size\_t**](classCoordinate2D.md) height, [**int**](classCoordinate2D.md) repeats=1) <br> |
|  [**void**](classCoordinate2D.md) | [**copy\_from**](#function-copy_from) ([**const**](classCoordinate2D.md) [**Grid**](classGrid.md) & other) <br> |
|  [**void**](classCoordinate2D.md) | [**fill**](#function-fill) ([**const**](classCoordinate2D.md) T & value) <br> |
|  [**void**](classCoordinate2D.md) | [**fill\_from**](#function-fill_from-12) ([**const**](classCoordinate2D.md) [**Grid**](classGrid.md) & other, [**const**](classCoordinate2D.md) [**Coordinate2D**](classCoordinate2D.md)&lt; [**size\_t**](classCoordinate2D.md) &gt; & top\_left={0, 0}) <br> |
|  [**void**](classCoordinate2D.md) | [**fill\_from**](#function-fill_from-22) ([**const**](classCoordinate2D.md) [**FlexGrid**](classFlexGrid.md) & other, [**const**](classCoordinate2D.md) [**Coordinate2D**](classCoordinate2D.md)&lt; [**long**](classCoordinate2D.md) [**long**](classCoordinate2D.md) &gt; & top\_left={0, 0}) <br> |
|  std::pair&lt; T, T &gt; | [**get\_values**](#function-get_values) ([**const**](classCoordinate2D.md) [**LineCoord2D**](classLineCoord2D.md)&lt; [**size\_t**](classCoordinate2D.md) &gt; & coord) const<br> |
|  T | [**max\_value**](#function-max_value) () const<br> |
|  T | [**min\_value**](#function-min_value) () const<br> |
|  T & | [**operator[]**](#function-operator) ([**Coordinate2D**](classCoordinate2D.md)&lt; [**size\_t**](classCoordinate2D.md) &gt; coord) <br> |
|  [**const**](classCoordinate2D.md) T & | [**operator[]**](#function-operator_1) ([**Coordinate2D**](classCoordinate2D.md)&lt; [**size\_t**](classCoordinate2D.md) &gt; coord) const<br> |


## Public Functions inherited from GridData

See [GridData](classGridData.md)

| Type | Name |
| ---: | :--- |
|   | [**GridData**](classGridData.md#function-griddata) ([**size\_t**](classCoordinate2D.md) width, [**size\_t**](classCoordinate2D.md) height) <br> |
|  [**size\_t**](classCoordinate2D.md) | [**height**](classGridData.md#function-height) () const<br> |
|  [**bool**](classCoordinate2D.md) | [**in\_bounds**](classGridData.md#function-in_bounds) ([**const**](classCoordinate2D.md) [**Coordinate2D**](classCoordinate2D.md)&lt; [**size\_t**](classCoordinate2D.md) &gt; & coord) const<br> |
|  [**size\_t**](classCoordinate2D.md) | [**width**](classGridData.md#function-width) () const<br> |






## Protected Types

| Type | Name |
| ---: | :--- |
| typedef std::conditional\_t&lt; std::is\_same\_v&lt; [**U**](classCoordinate2D.md), [**bool**](classCoordinate2D.md) &gt;, [**BlazeBool**](structBlazeBool.md), [**U**](classCoordinate2D.md) &gt; | [**T**](#typedef-t)  <br> |








## Protected Attributes

| Type | Name |
| ---: | :--- |
|  std::vector&lt; T &gt; | [**m\_data**](#variable-m_data)  <br> |
|  [**int**](classCoordinate2D.md) | [**m\_repeats**](#variable-m_repeats)  <br> |


## Protected Attributes inherited from GridData

See [GridData](classGridData.md)

| Type | Name |
| ---: | :--- |
|  [**size\_t**](classCoordinate2D.md) | [**m\_height**](classGridData.md#variable-m_height)  <br> |
|  [**size\_t**](classCoordinate2D.md) | [**m\_width**](classGridData.md#variable-m_width)  <br> |






































## Public Types Documentation




### typedef value\_type 

```C++
typedef T Grid< U >::value_type;
```




<hr>
## Public Functions Documentation




### function Grid 

```C++
inline Grid::Grid (
    size_t width,
    size_t height,
    int repeats=1
) 
```




<hr>



### function copy\_from 

```C++
inline void Grid::copy_from (
    const  Grid & other
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
    const  Grid & other,
    const  Coordinate2D < size_t > & top_left={0, 0}
) 
```




<hr>



### function fill\_from [2/2]

```C++
void Grid::fill_from (
    const  FlexGrid & other,
    const  Coordinate2D < long  long > & top_left={0, 0}
) 
```




<hr>



### function get\_values 

```C++
inline std::pair< T, T > Grid::get_values (
    const  LineCoord2D < size_t > & coord
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
## Protected Types Documentation




### typedef T 

```C++
using Grid< U >::T =  std::conditional_t<std::is_same_v<U, bool>, BlazeBool, U>;
```




<hr>
## Protected Attributes Documentation




### variable m\_data 

```C++
std::vector<T> Grid< U >::m_data;
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
    const  Grid & grid
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/lib/grid/grid.hpp`

