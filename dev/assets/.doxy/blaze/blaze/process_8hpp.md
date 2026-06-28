

# File process.hpp



[**FileList**](files.md) **>** [**src**](dir_68267d1309a1af8e8297ef4c3efbcdba.md) **>** [**process.hpp**](process_8hpp.md)

[Go to the source code of this file](process_8hpp_source.md)



* `#include "config_input/config_input.hpp"`
* `#include "las/las_file.hpp"`





































## Public Functions

| Type | Name |
| ---: | :--- |
|  void | [**process\_las\_data**](#function-process_las_data) ([**LASData**](classLASData.md) & las\_file, const fs::path & output\_dir, const [**Config**](structConfig.md) & config, [**ProgressTracker**](classProgressTracker.md) && progress\_tracker) <br> |
|  void | [**process\_las\_file**](#function-process_las_file) (const fs::path & las\_file, const [**Config**](structConfig.md) & config, [**ProgressTracker**](classProgressTracker.md) && progress\_tracker) <br> |




























## Public Functions Documentation




### function process\_las\_data 

```C++
void process_las_data (
    LASData & las_file,
    const fs::path & output_dir,
    const Config & config,
    ProgressTracker && progress_tracker
) 
```




<hr>



### function process\_las\_file 

```C++
void process_las_file (
    const fs::path & las_file,
    const Config & config,
    ProgressTracker && progress_tracker
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/process.hpp`

