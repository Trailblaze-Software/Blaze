#pragma once

#include <gdal.h>

#include <algorithm>
#include <atomic>
#include <cmath>
#include <future>
#include <mutex>
#include <optional>
#include <vector>

#include "grid/grid.hpp"
#include "io/crs.hpp"
#include "io/gdal_init.hpp"
#include "tif/tif.hpp"
#include "utilities/progress_tracker.hpp"

struct TifMetadata {
  GeoProjection projection;
  Extent3D extent;
};

inline TifMetadata read_tif_metadata(const fs::path& path) {
  ensure_gdal_initialized();
  GDALDataset* dataset = static_cast<GDALDataset*>(GDALOpen(path.string().c_str(), GA_ReadOnly));
  Assert(dataset, "Could not open raster " + path.string());

  GeoProjection projection = make_projection_from_wkt(std::string(dataset->GetProjectionRef()));
  GeoTransform transform(*dataset);
  const size_t width = dataset->GetRasterXSize();
  const size_t height = dataset->GetRasterYSize();

  Extent3D extent;
  const std::array<size_t, 2> corners{0, width > 0 ? width - 1 : 0};
  for (size_t corner_y : {size_t{0}, height > 0 ? height - 1 : size_t{0}}) {
    for (size_t corner_x : corners) {
      Coordinate2D<double> coord = transform.pixel_to_projection(
          {static_cast<double>(corner_x), static_cast<double>(corner_y)});
      extent.grow(coord.x(), coord.y(), 0);
    }
  }

  GDALClose(dataset);
  return {std::move(projection), extent};
}

inline std::array<size_t, 2> read_tif_dimensions(const fs::path& path) {
  ensure_gdal_initialized();
  GDALDataset* dataset = static_cast<GDALDataset*>(GDALOpen(path.string().c_str(), GA_ReadOnly));
  Assert(dataset, "Could not open raster " + path.string());
  const size_t width = dataset->GetRasterXSize();
  const size_t height = dataset->GetRasterYSize();
  GDALClose(dataset);
  return {width, height};
}

// Keep mesh vertex count manageable for large rasters while preserving detail on small ones.
inline int adaptive_dem_stride(size_t width, size_t height, size_t max_vertices_per_axis = 512) {
  const size_t max_dim = std::max(width, height);
  int stride = 1;
  while (static_cast<size_t>(stride) < max_dim &&
         (max_dim + static_cast<size_t>(stride) - 1) / static_cast<size_t>(stride) >
             max_vertices_per_axis) {
    stride *= 2;
  }
  return stride;
}

inline double flex_grid_value(const FlexGrid& band, size_t x, size_t y) {
  if (!band.in_bounds({x, y})) {
    return std::numeric_limits<double>::quiet_NaN();
  }
  switch (band.data_type()) {
    case GDT_Float32:
      return band.get<float>({static_cast<long long>(x), static_cast<long long>(y)});
    case GDT_Float64:
      return band.get<double>({static_cast<long long>(x), static_cast<long long>(y)});
    case GDT_Int16:
      return band.get<int16_t>({static_cast<long long>(x), static_cast<long long>(y)});
    case GDT_UInt16:
      return band.get<uint16_t>({static_cast<long long>(x), static_cast<long long>(y)});
    case GDT_Byte:
      return band.get<uint8_t>({static_cast<long long>(x), static_cast<long long>(y)});
    default:
      return band.get<float>({static_cast<long long>(x), static_cast<long long>(y)});
  }
}

inline bool is_valid_elevation(double value) { return std::isfinite(value) && value > -1e10; }

