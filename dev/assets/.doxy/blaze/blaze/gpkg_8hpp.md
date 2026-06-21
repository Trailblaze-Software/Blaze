

# File gpkg.hpp



[**FileList**](files.md) **>** [**io**](dir_65bc51589f8002bfcb72faf47ab41180.md) **>** [**gpkg.hpp**](gpkg_8hpp.md)

[Go to the source code of this file](gpkg_8hpp_source.md)



* `#include <cpl_error.h>`
* `#include <ogrsf_frmts.h>`
* `#include <algorithm>`
* `#include <functional>`
* `#include <iostream>`
* `#include <map>`
* `#include <string>`
* `#include <variant>`
* `#include <vector>`
* `#include "assert/assert.hpp"`
* `#include "assert/gdal_assert.hpp"`
* `#include "contour/contour.hpp"`
* `#include "gdal_priv.h"`
* `#include "io/gdal_init.hpp"`
* `#include "polyline/polyline.hpp"`
* `#include "utilities/filesystem.hpp"`
* `#include "utilities/progress_tracker.hpp"`
* `#include "utilities/timer.hpp"`















## Classes

| Type | Name |
| ---: | :--- |
| class | [**GDALDataset\_w**](classGDALDataset__w.md) <br> |
| class | [**GPKGWriter**](classGPKGWriter.md) <br> |






















## Public Functions

| Type | Name |
| ---: | :--- |
|  [**void**](classCoordinate2D.md) | [**combine\_gpkgs**](#function-combine_gpkgs) ([**const**](classCoordinate2D.md) std::vector&lt; fs::path &gt; & sources, [**const**](classCoordinate2D.md) fs::path & output, [**const**](classCoordinate2D.md) std::string & projection={}, [**ProgressTracker**](classProgressTracker.md) progress\_tracker=[**ProgressTracker**](classProgressTracker.md)()) <br> |
|  [**void**](classCoordinate2D.md) | [**copy\_gpkg\_feature**](#function-copy_gpkg_feature) ([**GDALDataset**](classCoordinate2D.md) \* dst, [**OGRLayer**](classCoordinate2D.md) \* src\_layer, [**OGRFeature**](classCoordinate2D.md) \* feature) <br> |
|  [**void**](classCoordinate2D.md) | [**copy\_gpkg\_layer**](#function-copy_gpkg_layer) ([**GDALDataset**](classCoordinate2D.md) \* dst, [**OGRLayer**](classCoordinate2D.md) \* src\_layer, [**const**](classCoordinate2D.md) std::function&lt; [**void**](classCoordinate2D.md)()&gt; & on\_feature\_copied={}) <br> |
|  [**void**](classCoordinate2D.md) | [**ensure\_dst\_layer\_fields**](#function-ensure_dst_layer_fields) ([**OGRLayer**](classCoordinate2D.md) \* dst\_layer, [**OGRFeatureDefn**](classCoordinate2D.md) \* src\_defn) <br> |
|  [**OGRLayer**](classCoordinate2D.md) \* | [**get\_or\_create\_dst\_layer**](#function-get_or_create_dst_layer) ([**GDALDataset**](classCoordinate2D.md) \* dst, [**OGRLayer**](classCoordinate2D.md) \* src\_layer, [**const**](classCoordinate2D.md) std::string & layer\_name, [**OGRwkbGeometryType**](classCoordinate2D.md) geom\_type) <br> |
|  [**size\_t**](classCoordinate2D.md) | [**gpkg\_feature\_count**](#function-gpkg_feature_count) ([**const**](classCoordinate2D.md) fs::path & path) <br> |
|  std::vector&lt; [**Contour**](classContour.md) &gt; | [**read\_gpkg**](#function-read_gpkg) ([**const**](classCoordinate2D.md) fs::path & filename) <br> |




























## Public Functions Documentation




### function combine\_gpkgs 

```C++
inline void combine_gpkgs (
    const std::vector< fs::path > & sources,
    const fs::path & output,
    const std::string & projection={},
    ProgressTracker progress_tracker=ProgressTracker ()
) 
```




<hr>



### function copy\_gpkg\_feature 

```C++
inline void copy_gpkg_feature (
    GDALDataset * dst,
    OGRLayer * src_layer,
    OGRFeature * feature
) 
```




<hr>



### function copy\_gpkg\_layer 

```C++
inline void copy_gpkg_layer (
    GDALDataset * dst,
    OGRLayer * src_layer,
    const std::function< void ()> & on_feature_copied={}
) 
```




<hr>



### function ensure\_dst\_layer\_fields 

```C++
inline void ensure_dst_layer_fields (
    OGRLayer * dst_layer,
    OGRFeatureDefn * src_defn
) 
```




<hr>



### function get\_or\_create\_dst\_layer 

```C++
inline OGRLayer * get_or_create_dst_layer (
    GDALDataset * dst,
    OGRLayer * src_layer,
    const std::string & layer_name,
    OGRwkbGeometryType geom_type
) 
```




<hr>



### function gpkg\_feature\_count 

```C++
inline size_t gpkg_feature_count (
    const fs::path & path
) 
```




<hr>



### function read\_gpkg 

```C++
inline std::vector< Contour > read_gpkg (
    const fs::path & filename
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/lib/io/gpkg.hpp`

