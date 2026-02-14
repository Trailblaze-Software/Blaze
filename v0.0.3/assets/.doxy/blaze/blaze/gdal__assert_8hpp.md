

# File gdal\_assert.hpp



[**FileList**](files.md) **>** [**assert**](dir_d1185b0cdad395d5facacbcb4739e037.md) **>** [**gdal\_assert.hpp**](gdal__assert_8hpp.md)

[Go to the source code of this file](gdal__assert_8hpp_source.md)



* `#include <cpl_error.h>`
* `#include <source_location>`
* `#include "assert/assert.hpp"`
* `#include "ogr_core.h"`





































## Public Functions

| Type | Name |
| ---: | :--- |
|  [**void**](classCoordinate2D.md) | [**\_GDALAssert**](#function-_gdalassert) ([**CPLErr**](classCoordinate2D.md) expr, [**const**](classCoordinate2D.md) std::string & expr\_string, [**const**](classCoordinate2D.md) std::source\_location & loc=std::source\_location::current()) <br> |
|  [**void**](classCoordinate2D.md) | [**\_GDALAssert**](#function-_gdalassert) ([**OGRErr**](classCoordinate2D.md) expr, [**const**](classCoordinate2D.md) std::string & expr\_string, [**const**](classCoordinate2D.md) std::source\_location & loc=std::source\_location::current()) <br> |



























## Macros

| Type | Name |
| ---: | :--- |
| define  | [**GDALAssert**](gdal__assert_8hpp.md#define-gdalassert) (expr) `\_GDALAssert([**expr**](classCoordinate2D.md), #[**expr**](classCoordinate2D.md))`<br> |

## Public Functions Documentation




### function \_GDALAssert 

```C++
inline void _GDALAssert (
    CPLErr expr,
    const std::string & expr_string,
    const std::source_location & loc=std::source_location::current()
) 
```




<hr>



### function \_GDALAssert 

```C++
inline void _GDALAssert (
    OGRErr expr,
    const std::string & expr_string,
    const std::source_location & loc=std::source_location::current()
) 
```




<hr>
## Macro Definition Documentation





### define GDALAssert 

```C++
#define GDALAssert (
    expr
) `_GDALAssert( expr , # expr )`
```




<hr>

------------------------------
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/lib/assert/gdal_assert.hpp`

