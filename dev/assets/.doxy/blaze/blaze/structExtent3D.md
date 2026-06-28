

# Struct Extent3D



[**ClassList**](annotated.md) **>** [**Extent3D**](structExtent3D.md)








Inherits the following classes: [Extent2D](structExtent2D.md)






















## Public Attributes

| Type | Name |
| ---: | :--- |
|  double | [**maxz**](#variable-maxz)   = `-std::numeric\_limits&lt;double&gt;::infinity()`<br> |
|  double | [**minz**](#variable-minz)   = `std::numeric\_limits&lt;double&gt;::infinity()`<br> |


## Public Attributes inherited from Extent2D

See [Extent2D](structExtent2D.md)

| Type | Name |
| ---: | :--- |
|  double | [**maxx**](structExtent2D.md#variable-maxx)   = `-std::numeric\_limits&lt;double&gt;::infinity()`<br> |
|  double | [**maxy**](structExtent2D.md#variable-maxy)   = `-std::numeric\_limits&lt;double&gt;::infinity()`<br> |
|  double | [**minx**](structExtent2D.md#variable-minx)   = `std::numeric\_limits&lt;double&gt;::infinity()`<br> |
|  double | [**miny**](structExtent2D.md#variable-miny)   = `std::numeric\_limits&lt;double&gt;::infinity()`<br> |






























## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**Extent3D**](#function-extent3d-13) () = default<br> |
|   | [**Extent3D**](#function-extent3d-23) (const [**Extent2D**](structExtent2D.md) & extent, double minz, double maxz) <br> |
|   | [**Extent3D**](#function-extent3d-33) (double minx, double maxx, double miny, double maxy, double minz, double maxz) <br> |
|  [**Coordinate3D**](classCoordinate3D.md)&lt; double &gt; | [**center**](#function-center) () const<br> |
|  void | [**grow**](#function-grow-13) (double x, double y, double z) <br> |
|  void | [**grow**](#function-grow-23) (double border) <br> |
|  void | [**grow**](#function-grow-33) (const [**Extent3D**](structExtent3D.md) & other) <br> |
|  [**Extent3D**](structExtent3D.md) | [**intersection**](#function-intersection) (const [**Extent3D**](structExtent3D.md) & other) const<br> |
|  bool | [**intersects**](#function-intersects) (const [**Extent3D**](structExtent3D.md) & other) const<br> |
|  double | [**max\_extent**](#function-max_extent) () const<br> |
|  bool | [**operator!=**](#function-operator) (const [**Extent3D**](structExtent3D.md) & other) const<br> |
|  [**Extent3D**](structExtent3D.md) | [**operator-**](#function-operator-) (const [**Coordinate3D**](classCoordinate3D.md)&lt; double &gt; & offset) const<br> |


## Public Functions inherited from Extent2D

See [Extent2D](structExtent2D.md)

| Type | Name |
| ---: | :--- |
|  double | [**area**](structExtent2D.md#function-area) () const<br> |
|  bool | [**contains**](structExtent2D.md#function-contains) (double x, double y) const<br> |
|  void | [**grow**](structExtent2D.md#function-grow) (const [**Extent2D**](structExtent2D.md) & other) <br> |
|  [**Extent2D**](structExtent2D.md) | [**intersection**](structExtent2D.md#function-intersection) (const [**Extent2D**](structExtent2D.md) & other) const<br> |
|  bool | [**overlaps**](structExtent2D.md#function-overlaps) (const [**Extent2D**](structExtent2D.md) & other) const<br> |






















































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
    const Extent2D & extent,
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
    const Extent3D & other
) 
```




<hr>



### function intersection 

```C++
inline Extent3D Extent3D::intersection (
    const Extent3D & other
) const
```




<hr>



### function intersects 

```C++
inline bool Extent3D::intersects (
    const Extent3D & other
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
    const Extent3D & other
) const
```




<hr>



### function operator- 

```C++
inline Extent3D Extent3D::operator- (
    const Coordinate3D < double > & offset
) const
```




<hr>## Friends Documentation





### friend operator&lt;&lt; 

```C++
inline std::ostream & Extent3D::operator<< (
    std::ostream & os,
    const Extent3D & extent
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/lib/utilities/coordinate.hpp`