inline double sample_grid_bilinear(const FlexGrid& band, double px, double py) {
  if (band.width() == 0 || band.height() == 0) {
    return std::numeric_limits<double>::quiet_NaN();
  }
  const long long x0 = std::clamp(static_cast<long long>(std::floor(px)), 0ll,
                                  static_cast<long long>(band.width() - 1));
  const long long y0 = std::clamp(static_cast<long long>(std::floor(py)), 0ll,
                                  static_cast<long long>(band.height() - 1));
  const long long x1 = std::min(x0 + 1, static_cast<long long>(band.width() - 1));
  const long long y1 = std::min(y0 + 1, static_cast<long long>(band.height() - 1));
  const double fx = px - static_cast<double>(x0);
  const double fy = py - static_cast<double>(y0);

  auto sample = [&](long long x, long long y) {
    return flex_grid_value(band, static_cast<size_t>(x), static_cast<size_t>(y));
  };

  const double v00 = sample(x0, y0);
  const double v10 = sample(x1, y0);
  const double v01 = sample(x0, y1);
  const double v11 = sample(x1, y1);
  if (!is_valid_elevation(v00) && !is_valid_elevation(v10) && !is_valid_elevation(v01) &&
      !is_valid_elevation(v11)) {
    return std::numeric_limits<double>::quiet_NaN();
  }
  const auto replace_invalid = [](double value, double fallback) {
    return is_valid_elevation(value) ? value : fallback;
  };
  const double v00_f = replace_invalid(v00, v10);
  const double v10_f = replace_invalid(v10, v00_f);
  const double v01_f = replace_invalid(v01, v00_f);
  const double v11_f = replace_invalid(v11, v10_f);
  const double top = v00_f + fx * (v10_f - v00_f);
  const double bottom = v01_f + fx * (v11_f - v01_f);
  return top + fy * (bottom - top);
}

// slope.tif stores byte values with flat terrain at 255 and vertical cliffs at 0.

struct DemMeshData {
  std::vector<double> vertices;
  std::vector<float> colors;
  std::vector<float> texcoords;
  std::vector<float> normals;
  std::vector<unsigned int> indices;
  Extent3D extent;
  bool has_texture = false;
};

inline std::pair<float, float> texture_uv_from_projection(const GeoTransform& texture_transform,
                                                          size_t texture_width,
                                                          size_t texture_height,
                                                          const Coordinate2D<double>& coord) {
  const Coordinate2D<double> tex_pixel = texture_transform.projection_to_pixel(coord);
  if (texture_width <= 1 || texture_height <= 1) {
    return {0.5f, 0.5f};
  }
  // Sample at pixel centres; flip V because GDAL rows grow downward while OpenGL v grows upward.
  const float u = static_cast<float>((tex_pixel.x() + 0.5) / static_cast<double>(texture_width));
  const float v =
      static_cast<float>(1.0 - (tex_pixel.y() + 0.5) / static_cast<double>(texture_height));
  return {std::clamp(u, 0.f, 1.f), std::clamp(v, 0.f, 1.f)};
}

inline void compute_terrain_normals_from_dem(DemMeshData& mesh,
                                             const Geo<MultiBand<FlexGrid>>& dem_grid, int stride,
                                             size_t cols, size_t rows) {
  const size_t width = dem_grid.width();
  const size_t height = dem_grid.height();
  const double cell_x = std::abs(dem_grid.transform().dx()) * stride;
  const double cell_y = std::abs(dem_grid.transform().dy()) * stride;
  mesh.normals.assign(mesh.vertices.size(), 0.0f);

  for (size_t row = 0; row < rows; ++row) {
    for (size_t col = 0; col < cols; ++col) {
      const size_t x = std::min(col * static_cast<size_t>(stride), width - 1);
      const size_t y = std::min(row * static_cast<size_t>(stride), height - 1);
      const size_t vi = (row * cols + col) * 3;

      auto sample_z = [&](long long sx, long long sy) -> double {
        const long long clamped_x = std::clamp(sx, 0ll, static_cast<long long>(width) - 1);
        const long long clamped_y = std::clamp(sy, 0ll, static_cast<long long>(height) - 1);
        const double z = flex_grid_value(dem_grid[0], static_cast<size_t>(clamped_x),
                                         static_cast<size_t>(clamped_y));
        return is_valid_elevation(z) ? z : 0.0;
      };

      const long long stride_ll = static_cast<long long>(stride);
      const double z_w = sample_z(static_cast<long long>(x) - stride_ll, y);
      const double z_e = sample_z(static_cast<long long>(x) + stride_ll, y);
      const double z_n = sample_z(x, static_cast<long long>(y) - stride_ll);
      const double z_s = sample_z(x, static_cast<long long>(y) + stride_ll);

      const double dzdx = (z_e - z_w) / (2.0 * cell_x);
      const double dzdy = (z_n - z_s) / (2.0 * cell_y);

      float nx = static_cast<float>(-dzdx);
      float ny = static_cast<float>(-dzdy);
      float nz = 1.f;
      const float len = std::sqrt(nx * nx + ny * ny + nz * nz);
      if (len > 1e-8f) {
        mesh.normals[vi] = nx / len;
        mesh.normals[vi + 1] = ny / len;
        mesh.normals[vi + 2] = nz / len;
      } else {
        mesh.normals[vi] = 0.f;
        mesh.normals[vi + 1] = 0.f;
        mesh.normals[vi + 2] = 1.f;
      }
    }
  }
}

