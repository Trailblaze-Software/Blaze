

# Class LASData



[**ClassList**](annotated.md) **>** [**LASData**](classLASData.md)








Inherits the following classes: [LASFile](classLASFile.md)


Inherited by the following classes: [AsyncLASData](classAsyncLASData.md)




















































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**LASData**](#function-lasdata-13) (const [**Extent2D**](structExtent2D.md) & bounds, const [**GeoProjection**](classGeoProjection.md) & projection) <br> |
|   | [**LASData**](#function-lasdata-23) (const [**GeoGrid**](classGeo.md)&lt; T &gt; & grid) <br> |
|   | [**LASData**](#function-lasdata-33) (const fs::path & filename, [**ProgressTracker**](classProgressTracker.md) && progress\_tracker, bool skip\_reading\_points=false, std::optional&lt; [**Extent2D**](structExtent2D.md) &gt; bounds=std::nullopt, const std::string & override\_crs="") <br> |
|  void | [**adopt\_points**](#function-adopt_points) (blaze::memory\_tracker::LasVector&lt; [**LASPoint**](classLASPoint.md) &gt; && points) <br> |
|  auto | [**begin**](#function-begin) () <br> |
|  auto | [**end**](#function-end) () <br> |
|  void | [**extract\_borders**](#function-extract_borders) (const fs::path & tmp\_dir, double border\_width, [**ProgressTracker**](classProgressTracker.md) && progress\_tracker) const<br> |
|  void | [**insert**](#function-insert-12) (const [**LASPoint**](classLASPoint.md) & point) <br> |
|  void | [**insert**](#function-insert-22) (std::span&lt; const [**LASPoint**](classLASPoint.md) &gt; pts) <br> |
|  std::pair&lt; uint16\_t, uint16\_t &gt; | [**intensity\_range**](#function-intensity_range) () const<br> |
|  std::size\_t | [**n\_points**](#function-n_points) () const<br> |
|  const [**LASPoint**](classLASPoint.md) & | [**operator[]**](#function-operator) (std::size\_t i) const<br> |
|  [**LASPoint**](classLASPoint.md) & | [**operator[]**](#function-operator_1) (std::size\_t i) <br> |
|  std::span&lt; const [**LASPoint**](classLASPoint.md) &gt; | [**points**](#function-points) () const<br> |
|  void | [**push\_back**](#function-push_back) (const [**LASPoint**](classLASPoint.md) & point) <br> |
|  void | [**release\_points**](#function-release_points) () <br> |
|  blaze::memory\_tracker::LasVector&lt; [**LASPoint**](classLASPoint.md) &gt; | [**take\_points**](#function-take_points) () <br> |
|  void | [**write**](#function-write) (const fs::path & filename, [**ProgressTracker**](classProgressTracker.md) && progress\_tracker) const<br> |


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


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  [**LASData**](classLASData.md) | [**with\_border**](#function-with_border-12) (const fs::path & filename, double border\_width, const std::vector&lt; std::pair&lt; [**Extent3D**](structExtent3D.md), fs::path &gt; &gt; & all\_las\_file\_extents, [**ProgressTracker**](classProgressTracker.md) && progress\_tracker, const std::string & override\_crs="") <br> |
|  [**LASData**](classLASData.md) | [**with\_border**](#function-with_border-22) (const fs::path & filename, double border\_width, [**ProgressTracker**](classProgressTracker.md) && progress\_tracker, const std::string & override\_crs="") <br> |














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






























## Protected Functions

| Type | Name |
| ---: | :--- |
|  void | [**read\_points**](#function-read_points) (laspp::LASReader & reader, [**ProgressTracker**](classProgressTracker.md) && progress\_tracker, std::optional&lt; [**Extent2D**](structExtent2D.md) &gt; bounds=std::nullopt) <br> |


## Protected Functions inherited from LASFile

See [LASFile](classLASFile.md)

| Type | Name |
| ---: | :--- |
|  void | [**from\_las\_reader**](classLASFile.md#function-from_las_reader) (const laspp::LASReader & reader, const std::string & override\_crs="") <br> |






## Public Functions Documentation




### function LASData [1/3]

```C++
inline LASData::LASData (
    const Extent2D & bounds,
    const GeoProjection & projection
) 
```




<hr>



### function LASData [2/3]

```C++
template<typename T>
inline explicit LASData::LASData (
    const GeoGrid < T > & grid
) 
```




<hr>



### function LASData [3/3]

```C++
inline explicit LASData::LASData (
    const fs::path & filename,
    ProgressTracker && progress_tracker,
    bool skip_reading_points=false,
    std::optional< Extent2D > bounds=std::nullopt,
    const std::string & override_crs=""
) 
```




<hr>



### function adopt\_points 

```C++
inline void LASData::adopt_points (
    blaze::memory_tracker::LasVector< LASPoint > && points
) 
```




<hr>



### function begin 

```C++
inline auto LASData::begin () 
```




<hr>



### function end 

```C++
inline auto LASData::end () 
```




<hr>



### function extract\_borders 

```C++
inline void LASData::extract_borders (
    const fs::path & tmp_dir,
    double border_width,
    ProgressTracker && progress_tracker
) const
```




<hr>



### function insert [1/2]

```C++
inline void LASData::insert (
    const LASPoint & point
) 
```




<hr>



### function insert [2/2]

```C++
inline void LASData::insert (
    std::span< const LASPoint > pts
) 
```




<hr>



### function intensity\_range 

```C++
inline std::pair< uint16_t, uint16_t > LASData::intensity_range () const
```




<hr>



### function n\_points 

```C++
inline std::size_t LASData::n_points () const
```




<hr>



### function operator[] 

```C++
inline const LASPoint & LASData::operator[] (
    std::size_t i
) const
```




<hr>



### function operator[] 

```C++
inline LASPoint & LASData::operator[] (
    std::size_t i
) 
```




<hr>



### function points 

```C++
inline std::span< const LASPoint > LASData::points () const
```




<hr>



### function push\_back 

```C++
inline void LASData::push_back (
    const LASPoint & point
) 
```




<hr>



### function release\_points 

```C++
inline void LASData::release_points () 
```




<hr>



### function take\_points 

```C++
inline blaze::memory_tracker::LasVector< LASPoint > LASData::take_points () 
```




<hr>



### function write 

```C++
inline void LASData::write (
    const fs::path & filename,
    ProgressTracker && progress_tracker
) const
```




<hr>
## Public Static Functions Documentation




### function with\_border [1/2]

```C++
static inline LASData LASData::with_border (
    const fs::path & filename,
    double border_width,
    const std::vector< std::pair< Extent3D , fs::path > > & all_las_file_extents,
    ProgressTracker && progress_tracker,
    const std::string & override_crs=""
) 
```




<hr>



### function with\_border [2/2]

```C++
static inline LASData LASData::with_border (
    const fs::path & filename,
    double border_width,
    ProgressTracker && progress_tracker,
    const std::string & override_crs=""
) 
```




<hr>
## Protected Functions Documentation




### function read\_points 

```C++
inline void LASData::read_points (
    laspp::LASReader & reader,
    ProgressTracker && progress_tracker,
    std::optional< Extent2D > bounds=std::nullopt
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/lib/las/las_file.hpp`

