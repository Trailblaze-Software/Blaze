

# File layer.hpp



[**FileList**](files.md) **>** [**gui**](dir_99d0482cf009f9d97a0877749b817f19.md) **>** [**layer.hpp**](layer_8hpp.md)

[Go to the source code of this file](layer_8hpp_source.md)



* `#include <QMetaObject>`
* `#include <QObject>`
* `#include <algorithm>`
* `#include <array>`
* `#include <atomic>`
* `#include <future>`
* `#include <mutex>`
* `#include <vector>`
* `#include "contour/contour.hpp"`
* `#include "gui/octree_las_data.hpp"`
* `#include "gui/point_cloud_visualization.hpp"`
* `#include "gui/raster_data.hpp"`
* `#include "io/crs.hpp"`
* `#include "io/gpkg.hpp"`
* `#include "las/las_file.hpp"`
* `#include "utilities/coordinate.hpp"`
* `#include "utilities/filesystem.hpp"`
* `#include "utilities/progress_tracker.hpp"`















## Classes

| Type | Name |
| ---: | :--- |
| class | [**ContourLayer**](classContourLayer.md) <br> |
| class | [**DemLayer**](classDemLayer.md) <br> |
| class | [**LASLayer**](classLASLayer.md) <br> |
| class | [**Layer**](classLayer.md) <br> |
| class | [**PointLayer**](classPointLayer.md) <br> |
| class | [**SlopeLayer**](classSlopeLayer.md) <br> |
| class | [**TexturedDemLayer**](classTexturedDemLayer.md) <br> |


## Public Types

| Type | Name |
| ---: | :--- |
| enum  | [**LayerKind**](#enum-layerkind)  <br> |
















































## Public Types Documentation




### enum LayerKind 

```C++
enum LayerKind {
    PointCloud,
    DemSurface,
    Contours,
    SlopeSurface,
    TexturedDem
};
```




<hr>

------------------------------
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/gui/layer.hpp`