inline void compute_mesh_normals(DemMeshData& mesh) {
  const size_t vertex_count = mesh.vertices.size() / 3;
  mesh.normals.assign(mesh.vertices.size(), 0.0f);

  auto accumulate = [&](unsigned int i0, unsigned int i1, unsigned int i2) {
    if (i0 >= vertex_count || i1 >= vertex_count || i2 >= vertex_count) {
      return;
    }
    const double* v0 = &mesh.vertices[i0 * 3];
    const double* v1 = &mesh.vertices[i1 * 3];
    const double* v2 = &mesh.vertices[i2 * 3];
    const double e1x = v1[0] - v0[0];
    const double e1y = v1[1] - v0[1];
    const double e1z = v1[2] - v0[2];
    const double e2x = v2[0] - v0[0];
    const double e2y = v2[1] - v0[1];
    const double e2z = v2[2] - v0[2];
    const double nx = e1y * e2z - e1z * e2y;
    const double ny = e1z * e2x - e1x * e2z;
    const double nz = e1x * e2y - e1y * e2x;
    for (unsigned int idx : {i0, i1, i2}) {
      mesh.normals[idx * 3] += static_cast<float>(nx);
      mesh.normals[idx * 3 + 1] += static_cast<float>(ny);
      mesh.normals[idx * 3 + 2] += static_cast<float>(nz);
    }
  };

  for (size_t i = 0; i + 2 < mesh.indices.size(); i += 3) {
    accumulate(mesh.indices[i], mesh.indices[i + 1], mesh.indices[i + 2]);
  }

  for (size_t i = 0; i < vertex_count; ++i) {
    float nx = mesh.normals[i * 3];
    float ny = mesh.normals[i * 3 + 1];
    float nz = mesh.normals[i * 3 + 2];
    const float len = std::sqrt(nx * nx + ny * ny + nz * nz);
    if (len > 1e-8f) {
      mesh.normals[i * 3] = nx / len;
      mesh.normals[i * 3 + 1] = ny / len;
      mesh.normals[i * 3 + 2] = nz / len;
    } else {
      mesh.normals[i * 3] = 0.f;
      mesh.normals[i * 3 + 1] = 0.f;
      mesh.normals[i * 3 + 2] = 1.f;
    }
  }
}

