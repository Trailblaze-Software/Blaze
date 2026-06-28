

# File run.cpp



[**FileList**](files.md) **>** [**src**](dir_68267d1309a1af8e8297ef4c3efbcdba.md) **>** [**run.cpp**](run_8cpp.md)

[Go to the source code of this file](run_8cpp_source.md)



* `#include "run.hpp"`
* `#include <omp.h>`
* `#include <array>`
* `#include <filesystem>`
* `#include <iostream>`
* `#include "config_input/config_input.hpp"`
* `#include "contour/contour.hpp"`
* `#include "contour/contour_gen.hpp"`
* `#include "crt/crt.hpp"`
* `#include "grid/grid.hpp"`
* `#include "io/gpkg.hpp"`
* `#include "las/las_file.hpp"`
* `#include "las/tile_mode.hpp"`
* `#include "methods/water/water.hpp"`
* `#include "printing/to_string.hpp"`
* `#include "process.hpp"`
* `#include "tif/tif.hpp"`
* `#include "utilities/coordinate.hpp"`
* `#include "utilities/filesystem.hpp"`
* `#include "utilities/progress_tracker.hpp"`
* `#include "utilities/trace_recorder.hpp"`
* `#include "vegetation/vegetation_polygon.hpp"`





































## Public Functions

| Type | Name |
| ---: | :--- |
|  void | [**run\_with\_config**](#function-run_with_config) (const [**Config**](structConfig.md) & config, const std::vector&lt; fs::path &gt; & additional\_las\_files, [**ProgressTracker**](classProgressTracker.md) && progress\_tracker\_param) <br> |




























## Public Functions Documentation




### function run\_with\_config 

```C++
void run_with_config (
    const Config & config,
    const std::vector< fs::path > & additional_las_files,
    ProgressTracker && progress_tracker_param
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/run.cpp`

