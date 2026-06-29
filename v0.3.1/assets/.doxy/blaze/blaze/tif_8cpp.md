

# File tif.cpp



[**FileList**](files.md) **>** [**lib**](dir_c85d3e3c5052e9ad9ce18c6863244a25.md) **>** [**tif**](dir_ca784dd9e8c063f2791dae69e4495085.md) **>** [**tif.cpp**](tif_8cpp.md)

[Go to the source code of this file](tif_8cpp_source.md)



* `#include "tif.hpp"`
* `#include <gdal.h>`
* `#include <algorithm>`
* `#include <optional>`
* `#include <type_traits>`
* `#include "assert/gdal_assert.hpp"`
* `#include "gdal_priv.h"`
* `#include "io/crs.hpp"`
* `#include "io/gdal_init.hpp"`
* `#include "isom/colors.hpp"`















## Classes

| Type | Name |
| ---: | :--- |
| struct | [**is\_std\_optional**](structis__std__optional.md) &lt;typename T&gt;<br> |
| struct | [**is\_std\_optional&lt; std::optional&lt; T &gt; &gt;**](structis__std__optional_3_01std_1_1optional_3_01T_01_4_01_4.md) &lt;typename T&gt;<br> |






## Public Attributes

| Type | Name |
| ---: | :--- |
|  constexpr bool | [**IS\_STD\_OPTIONAL\_V**](#variable-is_std_optional_v)   = `[**is\_std\_optional**](structis__std__optional.md)&lt;T&gt;::value`<br> |
















## Public Functions

| Type | Name |
| ---: | :--- |
|  constexpr GDALDataType | [**gdal\_type**](#function-gdal_type) () <br> |
|  [**Geo**](classGeo.md)&lt; [**MultiBand**](classMultiBand.md)&lt; [**FlexGrid**](classFlexGrid.md) &gt; &gt; | [**read\_tif**](#function-read_tif) (const fs::path & filename, [**ProgressTracker**](classProgressTracker.md) && progress\_tracker) <br> |
|  void | [**write\_to\_image\_tif**](#function-write_to_image_tif) (const [**GeoGrid**](classGeo.md)&lt; T &gt; & grid, const fs::path & filename, [**ProgressTracker**](classProgressTracker.md) && progress\_tracker, std::optional&lt; T &gt; min\_val, std::optional&lt; T &gt; max\_val) <br> |
|  template void | [**write\_to\_image\_tif**](#function-write_to_image_tif) (const [**GeoGrid**](classGeo.md)&lt; double &gt; & grid, const fs::path & filename, [**ProgressTracker**](classProgressTracker.md) && progress\_tracker, std::optional&lt; double &gt; min\_val, std::optional&lt; double &gt; max\_val) <br> |
|  void | [**write\_to\_tif**](#function-write_to_tif) (const [**Geo**](classGeo.md)&lt; GridT &gt; & grid, const fs::path & filename, [**ProgressTracker**](classProgressTracker.md) && progress\_tracker, const bool include\_vertical\_crs) <br> |
|  template void | [**write\_to\_tif**](#function-write_to_tif) (const [**GeoGrid**](classGeo.md)&lt; double &gt; & grid, const fs::path & filename, [**ProgressTracker**](classProgressTracker.md) && progress\_tracker, bool include\_vertical\_crs) <br> |
|  template void | [**write\_to\_tif**](#function-write_to_tif) (const [**GeoGrid**](classGeo.md)&lt; float &gt; & grid, const fs::path & filename, [**ProgressTracker**](classProgressTracker.md) && progress\_tracker, bool include\_vertical\_crs) <br> |
|  template void | [**write\_to\_tif**](#function-write_to_tif) (const [**GeoGrid**](classGeo.md)&lt; std::byte &gt; & grid, const fs::path & filename, [**ProgressTracker**](classProgressTracker.md) && progress\_tracker, bool include\_vertical\_crs) <br> |
|  template void | [**write\_to\_tif**](#function-write_to_tif) (const [**GeoGrid**](classGeo.md)&lt; [**RGBColor**](classRGBColor.md) &gt; & grid, const fs::path & filename, [**ProgressTracker**](classProgressTracker.md) && progress\_tracker, bool include\_vertical\_crs) <br> |
|  template void | [**write\_to\_tif**](#function-write_to_tif) (const [**GeoGrid**](classGeo.md)&lt; std::optional&lt; std::byte &gt; &gt; & grid, const fs::path & filename, [**ProgressTracker**](classProgressTracker.md) && progress\_tracker, bool include\_vertical\_crs) <br> |
|  template void | [**write\_to\_tif**](#function-write_to_tif) (const [**GeoGrid**](classGeo.md)&lt; std::optional&lt; double &gt; &gt; & grid, const fs::path & filename, [**ProgressTracker**](classProgressTracker.md) && progress\_tracker, bool include\_vertical\_crs) <br> |
|  template void | [**write\_to\_tif**](#function-write_to_tif) (const [**GeoGrid**](classGeo.md)&lt; std::optional&lt; float &gt; &gt; & grid, const fs::path & filename, [**ProgressTracker**](classProgressTracker.md) && progress\_tracker, bool include\_vertical\_crs) <br> |
|  template void | [**write\_to\_tif**](#function-write_to_tif) (const [**Geo**](classGeo.md)&lt; [**MultiBand**](classMultiBand.md)&lt; [**FlexGrid**](classFlexGrid.md) &gt; &gt; & grid, const fs::path & filename, [**ProgressTracker**](classProgressTracker.md) && progress\_tracker, bool include\_vertical\_crs) <br> |




























## Public Attributes Documentation




### variable IS\_STD\_OPTIONAL\_V 

```C++
constexpr bool IS_STD_OPTIONAL_V;
```




<hr>
## Public Functions Documentation




### function gdal\_type 

```C++
template<typename T>
constexpr GDALDataType gdal_type () 
```




<hr>



### function read\_tif 

```C++
Geo < MultiBand < FlexGrid > > read_tif (
    const fs::path & filename,
    ProgressTracker && progress_tracker
) 
```




<hr>



### function write\_to\_image\_tif 

```C++
template<typename T>
void write_to_image_tif (
    const GeoGrid < T > & grid,
    const fs::path & filename,
    ProgressTracker && progress_tracker,
    std::optional< T > min_val,
    std::optional< T > max_val
) 
```




<hr>



### function write\_to\_image\_tif 

```C++
template void write_to_image_tif (
    const GeoGrid < double > & grid,
    const fs::path & filename,
    ProgressTracker && progress_tracker,
    std::optional< double > min_val,
    std::optional< double > max_val
) 
```




<hr>



### function write\_to\_tif 

```C++
template<typename GridT>
void write_to_tif (
    const Geo < GridT > & grid,
    const fs::path & filename,
    ProgressTracker && progress_tracker,
    const bool include_vertical_crs
) 
```




<hr>



### function write\_to\_tif 

```C++
template void write_to_tif (
    const GeoGrid < double > & grid,
    const fs::path & filename,
    ProgressTracker && progress_tracker,
    bool include_vertical_crs
) 
```




<hr>



### function write\_to\_tif 

```C++
template void write_to_tif (
    const GeoGrid < float > & grid,
    const fs::path & filename,
    ProgressTracker && progress_tracker,
    bool include_vertical_crs
) 
```




<hr>



### function write\_to\_tif 

```C++
template void write_to_tif (
    const GeoGrid < std::byte > & grid,
    const fs::path & filename,
    ProgressTracker && progress_tracker,
    bool include_vertical_crs
) 
```




<hr>



### function write\_to\_tif 

```C++
template void write_to_tif (
    const GeoGrid < RGBColor > & grid,
    const fs::path & filename,
    ProgressTracker && progress_tracker,
    bool include_vertical_crs
) 
```




<hr>



### function write\_to\_tif 

```C++
template void write_to_tif (
    const GeoGrid < std::optional< std::byte > > & grid,
    const fs::path & filename,
    ProgressTracker && progress_tracker,
    bool include_vertical_crs
) 
```




<hr>



### function write\_to\_tif 

```C++
template void write_to_tif (
    const GeoGrid < std::optional< double > > & grid,
    const fs::path & filename,
    ProgressTracker && progress_tracker,
    bool include_vertical_crs
) 
```




<hr>



### function write\_to\_tif 

```C++
template void write_to_tif (
    const GeoGrid < std::optional< float > > & grid,
    const fs::path & filename,
    ProgressTracker && progress_tracker,
    bool include_vertical_crs
) 
```




<hr>



### function write\_to\_tif 

```C++
template void write_to_tif (
    const Geo < MultiBand < FlexGrid > > & grid,
    const fs::path & filename,
    ProgressTracker && progress_tracker,
    bool include_vertical_crs
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/lib/tif/tif.cpp`

