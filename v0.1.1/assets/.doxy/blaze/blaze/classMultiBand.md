

# Class MultiBand

**template &lt;[**typename**](classCoordinate2D.md) GridT&gt;**



[**ClassList**](annotated.md) **>** [**MultiBand**](classMultiBand.md)










































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**MultiBand**](#function-multiband-12) ([**int**](classCoordinate2D.md) n\_bands, Args... args) <br> |
|   | [**MultiBand**](#function-multiband-22) ([**size\_t**](classCoordinate2D.md) width, [**size\_t**](classCoordinate2D.md) height) <br> |
|  [**void**](classCoordinate2D.md) | [**fill\_from**](#function-fill_from) ([**const**](classCoordinate2D.md) [**MultiBand**](classMultiBand.md) & other, [**const**](classCoordinate2D.md) [**Coordinate2D**](classCoordinate2D.md)&lt; [**size\_t**](classCoordinate2D.md) &gt; & top\_left={0, 0}) <br> |
|  [**size\_t**](classCoordinate2D.md) | [**height**](#function-height) () const<br> |
|  [**bool**](classCoordinate2D.md) | [**in\_bounds**](#function-in_bounds) ([**const**](classCoordinate2D.md) [**Coordinate2D**](classCoordinate2D.md)&lt; [**size\_t**](classCoordinate2D.md) &gt; & coord) const<br> |
|  GridT & | [**operator[]**](#function-operator) ([**size\_t**](classCoordinate2D.md) i) <br> |
|  [**const**](classCoordinate2D.md) GridT & | [**operator[]**](#function-operator_1) ([**size\_t**](classCoordinate2D.md) i) const<br> |
|  [**size\_t**](classCoordinate2D.md) | [**size**](#function-size) () const<br> |
|  [**size\_t**](classCoordinate2D.md) | [**width**](#function-width) () const<br> |




























## Public Functions Documentation




### function MultiBand [1/2]

```C++
template<typename... Args>
inline MultiBand::MultiBand (
    int n_bands,
    Args... args
) 
```




<hr>



### function MultiBand [2/2]

```C++
inline MultiBand::MultiBand (
    size_t width,
    size_t height
) 
```




<hr>



### function fill\_from 

```C++
inline void MultiBand::fill_from (
    const  MultiBand & other,
    const  Coordinate2D < size_t > & top_left={0, 0}
) 
```




<hr>



### function height 

```C++
inline size_t MultiBand::height () const
```




<hr>



### function in\_bounds 

```C++
inline bool MultiBand::in_bounds (
    const  Coordinate2D < size_t > & coord
) const
```




<hr>



### function operator[] 

```C++
inline GridT & MultiBand::operator[] (
    size_t i
) 
```




<hr>



### function operator[] 

```C++
inline const GridT & MultiBand::operator[] (
    size_t i
) const
```




<hr>



### function size 

```C++
inline size_t MultiBand::size () const
```




<hr>



### function width 

```C++
inline size_t MultiBand::width () const
```




<hr>

------------------------------
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/lib/grid/grid.hpp`

