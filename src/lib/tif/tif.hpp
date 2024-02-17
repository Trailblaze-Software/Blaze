#pragma once

#include <gdal/gdal.h>
#include <gdal/gdal_priv.h>
#include <optional>
#include <type_traits>

#include "assert/gdal_assert.hpp"
#include "lib/grid/grid.hpp"
#include "utilities/timer.hpp"


template <typename T>
void write_to_tif(const GeoGrid<T>& grid, const std::string& filename) {
  Timer timer;
  std::cout << "Writing to tif " << filename << std::endl;
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
    } else if constexpr(std::is_same_v<std::optional<std::byte>, T>) {
      bands = 2;
      datatype = GDT_Byte;
    } else {
      static_assert(std::is_same_v<double, T>);
    }

    char **options = nullptr;
    options = CSLSetNameValue(options, "COMPRESS", "LZW");
    options = CSLSetNameValue(options, "ALPHA", "YES");

    GDALDriver *driver = GetGDALDriverManager()->GetDriverByName("GTiff");
    GDALDataset *dataset = driver->Create(filename.c_str(), grid.width(), grid.height(), bands, datatype, options);

    dataset->SetGeoTransform(const_cast<double*>(grid.transform().get_raw()));
    dataset->SetProjection(grid.projection().to_string().c_str());

    for (size_t i = 0; i < grid.height(); i++){
      for (size_t j = 0; j < grid.width(); j++) {
        if constexpr(std::is_same_v<std::optional<std::byte>, T>) {
          std::byte transparent = grid[{i, j}].has_value() ? std::byte{255} : std::byte{0};
          GDALAssert(dataset->GetRasterBand(1)->RasterIO(GF_Write, i, j, 1, 1, const_cast<std::byte*>(&*grid[{i, j}]), 1, 1, datatype, 0, 0));
          GDALAssert(dataset->GetRasterBand(2)->RasterIO(GF_Write, i, j, 1, 1, &transparent, 1, 1, datatype, 0, 0));
        } else {
          for (int band = 1; band <= bands; band++) {
           GDALAssert(dataset->GetRasterBand(band)->RasterIO(GF_Write, i, j, 1, 1, const_cast<T*>(&grid[{i, j}]), 1, 1, datatype, 0, 0));
          }
        }
      }
    }

    GDALClose(dataset);
    CSLDestroy(options);
    std::cout << "Writing to tif " << filename << " took " << timer << std::endl;
}

template <typename T>
void write_to_image_tif(const GeoGrid<T>& grid, const std::string& filename) {
  GeoGrid<std::byte> result(grid.width(), grid.height(), GeoTransform(grid.transform()), GeoProjection(grid.projection()));
  T min = grid.min_value();
  T max = grid.max_value();
  for (size_t i = 0; i < grid.height(); i++){
    for (size_t j = 0; j < grid.width(); j++) {
      result[{i, j}] = static_cast<std::byte>(255 * (grid[{i, j}] - min) / (max - min));
    }
  }
  write_to_tif(result, filename);
}
