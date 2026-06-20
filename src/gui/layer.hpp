#pragma once

#include <QMetaObject>
#include <QObject>
#include <algorithm>
#include <array>
#include <atomic>
#include <future>
#include <mutex>
#include <vector>

#include "contour/contour.hpp"
#include "gui/octree_las_data.hpp"
#include "gui/point_cloud_visualization.hpp"
#include "gui/raster_data.hpp"
#include "io/crs.hpp"
#include "io/gpkg.hpp"
#include "las/las_file.hpp"
#include "utilities/coordinate.hpp"
#include "utilities/filesystem.hpp"
#include "utilities/progress_tracker.hpp"

enum class LayerKind { PointCloud, DemSurface, Contours, SlopeSurface, TexturedDem };

class Layer : public QObject {
  Q_OBJECT

 protected:
  std::string m_name;
  LayerKind m_kind;
  bool m_visible = true;
  float m_opacity = 1.0f;

 signals:
  void data_updated() const;
  void visibility_changed(bool visible) const;
  void opacity_changed() const;

 public:
  Layer(std::string name, LayerKind kind) : m_name(std::move(name)), m_kind(kind) {}
  virtual Extent3D extent() const = 0;
  virtual std::string projection() const = 0;
  virtual std::string native_projection() const { return projection(); }
  virtual std::string name() const { return m_name; }
  LayerKind kind() const { return m_kind; }
  bool visible() const { return m_visible; }
  float opacity() const { return m_opacity; }
  void set_visible(bool visible) {
    if (m_visible != visible) {
      m_visible = visible;
      emit visibility_changed(visible);
    }
  }
  void set_opacity(float opacity) {
    const float clamped = std::clamp(opacity, 0.0f, 1.0f);
    if (m_opacity != clamped) {
      m_opacity = clamped;
      emit opacity_changed();
    }
  }
  virtual ~Layer() = default;
};

class PointLayer : public Layer {
 public:
  PointLayer(std::string name) : Layer(std::move(name), LayerKind::PointCloud) {}
  virtual ~PointLayer() = default;
};

class LASLayer : public PointLayer {
  Q_OBJECT

  fs::path m_file_path;
  AsyncOctreeLASData m_las_data;
  float m_point_radius_m = 0.15f;
  float m_point_alpha = 1.0f;
  float m_point_stream_budget_ms = 30.0f;
  PointColorMode m_point_color_mode = PointColorMode::File;
  std::array<uint8_t, 3> m_fixed_point_color = {217, 230, 255};
  std::array<bool, 256> m_classification_enabled = []() {
    std::array<bool, 256> enabled;
    enabled.fill(true);
    return enabled;
  }();

 signals:
  void point_size_changed() const;
  void point_colors_changed() const;
  void point_opacity_changed() const;
  void point_stream_budget_changed() const;

 public:
  explicit LASLayer(const fs::path& file, AsyncProgressTracker progress_tracker,
                    const std::string& target_crs_wkt = {})
      : PointLayer(file.filename().string()),
        m_file_path(file),
        m_las_data(file, progress_tracker, {[this] {
                     QMetaObject::invokeMethod(this, "notify_data_updated", Qt::QueuedConnection);
                   }},
                   target_crs_wkt) {}

  const fs::path& file_path() const { return m_file_path; }

  float point_radius_m() const { return m_point_radius_m; }
  float point_alpha() const { return m_point_alpha; }
  float point_stream_budget_ms() const { return m_point_stream_budget_ms; }
  PointColorMode point_color_mode() const { return m_point_color_mode; }
  const std::array<uint8_t, 3>& fixed_point_color() const { return m_fixed_point_color; }
  const std::array<bool, 256>& classification_enabled() const { return m_classification_enabled; }

  void set_classification_enabled(uint8_t classification, bool enabled) {
    if (m_classification_enabled[classification] != enabled) {
      m_classification_enabled[classification] = enabled;
      emit point_colors_changed();
    }
  }

  std::vector<uint8_t> present_classifications() const {
    std::vector<uint8_t> classes;
    std::array<bool, 256> present = {};
    const auto snap = m_las_data.snapshot();
    if (snap) {
      if (!snap->octree.points().empty()) {
        for (const auto& pt : snap->octree.points()) {
          present[pt.classification] = true;
        }
      } else {
        for (const auto& pt : snap->preview_points) {
          present[pt.classification] = true;
        }
      }
    }
    for (int i = 0; i < 256; ++i) {
      if (present[i]) {
        classes.push_back(static_cast<uint8_t>(i));
      }
    }
    return classes;
  }

