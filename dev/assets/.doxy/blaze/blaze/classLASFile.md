

# Class LASFile



[**ClassList**](annotated.md) **>** [**LASFile**](classLASFile.md)










Inherited by the following classes: [LASData](classLASData.md)
































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**LASFile**](#function-lasfile-12) (const [**Extent2D**](structExtent2D.md) & bounds, [**GeoProjection**](classGeoProjection.md) && projection) <br> |
|   | [**LASFile**](#function-lasfile-22) (const fs::path & filename, [**ProgressTracker**](classProgressTracker.md) progress\_tracker, const std::string & override\_crs="") <br> |
|  const [**Extent3D**](structExtent3D.md) & | [**bounds**](#function-bounds) () const<br> |
|  [**Extent2D**](structExtent2D.md) | [**export\_bounds**](#function-export_bounds) () const<br> |
|  double | [**height**](#function-height) () const<br> |
|  std::pair&lt; double, double &gt; | [**height\_range**](#function-height_range) () const<br> |
|  [**Extent2D**](structExtent2D.md) | [**original\_bounds**](#function-original_bounds) () const<br> |
|  const [**GeoProjection**](classGeoProjection.md) & | [**projection**](#function-projection) () const<br> |
|  void | [**set\_bounds**](#function-set_bounds) (const [**Extent2D**](structExtent2D.md) & bounds, std::optional&lt; [**Extent2D**](structExtent2D.md) &gt; tile\_core=std::nullopt) <br> |
|  [**Coordinate2D**](classCoordinate2D.md)&lt; double &gt; | [**top\_left**](#function-top_left) () const<br> |
|  double | [**width**](#function-width) () const<br> |








## Protected Attributes

| Type | Name |
| ---: | :--- |
|  [**Extent3D**](structExtent3D.md) | [**m\_bounds**](#variable-m_bounds)  <br> |
|  std::optional&lt; fs::path &gt; | [**m\_filename**](#variable-m_filename)  <br> |
|  [**Extent3D**](structExtent3D.md) | [**m\_original\_bounds**](#variable-m_original_bounds)  <br> |
|  [**GeoProjection**](classGeoProjection.md) | [**m\_projection**](#variable-m_projection)  <br> |
|  laspp::QuadtreeSpatialIndex | [**m\_spatial\_index**](#variable-m_spatial_index)  <br> |
















## Protected Functions

| Type | Name |
| ---: | :--- |
|  void | [**from\_las\_reader**](#function-from_las_reader) (const laspp::LASReader & reader, const std::string & override\_crs="") <br> |




## Public Functions Documentation




### function LASFile [1/2]

```C++
inline explicit LASFile::LASFile (
    const Extent2D & bounds,
    GeoProjection && projection
) 
```




<hr>



### function LASFile [2/2]

```C++
inline explicit LASFile::LASFile (
    const fs::path & filename,
    ProgressTracker progress_tracker,
    const std::string & override_crs=""
) 
```




<hr>



### function bounds 

```C++
inline const Extent3D & LASFile::bounds () const
```




<hr>



### function export\_bounds 

```C++
inline Extent2D LASFile::export_bounds () const
```




<hr>



### function height 

```C++
inline double LASFile::height () const
```




<hr>



### function height\_range 

```C++
inline std::pair< double, double > LASFile::height_range () const
```




<hr>



### function original\_bounds 

```C++
inline Extent2D LASFile::original_bounds () const
```




<hr>



### function projection 

```C++
inline const GeoProjection & LASFile::projection () const
```




<hr>



### function set\_bounds 

```C++
inline void LASFile::set_bounds (
    const Extent2D & bounds,
    std::optional< Extent2D > tile_core=std::nullopt
) 
```




<hr>



### function top\_left 

```C++
inline Coordinate2D < double > LASFile::top_left () const
```




<hr>



### function width 

```C++
inline double LASFile::width () const
```




<hr>
## Protected Attributes Documentation




### variable m\_bounds 

```C++
Extent3D LASFile::m_bounds;
```




<hr>



### variable m\_filename 

```C++
std::optional<fs::path> LASFile::m_filename;
```




<hr>



### variable m\_original\_bounds 

```C++
Extent3D LASFile::m_original_bounds;
```




<hr>



### variable m\_projection 

```C++
GeoProjection LASFile::m_projection;
```




<hr>



### variable m\_spatial\_index 

```C++
laspp::QuadtreeSpatialIndex LASFile::m_spatial_index;
```




<hr>
## Protected Functions Documentation




### function from\_las\_reader 

```C++
inline void LASFile::from_las_reader (
    const laspp::LASReader & reader,
    const std::string & override_crs=""
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/lib/las/las_file.hpp`

