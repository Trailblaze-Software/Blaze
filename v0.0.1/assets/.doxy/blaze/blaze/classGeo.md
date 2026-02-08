

# Class Geo

**template &lt;[**typename**](classCoordinate2D.md) GridT&gt;**



[**ClassList**](annotated.md) **>** [**Geo**](classGeo.md)








Inherits the following classes: GridT,  [GeoGridData](classGeoGridData.md)


Inherited by the following classes: [TestGrid](classTestGrid.md),  [TestGrid](classTestGrid.md)




















































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**Geo**](#function-geo-12) ([**size\_t**](classCoordinate2D.md) width, [**size\_t**](classCoordinate2D.md) height, [**GeoTransform**](classGeoTransform.md) && transform, [**GeoProjection**](classGeoProjection.md) && projection) <br> |
|   | [**Geo**](#function-geo-22) ([**GeoTransform**](classGeoTransform.md) && transform, [**GeoProjection**](classGeoProjection.md) && projection, Args... args) <br> |
|  std::unique\_ptr&lt; [**Extent2D**](structExtent2D.md) &gt; | [**extent**](#function-extent) () const<br> |
|  [**void**](classCoordinate2D.md) | [**fill\_from**](#function-fill_from-12) ([**const**](classCoordinate2D.md) [**Geo**](classGeo.md)&lt; [**U**](classCoordinate2D.md) &gt; & other) <br> |
|  [**void**](classCoordinate2D.md) | [**fill\_from**](#function-fill_from-22) ([**const**](classCoordinate2D.md) [**U**](classCoordinate2D.md) & other) <br> |
|  [**double**](classCoordinate2D.md) | [**height\_m**](#function-height_m) () const<br> |
|  [**Geo**](classGeo.md) | [**slice**](#function-slice) ([**const**](classCoordinate2D.md) [**Extent2D**](structExtent2D.md) & extent) <br> |
|  [**double**](classCoordinate2D.md) | [**width\_m**](#function-width_m) () const<br> |


## Public Functions inherited from GeoGridData

See [GeoGridData](classGeoGridData.md)

| Type | Name |
| ---: | :--- |
|   | [**GeoGridData**](classGeoGridData.md#function-geogriddata) ([**GeoTransform**](classGeoTransform.md) && transform, [**GeoProjection**](classGeoProjection.md) && projection) <br> |
|  [**double**](classCoordinate2D.md) | [**dx**](classGeoGridData.md#function-dx) () const<br> |
|  [**double**](classCoordinate2D.md) | [**dy**](classGeoGridData.md#function-dy) () const<br> |
|  [**const**](classCoordinate2D.md) [**GeoProjection**](classGeoProjection.md) & | [**projection**](classGeoGridData.md#function-projection) () const<br> |
|  [**const**](classCoordinate2D.md) [**GeoTransform**](classGeoTransform.md) & | [**transform**](classGeoGridData.md#function-transform) () const<br> |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  [**Geo**](classGeo.md)&lt; [**Grid**](classGrid.md)&lt; [**RGBColor**](classRGBColor.md) &gt; &gt; | [**FromGeoImg**](#function-fromgeoimg) ([**const**](classCoordinate2D.md) [**GeoImgGrid**](classGeoImgGrid.md) & grid) <br> |
|  [**Geo**](classGeo.md) | [**FromPoints**](#function-frompoints) ([**const**](classCoordinate2D.md) [**Geo**](classGeo.md) & grid) <br> |














## Protected Attributes inherited from GeoGridData

See [GeoGridData](classGeoGridData.md)

| Type | Name |
| ---: | :--- |
|  [**GeoProjection**](classGeoProjection.md) | [**m\_projection**](classGeoGridData.md#variable-m_projection)  <br> |
|  [**GeoTransform**](classGeoTransform.md) | [**m\_transform**](classGeoGridData.md#variable-m_transform)  <br> |






































## Public Functions Documentation




### function Geo [1/2]

```C++
inline Geo::Geo (
    size_t width,
    size_t height,
    GeoTransform && transform,
    GeoProjection && projection
) 
```




<hr>



### function Geo [2/2]

```C++
template<typename... Args>
inline Geo::Geo (
    GeoTransform && transform,
    GeoProjection && projection,
    Args... args
) 
```




<hr>



### function extent 

```C++
std::unique_ptr< Extent2D > Geo::extent () const
```




<hr>



### function fill\_from [1/2]

```C++
template<typename  U>
inline void Geo::fill_from (
    const  Geo < U > & other
) 
```




<hr>



### function fill\_from [2/2]

```C++
template<typename  U>
inline void Geo::fill_from (
    const  U & other
) 
```




<hr>



### function height\_m 

```C++
inline double Geo::height_m () const
```




<hr>



### function slice 

```C++
Geo Geo::slice (
    const  Extent2D & extent
) 
```




<hr>



### function width\_m 

```C++
inline double Geo::width_m () const
```




<hr>
## Public Static Functions Documentation




### function FromGeoImg 

```C++
static Geo < Grid < RGBColor > > Geo::FromGeoImg (
    const  GeoImgGrid & grid
) 
```




<hr>



### function FromPoints 

```C++
template<typename  U>
static inline Geo Geo::FromPoints (
    const  Geo & grid
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/lib/grid/grid.hpp`

