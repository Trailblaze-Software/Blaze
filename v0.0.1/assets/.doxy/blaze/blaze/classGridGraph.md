

# Class GridGraph

**template &lt;[**typename**](classCoordinate2D.md) T&gt;**



[**ClassList**](annotated.md) **>** [**GridGraph**](classGridGraph.md)










































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**GridGraph**](#function-gridgraph) ([**const**](classCoordinate2D.md) [**Grid**](classGrid.md)&lt; [**U**](classCoordinate2D.md) &gt; & grid) <br> |
|  [**size\_t**](classCoordinate2D.md) | [**height**](#function-height) () const<br> |
|  [**Grid**](classGrid.md)&lt; T &gt; & | [**horizontal**](#function-horizontal-12) () <br> |
|  [**const**](classCoordinate2D.md) [**Grid**](classGrid.md)&lt; T &gt; & | [**horizontal**](#function-horizontal-22) () const<br> |
|  [**bool**](classCoordinate2D.md) | [**in\_bounds**](#function-in_bounds) ([**const**](classCoordinate2D.md) [**LineCoord2D**](classLineCoord2D.md)&lt; [**U**](classCoordinate2D.md) &gt; & coord) const<br> |
|  [**const**](classCoordinate2D.md) T & | [**operator[]**](#function-operator) ([**const**](classCoordinate2D.md) [**LineCoord2D**](classLineCoord2D.md)&lt; [**size\_t**](classCoordinate2D.md) &gt; & coord) const<br> |
|  T & | [**operator[]**](#function-operator_1) ([**const**](classCoordinate2D.md) [**LineCoord2D**](classLineCoord2D.md)&lt; [**size\_t**](classCoordinate2D.md) &gt; & coord) <br> |
|  [**Grid**](classGrid.md)&lt; T &gt; & | [**vertical**](#function-vertical-12) () <br> |
|  [**const**](classCoordinate2D.md) [**Grid**](classGrid.md)&lt; T &gt; & | [**vertical**](#function-vertical-22) () const<br> |
|  [**size\_t**](classCoordinate2D.md) | [**width**](#function-width) () const<br> |




























## Public Functions Documentation




### function GridGraph 

```C++
template<typename  U>
inline explicit GridGraph::GridGraph (
    const  Grid < U > & grid
) 
```




<hr>



### function height 

```C++
inline size_t GridGraph::height () const
```




<hr>



### function horizontal [1/2]

```C++
inline Grid < T > & GridGraph::horizontal () 
```




<hr>



### function horizontal [2/2]

```C++
inline const  Grid < T > & GridGraph::horizontal () const
```




<hr>



### function in\_bounds 

```C++
template<typename  U>
inline bool GridGraph::in_bounds (
    const  LineCoord2D < U > & coord
) const
```




<hr>



### function operator[] 

```C++
inline const T & GridGraph::operator[] (
    const  LineCoord2D < size_t > & coord
) const
```




<hr>



### function operator[] 

```C++
inline T & GridGraph::operator[] (
    const  LineCoord2D < size_t > & coord
) 
```




<hr>



### function vertical [1/2]

```C++
inline Grid < T > & GridGraph::vertical () 
```




<hr>



### function vertical [2/2]

```C++
inline const  Grid < T > & GridGraph::vertical () const
```




<hr>



### function width 

```C++
inline size_t GridGraph::width () const
```




<hr>## Friends Documentation





### friend operator&lt;&lt; 

```C++
inline std::ostream & GridGraph::operator<< (
    std::ostream & os,
    const  GridGraph & graph
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/lib/grid/grid.hpp`

