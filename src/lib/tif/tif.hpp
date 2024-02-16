#pragma once

#include <gdal/gdal.h>
#include <gdal/gdal_priv.h>
#include <type_traits>

#include "assert/gdal_assert.hpp"
#include "lib/utilities/grid.hpp"

template <typename T>
void write_to_tif(GeoGrid<T>& grid, const std::string& filename) {
    GDALAllRegister();

    int bands;
    GDALDataType datatype;
    if constexpr(std::is_arithmetic_v<T>) {
      bands = 1;
      if constexpr(std::is_same_v<double, T>) {
        datatype = GDT_Float64;
      } else if constexpr(std::is_same_v<unsigned int, T>) {
        datatype = GDT_UInt32;
      } else {
        static_assert(std::is_same_v<double, T>);
      }
    } else if constexpr(std::is_same_v<std::byte, T>) {
      bands = 1;
      datatype = GDT_Byte;
    } else {
      static_assert(std::is_same_v<double, T>);
    }

    GDALDriver *driver = GetGDALDriverManager()->GetDriverByName("GTiff");
    GDALDataset *dataset = driver->Create(filename.c_str(), grid.width(), grid.height(), bands, datatype, NULL);

    dataset->SetGeoTransform(const_cast<double*>(grid.transform().get_raw()));
    dataset->SetProjection(grid.projection().to_string().c_str());

    for (size_t i = 0; i < grid.height(); i++){
      for (size_t j = 0; j < grid.width(); j++) {
        for (int band = 1; band <= bands; band++) {
         GDALAssert(dataset->GetRasterBand(band)->RasterIO(GF_Write, i, j, 1, 1, &grid[{i, j}], 1, 1, datatype, 0, 0));
        }
      }
    }
    GDALClose(dataset);
}