inline DemMeshData build_dem_mesh(const Geo<MultiBand<FlexGrid>>& grid, int stride = 1,
                                  const Geo<MultiBand<FlexGrid>>* texture = nullptr) {
  DemMeshData mesh;
  const size_t width = grid.width();
  const size_t height = grid.height();
  stride = std::max(1, stride);

  double min_z = std::numeric_limits<double>::infinity();
  double max_z = -std::numeric_limits<double>::infinity();
  for (size_t y = 0; y < height; y += stride) {
    for (size_t x = 0; x < width; x += stride) {
      double z = flex_grid_value(grid[0], x, y);
      if (is_valid_elevation(z)) {
        min_z = std::min(min_z, z);
        max_z = std::max(max_z, z);
      }
    }
  }
  double z_range = std::max(max_z - min_z, 1.0);

  const auto& transform = grid.transform();
  mesh.has_texture = texture != nullptr;

  auto sample_texture = [&](size_t x, size_t y) -> std::array<float, 3> {
    if (!texture) {
      return {0.5f, 0.7f, 0.4f};
    }
    size_t tx = x * texture->width() / width;
    size_t ty = y * texture->height() / height;
    tx = std::min(tx, texture->width() - 1);
    ty = std::min(ty, texture->height() - 1);
    double r = flex_grid_value((*texture)[0], tx, ty) / 255.0;
    double g = texture->size() > 1 ? flex_grid_value((*texture)[1], tx, ty) / 255.0 : r;
    double b = texture->size() > 2 ? flex_grid_value((*texture)[2], tx, ty) / 255.0 : r;
    return {static_cast<float>(r), static_cast<float>(g), static_cast<float>(b)};
  };

  const size_t cols = (width + stride - 1) / stride;
  const size_t rows = (height + stride - 1) / stride;

  auto vertex_index = [&](size_t col, size_t row) { return row * cols + col; };

  for (size_t row = 0; row < rows; ++row) {
    for (size_t col = 0; col < cols; ++col) {
      size_t x = std::min(col * stride, width - 1);
      size_t y = std::min(row * stride, height - 1);
      Coordinate2D<double> coord = transform.pixel_to_projection({x + 0.5, y + 0.5});
      double z = flex_grid_value(grid[0], x, y);
      if (!is_valid_elevation(z)) {
        z = min_z;
      }

      mesh.vertices.push_back(coord.x());
      mesh.vertices.push_back(coord.y());
      mesh.vertices.push_back(z);

      if (mesh.has_texture) {
        auto rgb = sample_texture(x, y);
        mesh.colors.push_back(rgb[0]);
        mesh.colors.push_back(rgb[1]);
        mesh.colors.push_back(rgb[2]);
        const auto grid_coord = [](size_t idx, size_t count) -> float {
          return count <= 1 ? 0.f : static_cast<float>(idx) / static_cast<float>(count - 1);
        };
        mesh.texcoords.push_back(grid_coord(col, cols));
        mesh.texcoords.push_back(
            rows <= 1 ? 0.f : static_cast<float>(row) / static_cast<float>(rows - 1));
      } else {
        float t = static_cast<float>((z - min_z) / z_range);
        mesh.colors.push_back(0.2f + 0.6f * t);
        mesh.colors.push_back(0.5f + 0.3f * (1.0f - t));
        mesh.colors.push_back(0.2f);
      }

      mesh.extent.grow(coord.x(), coord.y(), z);
    }
  }

  for (size_t row = 0; row + 1 < rows; ++row) {
    for (size_t col = 0; col + 1 < cols; ++col) {
      unsigned int i0 = static_cast<unsigned int>(vertex_index(col, row));
      unsigned int i1 = static_cast<unsigned int>(vertex_index(col + 1, row));
      unsigned int i2 = static_cast<unsigned int>(vertex_index(col, row + 1));
      unsigned int i3 = static_cast<unsigned int>(vertex_index(col + 1, row + 1));
      mesh.indices.push_back(i0);
      mesh.indices.push_back(i1);
      mesh.indices.push_back(i2);
      mesh.indices.push_back(i1);
      mesh.indices.push_back(i3);
      mesh.indices.push_back(i2);
    }
  }

  compute_terrain_normals_from_dem(mesh, grid, stride, cols, rows);
  return mesh;
}

inline DemMeshData build_textured_dem_mesh(const Geo<MultiBand<FlexGrid>>& dem_grid,
                                           const Geo<MultiBand<FlexGrid>>& texture_grid,
                                           int stride = 1,
                                           OGRCoordinateTransformation* coord_transform = nullptr) {
  DemMeshData mesh;
  const size_t width = dem_grid.width();
  const size_t height = dem_grid.height();
  stride = std::max(1, stride);

  double min_z = std::numeric_limits<double>::infinity();
  double max_z = -std::numeric_limits<double>::infinity();
  const auto& dem_transform = dem_grid.transform();
  const auto& texture_transform = texture_grid.transform();

  for (size_t y = 0; y < height; y += stride) {
    for (size_t x = 0; x < width; x += stride) {
      const double z = flex_grid_value(dem_grid[0], x, y);
      if (is_valid_elevation(z)) {
        min_z = std::min(min_z, z);
        max_z = std::max(max_z, z);
      }
    }
  }
  if (!std::isfinite(min_z)) {
    min_z = 0.0;
    max_z = 1.0;
  }

  mesh.has_texture = true;
  const size_t cols = (width + stride - 1) / stride;
  const size_t rows = (height + stride - 1) / stride;
  auto vertex_index = [&](size_t col, size_t row) { return row * cols + col; };

  for (size_t row = 0; row < rows; ++row) {
    for (size_t col = 0; col < cols; ++col) {
      const size_t x = std::min(col * stride, width - 1);
      const size_t y = std::min(row * stride, height - 1);
      Coordinate2D<double> coord = dem_transform.pixel_to_projection({x + 0.5, y + 0.5});
      double z = flex_grid_value(dem_grid[0], x, y);
      if (!is_valid_elevation(z)) {
        z = min_z;
      }

      double vx = coord.x();
      double vy = coord.y();
      if (coord_transform && !transform_xy_h(coord_transform, vx, vy)) {
        Fail("Failed to reproject textured DEM mesh vertex.");
      }

      const auto [u, v] = texture_uv_from_projection(texture_transform, texture_grid.width(),
                                                     texture_grid.height(), coord);
      mesh.vertices.push_back(vx);
      mesh.vertices.push_back(vy);
      mesh.vertices.push_back(z);
      mesh.texcoords.push_back(u);
      mesh.texcoords.push_back(v);
      mesh.extent.grow(vx, vy, z);
    }
  }

  for (size_t row = 0; row + 1 < rows; ++row) {
    for (size_t col = 0; col + 1 < cols; ++col) {
      unsigned int i0 = static_cast<unsigned int>(vertex_index(col, row));
      unsigned int i1 = static_cast<unsigned int>(vertex_index(col + 1, row));
      unsigned int i2 = static_cast<unsigned int>(vertex_index(col, row + 1));
      unsigned int i3 = static_cast<unsigned int>(vertex_index(col + 1, row + 1));
      mesh.indices.push_back(i0);
      mesh.indices.push_back(i1);
      mesh.indices.push_back(i2);
      mesh.indices.push_back(i1);
      mesh.indices.push_back(i3);
      mesh.indices.push_back(i2);
    }
  }

  compute_terrain_normals_from_dem(mesh, dem_grid, stride, cols, rows);
  return mesh;
}

