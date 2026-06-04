

# File gdal\_init.hpp

[**File List**](files.md) **>** [**io**](dir_65bc51589f8002bfcb72faf47ab41180.md) **>** [**gdal\_init.hpp**](gdal__init_8hpp.md)

[Go to the documentation of this file](gdal__init_8hpp.md)


```C++
#pragma once

#include "gdal_priv.h"

// Singleton to ensure GDAL is registered only once
class GDALInitializer {
 public:
  static void ensure_initialized() {
    static GDALInitializer instance;
    (void)instance;  // Suppress unused variable warning
  }

 private:
  GDALInitializer() { GDALAllRegister(); }
  // Prevent copying
  GDALInitializer(const GDALInitializer&) = delete;
  GDALInitializer& operator=(const GDALInitializer&) = delete;
};

// Convenience function to ensure GDAL is initialized
inline void ensure_gdal_initialized() { GDALInitializer::ensure_initialized(); }
```


