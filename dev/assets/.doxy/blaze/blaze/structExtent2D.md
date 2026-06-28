

# Struct Extent2D



[**ClassList**](annotated.md) **>** [**Extent2D**](structExtent2D.md)










Inherited by the following classes: [Extent3D](structExtent3D.md)
















## Public Attributes

| Type | Name |
| ---: | :--- |
|  double | [**maxx**](#variable-maxx)   = `-std::numeric\_limits&lt;double&gt;::infinity()`<br> |
|  double | [**maxy**](#variable-maxy)   = `-std::numeric\_limits&lt;double&gt;::infinity()`<br> |
|  double | [**minx**](#variable-minx)   = `std::numeric\_limits&lt;double&gt;::infinity()`<br> |
|  double | [**miny**](#variable-miny)   = `std::numeric\_limits&lt;double&gt;::infinity()`<br> |
















## Public Functions

| Type | Name |
| ---: | :--- |
|  double | [**area**](#function-area) () const<br> |
|  bool | [**contains**](#function-contains) (double x, double y) const<br> |
|  void | [**grow**](#function-grow) (const [**Extent2D**](structExtent2D.md) & other) <br> |
|  [**Extent2D**](structExtent2D.md) | [**intersection**](#function-intersection) (const [**Extent2D**](structExtent2D.md) & other) const<br> |
|  bool | [**overlaps**](#function-overlaps) (const [**Extent2D**](structExtent2D.md) & other) const<br> |




























## Public Attributes Documentation




### variable maxx 

```C++
double Extent2D::maxx;
```




<hr>



### variable maxy 

```C++
double Extent2D::maxy;
```




<hr>



### variable minx 

```C++
double Extent2D::minx;
```




<hr>



### variable miny 

```C++
double Extent2D::miny;
```




<hr>
## Public Functions Documentation




### function area 

```C++
inline double Extent2D::area () const
```




<hr>



### function contains 

```C++
inline bool Extent2D::contains (
    double x,
    double y
) const
```




<hr>



### function grow 

```C++
inline void Extent2D::grow (
    const Extent2D & other
) 
```




<hr>



### function intersection 

```C++
inline Extent2D Extent2D::intersection (
    const Extent2D & other
) const
```




<hr>



### function overlaps 

```C++
inline bool Extent2D::overlaps (
    const Extent2D & other
) const
```




<hr>## Friends Documentation





### friend operator&lt;&lt; 

```C++
inline std::ostream & Extent2D::operator<< (
    std::ostream & os,
    const Extent2D & extent
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/lib/utilities/coordinate.hpp`

