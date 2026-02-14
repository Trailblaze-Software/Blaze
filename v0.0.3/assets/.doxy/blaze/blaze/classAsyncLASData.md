

# Class AsyncLASData



[**ClassList**](annotated.md) **>** [**AsyncLASData**](classAsyncLASData.md)








Inherits the following classes: [LASData](classLASData.md)










































































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**AsyncLASData**](#function-asynclasdata) ([**const**](classCoordinate2D.md) fs::path & filename, [**AsyncProgressTracker**](classAsyncProgressTracker.md) progress\_tracker, std::vector&lt; std::function&lt; [**void**](classCoordinate2D.md)()&gt; &gt; callbacks={}) <br> |
|  [**bool**](classCoordinate2D.md) | [**data\_ready**](#function-data_ready) () <br> |
|  std::mutex & | [**mutex**](#function-mutex) () <br> |
|  [**void**](classCoordinate2D.md) | [**wait\_for\_data**](#function-wait_for_data) () <br> |
|   | [**~AsyncLASData**](#function-asynclasdata) () <br> |


## Public Functions inherited from LASData

See [LASData](classLASData.md)

| Type | Name |
| ---: | :--- |
|   | [**LASData**](classLASData.md#function-lasdata-13) ([**const**](classCoordinate2D.md) [**Extent2D**](structExtent2D.md) & bounds, [**const**](classCoordinate2D.md) [**GeoProjection**](classGeoProjection.md) & projection) <br> |
|   | [**LASData**](classLASData.md#function-lasdata-23) ([**const**](classCoordinate2D.md) [**GeoGrid**](classGeo.md)&lt; T &gt; & grid) <br> |
|   | [**LASData**](classLASData.md#function-lasdata-33) ([**const**](classCoordinate2D.md) fs::path & filename, [**ProgressTracker**](classProgressTracker.md) progress\_tracker, [**bool**](classCoordinate2D.md) skip\_reading\_points=[**false**](classCoordinate2D.md), std::optional&lt; [**Extent2D**](structExtent2D.md) &gt; bounds=std::nullopt) <br> |
|  [**auto**](classCoordinate2D.md) | [**begin**](classLASData.md#function-begin) () <br> |
|  [**auto**](classCoordinate2D.md) | [**end**](classLASData.md#function-end) () <br> |
|  [**void**](classCoordinate2D.md) | [**extract\_borders**](classLASData.md#function-extract_borders) ([**const**](classCoordinate2D.md) fs::path & tmp\_dir, [**double**](classCoordinate2D.md) border\_width, [**ProgressTracker**](classProgressTracker.md) progress\_tracker) const<br> |
|  [**void**](classCoordinate2D.md) | [**insert**](classLASData.md#function-insert) ([**const**](classCoordinate2D.md) [**LASPoint**](classLASPoint.md) & point) <br> |
|  std::pair&lt; [**uint16\_t**](classCoordinate2D.md), [**uint16\_t**](classCoordinate2D.md) &gt; | [**intensity\_range**](classLASData.md#function-intensity_range) () const<br> |
|  std::size\_t | [**n\_points**](classLASData.md#function-n_points) () const<br> |
|  [**const**](classCoordinate2D.md) [**LASPoint**](classLASPoint.md) & | [**operator[]**](classLASData.md#function-operator) (std::size\_t i) const<br> |
|  [**LASPoint**](classLASPoint.md) & | [**operator[]**](classLASData.md#function-operator_1) (std::size\_t i) <br> |
|  [**void**](classCoordinate2D.md) | [**push\_back**](classLASData.md#function-push_back) ([**const**](classCoordinate2D.md) [**LASPoint**](classLASPoint.md) & point) <br> |
|  [**void**](classCoordinate2D.md) | [**write**](classLASData.md#function-write) ([**const**](classCoordinate2D.md) fs::path & filename, std::optional&lt; [**ProgressTracker**](classProgressTracker.md) &gt; progress\_tracker={}) const<br> |


## Public Functions inherited from LASFile

See [LASFile](classLASFile.md)

| Type | Name |
| ---: | :--- |
|   | [**LASFile**](classLASFile.md#function-lasfile-12) ([**const**](classCoordinate2D.md) [**Extent2D**](structExtent2D.md) & bounds, [**GeoProjection**](classGeoProjection.md) && projection) <br> |
|   | [**LASFile**](classLASFile.md#function-lasfile-22) ([**const**](classCoordinate2D.md) fs::path & filename, [**ProgressTracker**](classProgressTracker.md) progress\_tracker) <br> |
|  [**const**](classCoordinate2D.md) [**Extent3D**](structExtent3D.md) & | [**bounds**](classLASFile.md#function-bounds) () const<br> |
|  [**Extent2D**](structExtent2D.md) | [**export\_bounds**](classLASFile.md#function-export_bounds) () const<br> |
|  [**double**](classCoordinate2D.md) | [**height**](classLASFile.md#function-height) () const<br> |
|  std::pair&lt; [**double**](classCoordinate2D.md), [**double**](classCoordinate2D.md) &gt; | [**height\_range**](classLASFile.md#function-height_range) () const<br> |
|  [**Extent2D**](structExtent2D.md) | [**original\_bounds**](classLASFile.md#function-original_bounds) () const<br> |
|  [**const**](classCoordinate2D.md) [**GeoProjection**](classGeoProjection.md) & | [**projection**](classLASFile.md#function-projection) () const<br> |
|  [**Coordinate2D**](classCoordinate2D.md)&lt; [**double**](classCoordinate2D.md) &gt; | [**top\_left**](classLASFile.md#function-top_left) () const<br> |
|  [**double**](classCoordinate2D.md) | [**width**](classLASFile.md#function-width) () const<br> |




## Public Static Functions inherited from LASData

See [LASData](classLASData.md)

| Type | Name |
| ---: | :--- |
|  [**LASData**](classLASData.md) | [**with\_border**](classLASData.md#function-with_border-12) ([**const**](classCoordinate2D.md) fs::path & filename, [**double**](classCoordinate2D.md) border\_width, [**const**](classCoordinate2D.md) std::vector&lt; std::pair&lt; [**Extent3D**](structExtent3D.md), fs::path &gt; &gt; & all\_las\_file\_extents, [**ProgressTracker**](classProgressTracker.md) progress\_tracker) <br> |
|  [**LASData**](classLASData.md) | [**with\_border**](classLASData.md#function-with_border-22) ([**const**](classCoordinate2D.md) fs::path & filename, [**double**](classCoordinate2D.md) border\_width, [**ProgressTracker**](classProgressTracker.md) progress\_tracker) <br> |




















## Protected Attributes inherited from LASFile

See [LASFile](classLASFile.md)

| Type | Name |
| ---: | :--- |
|  [**Extent3D**](structExtent3D.md) | [**m\_bounds**](classLASFile.md#variable-m_bounds)  <br> |
|  std::optional&lt; fs::path &gt; | [**m\_filename**](classLASFile.md#variable-m_filename)  <br> |
|  [**Extent3D**](structExtent3D.md) | [**m\_original\_bounds**](classLASFile.md#variable-m_original_bounds)  <br> |
|  [**GeoProjection**](classGeoProjection.md) | [**m\_projection**](classLASFile.md#variable-m_projection)  <br> |
|  laspp::QuadtreeSpatialIndex | [**m\_spatial\_index**](classLASFile.md#variable-m_spatial_index)  <br> |














































## Protected Functions inherited from LASData

See [LASData](classLASData.md)

| Type | Name |
| ---: | :--- |
|  [**void**](classCoordinate2D.md) | [**read\_points**](classLASData.md#function-read_points) (laspp::LASReader & reader, [**ProgressTracker**](classProgressTracker.md) progress\_tracker, std::optional&lt; [**Extent2D**](structExtent2D.md) &gt; bounds=std::nullopt) <br> |


## Protected Functions inherited from LASFile

See [LASFile](classLASFile.md)

| Type | Name |
| ---: | :--- |
|  [**void**](classCoordinate2D.md) | [**from\_las\_reader**](classLASFile.md#function-from_las_reader) ([**const**](classCoordinate2D.md) laspp::LASReader & reader) <br> |








## Public Functions Documentation




### function AsyncLASData 

```C++
inline AsyncLASData::AsyncLASData (
    const fs::path & filename,
    AsyncProgressTracker progress_tracker,
    std::vector< std::function< void ()> > callbacks={}
) 
```




<hr>



### function data\_ready 

```C++
inline bool AsyncLASData::data_ready () 
```




<hr>



### function mutex 

```C++
inline std::mutex & AsyncLASData::mutex () 
```




<hr>



### function wait\_for\_data 

```C++
inline void AsyncLASData::wait_for_data () 
```




<hr>



### function ~AsyncLASData 

```C++
inline AsyncLASData::~AsyncLASData () 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/lib/las/las_file.hpp`

