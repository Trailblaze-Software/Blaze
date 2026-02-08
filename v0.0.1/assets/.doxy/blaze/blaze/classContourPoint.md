

# Class ContourPoint



[**ClassList**](annotated.md) **>** [**ContourPoint**](classContourPoint.md)








Inherits the following classes: [Coordinate2D](classCoordinate2D.md)






















































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**ContourPoint**](#function-contourpoint) ([**double**](classCoordinate2D.md) x, [**double**](classCoordinate2D.md) y, [**double**](classCoordinate2D.md) height) <br> |
|  [**void**](classCoordinate2D.md) | [**find\_up\_down**](#function-find_up_down) ([**const**](classCoordinate2D.md) [**GeoGrid**](classGeo.md)&lt; std::vector&lt; std::shared\_ptr&lt; [**ContourPoint**](classContourPoint.md) &gt; &gt; &gt; & point\_grid) <br> |
|  [**double**](classCoordinate2D.md) | [**height**](#function-height) () const<br> |
|  [**void**](classCoordinate2D.md) | [**set\_next**](#function-set_next) (std::shared\_ptr&lt; [**ContourPoint**](classContourPoint.md) &gt; next) <br> |
|  [**void**](classCoordinate2D.md) | [**set\_previous**](#function-set_previous) (std::shared\_ptr&lt; [**ContourPoint**](classContourPoint.md) &gt; prev) <br> |
|  [**double**](classCoordinate2D.md) | [**slope**](#function-slope) () const<br> |


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




### function ContourPoint 

```C++
inline ContourPoint::ContourPoint (
    double x,
    double y,
    double height
) 
```




<hr>



### function find\_up\_down 

```C++
inline void ContourPoint::find_up_down (
    const  GeoGrid < std::vector< std::shared_ptr< ContourPoint > > > & point_grid
) 
```




<hr>



### function height 

```C++
inline double ContourPoint::height () const
```




<hr>



### function set\_next 

```C++
inline void ContourPoint::set_next (
    std::shared_ptr< ContourPoint > next
) 
```




<hr>



### function set\_previous 

```C++
inline void ContourPoint::set_previous (
    std::shared_ptr< ContourPoint > prev
) 
```




<hr>



### function slope 

```C++
inline double ContourPoint::slope () const
```




<hr>

------------------------------
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/lib/cliff/cliff.hpp`

