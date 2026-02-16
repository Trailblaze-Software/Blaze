

# Class GeoGridData



[**ClassList**](annotated.md) **>** [**GeoGridData**](classGeoGridData.md)










Inherited by the following classes: [Geo](classGeo.md),  [GeoImgGrid](classGeoImgGrid.md)
































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**GeoGridData**](#function-geogriddata) ([**GeoTransform**](classGeoTransform.md) && transform, [**GeoProjection**](classGeoProjection.md) && projection) <br> |
|  [**double**](classCoordinate2D.md) | [**dx**](#function-dx) () const<br> |
|  [**double**](classCoordinate2D.md) | [**dy**](#function-dy) () const<br> |
|  [**const**](classCoordinate2D.md) [**GeoProjection**](classGeoProjection.md) & | [**projection**](#function-projection) () const<br> |
|  [**const**](classCoordinate2D.md) [**GeoTransform**](classGeoTransform.md) & | [**transform**](#function-transform) () const<br> |








## Protected Attributes

| Type | Name |
| ---: | :--- |
|  [**GeoProjection**](classGeoProjection.md) | [**m\_projection**](#variable-m_projection)  <br> |
|  [**GeoTransform**](classGeoTransform.md) | [**m\_transform**](#variable-m_transform)  <br> |




















## Public Functions Documentation




### function GeoGridData 

```C++
inline GeoGridData::GeoGridData (
    GeoTransform && transform,
    GeoProjection && projection
) 
```




<hr>



### function dx 

```C++
inline double GeoGridData::dx () const
```




<hr>



### function dy 

```C++
inline double GeoGridData::dy () const
```




<hr>



### function projection 

```C++
inline const  GeoProjection & GeoGridData::projection () const
```




<hr>



### function transform 

```C++
inline const  GeoTransform & GeoGridData::transform () const
```




<hr>
## Protected Attributes Documentation




### variable m\_projection 

```C++
GeoProjection GeoGridData::m_projection;
```




<hr>



### variable m\_transform 

```C++
GeoTransform GeoGridData::m_transform;
```




<hr>

------------------------------
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/lib/grid/grid.hpp`

