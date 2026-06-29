

# File resources.hpp

[**File List**](files.md) **>** [**lib**](dir_c85d3e3c5052e9ad9ce18c6863244a25.md) **>** [**utilities**](dir_f68f3bc40609949e989ead5b0b6dedfd.md) **>** [**resources.hpp**](resources_8hpp.md)

[Go to the documentation of this file](resources_8hpp.md)


```C++
#pragma once

#include "utilities/filesystem.hpp"

class AssetRetriever {
 public:
  static fs::path get_asset(const fs::path& asset);
};

class LocalDataRetriever {
 public:
  static fs::path get_local_data(const fs::path& asset);
};
```


