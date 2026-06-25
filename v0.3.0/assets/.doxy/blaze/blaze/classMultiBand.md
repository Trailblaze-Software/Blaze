

# Class MultiBand

**template &lt;typename GridT&gt;**



[**ClassList**](annotated.md) **>** [**MultiBand**](classMultiBand.md)










































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**MultiBand**](#function-multiband-12) (int n\_bands, Args... args) <br> |
|   | [**MultiBand**](#function-multiband-22) (size\_t width, size\_t height) <br> |
|  void | [**fill\_from**](#function-fill_from) (const [**MultiBand**](classMultiBand.md) & other, const [**Coordinate2D**](classCoordinate2D.md)&lt; size\_t &gt; & top\_left={0, 0}) <br> |
|  size\_t | [**height**](#function-height) () const<br> |
|  bool | [**in\_bounds**](#function-in_bounds) (const [**Coordinate2D**](classCoordinate2D.md)&lt; size\_t &gt; & coord) const<br> |
|  GridT & | [**operator[]**](#function-operator) (size\_t i) <br> |
|  const GridT & | [**operator[]**](#function-operator_1) (size\_t i) const<br> |
|  size\_t | [**size**](#function-size) () const<br> |
|  size\_t | [**width**](#function-width) () const<br> |




























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
    const MultiBand & other,
    const Coordinate2D < size_t > & top_left={0, 0}
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
    const Coordinate2D < size_t > & coord
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

