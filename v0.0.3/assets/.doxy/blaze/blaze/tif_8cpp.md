

# File tif.cpp



[**FileList**](files.md) **>** [**lib**](dir_c85d3e3c5052e9ad9ce18c6863244a25.md) **>** [**tif**](dir_ca784dd9e8c063f2791dae69e4495085.md) **>** [**tif.cpp**](tif_8cpp.md)

[Go to the source code of this file](tif_8cpp_source.md)



* `#include "tif.hpp"`
* `#include <gdal.h>`
* `#include <optional>`
* `#include <type_traits>`
* `#include "assert/gdal_assert.hpp"`
* `#include "gdal_priv.h"`
* `#include "isom/colors.hpp"`
* `#include "utilities/timer.hpp"`















## Classes

| Type | Name |
| ---: | :--- |
| struct | [**is\_std\_optional**](structis__std__optional.md) &lt;[**typename**](classCoordinate2D.md) T&gt;<br> |
| struct | [**is\_std\_optional&lt; std::optional&lt; T &gt; &gt;**](structis__std__optional_3_01std_1_1optional_3_01T_01_4_01_4.md) &lt;[**typename**](classCoordinate2D.md) T&gt;<br> |






## Public Attributes

| Type | Name |
| ---: | :--- |
|  [**constexpr**](classCoordinate2D.md) [**bool**](classCoordinate2D.md) | [**is\_std\_optional\_v**](#variable-is_std_optional_v)   = `[**is\_std\_optional**](structis__std__optional.md)&lt;T&gt;::value`<br> |
















## Public Functions

| Type | Name |
| ---: | :--- |
|  [**constexpr**](classCoordinate2D.md) [**GDALDataType**](classCoordinate2D.md) | [**gdal\_type**](#function-gdal_type) () <br> |
|  [**Geo**](classGeo.md)&lt; [**MultiBand**](classMultiBand.md)&lt; [**FlexGrid**](classFlexGrid.md) &gt; &gt; | [**read\_tif**](#function-read_tif) ([**const**](classCoordinate2D.md) fs::path & filename) <br> |
|  [**void**](classCoordinate2D.md) | [**write\_to\_image\_tif**](#function-write_to_image_tif) ([**const**](classCoordinate2D.md) [**GeoGrid**](classGeo.md)&lt; T &gt; & grid, [**const**](classCoordinate2D.md) fs::path & filename, std::optional&lt; [**ProgressTracker**](classProgressTracker.md) &gt; progress\_tracker) <br> |
|  [**template**](classCoordinate2D.md) [**void**](classCoordinate2D.md) | [**write\_to\_image\_tif**](#function-write_to_image_tif) ([**const**](classCoordinate2D.md) [**GeoGrid**](classGeo.md)&lt; [**double**](classCoordinate2D.md) &gt; & grid, [**const**](classCoordinate2D.md) fs::path & filename, std::optional&lt; [**ProgressTracker**](classProgressTracker.md) &gt; progress\_tracker) <br> |
|  [**void**](classCoordinate2D.md) | [**write\_to\_tif**](#function-write_to_tif) ([**const**](classCoordinate2D.md) [**Geo**](classGeo.md)&lt; GridT &gt; & grid, [**const**](classCoordinate2D.md) fs::path & filename, std::optional&lt; [**ProgressTracker**](classProgressTracker.md) &gt; progress\_tracker) <br> |
|  [**template**](classCoordinate2D.md) [**void**](classCoordinate2D.md) | [**write\_to\_tif**](#function-write_to_tif) ([**const**](classCoordinate2D.md) [**GeoGrid**](classGeo.md)&lt; [**double**](classCoordinate2D.md) &gt; & grid, [**const**](classCoordinate2D.md) fs::path & filename, std::optional&lt; [**ProgressTracker**](classProgressTracker.md) &gt; progress\_tracker) <br> |
|  [**template**](classCoordinate2D.md) [**void**](classCoordinate2D.md) | [**write\_to\_tif**](#function-write_to_tif) ([**const**](classCoordinate2D.md) [**GeoGrid**](classGeo.md)&lt; [**float**](classCoordinate2D.md) &gt; & grid, [**const**](classCoordinate2D.md) fs::path & filename, std::optional&lt; [**ProgressTracker**](classProgressTracker.md) &gt; progress\_tracker) <br> |
|  [**template**](classCoordinate2D.md) [**void**](classCoordinate2D.md) | [**write\_to\_tif**](#function-write_to_tif) ([**const**](classCoordinate2D.md) [**GeoGrid**](classGeo.md)&lt; std::byte &gt; & grid, [**const**](classCoordinate2D.md) fs::path & filename, std::optional&lt; [**ProgressTracker**](classProgressTracker.md) &gt; progress\_tracker) <br> |
|  [**template**](classCoordinate2D.md) [**void**](classCoordinate2D.md) | [**write\_to\_tif**](#function-write_to_tif) ([**const**](classCoordinate2D.md) [**GeoGrid**](classGeo.md)&lt; [**RGBColor**](classRGBColor.md) &gt; & grid, [**const**](classCoordinate2D.md) fs::path & filename, std::optional&lt; [**ProgressTracker**](classProgressTracker.md) &gt; progress\_tracker) <br> |
|  [**template**](classCoordinate2D.md) [**void**](classCoordinate2D.md) | [**write\_to\_tif**](#function-write_to_tif) ([**const**](classCoordinate2D.md) [**GeoGrid**](classGeo.md)&lt; [**CMYKColor**](classCMYKColor.md) &gt; & grid, [**const**](classCoordinate2D.md) fs::path & filename, std::optional&lt; [**ProgressTracker**](classProgressTracker.md) &gt; progress\_tracker) <br> |
|  [**template**](classCoordinate2D.md) [**void**](classCoordinate2D.md) | [**write\_to\_tif**](#function-write_to_tif) ([**const**](classCoordinate2D.md) [**GeoGrid**](classGeo.md)&lt; std::optional&lt; std::byte &gt; &gt; & grid, [**const**](classCoordinate2D.md) fs::path & filename, std::optional&lt; [**ProgressTracker**](classProgressTracker.md) &gt; progress\_tracker) <br> |
|  [**template**](classCoordinate2D.md) [**void**](classCoordinate2D.md) | [**write\_to\_tif**](#function-write_to_tif) ([**const**](classCoordinate2D.md) [**GeoGrid**](classGeo.md)&lt; std::optional&lt; [**double**](classCoordinate2D.md) &gt; &gt; & grid, [**const**](classCoordinate2D.md) fs::path & filename, std::optional&lt; [**ProgressTracker**](classProgressTracker.md) &gt; progress\_tracker) <br> |
|  [**template**](classCoordinate2D.md) [**void**](classCoordinate2D.md) | [**write\_to\_tif**](#function-write_to_tif) ([**const**](classCoordinate2D.md) [**GeoGrid**](classGeo.md)&lt; std::optional&lt; [**float**](classCoordinate2D.md) &gt; &gt; & grid, [**const**](classCoordinate2D.md) fs::path & filename, std::optional&lt; [**ProgressTracker**](classProgressTracker.md) &gt; progress\_tracker) <br> |
|  [**template**](classCoordinate2D.md) [**void**](classCoordinate2D.md) | [**write\_to\_tif**](#function-write_to_tif) ([**const**](classCoordinate2D.md) [**Geo**](classGeo.md)&lt; [**MultiBand**](classMultiBand.md)&lt; [**FlexGrid**](classFlexGrid.md) &gt; &gt; & grid, [**const**](classCoordinate2D.md) fs::path & filename, std::optional&lt; [**ProgressTracker**](classProgressTracker.md) &gt; progress\_tracker) <br> |




























## Public Attributes Documentation




### variable is\_std\_optional\_v 

```C++
constexpr bool is_std_optional_v;
```




<hr>
## Public Functions Documentation




### function gdal\_type 

```C++
template<typename T>
constexpr  GDALDataType gdal_type () 
```




<hr>



### function read\_tif 

```C++
Geo < MultiBand < FlexGrid > > read_tif (
    const fs::path & filename
) 
```




<hr>



### function write\_to\_image\_tif 

```C++
template<typename T>
void write_to_image_tif (
    const  GeoGrid < T > & grid,
    const fs::path & filename,
    std::optional< ProgressTracker > progress_tracker
) 
```




<hr>



### function write\_to\_image\_tif 

```C++
template  void write_to_image_tif (
    const  GeoGrid < double > & grid,
    const fs::path & filename,
    std::optional< ProgressTracker > progress_tracker
) 
```




<hr>



### function write\_to\_tif 

```C++
template<typename GridT>
void write_to_tif (
    const  Geo < GridT > & grid,
    const fs::path & filename,
    std::optional< ProgressTracker > progress_tracker
) 
```




<hr>



### function write\_to\_tif 

```C++
template  void write_to_tif (
    const  GeoGrid < double > & grid,
    const fs::path & filename,
    std::optional< ProgressTracker > progress_tracker
) 
```




<hr>



### function write\_to\_tif 

```C++
template  void write_to_tif (
    const  GeoGrid < float > & grid,
    const fs::path & filename,
    std::optional< ProgressTracker > progress_tracker
) 
```




<hr>



### function write\_to\_tif 

```C++
template  void write_to_tif (
    const  GeoGrid < std::byte > & grid,
    const fs::path & filename,
    std::optional< ProgressTracker > progress_tracker
) 
```




<hr>



### function write\_to\_tif 

```C++
template  void write_to_tif (
    const  GeoGrid < RGBColor > & grid,
    const fs::path & filename,
    std::optional< ProgressTracker > progress_tracker
) 
```




<hr>



### function write\_to\_tif 

```C++
template  void write_to_tif (
    const  GeoGrid < CMYKColor > & grid,
    const fs::path & filename,
    std::optional< ProgressTracker > progress_tracker
) 
```




<hr>



### function write\_to\_tif 

```C++
template  void write_to_tif (
    const  GeoGrid < std::optional< std::byte > > & grid,
    const fs::path & filename,
    std::optional< ProgressTracker > progress_tracker
) 
```




<hr>



### function write\_to\_tif 

```C++
template  void write_to_tif (
    const  GeoGrid < std::optional< double > > & grid,
    const fs::path & filename,
    std::optional< ProgressTracker > progress_tracker
) 
```




<hr>



### function write\_to\_tif 

```C++
template  void write_to_tif (
    const  GeoGrid < std::optional< float > > & grid,
    const fs::path & filename,
    std::optional< ProgressTracker > progress_tracker
) 
```




<hr>



### function write\_to\_tif 

```C++
template  void write_to_tif (
    const  Geo < MultiBand < FlexGrid > > & grid,
    const fs::path & filename,
    std::optional< ProgressTracker > progress_tracker
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/lib/tif/tif.cpp`

