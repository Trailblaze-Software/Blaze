

# Class GridData



[**ClassList**](annotated.md) **>** [**GridData**](classGridData.md)










Inherited by the following classes: [Grid](classGrid.md),  [FlexGrid](classFlexGrid.md),  [Grid](classGrid.md),  [ImgGrid](classImgGrid.md)
































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**GridData**](#function-griddata) ([**size\_t**](classCoordinate2D.md) width, [**size\_t**](classCoordinate2D.md) height) <br> |
|  [**size\_t**](classCoordinate2D.md) | [**height**](#function-height) () const<br> |
|  [**bool**](classCoordinate2D.md) | [**in\_bounds**](#function-in_bounds) ([**const**](classCoordinate2D.md) [**Coordinate2D**](classCoordinate2D.md)&lt; [**size\_t**](classCoordinate2D.md) &gt; & coord) const<br> |
|  [**size\_t**](classCoordinate2D.md) | [**width**](#function-width) () const<br> |








## Protected Attributes

| Type | Name |
| ---: | :--- |
|  [**size\_t**](classCoordinate2D.md) | [**m\_height**](#variable-m_height)  <br> |
|  [**size\_t**](classCoordinate2D.md) | [**m\_width**](#variable-m_width)  <br> |




















## Public Functions Documentation




### function GridData 

```C++
inline GridData::GridData (
    size_t width,
    size_t height
) 
```




<hr>



### function height 

```C++
inline size_t GridData::height () const
```




<hr>



### function in\_bounds 

```C++
inline bool GridData::in_bounds (
    const  Coordinate2D < size_t > & coord
) const
```




<hr>



### function width 

```C++
inline size_t GridData::width () const
```




<hr>
## Protected Attributes Documentation




### variable m\_height 

```C++
size_t GridData::m_height;
```




<hr>



### variable m\_width 

```C++
size_t GridData::m_width;
```




<hr>

------------------------------
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/lib/grid/grid.hpp`

