

# Class LASPoint



[**ClassList**](annotated.md) **>** [**LASPoint**](classLASPoint.md)








Inherits the following classes: [Coordinate3D](classCoordinate3D.md)










































































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**LASPoint**](#function-laspoint-12) ([**double**](classCoordinate2D.md) x, [**double**](classCoordinate2D.md) y, [**double**](classCoordinate2D.md) z, [**uint16\_t**](classCoordinate2D.md) intensity, LASClassification classification) <br> |
|   | [**LASPoint**](#function-laspoint-22) () = default<br> |
|  LASClassification | [**classification**](#function-classification-12) () const<br> |
|  LASClassification & | [**classification**](#function-classification-22) () <br> |
|  [**uint16\_t**](classCoordinate2D.md) | [**intensity**](#function-intensity-12) () const<br> |
|  [**uint16\_t**](classCoordinate2D.md) & | [**intensity**](#function-intensity-22) () <br> |


## Public Functions inherited from Coordinate3D

See [Coordinate3D](classCoordinate3D.md)

| Type | Name |
| ---: | :--- |
|   | [**Coordinate3D**](classCoordinate3D.md#function-coordinate3d-12) (T x, T y, T z) <br> |
|   | [**Coordinate3D**](classCoordinate3D.md#function-coordinate3d-22) () = default<br> |
|  [**const**](classCoordinate2D.md) T | [**z**](classCoordinate3D.md#function-z-12) () const<br> |
|  T & | [**z**](classCoordinate3D.md#function-z-22) () <br> |


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




### function LASPoint [1/2]

```C++
inline LASPoint::LASPoint (
    double x,
    double y,
    double z,
    uint16_t intensity,
    LASClassification classification
) 
```




<hr>



### function LASPoint [2/2]

```C++
LASPoint::LASPoint () = default
```




<hr>



### function classification [1/2]

```C++
inline LASClassification LASPoint::classification () const
```




<hr>



### function classification [2/2]

```C++
inline LASClassification & LASPoint::classification () 
```




<hr>



### function intensity [1/2]

```C++
inline uint16_t LASPoint::intensity () const
```




<hr>



### function intensity [2/2]

```C++
inline uint16_t & LASPoint::intensity () 
```




<hr>## Friends Documentation





### friend operator&lt;&lt; 

```C++
inline std::ostream & LASPoint::operator<< (
    std::ostream & os,
    const  LASPoint & point
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/lib/las/las_point.hpp`

