

# Class AsyncRasterData



[**ClassList**](annotated.md) **>** [**AsyncRasterData**](classAsyncRasterData.md)










































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**AsyncRasterData**](#function-asyncrasterdata) (const fs::path & dem\_path, [**AsyncProgressTracker**](classAsyncProgressTracker.md) async\_progress\_tracker, const std::optional&lt; fs::path &gt; & texture\_path=std::nullopt, int stride=1, bool slope\_colored=false, const std::optional&lt; fs::path &gt; & slope\_path=std::nullopt, std::function&lt; void()&gt; on\_ready={}, const std::string & target\_crs\_wkt={}, bool flat\_cells=false) <br> |
|  [**Extent3D**](structExtent3D.md) | [**extent**](#function-extent) () const<br> |
|  bool | [**has\_texture**](#function-has_texture) () const<br> |
|  const [**DemMeshData**](structDemMeshData.md) & | [**mesh**](#function-mesh) () const<br> |
|  std::mutex & | [**mutex**](#function-mutex) () const<br> |
|  const [**GeoProjection**](classGeoProjection.md) & | [**native\_projection**](#function-native_projection) () const<br> |
|  const [**GeoProjection**](classGeoProjection.md) & | [**projection**](#function-projection) () const<br> |
|  bool | [**ready**](#function-ready) () const<br> |
|  const [**Geo**](classGeo.md)&lt; [**MultiBand**](classMultiBand.md)&lt; [**FlexGrid**](classFlexGrid.md) &gt; &gt; & | [**texture\_grid**](#function-texture_grid) () const<br> |




























## Public Functions Documentation




### function AsyncRasterData 

```C++
inline AsyncRasterData::AsyncRasterData (
    const fs::path & dem_path,
    AsyncProgressTracker async_progress_tracker,
    const std::optional< fs::path > & texture_path=std::nullopt,
    int stride=1,
    bool slope_colored=false,
    const std::optional< fs::path > & slope_path=std::nullopt,
    std::function< void()> on_ready={},
    const std::string & target_crs_wkt={},
    bool flat_cells=false
) 
```




<hr>



### function extent 

```C++
inline Extent3D AsyncRasterData::extent () const
```




<hr>



### function has\_texture 

```C++
inline bool AsyncRasterData::has_texture () const
```




<hr>



### function mesh 

```C++
inline const DemMeshData & AsyncRasterData::mesh () const
```




<hr>



### function mutex 

```C++
inline std::mutex & AsyncRasterData::mutex () const
```




<hr>



### function native\_projection 

```C++
inline const GeoProjection & AsyncRasterData::native_projection () const
```




<hr>



### function projection 

```C++
inline const GeoProjection & AsyncRasterData::projection () const
```




<hr>



### function ready 

```C++
inline bool AsyncRasterData::ready () const
```




<hr>



### function texture\_grid 

```C++
inline const Geo < MultiBand < FlexGrid > > & AsyncRasterData::texture_grid () const
```




<hr>

------------------------------
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/gui/raster_data.hpp`