  void set_point_radius_m(float radius_m) {
    const float clamped = std::clamp(radius_m, 0.008f, 1.2f);
    if (m_point_radius_m != clamped) {
      m_point_radius_m = clamped;
      emit point_size_changed();
    }
  }

  void set_point_alpha(float alpha) {
    const float clamped = std::clamp(alpha, 0.0f, 1.0f);
    if (m_point_alpha != clamped) {
      m_point_alpha = clamped;
      emit point_opacity_changed();
    }
  }

  void set_point_stream_budget_ms(float ms) {
    const float clamped = std::clamp(ms, 8.0f, 200.0f);
    if (m_point_stream_budget_ms != clamped) {
      m_point_stream_budget_ms = clamped;
      emit point_stream_budget_changed();
    }
  }

  void set_point_color_mode(PointColorMode mode) {
    if (m_point_color_mode != mode) {
      m_point_color_mode = mode;
      emit point_colors_changed();
    }
  }

  void set_fixed_point_color(const std::array<uint8_t, 3>& color) {
    if (m_fixed_point_color != color) {
      m_fixed_point_color = color;
      if (m_point_color_mode == PointColorMode::Fixed) {
        emit point_colors_changed();
      }
    }
  }

  virtual Extent3D extent() const override { return m_las_data.bounds(); }
  virtual std::string projection() const override { return m_las_data.projection().to_string(); }
  virtual std::string native_projection() const override {
    return m_las_data.native_projection().to_string();
  }

  const AsyncOctreeLASData& las_data() const { return m_las_data; }
  AsyncOctreeLASData& las_data() { return m_las_data; }

 private slots:
  void notify_data_updated() { emit data_updated(); }
};

class DemLayer : public Layer {
  Q_OBJECT

  AsyncRasterData m_raster;

 public:
  DemLayer(const fs::path& dem_path, AsyncProgressTracker progress_tracker,
           const std::optional<fs::path>& texture_path = std::nullopt,
           const std::string& target_crs_wkt = {})
      : Layer(dem_path.filename().string(), LayerKind::DemSurface),
        m_raster(
            dem_path, progress_tracker, texture_path,
            [&] {
              const auto dims = read_tif_dimensions(dem_path);
              return adaptive_dem_stride(dims[0], dims[1]);
            }(),
            false, std::nullopt,
            [this] {
              QMetaObject::invokeMethod(this, "notify_data_updated", Qt::QueuedConnection);
            },
            target_crs_wkt) {}

  virtual Extent3D extent() const override { return m_raster.extent(); }
  virtual std::string projection() const override { return m_raster.projection().to_string(); }
  virtual std::string native_projection() const override {
    return m_raster.native_projection().to_string();
  }

  const AsyncRasterData& raster() const { return m_raster; }
  AsyncRasterData& raster() { return m_raster; }

 private slots:
  void notify_data_updated() { emit data_updated(); }
};

class SlopeLayer : public Layer {
  Q_OBJECT

  AsyncRasterData m_raster;

 public:
  SlopeLayer(const fs::path& dem_path, const fs::path& slope_path,
             AsyncProgressTracker progress_tracker, const std::string& target_crs_wkt = {})
      : Layer(slope_path.filename().string(), LayerKind::SlopeSurface),
        m_raster(
            dem_path, progress_tracker, std::nullopt,
            [&] {
              const auto dims = read_tif_dimensions(slope_path);
              return adaptive_dem_stride(dims[0], dims[1]);
            }(),
            true, slope_path,
            [this] {
              QMetaObject::invokeMethod(this, "notify_data_updated", Qt::QueuedConnection);
            },
            target_crs_wkt) {}

  virtual Extent3D extent() const override { return m_raster.extent(); }
  virtual std::string projection() const override { return m_raster.projection().to_string(); }
  virtual std::string native_projection() const override {
    return m_raster.native_projection().to_string();
  }

  const AsyncRasterData& raster() const { return m_raster; }
  AsyncRasterData& raster() { return m_raster; }

 private slots:
  void notify_data_updated() { emit data_updated(); }
};

class TexturedDemLayer : public Layer {
  Q_OBJECT

  AsyncRasterData m_raster;

