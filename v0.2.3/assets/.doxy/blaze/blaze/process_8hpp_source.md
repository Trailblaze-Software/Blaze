

# File process.hpp

[**File List**](files.md) **>** [**src**](dir_68267d1309a1af8e8297ef4c3efbcdba.md) **>** [**process.hpp**](process_8hpp.md)

[Go to the documentation of this file](process_8hpp.md)


```C++
#include "config_input/config_input.hpp"
#include "las/las_file.hpp"

class ProgressTracker;

void process_las_file(const fs::path& las_file, const Config& config, ProgressTracker tracker);
void process_las_data(LASData& las_file, const fs::path& output_dir, const Config& config,
                      ProgressTracker tracker);
```


