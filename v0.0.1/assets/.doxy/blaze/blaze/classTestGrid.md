

# Class TestGrid



[**ClassList**](annotated.md) **>** [**TestGrid**](classTestGrid.md)








Inherits the following classes: [Geo](classGeo.md),  [Geo](classGeo.md)


















































































































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**TestGrid**](#function-testgrid-12) ([**const**](classCoordinate2D.md) std::vector&lt; std::vector&lt; [**double**](classCoordinate2D.md) &gt; &gt; & data) <br> |
|   | [**TestGrid**](#function-testgrid-12) ([**const**](classCoordinate2D.md) std::vector&lt; std::vector&lt; [**double**](classCoordinate2D.md) &gt; &gt; & data) <br> |


## Public Functions inherited from Geo

See [Geo](classGeo.md)

| Type | Name |
| ---: | :--- |
|   | [**Geo**](classGeo.md#function-geo-12) ([**size\_t**](classCoordinate2D.md) width, [**size\_t**](classCoordinate2D.md) height, [**GeoTransform**](classGeoTransform.md) && transform, [**GeoProjection**](classGeoProjection.md) && projection) <br> |
|   | [**Geo**](classGeo.md#function-geo-22) ([**GeoTransform**](classGeoTransform.md) && transform, [**GeoProjection**](classGeoProjection.md) && projection, Args... args) <br> |
|  std::unique\_ptr&lt; [**Extent2D**](structExtent2D.md) &gt; | [**extent**](classGeo.md#function-extent) () const<br> |
|  [**void**](classCoordinate2D.md) | [**fill\_from**](classGeo.md#function-fill_from-12) ([**const**](classCoordinate2D.md) [**Geo**](classGeo.md)&lt; [**U**](classCoordinate2D.md) &gt; & other) <br> |
|  [**void**](classCoordinate2D.md) | [**fill\_from**](classGeo.md#function-fill_from-22) ([**const**](classCoordinate2D.md) [**U**](classCoordinate2D.md) & other) <br> |
|  [**double**](classCoordinate2D.md) | [**height\_m**](classGeo.md#function-height_m) () const<br> |
|  [**Geo**](classGeo.md) | [**slice**](classGeo.md#function-slice) ([**const**](classCoordinate2D.md) [**Extent2D**](structExtent2D.md) & extent) <br> |
|  [**double**](classCoordinate2D.md) | [**width\_m**](classGeo.md#function-width_m) () const<br> |


## Public Functions inherited from GeoGridData

See [GeoGridData](classGeoGridData.md)

| Type | Name |
| ---: | :--- |
|   | [**GeoGridData**](classGeoGridData.md#function-geogriddata) ([**GeoTransform**](classGeoTransform.md) && transform, [**GeoProjection**](classGeoProjection.md) && projection) <br> |
|  [**double**](classCoordinate2D.md) | [**dx**](classGeoGridData.md#function-dx) () const<br> |
|  [**double**](classCoordinate2D.md) | [**dy**](classGeoGridData.md#function-dy) () const<br> |
|  [**const**](classCoordinate2D.md) [**GeoProjection**](classGeoProjection.md) & | [**projection**](classGeoGridData.md#function-projection) () const<br> |
|  [**const**](classCoordinate2D.md) [**GeoTransform**](classGeoTransform.md) & | [**transform**](classGeoGridData.md#function-transform) () const<br> |


## Public Functions inherited from Geo

See [Geo](classGeo.md)

| Type | Name |
| ---: | :--- |
|   | [**Geo**](classGeo.md#function-geo-12) ([**size\_t**](classCoordinate2D.md) width, [**size\_t**](classCoordinate2D.md) height, [**GeoTransform**](classGeoTransform.md) && transform, [**GeoProjection**](classGeoProjection.md) && projection) <br> |
|   | [**Geo**](classGeo.md#function-geo-22) ([**GeoTransform**](classGeoTransform.md) && transform, [**GeoProjection**](classGeoProjection.md) && projection, Args... args) <br> |
|  std::unique\_ptr&lt; [**Extent2D**](structExtent2D.md) &gt; | [**extent**](classGeo.md#function-extent) () const<br> |
|  [**void**](classCoordinate2D.md) | [**fill\_from**](classGeo.md#function-fill_from-12) ([**const**](classCoordinate2D.md) [**Geo**](classGeo.md)&lt; [**U**](classCoordinate2D.md) &gt; & other) <br> |
|  [**void**](classCoordinate2D.md) | [**fill\_from**](classGeo.md#function-fill_from-22) ([**const**](classCoordinate2D.md) [**U**](classCoordinate2D.md) & other) <br> |
|  [**double**](classCoordinate2D.md) | [**height\_m**](classGeo.md#function-height_m) () const<br> |
|  [**Geo**](classGeo.md) | [**slice**](classGeo.md#function-slice) ([**const**](classCoordinate2D.md) [**Extent2D**](structExtent2D.md) & extent) <br> |
|  [**double**](classCoordinate2D.md) | [**width\_m**](classGeo.md#function-width_m) () const<br> |


## Public Functions inherited from GeoGridData

See [GeoGridData](classGeoGridData.md)

| Type | Name |
| ---: | :--- |
|   | [**GeoGridData**](classGeoGridData.md#function-geogriddata) ([**GeoTransform**](classGeoTransform.md) && transform, [**GeoProjection**](classGeoProjection.md) && projection) <br> |
|  [**double**](classCoordinate2D.md) | [**dx**](classGeoGridData.md#function-dx) () const<br> |
|  [**double**](classCoordinate2D.md) | [**dy**](classGeoGridData.md#function-dy) () const<br> |
|  [**const**](classCoordinate2D.md) [**GeoProjection**](classGeoProjection.md) & | [**projection**](classGeoGridData.md#function-projection) () const<br> |
|  [**const**](classCoordinate2D.md) [**GeoTransform**](classGeoTransform.md) & | [**transform**](classGeoGridData.md#function-transform) () const<br> |




## Public Static Functions inherited from Geo

See [Geo](classGeo.md)

| Type | Name |
| ---: | :--- |
|  [**Geo**](classGeo.md)&lt; [**Grid**](classGrid.md)&lt; [**RGBColor**](classRGBColor.md) &gt; &gt; | [**FromGeoImg**](classGeo.md#function-fromgeoimg) ([**const**](classCoordinate2D.md) [**GeoImgGrid**](classGeoImgGrid.md) & grid) <br> |
|  [**Geo**](classGeo.md) | [**FromPoints**](classGeo.md#function-frompoints) ([**const**](classCoordinate2D.md) [**Geo**](classGeo.md) & grid) <br> |




## Public Static Functions inherited from Geo

See [Geo](classGeo.md)

| Type | Name |
| ---: | :--- |
|  [**Geo**](classGeo.md)&lt; [**Grid**](classGrid.md)&lt; [**RGBColor**](classRGBColor.md) &gt; &gt; | [**FromGeoImg**](classGeo.md#function-fromgeoimg) ([**const**](classCoordinate2D.md) [**GeoImgGrid**](classGeoImgGrid.md) & grid) <br> |
|  [**Geo**](classGeo.md) | [**FromPoints**](classGeo.md#function-frompoints) ([**const**](classCoordinate2D.md) [**Geo**](classGeo.md) & grid) <br> |




























## Protected Attributes inherited from GeoGridData

See [GeoGridData](classGeoGridData.md)

| Type | Name |
| ---: | :--- |
|  [**GeoProjection**](classGeoProjection.md) | [**m\_projection**](classGeoGridData.md#variable-m_projection)  <br> |
|  [**GeoTransform**](classGeoTransform.md) | [**m\_transform**](classGeoGridData.md#variable-m_transform)  <br> |




## Protected Attributes inherited from GeoGridData

See [GeoGridData](classGeoGridData.md)

| Type | Name |
| ---: | :--- |
|  [**GeoProjection**](classGeoProjection.md) | [**m\_projection**](classGeoGridData.md#variable-m_projection)  <br> |
|  [**GeoTransform**](classGeoTransform.md) | [**m\_transform**](classGeoGridData.md#variable-m_transform)  <br> |




























































































## Public Functions Documentation




### function TestGrid [1/2]

```C++
inline explicit TestGrid::TestGrid (
    const std::vector< std::vector< double > > & data
) 
```




<hr>



### function TestGrid [1/2]

```C++
inline explicit TestGrid::TestGrid (
    const std::vector< std::vector< double > > & data
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/lib/contour/tests/test_contour_gen.cpp`

