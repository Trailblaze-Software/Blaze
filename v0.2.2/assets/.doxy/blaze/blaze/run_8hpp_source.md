

# File run.hpp

[**File List**](files.md) **>** [**src**](dir_68267d1309a1af8e8297ef4c3efbcdba.md) **>** [**run.hpp**](run_8hpp.md)

[Go to the documentation of this file](run_8hpp.md)


```C++
#pragma once

#include <vector>

#include "utilities/filesystem.hpp"

struct Config;
class ProgressTracker;

void run_with_config(const Config& config, const std::vector<fs::path>& additional_las_files,
                     ProgressTracker&& tracker);
```


