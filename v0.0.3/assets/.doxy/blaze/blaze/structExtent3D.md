

# Struct Extent3D



[**ClassList**](annotated.md) **>** [**Extent3D**](structExtent3D.md)








Inherits the following classes: [Extent2D](structExtent2D.md)






















## Public Attributes

| Type | Name |
| ---: | :--- |
|  [**double**](classCoordinate2D.md) | [**maxz**](#variable-maxz)   = `-std::numeric\_limits&lt;[**double**](classCoordinate2D.md)&gt;[**::infinity**](classCoordinate2D.md)()`<br> |
|  [**double**](classCoordinate2D.md) | [**minz**](#variable-minz)   = `std::numeric\_limits&lt;[**double**](classCoordinate2D.md)&gt;[**::infinity**](classCoordinate2D.md)()`<br> |


## Public Attributes inherited from Extent2D

See [Extent2D](structExtent2D.md)

| Type | Name |
| ---: | :--- |
|  [**double**](classCoordinate2D.md) | [**maxx**](structExtent2D.md#variable-maxx)   = `-std::numeric\_limits&lt;[**double**](classCoordinate2D.md)&gt;[**::infinity**](classCoordinate2D.md)()`<br> |
|  [**double**](classCoordinate2D.md) | [**maxy**](structExtent2D.md#variable-maxy)   = `-std::numeric\_limits&lt;[**double**](classCoordinate2D.md)&gt;[**::infinity**](classCoordinate2D.md)()`<br> |
|  [**double**](classCoordinate2D.md) | [**minx**](structExtent2D.md#variable-minx)   = `std::numeric\_limits&lt;[**double**](classCoordinate2D.md)&gt;[**::infinity**](classCoordinate2D.md)()`<br> |
|  [**double**](classCoordinate2D.md) | [**miny**](structExtent2D.md#variable-miny)   = `std::numeric\_limits&lt;[**double**](classCoordinate2D.md)&gt;[**::infinity**](classCoordinate2D.md)()`<br> |






























## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**Extent3D**](#function-extent3d-13) () = default<br> |
|   | [**Extent3D**](#function-extent3d-23) ([**const**](classCoordinate2D.md) [**Extent2D**](structExtent2D.md) & extent, [**double**](classCoordinate2D.md) minz, [**double**](classCoordinate2D.md) maxz) <br> |
|   | [**Extent3D**](#function-extent3d-33) ([**double**](classCoordinate2D.md) minx, [**double**](classCoordinate2D.md) maxx, [**double**](classCoordinate2D.md) miny, [**double**](classCoordinate2D.md) maxy, [**double**](classCoordinate2D.md) minz, [**double**](classCoordinate2D.md) maxz) <br> |
|  [**Coordinate3D**](classCoordinate3D.md)&lt; [**double**](classCoordinate2D.md) &gt; | [**center**](#function-center) () const<br> |
|  [**void**](classCoordinate2D.md) | [**grow**](#function-grow-13) ([**double**](classCoordinate2D.md) x, [**double**](classCoordinate2D.md) y, [**double**](classCoordinate2D.md) z) <br> |
|  [**void**](classCoordinate2D.md) | [**grow**](#function-grow-23) ([**double**](classCoordinate2D.md) border) <br> |
|  [**void**](classCoordinate2D.md) | [**grow**](#function-grow-33) ([**const**](classCoordinate2D.md) [**Extent3D**](structExtent3D.md) & other) <br> |
|  [**Extent3D**](structExtent3D.md) | [**intersection**](#function-intersection) ([**const**](classCoordinate2D.md) [**Extent3D**](structExtent3D.md) & other) const<br> |
|  [**bool**](classCoordinate2D.md) | [**intersects**](#function-intersects) ([**const**](classCoordinate2D.md) [**Extent3D**](structExtent3D.md) & other) const<br> |
|  [**double**](classCoordinate2D.md) | [**max\_extent**](#function-max_extent) () const<br> |
|  [**bool**](classCoordinate2D.md) | [**operator!=**](#function-operator) ([**const**](classCoordinate2D.md) [**Extent3D**](structExtent3D.md) & other) const<br> |
|  [**Extent3D**](structExtent3D.md) | [**operator-**](#function-operator-) ([**const**](classCoordinate2D.md) [**Coordinate3D**](classCoordinate3D.md)&lt; [**double**](classCoordinate2D.md) &gt; & offset) const<br> |


## Public Functions inherited from Extent2D

See [Extent2D](structExtent2D.md)

| Type | Name |
| ---: | :--- |
|  [**bool**](classCoordinate2D.md) | [**contains**](structExtent2D.md#function-contains) ([**double**](classCoordinate2D.md) x, [**double**](classCoordinate2D.md) y) const<br> |
|  [**void**](classCoordinate2D.md) | [**grow**](structExtent2D.md#function-grow) ([**const**](classCoordinate2D.md) [**Extent2D**](structExtent2D.md) & other) <br> |






















































## Public Attributes Documentation




### variable maxz 

```C++
double Extent3D::maxz;
```




<hr>



### variable minz 

```C++
double Extent3D::minz;
```




<hr>
## Public Functions Documentation




### function Extent3D [1/3]

```C++
Extent3D::Extent3D () = default
```




<hr>



### function Extent3D [2/3]

```C++
inline Extent3D::Extent3D (
    const  Extent2D & extent,
    double minz,
    double maxz
) 
```




<hr>



### function Extent3D [3/3]

```C++
inline Extent3D::Extent3D (
    double minx,
    double maxx,
    double miny,
    double maxy,
    double minz,
    double maxz
) 
```




<hr>



### function center 

```C++
inline Coordinate3D < double > Extent3D::center () const
```




<hr>



### function grow [1/3]

```C++
inline void Extent3D::grow (
    double x,
    double y,
    double z
) 
```




<hr>



### function grow [2/3]

```C++
inline void Extent3D::grow (
    double border
) 
```




<hr>



### function grow [3/3]

```C++
inline void Extent3D::grow (
    const  Extent3D & other
) 
```




<hr>



### function intersection 

```C++
inline Extent3D Extent3D::intersection (
    const  Extent3D & other
) const
```




<hr>



### function intersects 

```C++
inline bool Extent3D::intersects (
    const  Extent3D & other
) const
```




<hr>



### function max\_extent 

```C++
inline double Extent3D::max_extent () const
```




<hr>



### function operator!= 

```C++
inline bool Extent3D::operator!= (
    const  Extent3D & other
) const
```




<hr>



### function operator- 

```C++
inline Extent3D Extent3D::operator- (
    const  Coordinate3D < double > & offset
) const
```




<hr>## Friends Documentation





### friend operator&lt;&lt; 

```C++
inline std::ostream & Extent3D::operator<< (
    std::ostream & os,
    const  Extent3D & extent
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/lib/utilities/coordinate.hpp`

