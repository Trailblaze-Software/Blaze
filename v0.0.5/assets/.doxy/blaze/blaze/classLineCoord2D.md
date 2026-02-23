

# Class LineCoord2D

**template &lt;[**typename**](classCoordinate2D.md) T, [**typename**](classCoordinate2D.md)&gt;**



[**ClassList**](annotated.md) **>** [**LineCoord2D**](classLineCoord2D.md)








Inherits the following classes: [Coordinate2D](classCoordinate2D.md)


Inherited by the following classes: [LineCoord2DCrossing](classLineCoord2DCrossing.md)




















































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**LineCoord2D**](#function-linecoord2d-12) (T x, T y, [**Direction2D**](classDirection2D.md) dir) <br> |
|   | [**LineCoord2D**](#function-linecoord2d-22) ([**const**](classCoordinate2D.md) [**Coordinate2D**](classCoordinate2D.md)&lt; T &gt; & coord, [**Direction2D**](classDirection2D.md) dir) <br> |
|  [**Direction2D**](classDirection2D.md) | [**dir**](#function-dir) () const<br> |
|  [**Coordinate2D**](classCoordinate2D.md)&lt; T &gt; | [**end**](#function-end) () const<br> |
|  [**Coordinate2D**](classCoordinate2D.md)&lt; T &gt; | [**start**](#function-start) () const<br> |


## Public Functions inherited from Coordinate2D

See [Coordinate2D](classCoordinate2D.md)

| Type | Name |
| ---: | :--- |
|   | [**Coordinate2D**](classCoordinate2D.md#function-coordinate2d-12) (T x, T y) <br> |
|   | [**Coordinate2D**](classCoordinate2D.md#function-coordinate2d-22) () = default<br> |
|  T | [**magnitude**](classCoordinate2D.md#function-magnitude) () const<br> |
|  T | [**magnitude\_sqd**](classCoordinate2D.md#function-magnitude_sqd) () const<br> |
|  [**Coordinate2D**](classCoordinate2D.md)&lt; [**double**](classCoordinate2D.md) &gt; | [**offset\_to\_center**](classCoordinate2D.md#function-offset_to_center) () const<br> |
|   | [**operator Coordinate2D&lt; U &gt;**](classCoordinate2D.md#function-operator-coordinate2d-u) () const<br> |
|  [**Coordinate2D**](classCoordinate2D.md) | [**operator+**](classCoordinate2D.md#function-operator) ([**Direction2D**](classDirection2D.md) dir) const<br> |
|  [**Coordinate2D**](classCoordinate2D.md) | [**operator+**](classCoordinate2D.md#function-operator_1) ([**Coordinate2D**](classCoordinate2D.md) o) const<br> |
|  [**Coordinate2D**](classCoordinate2D.md) | [**operator-**](classCoordinate2D.md#function-operator-) ([**Coordinate2D**](classCoordinate2D.md) o) const<br> |
|  [**bool**](classCoordinate2D.md) | [**operator==**](classCoordinate2D.md#function-operator_2) ([**const**](classCoordinate2D.md) [**Coordinate2D**](classCoordinate2D.md) & o) const<br> |
|  [**Coordinate2D**](classCoordinate2D.md)&lt; [**size\_t**](classCoordinate2D.md) &gt; | [**round**](classCoordinate2D.md#function-round) () const<br> |
|  [**Coordinate2D**](classCoordinate2D.md)&lt; [**double**](classCoordinate2D.md) &gt; | [**round\_NW**](classCoordinate2D.md#function-round_nw) ([**double**](classCoordinate2D.md) grid\_size) const<br> |
|  [**const**](classCoordinate2D.md) T & | [**x**](classCoordinate2D.md#function-x-12) () const<br> |
|  T & | [**x**](classCoordinate2D.md#function-x-22) () <br> |
|  [**const**](classCoordinate2D.md) T & | [**y**](classCoordinate2D.md#function-y-12) () const<br> |
|  T & | [**y**](classCoordinate2D.md#function-y-22) () <br> |






















































## Public Functions Documentation




### function LineCoord2D [1/2]

```C++
inline LineCoord2D::LineCoord2D (
    T x,
    T y,
    Direction2D dir
) 
```




<hr>



### function LineCoord2D [2/2]

```C++
inline LineCoord2D::LineCoord2D (
    const  Coordinate2D < T > & coord,
    Direction2D dir
) 
```




<hr>



### function dir 

```C++
inline Direction2D LineCoord2D::dir () const
```




<hr>



### function end 

```C++
inline Coordinate2D < T > LineCoord2D::end () const
```




<hr>



### function start 

```C++
inline Coordinate2D < T > LineCoord2D::start () const
```




<hr>## Friends Documentation





### friend operator&lt;&lt; 

```C++
inline std::ostream & LineCoord2D::operator<< (
    std::ostream & os,
    const  LineCoord2D & line_coord
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/lib/utilities/coordinate.hpp`

