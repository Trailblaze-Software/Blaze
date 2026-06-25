

# File crs.hpp



[**FileList**](files.md) **>** [**io**](dir_65bc51589f8002bfcb72faf47ab41180.md) **>** [**crs.hpp**](crs_8hpp.md)

[Go to the source code of this file](crs_8hpp_source.md)



* `#include <ogr_spatialref.h>`
* `#include <array>`
* `#include <cmath>`
* `#include <memory>`
* `#include <string>`
* `#include "assert/assert.hpp"`
* `#include "grid/grid.hpp"`
* `#include "utilities/coordinate.hpp"`















## Classes

| Type | Name |
| ---: | :--- |
| struct | [**UserCrsParseResult**](structUserCrsParseResult.md) <br> |






















## Public Functions

| Type | Name |
| ---: | :--- |
|  std::string | [**build\_compound\_crs\_wkt**](#function-build_compound_crs_wkt) (const std::string & wkt, const std::string & normalized\_horizontal) <br> |
|  bool | [**crs\_compatible\_for\_viewing**](#function-crs_compatible_for_viewing) (const std::string & a, const std::string & b) <br> |
|  std::unique\_ptr&lt; OGRCoordinateTransformation &gt; | [**make\_coord\_transform**](#function-make_coord_transform) (const std::string & src\_wkt, const std::string & dst\_wkt) <br> |
|  [**GeoProjection**](classGeoProjection.md) | [**make\_projection\_from\_wkt**](#function-make_projection_from_wkt) (const std::string & raw\_wkt) <br> |
|  std::string | [**normalize\_crs\_wkt**](#function-normalize_crs_wkt) (const std::string & wkt) <br> |
|  [**Extent3D**](structExtent3D.md) | [**reproject\_extent3d\_horizontal**](#function-reproject_extent3d_horizontal) (const [**Extent3D**](structExtent3D.md) & extent, OGRCoordinateTransformation \* ct) <br> |
|  bool | [**transform\_xy\_h**](#function-transform_xy_h) (OGRCoordinateTransformation \* ct, double & x, double & y) <br> |
|  [**UserCrsParseResult**](structUserCrsParseResult.md) | [**try\_user\_crs\_to\_wkt**](#function-try_user_crs_to_wkt) (const std::string & user\_crs) <br> |
|  std::string | [**user\_crs\_to\_wkt**](#function-user_crs_to_wkt) (const std::string & user\_crs) <br> |
|  bool | [**wkt\_matches**](#function-wkt_matches) (const std::string & a, const std::string & b) <br> |
|  bool | [**wkt\_parses**](#function-wkt_parses) (const std::string & wkt) <br> |




























## Public Functions Documentation




### function build\_compound\_crs\_wkt 

```C++
inline std::string build_compound_crs_wkt (
    const std::string & wkt,
    const std::string & normalized_horizontal
) 
```




<hr>



### function crs\_compatible\_for\_viewing 

```C++
inline bool crs_compatible_for_viewing (
    const std::string & a,
    const std::string & b
) 
```




<hr>



### function make\_coord\_transform 

```C++
inline std::unique_ptr< OGRCoordinateTransformation > make_coord_transform (
    const std::string & src_wkt,
    const std::string & dst_wkt
) 
```




<hr>



### function make\_projection\_from\_wkt 

```C++
inline GeoProjection make_projection_from_wkt (
    const std::string & raw_wkt
) 
```




<hr>



### function normalize\_crs\_wkt 

```C++
inline std::string normalize_crs_wkt (
    const std::string & wkt
) 
```




<hr>



### function reproject\_extent3d\_horizontal 

```C++
inline Extent3D reproject_extent3d_horizontal (
    const Extent3D & extent,
    OGRCoordinateTransformation * ct
) 
```




<hr>



### function transform\_xy\_h 

```C++
inline bool transform_xy_h (
    OGRCoordinateTransformation * ct,
    double & x,
    double & y
) 
```




<hr>



### function try\_user\_crs\_to\_wkt 

```C++
inline UserCrsParseResult try_user_crs_to_wkt (
    const std::string & user_crs
) 
```




<hr>



### function user\_crs\_to\_wkt 

```C++
inline std::string user_crs_to_wkt (
    const std::string & user_crs
) 
```




<hr>



### function wkt\_matches 

```C++
inline bool wkt_matches (
    const std::string & a,
    const std::string & b
) 
```




<hr>



### function wkt\_parses 

```C++
inline bool wkt_parses (
    const std::string & wkt
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/lib/io/crs.hpp`

