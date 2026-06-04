

# File process.hpp



[**FileList**](files.md) **>** [**src**](dir_68267d1309a1af8e8297ef4c3efbcdba.md) **>** [**process.hpp**](process_8hpp.md)

[Go to the source code of this file](process_8hpp_source.md)



* `#include <cmath>`
* `#include <limits>`
* `#include <stdexcept>`
* `#include "config_input/config_input.hpp"`
* `#include "las/las_file.hpp"`





































## Public Functions

| Type | Name |
| ---: | :--- |
|  [**size\_t**](classCoordinate2D.md) | [**num\_cells\_by\_distance**](#function-num_cells_by_distance) ([**double**](classCoordinate2D.md) x, [**double**](classCoordinate2D.md) dx) <br> |
|  [**void**](classCoordinate2D.md) | [**process\_las\_data**](#function-process_las_data) ([**LASData**](classLASData.md) & las\_file, [**const**](classCoordinate2D.md) fs::path & output\_dir, [**const**](classCoordinate2D.md) [**Config**](structConfig.md) & config, [**ProgressTracker**](classProgressTracker.md) tracker) <br> |
|  [**void**](classCoordinate2D.md) | [**process\_las\_file**](#function-process_las_file) ([**const**](classCoordinate2D.md) fs::path & las\_file, [**const**](classCoordinate2D.md) [**Config**](structConfig.md) & config, [**ProgressTracker**](classProgressTracker.md) tracker) <br> |




























## Public Functions Documentation




### function num\_cells\_by\_distance 

```C++
inline size_t num_cells_by_distance (
    double x,
    double dx
) 
```




<hr>



### function process\_las\_data 

```C++
void process_las_data (
    LASData & las_file,
    const fs::path & output_dir,
    const  Config & config,
    ProgressTracker tracker
) 
```




<hr>



### function process\_las\_file 

```C++
void process_las_file (
    const fs::path & las_file,
    const  Config & config,
    ProgressTracker tracker
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/process.hpp`

