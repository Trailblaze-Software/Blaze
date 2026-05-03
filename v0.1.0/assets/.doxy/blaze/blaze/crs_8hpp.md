

# File crs.hpp



[**FileList**](files.md) **>** [**io**](dir_65bc51589f8002bfcb72faf47ab41180.md) **>** [**crs.hpp**](crs_8hpp.md)

[Go to the source code of this file](crs_8hpp_source.md)



* `#include <ogr_spatialref.h>`
* `#include <string>`
* `#include "assert/assert.hpp"`
* `#include "grid/grid.hpp"`















## Classes

| Type | Name |
| ---: | :--- |
| struct | [**UserCrsParseResult**](structUserCrsParseResult.md) <br> |






















## Public Functions

| Type | Name |
| ---: | :--- |
|  std::string | [**build\_compound\_crs\_wkt**](#function-build_compound_crs_wkt) ([**const**](classCoordinate2D.md) std::string & wkt, [**const**](classCoordinate2D.md) std::string & normalized\_horizontal) <br> |
|  [**GeoProjection**](classGeoProjection.md) | [**make\_projection\_from\_wkt**](#function-make_projection_from_wkt) ([**const**](classCoordinate2D.md) std::string & raw\_wkt) <br> |
|  std::string | [**normalize\_crs\_wkt**](#function-normalize_crs_wkt) ([**const**](classCoordinate2D.md) std::string & wkt) <br> |
|  [**UserCrsParseResult**](structUserCrsParseResult.md) | [**try\_user\_crs\_to\_wkt**](#function-try_user_crs_to_wkt) ([**const**](classCoordinate2D.md) std::string & user\_crs) <br> |
|  std::string | [**user\_crs\_to\_wkt**](#function-user_crs_to_wkt) ([**const**](classCoordinate2D.md) std::string & user\_crs) <br> |
|  [**bool**](classCoordinate2D.md) | [**wkt\_matches**](#function-wkt_matches) ([**const**](classCoordinate2D.md) std::string & a, [**const**](classCoordinate2D.md) std::string & b) <br> |




























## Public Functions Documentation




### function build\_compound\_crs\_wkt 

```C++
inline std::string build_compound_crs_wkt (
    const std::string & wkt,
    const std::string & normalized_horizontal
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

------------------------------
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/lib/io/crs.hpp`

