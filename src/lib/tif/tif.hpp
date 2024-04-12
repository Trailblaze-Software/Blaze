#pragma once

#include <gdal/gdal.h>
#include <gdal/gdal_priv.h>

#include <optional>
#include <type_traits>

#include "assert/gdal_assert.hpp"
#include "isom/colors.hpp"
#include "lib/grid/grid.hpp"
#include "utilities/filesystem.hpp"
#include "utilities/timer.hpp"

template <typename T>
struct is_std_optional : std::false_type {};

template <typename T>
struct is_std_optional<std::optional<T>> : std::true_type {};

template <typename T>
inline constexpr bool is_std_optional_v = is_std_optional<T>::value;

template <typename T>
constexpr GDALDataType gdal_type() {
  if constexpr (std::is_same_v<double, T>) {
    return GDT_Float64;
  } else if constexpr (std::is_same_v<unsigned int, T>) {
    return GDT_UInt32;
  } else if constexpr (std::is_same_v<std::byte, T>) {
    return GDT_Byte;
  } else if constexpr (is_std_optional_v<T>) {
    return gdal_type<typename T::value_type>();
  } else if constexpr (std::is_base_of_v<Color, T>) {
    return GDT_Byte;
  } else {
    static_assert(std::is_base_of_v<Color, T>);
  }
}

template <typename T>
void write_to_tif(const GeoGrid<T> &grid, const fs::path &filename) {
  TimeFunction timer("writing to tif " + filename.string());
  GDALAllRegister();

  constexpr int bands = is_std_optional_v<T> ? 2 : std::is_base_of_v<Color, T> ? 3 : 1;
  GDALDataType datatype = gdal_type<T>();

  char **options = nullptr;
  options = CSLSetNameValue(options, "COMPRESS", "LZW");
  options = CSLSetNameValue(options, "ALPHA", "YES");

  GDALDriver *driver = GetGDALDriverManager()->GetDriverByName("GTiff");
  GDALDataset *dataset =
      driver->Create(filename.c_str(), grid.width(), grid.height(), bands, datatype, options);

  dataset->SetGeoTransform(const_cast<double *>(grid.transform().get_raw()));
  dataset->SetProjection(grid.projection().to_string().c_str());

  // GDALAssert(dataset->GetRasterBand(1)->SetNoDataValue(0));
  if constexpr (is_std_optional_v<T>) {
    for (size_t i = 0; i < grid.height(); i++) {
      std::vector<typename T::value_type> data(grid.width());
      std::vector<typename T::value_type> transparent(grid.width());
      for (size_t j = 0; j < grid.width(); j++) {
        data[j] = grid[{j, i}].has_value() ? grid[{j, i}].value() : typename T::value_type(0);
        transparent[j] =
            grid[{j, i}].has_value() ? typename T::value_type(255) : typename T::value_type(0);
      }

      GDALAssert(dataset->GetRasterBand(1)->RasterIO(GF_Write, 0, i, grid.width(), 1, data.data(),
                                                     grid.width(), 1, datatype, 0, 0));
      GDALAssert(dataset->GetRasterBand(2)->RasterIO(
          GF_Write, 0, i, grid.width(), 1, transparent.data(), grid.width(), 1, datatype, 0, 0));
    }
  } else if constexpr (std::is_base_of_v<Color, T>) {
    for (int band = 0; band < 3; band++) {
      std::vector<unsigned char> data(grid.width() * grid.height());
      for (size_t i = 0; i < grid.height(); i++) {
        for (size_t j = 0; j < grid.width(); j++) {
          data[i * grid.width() + j] = grid[{j, i}].toRGB()[band];
        }
      }
      GDALAssert(dataset->GetRasterBand(band + 1)->RasterIO(
          GF_Write, 0, 0, grid.width(), grid.height(), data.data(), grid.width(), grid.height(),
          datatype, 0, 0));
    }
  } else {
    GDALAssert(dataset->GetRasterBand(1)->RasterIO(GF_Write, 0, 0, grid.width(), grid.height(),
                                                   const_cast<T *>(&grid[{0, 0}]), grid.width(),
                                                   grid.height(), datatype, 0, 0));
  }

  GDALClose(dataset);
  CSLDestroy(options);
}

template <typename T>
void write_to_tif_with_thresh(const GeoGrid<T> &grid, const fs::path &filename, double threshold) {
  GeoGrid<std::optional<T>> result(grid.width(), grid.height(), GeoTransform(grid.transform()),
                                   GeoProjection(grid.projection()));
  for (size_t i = 0; i < grid.height(); i++) {
    for (size_t j = 0; j < grid.width(); j++) {
      result[{j, i}] = grid[{j, i}] > threshold ? std::optional<T>{grid[{j, i}]} : std::nullopt;
    }
  }
  write_to_tif(result, filename);
}

template <typename T>
void write_to_image_tif(const GeoGrid<T> &grid, const fs::path &filename) {
  GeoGrid<std::byte> result(grid.width(), grid.height(), GeoTransform(grid.transform()),
                            GeoProjection(grid.projection()));
  T min = grid.min_value();
  T max = grid.max_value();
  for (size_t i = 0; i < grid.height(); i++) {
    for (size_t j = 0; j < grid.width(); j++) {
      result[{i, j}] = static_cast<std::byte>(255 * (grid[{i, j}] - min) / (max - min));
    }
  }
  CMYKColor cmyk = CMYKColor::FromRGB(RGBColor(255, 255, 255));
  (void)cmyk;
  write_to_tif(result, filename);
}