inline void reproject_dem_mesh_horizontal(DemMeshData& mesh, OGRCoordinateTransformation* ct) {
  if (!ct) return;
  mesh.extent = Extent3D();
  for (size_t i = 0; i + 2 < mesh.vertices.size(); i += 3) {
    double& x = mesh.vertices[i];
    double& y = mesh.vertices[i + 1];
    const double z = mesh.vertices[i + 2];
    if (!transform_xy_h(ct, x, y)) {
      Fail("Failed to reproject DEM mesh vertex.");
    }
    mesh.extent.grow(x, y, z);
  }
}

inline DemMeshData build_slope_colored_mesh(const Geo<MultiBand<FlexGrid>>& slope_grid,
                                            const Geo<MultiBand<FlexGrid>>& dem_grid,
                                            int stride = 1) {
  DemMeshData mesh;
  const size_t width = slope_grid.width();
  const size_t height = slope_grid.height();
  stride = std::max(1, stride);

  const auto& slope_transform = slope_grid.transform();
  const auto& dem_transform = dem_grid.transform();
  const size_t cols = (width + stride - 1) / stride;
  const size_t rows = (height + stride - 1) / stride;
  auto vertex_index = [&](size_t col, size_t row) { return row * cols + col; };

  struct VertexScratch {
    double x = 0.0;
    double y = 0.0;
    double z = 0.0;
    float gray = 0.f;
    bool valid_z = false;
  };
  std::vector<VertexScratch> scratch;
  scratch.reserve(cols * rows);

  double min_z = std::numeric_limits<double>::infinity();
  double max_z = -std::numeric_limits<double>::infinity();

  for (size_t row = 0; row < rows; ++row) {
    for (size_t col = 0; col < cols; ++col) {
      const size_t x = std::min(col * stride, width - 1);
      const size_t y = std::min(row * stride, height - 1);
      const Coordinate2D<double> coord = slope_transform.pixel_to_projection({x + 0.5, y + 0.5});
      const Coordinate2D<double> dem_pixel = dem_transform.projection_to_pixel(coord);
      const double z = sample_grid_bilinear(dem_grid[0], dem_pixel.x(), dem_pixel.y());
      const double slope_byte = flex_grid_value(slope_grid[0], x, y);

      VertexScratch vertex;
      vertex.x = coord.x();
      vertex.y = coord.y();
      vertex.z = z;
      vertex.gray = static_cast<float>(std::clamp(slope_byte, 0.0, 255.0) / 255.0);
      vertex.valid_z = is_valid_elevation(z);
      if (vertex.valid_z) {
        min_z = std::min(min_z, z);
        max_z = std::max(max_z, z);
      }
      scratch.push_back(vertex);
    }
  }

  if (!std::isfinite(min_z)) {
    min_z = 0.0;
    max_z = 1.0;
  }
  for (const VertexScratch& vertex : scratch) {
    const double z = vertex.valid_z ? vertex.z : min_z;
    mesh.vertices.push_back(vertex.x);
    mesh.vertices.push_back(vertex.y);
    mesh.vertices.push_back(z);
    mesh.colors.push_back(vertex.gray);
    mesh.colors.push_back(vertex.gray);
    mesh.colors.push_back(vertex.gray);
    mesh.extent.grow(vertex.x, vertex.y, z);
  }

  for (size_t row = 0; row + 1 < rows; ++row) {
    for (size_t col = 0; col + 1 < cols; ++col) {
      unsigned int i0 = static_cast<unsigned int>(vertex_index(col, row));
      unsigned int i1 = static_cast<unsigned int>(vertex_index(col + 1, row));
      unsigned int i2 = static_cast<unsigned int>(vertex_index(col, row + 1));
      unsigned int i3 = static_cast<unsigned int>(vertex_index(col + 1, row + 1));
      mesh.indices.push_back(i0);
      mesh.indices.push_back(i1);
      mesh.indices.push_back(i2);
      mesh.indices.push_back(i1);
      mesh.indices.push_back(i3);
      mesh.indices.push_back(i2);
    }
  }

  compute_terrain_normals_from_dem(mesh, dem_grid, stride, cols, rows);
  return mesh;
}

