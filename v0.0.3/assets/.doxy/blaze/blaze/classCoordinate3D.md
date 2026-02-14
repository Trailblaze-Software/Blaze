

# Class Coordinate3D

**template &lt;[**typename**](classCoordinate2D.md) T&gt;**



[**ClassList**](annotated.md) **>** [**Coordinate3D**](classCoordinate3D.md)








Inherits the following classes: [Coordinate2D](classCoordinate2D.md)






















































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**Coordinate3D**](#function-coordinate3d-12) (T x, T y, T z) <br> |
|   | [**Coordinate3D**](#function-coordinate3d-22) () = default<br> |
|  [**const**](classCoordinate2D.md) T | [**z**](#function-z-12) () const<br> |
|  T & | [**z**](#function-z-22) () <br> |


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




### function Coordinate3D [1/2]

```C++
inline Coordinate3D::Coordinate3D (
    T x,
    T y,
    T z
) 
```




<hr>



### function Coordinate3D [2/2]

```C++
Coordinate3D::Coordinate3D () = default
```




<hr>



### function z [1/2]

```C++
inline const T Coordinate3D::z () const
```




<hr>



### function z [2/2]

```C++
inline T & Coordinate3D::z () 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/lib/utilities/coordinate.hpp`

