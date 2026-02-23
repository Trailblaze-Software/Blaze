

# File gpkg.hpp



[**FileList**](files.md) **>** [**io**](dir_65bc51589f8002bfcb72faf47ab41180.md) **>** [**gpkg.hpp**](gpkg_8hpp.md)

[Go to the source code of this file](gpkg_8hpp_source.md)



* `#include <ogrsf_frmts.h>`
* `#include "assert/assert.hpp"`
* `#include "assert/gdal_assert.hpp"`
* `#include "contour/contour.hpp"`
* `#include "gdal_priv.h"`
* `#include "io/gdal_init.hpp"`
* `#include "polyline/polyline.hpp"`
* `#include "utilities/filesystem.hpp"`
* `#include "utilities/timer.hpp"`















## Classes

| Type | Name |
| ---: | :--- |
| class | [**GDALDataset\_w**](classGDALDataset__w.md) <br> |
| class | [**GPKGWriter**](classGPKGWriter.md) <br> |






















## Public Functions

| Type | Name |
| ---: | :--- |
|  std::vector&lt; [**Contour**](classContour.md) &gt; | [**read\_gpkg**](#function-read_gpkg) ([**const**](classCoordinate2D.md) fs::path & filename) <br> |




























## Public Functions Documentation




### function read\_gpkg 

```C++
inline std::vector< Contour > read_gpkg (
    const fs::path & filename
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/lib/io/gpkg.hpp`