class AsyncRasterData {
  mutable std::mutex m_mutex;
  GeoProjection m_header_projection;
  GeoProjection m_native_projection;
  Extent3D m_header_extent;
  std::optional<Geo<MultiBand<FlexGrid>>> m_grid;
  std::optional<Geo<MultiBand<FlexGrid>>> m_texture;
  DemMeshData m_mesh;
  std::atomic<bool> m_ready{false};
  std::future<void> m_future;

 public:
  AsyncRasterData(const fs::path& dem_path, AsyncProgressTracker progress_tracker,
                  const std::optional<fs::path>& texture_path = std::nullopt, int stride = 1,
                  bool slope_colored = false,
                  const std::optional<fs::path>& slope_path = std::nullopt,
                  std::function<void()> on_ready = {}, const std::string& target_crs_wkt = {}) {
    TifMetadata metadata = read_tif_metadata(dem_path);
    m_header_projection = std::move(metadata.projection);
    m_native_projection = m_header_projection;
    m_header_extent = metadata.extent;
    if (!target_crs_wkt.empty()) {
      if (auto ct = make_coord_transform(m_header_projection.to_string(), target_crs_wkt)) {
        m_header_extent = reproject_extent3d_horizontal(m_header_extent, ct.get());
        m_header_projection = make_projection_from_wkt(target_crs_wkt);
      }
    }

    m_future =
        std::async(std::launch::async, [this, dem_path, texture_path, slope_path, slope_colored,
                                        stride, progress_tracker, on_ready = std::move(on_ready),
                                        target_crs_wkt]() mutable {
          ProgressTracker tracker = progress_tracker.tracker()->subtracker(0, 1.0);
          tracker.text_update("Loading raster " + dem_path.string());
          auto dem = read_tif(dem_path);
          std::optional<Geo<MultiBand<FlexGrid>>> loaded_texture;
          if (texture_path) {
            loaded_texture = read_tif(*texture_path);
          }
          std::unique_ptr<OGRCoordinateTransformation> coord_transform =
              make_coord_transform(m_native_projection.to_string(), target_crs_wkt);
          DemMeshData mesh;
          if (slope_colored && slope_path) {
            auto slope = read_tif(*slope_path);
            mesh = build_slope_colored_mesh(slope, dem, stride);
            reproject_dem_mesh_horizontal(mesh, coord_transform.get());
          } else if (loaded_texture) {
            mesh = build_textured_dem_mesh(dem, *loaded_texture, stride, coord_transform.get());
          } else {
            mesh = build_dem_mesh(dem, stride, nullptr);
            reproject_dem_mesh_horizontal(mesh, coord_transform.get());
          }
          {
            std::lock_guard<std::mutex> lock(m_mutex);
            m_grid = std::move(dem);
            if (loaded_texture) {
              m_texture = std::move(*loaded_texture);
            }
            m_mesh = std::move(mesh);
            m_ready.store(true, std::memory_order_release);
          }
          if (on_ready) {
            on_ready();
          }
        });
  }

  std::mutex& mutex() const { return m_mutex; }
  bool ready() const { return m_ready.load(std::memory_order_acquire); }
  bool has_texture() const {
    std::lock_guard<std::mutex> lock(m_mutex);
    return m_texture.has_value();
  }
  // Caller must hold mutex().
  const DemMeshData& mesh() const { return m_mesh; }
  // Caller must hold mutex().
  const Geo<MultiBand<FlexGrid>>& texture_grid() const {
    Assert(m_texture.has_value(), "No texture loaded");
    return *m_texture;
  }
  const GeoProjection& projection() const { return m_header_projection; }
  const GeoProjection& native_projection() const { return m_native_projection; }
  Extent3D extent() const {
    if (m_ready && m_mesh.extent.max_extent() > 0) {
      return m_mesh.extent;
    }
    return m_header_extent;
  }
};