 public:
  TexturedDemLayer(const fs::path& dem_path, const fs::path& texture_path,
                   AsyncProgressTracker progress_tracker, const std::string& target_crs_wkt = {})
      : Layer(texture_path.filename().string(), LayerKind::TexturedDem),
        m_raster(
            dem_path, progress_tracker, texture_path,
            [&] {
              const auto dem_dims = read_tif_dimensions(dem_path);
              const auto tex_dims = read_tif_dimensions(texture_path);
              return adaptive_dem_stride(std::max(dem_dims[0], tex_dims[0]),
                                         std::max(dem_dims[1], tex_dims[1]));
            }(),
            false, std::nullopt,
            [this] {
              QMetaObject::invokeMethod(this, "notify_data_updated", Qt::QueuedConnection);
            },
            target_crs_wkt) {}

  virtual Extent3D extent() const override { return m_raster.extent(); }
  virtual std::string projection() const override { return m_raster.projection().to_string(); }
  virtual std::string native_projection() const override {
    return m_raster.native_projection().to_string();
  }

  const AsyncRasterData& raster() const { return m_raster; }
  AsyncRasterData& raster() { return m_raster; }

 private slots:
  void notify_data_updated() { emit data_updated(); }
};

class ContourLayer : public Layer {
  Q_OBJECT

  mutable std::mutex m_mutex;
  std::vector<Contour> m_contours;
  Extent3D m_extent;
  std::string m_projection;
  std::string m_native_projection;
  std::atomic<bool> m_ready{false};
  std::future<void> m_future;

 public:
  ContourLayer(const fs::path& gpkg_path, AsyncProgressTracker progress_tracker,
               const std::string& target_crs_wkt = {})
      : Layer(gpkg_path.filename().string(), LayerKind::Contours) {
    ensure_gdal_initialized();
    GDALDataset* header_dataset = (GDALDataset*)GDALOpenEx(
        gpkg_path.string().c_str(), GDAL_OF_VECTOR, nullptr, nullptr, nullptr);
    if (header_dataset) {
      m_native_projection =
          make_projection_from_wkt(std::string(header_dataset->GetProjectionRef())).to_string();
      GDALClose(header_dataset);
    }
    m_projection = target_crs_wkt.empty() ? m_native_projection : target_crs_wkt;

    m_future = std::async(
        std::launch::async, [this, gpkg_path, progress_tracker, target_crs_wkt]() mutable {
          ProgressTracker tracker = progress_tracker.tracker()->subtracker(0, 1.0);
          tracker.text_update("Loading contours " + gpkg_path.string());
          auto contours = read_gpkg(gpkg_path);
          const std::string native_projection = m_native_projection;
          std::unique_ptr<OGRCoordinateTransformation> coord_transform =
              make_coord_transform(native_projection, target_crs_wkt);
          if (coord_transform) {
            for (auto& contour : contours) {
              for (auto& pt : contour.points()) {
                double x = pt.x();
                double y = pt.y();
                if (!transform_xy_h(coord_transform.get(), x, y)) {
                  Fail("Failed to reproject contour vertex.");
                }
                pt = Coordinate2D<double>(x, y);
              }
            }
          }
          Extent3D extent;
          for (const auto& contour : contours) {
            for (const auto& pt : contour.points()) {
              extent.grow(pt.x(), pt.y(), contour.height());
            }
          }
          {
            std::lock_guard<std::mutex> lock(m_mutex);
            m_contours = std::move(contours);
            m_projection = coord_transform ? target_crs_wkt : native_projection;
            m_extent = std::move(extent);
            m_ready.store(true, std::memory_order_release);
          }
          QMetaObject::invokeMethod(this, "notify_data_updated", Qt::QueuedConnection);
        });
  }

 private slots:
  void notify_data_updated() { emit data_updated(); }

 public:
  virtual Extent3D extent() const override {
    std::lock_guard<std::mutex> lock(m_mutex);
    return m_extent;
  }
  virtual std::string projection() const override {
    std::lock_guard<std::mutex> lock(m_mutex);
    return m_projection;
  }
  virtual std::string native_projection() const override {
    std::lock_guard<std::mutex> lock(m_mutex);
    return m_native_projection;
  }
  bool ready() const { return m_ready.load(std::memory_order_acquire); }
  std::vector<Contour> copy_contours() const {
    std::lock_guard<std::mutex> lock(m_mutex);
    return m_contours;
  }
  const std::vector<Contour>& contours() const {
    std::lock_guard<std::mutex> lock(m_mutex);
    return m_contours;
  }
};
