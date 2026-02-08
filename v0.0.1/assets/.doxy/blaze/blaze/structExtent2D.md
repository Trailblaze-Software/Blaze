

# Struct Extent2D



[**ClassList**](annotated.md) **>** [**Extent2D**](structExtent2D.md)










Inherited by the following classes: [Extent3D](structExtent3D.md)
















## Public Attributes

| Type | Name |
| ---: | :--- |
|  [**double**](classCoordinate2D.md) | [**maxx**](#variable-maxx)   = `-std::numeric\_limits&lt;[**double**](classCoordinate2D.md)&gt;[**::infinity**](classCoordinate2D.md)()`<br> |
|  [**double**](classCoordinate2D.md) | [**maxy**](#variable-maxy)   = `-std::numeric\_limits&lt;[**double**](classCoordinate2D.md)&gt;[**::infinity**](classCoordinate2D.md)()`<br> |
|  [**double**](classCoordinate2D.md) | [**minx**](#variable-minx)   = `std::numeric\_limits&lt;[**double**](classCoordinate2D.md)&gt;[**::infinity**](classCoordinate2D.md)()`<br> |
|  [**double**](classCoordinate2D.md) | [**miny**](#variable-miny)   = `std::numeric\_limits&lt;[**double**](classCoordinate2D.md)&gt;[**::infinity**](classCoordinate2D.md)()`<br> |
















## Public Functions

| Type | Name |
| ---: | :--- |
|  [**bool**](classCoordinate2D.md) | [**contains**](#function-contains) ([**double**](classCoordinate2D.md) x, [**double**](classCoordinate2D.md) y) const<br> |
|  [**void**](classCoordinate2D.md) | [**grow**](#function-grow) ([**const**](classCoordinate2D.md) [**Extent2D**](structExtent2D.md) & other) <br> |




























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
    const  Extent2D & other
) 
```




<hr>## Friends Documentation





### friend operator&lt;&lt; 

```C++
inline std::ostream & Extent2D::operator<< (
    std::ostream & os,
    const  Extent2D & extent
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/lib/utilities/coordinate.hpp`

