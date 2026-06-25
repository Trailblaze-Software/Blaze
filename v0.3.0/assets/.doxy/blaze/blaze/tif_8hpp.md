

# File tif.hpp



[**FileList**](files.md) **>** [**lib**](dir_c85d3e3c5052e9ad9ce18c6863244a25.md) **>** [**tif**](dir_ca784dd9e8c063f2791dae69e4495085.md) **>** [**tif.hpp**](tif_8hpp.md)

[Go to the source code of this file](tif_8hpp_source.md)



* `#include "lib/grid/grid.hpp"`
* `#include "utilities/filesystem.hpp"`
* `#include "utilities/progress_tracker.hpp"`





































## Public Functions

| Type | Name |
| ---: | :--- |
|  [**Geo**](classGeo.md)&lt; [**MultiBand**](classMultiBand.md)&lt; [**FlexGrid**](classFlexGrid.md) &gt; &gt; | [**read\_tif**](#function-read_tif) (const fs::path & filename, [**ProgressTracker**](classProgressTracker.md) \* progress\_tracker=nullptr) <br> |
|  void | [**write\_to\_image\_tif**](#function-write_to_image_tif) (const [**GeoGrid**](classGeo.md)&lt; T &gt; & grid, const fs::path & filename, std::optional&lt; [**ProgressTracker**](classProgressTracker.md) &gt; progress\_tracker={}, std::optional&lt; T &gt; min\_val={}, std::optional&lt; T &gt; max\_val={}) <br> |
|  void | [**write\_to\_tif**](#function-write_to_tif) (const [**Geo**](classGeo.md)&lt; GridT &gt; & grid, const fs::path & filename, std::optional&lt; [**ProgressTracker**](classProgressTracker.md) &gt; progress\_tracker={}, bool include\_vertical\_crs=false) <br> |




























## Public Functions Documentation




### function read\_tif 

```C++
Geo < MultiBand < FlexGrid > > read_tif (
    const fs::path & filename,
    ProgressTracker * progress_tracker=nullptr
) 
```




<hr>



### function write\_to\_image\_tif 

```C++
template<typename T>
void write_to_image_tif (
    const GeoGrid < T > & grid,
    const fs::path & filename,
    std::optional< ProgressTracker > progress_tracker={},
    std::optional< T > min_val={},
    std::optional< T > max_val={}
) 
```




<hr>



### function write\_to\_tif 

```C++
template<typename GridT>
void write_to_tif (
    const Geo < GridT > & grid,
    const fs::path & filename,
    std::optional< ProgressTracker > progress_tracker={},
    bool include_vertical_crs=false
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/lib/tif/tif.hpp`

