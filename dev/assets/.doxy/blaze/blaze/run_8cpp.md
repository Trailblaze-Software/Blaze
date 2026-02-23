

# File run.cpp



[**FileList**](files.md) **>** [**src**](dir_68267d1309a1af8e8297ef4c3efbcdba.md) **>** [**run.cpp**](run_8cpp.md)

[Go to the source code of this file](run_8cpp_source.md)



* `#include "run.hpp"`
* `#include <omp.h>`
* `#include <filesystem>`
* `#include <iostream>`
* `#include "config_input/config_input.hpp"`
* `#include "contour/contour.hpp"`
* `#include "contour/contour_gen.hpp"`
* `#include "crt/crt.hpp"`
* `#include "grid/grid.hpp"`
* `#include "io/gpkg.hpp"`
* `#include "las/las_file.hpp"`
* `#include "methods/water/water.hpp"`
* `#include "printing/to_string.hpp"`
* `#include "process.hpp"`
* `#include "tif/tif.hpp"`
* `#include "utilities/coordinate.hpp"`
* `#include "utilities/filesystem.hpp"`
* `#include "utilities/progress_tracker.hpp"`
* `#include "utilities/timer.hpp"`





































## Public Functions

| Type | Name |
| ---: | :--- |
|  [**void**](classCoordinate2D.md) | [**run\_with\_config**](#function-run_with_config) ([**const**](classCoordinate2D.md) [**Config**](structConfig.md) & config, [**const**](classCoordinate2D.md) std::vector&lt; fs::path &gt; & additional\_las\_files, [**ProgressTracker**](classProgressTracker.md) && tracker) <br> |




























## Public Functions Documentation




### function run\_with\_config 

```C++
void run_with_config (
    const  Config & config,
    const std::vector< fs::path > & additional_las_files,
    ProgressTracker && tracker
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/run.cpp`

