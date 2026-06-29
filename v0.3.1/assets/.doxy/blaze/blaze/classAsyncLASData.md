

# Class AsyncLASData



[**ClassList**](annotated.md) **>** [**AsyncLASData**](classAsyncLASData.md)








Inherits the following classes: [LASData](classLASData.md)










































































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**AsyncLASData**](#function-asynclasdata) (const fs::path & filename, [**AsyncProgressTracker**](classAsyncProgressTracker.md) progress\_tracker, std::vector&lt; std::function&lt; void()&gt; &gt; callbacks={}) <br> |
|  bool | [**data\_ready**](#function-data_ready) () <br> |
|  std::mutex & | [**mutex**](#function-mutex) () <br> |
|  void | [**wait\_for\_data**](#function-wait_for_data) () <br> |
|   | [**~AsyncLASData**](#function-asynclasdata) () <br> |


## Public Functions inherited from LASData

See [LASData](classLASData.md)

| Type | Name |
| ---: | :--- |
|   | [**LASData**](classLASData.md#function-lasdata-13) (const [**Extent2D**](structExtent2D.md) & bounds, const [**GeoProjection**](classGeoProjection.md) & projection) <br> |
|   | [**LASData**](classLASData.md#function-lasdata-23) (const [**GeoGrid**](classGeo.md)&lt; T &gt; & grid) <br> |
|   | [**LASData**](classLASData.md#function-lasdata-33) (const fs::path & filename, [**ProgressTracker**](classProgressTracker.md) && progress\_tracker, bool skip\_reading\_points=false, std::optional&lt; [**Extent2D**](structExtent2D.md) &gt; bounds=std::nullopt, const std::string & override\_crs="") <br> |
|  void | [**adopt\_points**](classLASData.md#function-adopt_points) (blaze::memory\_tracker::LasVector&lt; [**LASPoint**](classLASPoint.md) &gt; && points) <br> |
|  auto | [**begin**](classLASData.md#function-begin) () <br> |
|  auto | [**end**](classLASData.md#function-end) () <br> |
|  void | [**extract\_borders**](classLASData.md#function-extract_borders) (const fs::path & tmp\_dir, double border\_width, [**ProgressTracker**](classProgressTracker.md) && progress\_tracker) const<br> |
|  void | [**insert**](classLASData.md#function-insert-12) (const [**LASPoint**](classLASPoint.md) & point) <br> |
|  void | [**insert**](classLASData.md#function-insert-22) (std::span&lt; const [**LASPoint**](classLASPoint.md) &gt; pts) <br> |
|  std::pair&lt; uint16\_t, uint16\_t &gt; | [**intensity\_range**](classLASData.md#function-intensity_range) () const<br> |
|  std::size\_t | [**n\_points**](classLASData.md#function-n_points) () const<br> |
|  const [**LASPoint**](classLASPoint.md) & | [**operator[]**](classLASData.md#function-operator) (std::size\_t i) const<br> |
|  [**LASPoint**](classLASPoint.md) & | [**operator[]**](classLASData.md#function-operator_1) (std::size\_t i) <br> |
|  std::span&lt; const [**LASPoint**](classLASPoint.md) &gt; | [**points**](classLASData.md#function-points) () const<br> |
|  void | [**push\_back**](classLASData.md#function-push_back) (const [**LASPoint**](classLASPoint.md) & point) <br> |
|  void | [**release\_points**](classLASData.md#function-release_points) () <br> |
|  blaze::memory\_tracker::LasVector&lt; [**LASPoint**](classLASPoint.md) &gt; | [**take\_points**](classLASData.md#function-take_points) () <br> |
|  void | [**write**](classLASData.md#function-write) (const fs::path & filename, [**ProgressTracker**](classProgressTracker.md) && progress\_tracker) const<br> |


## Public Functions inherited from LASFile

See [LASFile](classLASFile.md)

| Type | Name |
| ---: | :--- |
|   | [**LASFile**](classLASFile.md#function-lasfile-12) (const [**Extent2D**](structExtent2D.md) & bounds, [**GeoProjection**](classGeoProjection.md) && projection) <br> |
|   | [**LASFile**](classLASFile.md#function-lasfile-22) (const fs::path & filename, [**ProgressTracker**](classProgressTracker.md) && progress\_tracker, const std::string & override\_crs="") <br> |
|  const [**Extent3D**](structExtent3D.md) & | [**bounds**](classLASFile.md#function-bounds) () const<br> |
|  [**Extent2D**](structExtent2D.md) | [**export\_bounds**](classLASFile.md#function-export_bounds) () const<br> |
|  std::size\_t | [**header\_point\_count**](classLASFile.md#function-header_point_count) () const<br> |
|  double | [**height**](classLASFile.md#function-height) () const<br> |
|  std::pair&lt; double, double &gt; | [**height\_range**](classLASFile.md#function-height_range) () const<br> |
|  [**Extent2D**](structExtent2D.md) | [**original\_bounds**](classLASFile.md#function-original_bounds) () const<br> |
|  const [**GeoProjection**](classGeoProjection.md) & | [**projection**](classLASFile.md#function-projection) () const<br> |
|  void | [**set\_bounds**](classLASFile.md#function-set_bounds) (const [**Extent2D**](structExtent2D.md) & bounds, std::optional&lt; [**Extent2D**](structExtent2D.md) &gt; tile\_core=std::nullopt) <br> |
|  [**Coordinate2D**](classCoordinate2D.md)&lt; double &gt; | [**top\_left**](classLASFile.md#function-top_left) () const<br> |
|  double | [**width**](classLASFile.md#function-width) () const<br> |




## Public Static Functions inherited from LASData

See [LASData](classLASData.md)

| Type | Name |
| ---: | :--- |
|  [**LASData**](classLASData.md) | [**with\_border**](classLASData.md#function-with_border-12) (const fs::path & filename, double border\_width, const std::vector&lt; std::pair&lt; [**Extent3D**](structExtent3D.md), fs::path &gt; &gt; & all\_las\_file\_extents, [**ProgressTracker**](classProgressTracker.md) && progress\_tracker, const std::string & override\_crs="") <br> |
|  [**LASData**](classLASData.md) | [**with\_border**](classLASData.md#function-with_border-22) (const fs::path & filename, double border\_width, [**ProgressTracker**](classProgressTracker.md) && progress\_tracker, const std::string & override\_crs="") <br> |




















## Protected Attributes inherited from LASFile

See [LASFile](classLASFile.md)

| Type | Name |
| ---: | :--- |
|  [**Extent3D**](structExtent3D.md) | [**m\_bounds**](classLASFile.md#variable-m_bounds)  <br> |
|  std::optional&lt; fs::path &gt; | [**m\_filename**](classLASFile.md#variable-m_filename)  <br> |
|  std::size\_t | [**m\_header\_point\_count**](classLASFile.md#variable-m_header_point_count)   = `0`<br> |
|  [**Extent3D**](structExtent3D.md) | [**m\_original\_bounds**](classLASFile.md#variable-m_original_bounds)  <br> |
|  [**GeoProjection**](classGeoProjection.md) | [**m\_projection**](classLASFile.md#variable-m_projection)  <br> |
|  laspp::QuadtreeSpatialIndex | [**m\_spatial\_index**](classLASFile.md#variable-m_spatial_index)  <br> |














































## Protected Functions inherited from LASData

See [LASData](classLASData.md)

| Type | Name |
| ---: | :--- |
|  void | [**read\_points**](classLASData.md#function-read_points) (laspp::LASReader & reader, [**ProgressTracker**](classProgressTracker.md) && progress\_tracker, std::optional&lt; [**Extent2D**](structExtent2D.md) &gt; bounds=std::nullopt) <br> |


## Protected Functions inherited from LASFile

See [LASFile](classLASFile.md)

| Type | Name |
| ---: | :--- |
|  void | [**from\_las\_reader**](classLASFile.md#function-from_las_reader) (const laspp::LASReader & reader, const std::string & override\_crs="") <br> |








## Public Functions Documentation




### function AsyncLASData 

```C++
inline AsyncLASData::AsyncLASData (
    const fs::path & filename,
    AsyncProgressTracker progress_tracker,
    std::vector< std::function< void()> > callbacks={}
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

