

# Class FlexGrid



[**ClassList**](annotated.md) **>** [**FlexGrid**](classFlexGrid.md)








Inherits the following classes: [GridData](classGridData.md)






















































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**FlexGrid**](#function-flexgrid) ([**size\_t**](classCoordinate2D.md) width, [**size\_t**](classCoordinate2D.md) height, [**int**](classCoordinate2D.md) n\_bytes, [**int**](classCoordinate2D.md) data\_type={}) <br> |
|  std::byte \* | [**data**](#function-data-12) () <br> |
|  [**const**](classCoordinate2D.md) std::byte \* | [**data**](#function-data-22) () const<br> |
|  [**int**](classCoordinate2D.md) | [**data\_type**](#function-data_type) () const<br> |
|  [**void**](classCoordinate2D.md) | [**fill\_from**](#function-fill_from) ([**const**](classCoordinate2D.md) [**FlexGrid**](classFlexGrid.md) & other, [**const**](classCoordinate2D.md) [**Coordinate2D**](classCoordinate2D.md)&lt; [**long**](classCoordinate2D.md) [**long**](classCoordinate2D.md) &gt; & top\_left={0, 0}) <br> |
|  T | [**get**](#function-get) ([**const**](classCoordinate2D.md) [**Coordinate2D**](classCoordinate2D.md)&lt; [**long**](classCoordinate2D.md) [**long**](classCoordinate2D.md) &gt; & coord) const<br> |
|  [**unsigned**](classCoordinate2D.md) [**int**](classCoordinate2D.md) | [**n\_bytes**](#function-n_bytes) () const<br> |
|  std::byte \* | [**operator[]**](#function-operator) ([**Coordinate2D**](classCoordinate2D.md)&lt; [**size\_t**](classCoordinate2D.md) &gt; coord) <br> |
|  [**const**](classCoordinate2D.md) std::byte \* | [**operator[]**](#function-operator_1) ([**Coordinate2D**](classCoordinate2D.md)&lt; [**size\_t**](classCoordinate2D.md) &gt; coord) const<br> |


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
|  std::vector&lt; std::byte &gt; | [**m\_data**](#variable-m_data)  <br> |
|  [**unsigned**](classCoordinate2D.md) [**int**](classCoordinate2D.md) | [**m\_data\_size**](#variable-m_data_size)  <br> |
|  [**int**](classCoordinate2D.md) | [**m\_data\_type**](#variable-m_data_type)  <br> |


## Protected Attributes inherited from GridData

See [GridData](classGridData.md)

| Type | Name |
| ---: | :--- |
|  [**size\_t**](classCoordinate2D.md) | [**m\_height**](classGridData.md#variable-m_height)  <br> |
|  [**size\_t**](classCoordinate2D.md) | [**m\_width**](classGridData.md#variable-m_width)  <br> |






































## Public Functions Documentation




### function FlexGrid 

```C++
FlexGrid::FlexGrid (
    size_t width,
    size_t height,
    int n_bytes,
    int data_type={}
) 
```




<hr>



### function data [1/2]

```C++
inline std::byte * FlexGrid::data () 
```




<hr>



### function data [2/2]

```C++
inline const std::byte * FlexGrid::data () const
```




<hr>



### function data\_type 

```C++
int FlexGrid::data_type () const
```




<hr>



### function fill\_from 

```C++
inline void FlexGrid::fill_from (
    const  FlexGrid & other,
    const  Coordinate2D < long  long > & top_left={0, 0}
) 
```




<hr>



### function get 

```C++
template<typename T>
inline T FlexGrid::get (
    const  Coordinate2D < long  long > & coord
) const
```




<hr>



### function n\_bytes 

```C++
inline unsigned  int FlexGrid::n_bytes () const
```




<hr>



### function operator[] 

```C++
inline std::byte * FlexGrid::operator[] (
    Coordinate2D < size_t > coord
) 
```




<hr>



### function operator[] 

```C++
inline const std::byte * FlexGrid::operator[] (
    Coordinate2D < size_t > coord
) const
```




<hr>
## Protected Attributes Documentation




### variable m\_data 

```C++
std::vector<std::byte> FlexGrid::m_data;
```




<hr>



### variable m\_data\_size 

```C++
unsigned int FlexGrid::m_data_size;
```




<hr>



### variable m\_data\_type 

```C++
int FlexGrid::m_data_type;
```




<hr>

------------------------------
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/lib/grid/grid.hpp`

