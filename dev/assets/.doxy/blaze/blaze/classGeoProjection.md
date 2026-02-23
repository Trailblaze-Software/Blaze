

# Class GeoProjection



[**ClassList**](annotated.md) **>** [**GeoProjection**](classGeoProjection.md)










































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**GeoProjection**](#function-geoprojection-14) ([**const**](classCoordinate2D.md) std::string & projection) <br> |
|   | [**GeoProjection**](#function-geoprojection-24) () = default<br> |
|   | [**GeoProjection**](#function-geoprojection-34) ([**const**](classCoordinate2D.md) [**GeoProjection**](classGeoProjection.md) & other) = default<br> |
|   | [**GeoProjection**](#function-geoprojection-44) ([**GeoProjection**](classGeoProjection.md) && other) noexcept<br> |
|  [**GeoProjection**](classGeoProjection.md) & | [**operator=**](#function-operator) ([**const**](classCoordinate2D.md) [**GeoProjection**](classGeoProjection.md) & other) = default<br> |
|  [**GeoProjection**](classGeoProjection.md) & | [**operator=**](#function-operator_1) ([**GeoProjection**](classGeoProjection.md) && other) noexcept<br> |
|  [**const**](classCoordinate2D.md) std::string & | [**to\_string**](#function-to_string) () const<br> |




























## Public Functions Documentation




### function GeoProjection [1/4]

```C++
inline explicit GeoProjection::GeoProjection (
    const std::string & projection
) 
```




<hr>



### function GeoProjection [2/4]

```C++
GeoProjection::GeoProjection () = default
```




<hr>



### function GeoProjection [3/4]

```C++
GeoProjection::GeoProjection (
    const  GeoProjection & other
) = default
```




<hr>



### function GeoProjection [4/4]

```C++
GeoProjection::GeoProjection (
    GeoProjection && other
) noexcept
```




<hr>



### function operator= 

```C++
GeoProjection & GeoProjection::operator= (
    const  GeoProjection & other
) = default
```




<hr>



### function operator= 

```C++
GeoProjection & GeoProjection::operator= (
    GeoProjection && other
) noexcept
```




<hr>



### function to\_string 

```C++
inline const std::string & GeoProjection::to_string () const
```




<hr>

------------------------------
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/lib/grid/grid.hpp`

