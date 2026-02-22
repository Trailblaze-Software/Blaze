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
