

# Class Coordinate2D

**template &lt;[**typename**](classCoordinate2D.md) T&gt;**



[**ClassList**](annotated.md) **>** [**Coordinate2D**](classCoordinate2D.md)










Inherited by the following classes: [Coordinate3D](classCoordinate3D.md),  [Coordinate3D](classCoordinate3D.md),  [LineCoord2D](classLineCoord2D.md)
































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**Coordinate2D**](#function-coordinate2d-12) (T x, T y) <br> |
|   | [**Coordinate2D**](#function-coordinate2d-22) () = default<br> |
|  T | [**magnitude**](#function-magnitude) () const<br> |
|  T | [**magnitude\_sqd**](#function-magnitude_sqd) () const<br> |
|  [**Coordinate2D**](classCoordinate2D.md)&lt; [**double**](classCoordinate2D.md) &gt; | [**offset\_to\_center**](#function-offset_to_center) () const<br> |
|   | [**operator Coordinate2D&lt; U &gt;**](#function-operator-coordinate2d-u) () const<br> |
|  [**Coordinate2D**](classCoordinate2D.md) | [**operator+**](#function-operator) ([**Direction2D**](classDirection2D.md) dir) const<br> |
|  [**Coordinate2D**](classCoordinate2D.md) | [**operator+**](#function-operator_1) ([**Coordinate2D**](classCoordinate2D.md) o) const<br> |
|  [**Coordinate2D**](classCoordinate2D.md) | [**operator-**](#function-operator-) ([**Coordinate2D**](classCoordinate2D.md) o) const<br> |
|  [**bool**](classCoordinate2D.md) | [**operator==**](#function-operator_2) ([**const**](classCoordinate2D.md) [**Coordinate2D**](classCoordinate2D.md) & o) const<br> |
|  [**Coordinate2D**](classCoordinate2D.md)&lt; [**size\_t**](classCoordinate2D.md) &gt; | [**round**](#function-round) () const<br> |
|  [**Coordinate2D**](classCoordinate2D.md)&lt; [**double**](classCoordinate2D.md) &gt; | [**round\_NW**](#function-round_nw) ([**double**](classCoordinate2D.md) grid\_size) const<br> |
|  [**const**](classCoordinate2D.md) T & | [**x**](#function-x-12) () const<br> |
|  T & | [**x**](#function-x-22) () <br> |
|  [**const**](classCoordinate2D.md) T & | [**y**](#function-y-12) () const<br> |
|  T & | [**y**](#function-y-22) () <br> |




























## Public Functions Documentation




### function Coordinate2D [1/2]

```C++
inline Coordinate2D::Coordinate2D (
    T x,
    T y
) 
```




<hr>



### function Coordinate2D [2/2]

```C++
Coordinate2D::Coordinate2D () = default
```




<hr>



### function magnitude 

```C++
inline T Coordinate2D::magnitude () const
```




<hr>



### function magnitude\_sqd 

```C++
inline T Coordinate2D::magnitude_sqd () const
```




<hr>



### function offset\_to\_center 

```C++
inline Coordinate2D < double > Coordinate2D::offset_to_center () const
```




<hr>



### function operator Coordinate2D&lt; U &gt; 

```C++
template<typename  U>
inline Coordinate2D::operator Coordinate2D< U > () const
```




<hr>



### function operator+ 

```C++
inline Coordinate2D Coordinate2D::operator+ (
    Direction2D dir
) const
```




<hr>



### function operator+ 

```C++
inline Coordinate2D Coordinate2D::operator+ (
    Coordinate2D o
) const
```




<hr>



### function operator- 

```C++
inline Coordinate2D Coordinate2D::operator- (
    Coordinate2D o
) const
```




<hr>



### function operator== 

```C++
inline bool Coordinate2D::operator== (
    const  Coordinate2D & o
) const
```




<hr>



### function round 

```C++
inline Coordinate2D < size_t > Coordinate2D::round () const
```




<hr>



### function round\_NW 

```C++
inline Coordinate2D < double > Coordinate2D::round_NW (
    double grid_size
) const
```




<hr>



### function x [1/2]

```C++
inline const T & Coordinate2D::x () const
```




<hr>



### function x [2/2]

```C++
inline T & Coordinate2D::x () 
```




<hr>



### function y [1/2]

```C++
inline const T & Coordinate2D::y () const
```




<hr>



### function y [2/2]

```C++
inline T & Coordinate2D::y () 
```




<hr>## Friends Documentation





### friend operator&lt;&lt; 

```C++
inline std::ostream & Coordinate2D::operator<< (
    std::ostream & os,
    const  Coordinate2D & coord
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/lib/utilities/coordinate.hpp`

