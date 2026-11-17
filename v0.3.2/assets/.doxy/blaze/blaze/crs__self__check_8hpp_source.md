

# File crs\_self\_check.hpp

[**File List**](files.md) **>** [**las**](dir_50e4ddd575fc604ec1609997d931fab5.md) **>** [**crs\_self\_check.hpp**](crs__self__check_8hpp.md)

[Go to the documentation of this file](crs__self__check_8hpp.md)


```C++
#pragma once

#include <vector>

#include "utilities/filesystem.hpp"

// --check-crs for blaze-cli and Blaze: print PROJ's search paths, whether
// proj.db is usable and whether each file's embedded CRS can be read. Returns
// 0 if all OK. Used by the macOS packaging CI (issue #36) and for bug reports.
int run_crs_self_check(const std::vector<fs::path>& las_files);
```


