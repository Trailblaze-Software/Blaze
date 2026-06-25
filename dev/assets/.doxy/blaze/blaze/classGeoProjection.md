

# Class GeoProjection



[**ClassList**](annotated.md) **>** [**GeoProjection**](classGeoProjection.md)










































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**GeoProjection**](#function-geoprojection-15) (const std::string & projection) <br> |
|   | [**GeoProjection**](#function-geoprojection-25) (const std::string & horizontal\_projection, const std::string & compound\_wkt) <br> |
|   | [**GeoProjection**](#function-geoprojection-35) () = default<br> |
|   | [**GeoProjection**](#function-geoprojection-45) (const [**GeoProjection**](classGeoProjection.md) & other) = default<br> |
|   | [**GeoProjection**](#function-geoprojection-55) ([**GeoProjection**](classGeoProjection.md) && other) noexcept<br> |
|  const std::string & | [**compound\_wkt**](#function-compound_wkt) () const<br> |
|  bool | [**has\_vertical**](#function-has_vertical) () const<br> |
|  [**GeoProjection**](classGeoProjection.md) & | [**operator=**](#function-operator) (const [**GeoProjection**](classGeoProjection.md) & other) = default<br> |
|  [**GeoProjection**](classGeoProjection.md) & | [**operator=**](#function-operator_1) ([**GeoProjection**](classGeoProjection.md) && other) noexcept<br> |
|  const std::string & | [**to\_string**](#function-to_string) () const<br> |




























## Public Functions Documentation




### function GeoProjection [1/5]

```C++
inline explicit GeoProjection::GeoProjection (
    const std::string & projection
) 
```




<hr>



### function GeoProjection [2/5]

```C++
inline GeoProjection::GeoProjection (
    const std::string & horizontal_projection,
    const std::string & compound_wkt
) 
```




<hr>



### function GeoProjection [3/5]

```C++
GeoProjection::GeoProjection () = default
```




<hr>



### function GeoProjection [4/5]

```C++
GeoProjection::GeoProjection (
    const GeoProjection & other
) = default
```




<hr>



### function GeoProjection [5/5]

```C++
GeoProjection::GeoProjection (
    GeoProjection && other
) noexcept
```




<hr>



### function compound\_wkt 

```C++
inline const std::string & GeoProjection::compound_wkt () const
```




<hr>



### function has\_vertical 

```C++
inline bool GeoProjection::has_vertical () const
```




<hr>



### function operator= 

```C++
GeoProjection & GeoProjection::operator= (
    const GeoProjection & other
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

