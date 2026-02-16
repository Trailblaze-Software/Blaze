

# Class LineCoord2DCrossing

**template &lt;[**typename**](classCoordinate2D.md) T&gt;**



[**ClassList**](annotated.md) **>** [**LineCoord2DCrossing**](classLineCoord2DCrossing.md)








Inherits the following classes: [LineCoord2D](classLineCoord2D.md)










































































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**LineCoord2DCrossing**](#function-linecoord2dcrossing-12) (T x, T y, [**Direction2D**](classDirection2D.md) dir, [**Direction2D**](classDirection2D.md) crossing\_dir) <br> |
|   | [**LineCoord2DCrossing**](#function-linecoord2dcrossing-22) ([**const**](classCoordinate2D.md) [**LineCoord2D**](classLineCoord2D.md)&lt; T &gt; & line\_coord, [**Direction2D**](classDirection2D.md) crossing\_dir) <br> |
|  [**Direction2D**](classDirection2D.md) | [**crossing\_dir**](#function-crossing_dir) () const<br> |
|  [**LineCoord2DCrossing**](classLineCoord2DCrossing.md) | [**flip**](#function-flip) () const<br> |
|  std::vector&lt; [**LineCoord2DCrossing**](classLineCoord2DCrossing.md) &gt; | [**next\_points**](#function-next_points) () const<br> |


## Public Functions inherited from LineCoord2D

See [LineCoord2D](classLineCoord2D.md)

| Type | Name |
| ---: | :--- |
|   | [**LineCoord2D**](classLineCoord2D.md#function-linecoord2d-12) (T x, T y, [**Direction2D**](classDirection2D.md) dir) <br> |
|   | [**LineCoord2D**](classLineCoord2D.md#function-linecoord2d-22) ([**const**](classCoordinate2D.md) [**Coordinate2D**](classCoordinate2D.md)&lt; T &gt; & coord, [**Direction2D**](classDirection2D.md) dir) <br> |
|  [**Direction2D**](classDirection2D.md) | [**dir**](classLineCoord2D.md#function-dir) () const<br> |
|  [**Coordinate2D**](classCoordinate2D.md)&lt; T &gt; | [**end**](classLineCoord2D.md#function-end) () const<br> |
|  [**Coordinate2D**](classCoordinate2D.md)&lt; T &gt; | [**start**](classLineCoord2D.md#function-start) () const<br> |


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




### function LineCoord2DCrossing [1/2]

```C++
inline LineCoord2DCrossing::LineCoord2DCrossing (
    T x,
    T y,
    Direction2D dir,
    Direction2D crossing_dir
) 
```




<hr>



### function LineCoord2DCrossing [2/2]

```C++
inline LineCoord2DCrossing::LineCoord2DCrossing (
    const  LineCoord2D < T > & line_coord,
    Direction2D crossing_dir
) 
```




<hr>



### function crossing\_dir 

```C++
inline Direction2D LineCoord2DCrossing::crossing_dir () const
```




<hr>



### function flip 

```C++
inline LineCoord2DCrossing LineCoord2DCrossing::flip () const
```




<hr>



### function next\_points 

```C++
inline std::vector< LineCoord2DCrossing > LineCoord2DCrossing::next_points () const
```




<hr>## Friends Documentation





### friend operator&lt;&lt; 

```C++
inline std::ostream & LineCoord2DCrossing::operator<< (
    std::ostream & os,
    const  LineCoord2DCrossing & line_coord
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/lib/utilities/coordinate.hpp`

