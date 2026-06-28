

# File octree\_las\_data.hpp

[**File List**](files.md) **>** [**gui**](dir_99d0482cf009f9d97a0877749b817f19.md) **>** [**octree\_las\_data.hpp**](octree__las__data_8hpp.md)

[Go to the documentation of this file](octree__las__data_8hpp.md)


```C++
#pragma once

#include <omp.h>

#include <algorithm>
#include <atomic>
#include <chrono>
#include <functional>
#include <iostream>
#include <memory>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

#include "gui/point_octree.hpp"
#include "io/crs.hpp"
#include "las/las_file.hpp"
#include "utilities/progress_tracker.hpp"

#ifndef USE_PDAL
#include "las_reader.hpp"

namespace octree_las_detail {

// Simple RAII timer for benchmarking.
struct BenchTimer {
  using Clock = std::chrono::high_resolution_clock;
  const char* m_label;
  size_t m_point_count;
  Clock::time_point m_start;
  BenchTimer(const char* label, size_t n = 0)
      : m_label(label), m_point_count(n), m_start(Clock::now()) {}
  ~BenchTimer() {
    auto ms = std::chrono::duration<double, std::milli>(Clock::now() - m_start).count();
    if (m_point_count > 0) {
      std::cerr << "[blaze bench] [" << m_label << "] " << ms << " ms  ("
                << static_cast<double>(m_point_count) / (ms * 1000.0) << " M pts/s)" << std::endl;
    } else {
      std::cerr << "[blaze bench] [" << m_label << "] " << ms << " ms" << std::endl;
    }
  }
};

static constexpr size_t MAX_PREVIEW_POINTS = 500'000;

// ProgressTracker requires monotonically increasing proportions; parallel loaders
// must funnel updates through here.
class MonotonicProgress {
  ProgressTracker& m_tracker;
  std::mutex m_mutex;
  double m_last = -1.0;

 public:
  explicit MonotonicProgress(ProgressTracker& tracker) : m_tracker(tracker) {}

  void set_proportion(double proportion) {
    std::lock_guard<std::mutex> lock(m_mutex);
    if (proportion <= m_last) {
      return;
    }
    m_last = proportion;
    m_tracker.set_proportion(proportion);
  }
};

template <typename LasPt>
uint8_t las_point_classification(const LasPt& pt) {
  if constexpr (requires { pt.classification(); }) {
    return static_cast<uint8_t>(pt.classification());
  } else {
    return static_cast<uint8_t>(pt.classification);
  }
}

template <typename LasPt>
void las_point_file_color(const LasPt& pt, OctreePoint& out) {
  if constexpr (requires {
                  pt.red;
                  pt.green;
                  pt.blue;
                }) {
    out.file_r = static_cast<uint8_t>(pt.red >> 8);
    out.file_g = static_cast<uint8_t>(pt.green >> 8);
    out.file_b = static_cast<uint8_t>(pt.blue >> 8);
    out.has_file_rgb = (pt.red | pt.green | pt.blue) != 0 ? uint8_t{1} : uint8_t{0};
  } else {
    out.has_file_rgb = 0;
  }
}

template <typename LasPt>
OctreePoint convert_las_point(const LasPt& pt, const laspp::LASHeader& header,
                              OGRCoordinateTransformation* coord_transform,
                              const Coordinate3D<double>& origin) {
  const auto& transform = header.transform();
  const auto coords = transform.transform_point(pt.x, pt.y, pt.z);
  double x = coords.x();
  double y = coords.y();
  if (coord_transform && !transform_xy_h(coord_transform, x, y)) {
    Fail("Failed to reproject LAS point coordinates.");
  }
  OctreePoint octree_point;
  octree_point.x = static_cast<float>(x - origin.x());
  octree_point.y = static_cast<float>(y - origin.y());
  octree_point.z = static_cast<float>(coords.z() - origin.z());
  octree_point.intensity = pt.intensity;
  octree_point.classification = las_point_classification(pt);
  las_point_file_color(pt, octree_point);
  return octree_point;
}

using PreviewCallback = std::function<void(const OctreePointVector& preview, size_t points_loaded,
                                           const Extent3D& bounds)>;

template <typename LasPt>
inline void load_points_parallel(laspp::LASReader& reader,
                                 OGRCoordinateTransformation* coord_transform,
                                 const Coordinate3D<double>& origin, size_t preview_stride,
                                 OctreePointVector& converted, OctreePointVector& preview,
                                 Extent3D& bounds, ProgressTracker& tracker,
                                 const PreviewCallback& publish_preview,
                                 const std::atomic<bool>* cancel = nullptr) {
  MonotonicProgress progress(tracker);
  const size_t num_points = reader.num_points();
  const size_t num_chunks = reader.num_chunks();
  const auto& points_per_chunk = reader.points_per_chunk();

  BenchTimer total_timer("load total", num_points);
  double decompress_ms = 0;
  double convert_ms = 0;

  converted.resize(num_points);
  preview.reserve(std::min(num_points / preview_stride + 1, MAX_PREVIEW_POINTS));
  bounds = Extent3D();

  // Read in batches: parallel decompression within each batch, incremental progress
  // and previews between batches. Progress range: 0.0→0.35 decompress, 0.35→0.70 convert+bounds.
  constexpr size_t BATCH_CHUNKS = 64;
  size_t converted_offset = 0;
  if (num_points > 0) progress.set_proportion(0.0);

  for (size_t batch_start = 0; batch_start < num_chunks; batch_start += BATCH_CHUNKS) {
    if (cancel && cancel->load(std::memory_order_relaxed)) return;

    const size_t batch_end = std::min(batch_start + BATCH_CHUNKS, num_chunks);
    size_t batch_points = 0;
    for (size_t ci = batch_start; ci < batch_end; ++ci) {
      batch_points += points_per_chunk[ci];
    }

    // Show progress advancing into this batch before the (blocking) decompress.
    if (num_points > 0) {
      progress.set_proportion(0.35 * static_cast<double>(converted_offset) / num_points);
    }

    auto t0 = std::chrono::high_resolution_clock::now();
    blaze::memory_tracker::LasVector<LasPt> raw_batch(batch_points);
    reader.read_chunks(std::span<LasPt>(raw_batch), {batch_start, batch_end});
    auto t1 = std::chrono::high_resolution_clock::now();
    decompress_ms += std::chrono::duration<double, std::milli>(t1 - t0).count();

    if (num_points > 0) {
      progress.set_proportion(0.35 * static_cast<double>(converted_offset + batch_points) /
                              num_points);
    }

    // Convert batch in parallel.
    auto tc0 = std::chrono::high_resolution_clock::now();
    if (coord_transform) {
      for (size_t i = 0; i < batch_points; ++i) {
        converted[converted_offset + i] =
            convert_las_point(raw_batch[i], reader.header(), coord_transform, origin);
      }
    } else {
#pragma omp parallel for schedule(static)
      for (ptrdiff_t i = 0; i < static_cast<ptrdiff_t>(batch_points); ++i) {
        converted[converted_offset + static_cast<size_t>(i)] =
            convert_las_point(raw_batch[static_cast<size_t>(i)], reader.header(), nullptr, origin);
      }
    }
    auto tc1 = std::chrono::high_resolution_clock::now();
    convert_ms += std::chrono::duration<double, std::milli>(tc1 - tc0).count();

    // Grow bounds and extract preview for this batch.
    for (size_t i = 0; i < batch_points; ++i) {
      const size_t global_i = converted_offset + i;
      if (global_i % preview_stride == 0 && preview.size() < MAX_PREVIEW_POINTS) {
        preview.push_back(converted[global_i]);
      }
      const OctreePoint& point = converted[global_i];
      bounds.grow(point.x + origin.x(), point.y + origin.y(), point.z + origin.z());
    }

    converted_offset += batch_points;
    if (num_points > 0) {
      progress.set_proportion(0.35 + 0.35 * static_cast<double>(converted_offset) / num_points);
    }

    // Publish incremental preview so the user sees points appearing.
    if (!preview.empty() && publish_preview) {
      publish_preview(preview, converted_offset, bounds);
    }
  }

  std::cerr << "[blaze bench]   decompress: " << decompress_ms << " ms  convert: " << convert_ms
            << " ms" << std::endl;

  progress.set_proportion(0.72);
}

inline bool las_point_format_has_rgb(uint8_t point_format) {
  switch (point_format & 0x7Fu) {
    case 2:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
      return true;
    default:
      return false;
  }
}

inline void load_points_dispatch(laspp::LASReader& reader,
                                 OGRCoordinateTransformation* coord_transform,
                                 const Coordinate3D<double>& origin, size_t preview_stride,
                                 OctreePointVector& converted, OctreePointVector& preview,
                                 Extent3D& bounds, ProgressTracker& tracker,
                                 const PreviewCallback& publish_preview,
                                 const std::atomic<bool>* cancel = nullptr) {
  switch (reader.header().point_format() & 0x7Fu) {
    case 0:
      load_points_parallel<laspp::LASPointFormat0>(reader, coord_transform, origin, preview_stride,
                                                   converted, preview, bounds, tracker,
                                                   publish_preview, cancel);
      break;
    case 1:
      load_points_parallel<laspp::LASPointFormat1>(reader, coord_transform, origin, preview_stride,
                                                   converted, preview, bounds, tracker,
                                                   publish_preview, cancel);
      break;
    case 2:
      load_points_parallel<laspp::LASPointFormat2>(reader, coord_transform, origin, preview_stride,
                                                   converted, preview, bounds, tracker,
                                                   publish_preview, cancel);
      break;
    case 3:
      load_points_parallel<laspp::LASPointFormat3>(reader, coord_transform, origin, preview_stride,
                                                   converted, preview, bounds, tracker,
                                                   publish_preview, cancel);
      break;
    case 6:
      load_points_parallel<laspp::LASPointFormat6>(reader, coord_transform, origin, preview_stride,
                                                   converted, preview, bounds, tracker,
                                                   publish_preview, cancel);
      break;
    case 7:
      load_points_parallel<laspp::LASPointFormat7>(reader, coord_transform, origin, preview_stride,
                                                   converted, preview, bounds, tracker,
                                                   publish_preview, cancel);
      break;
    default:
      Fail("Unsupported LAS point format in Blaze3D octree loader: " +
           std::to_string(reader.header().point_format() & 0x7Fu));
  }
}

}  // namespace octree_las_detail
#endif

// Immutable point cloud state published by the loader thread. Renderers hold a
// shared_ptr for the duration of a frame.
struct LasRenderSnapshot {
  PointOctree octree;
  OctreePointVector preview_points;
  size_t points_loaded = 0;
  Extent3D bounds;
  bool bounds_valid = false;
};

// Thread-safe published snapshot pointer. Uses std::atomic<std::shared_ptr>
// when the standard library provides it (libstdc++ 12+, recent libc++/MSVC);
// otherwise a mutex — avoids the C++20-deprecated atomic_{load,store} free
// functions for shared_ptr.
class AtomicSnapshotPtr {
#if defined(__cpp_lib_atomic_shared_ptr) && __cpp_lib_atomic_shared_ptr >= 201711L
  std::atomic<std::shared_ptr<const LasRenderSnapshot>> m_value;

 public:
  void store(std::shared_ptr<const LasRenderSnapshot> value) {
    m_value.store(std::move(value), std::memory_order_release);
  }

  std::shared_ptr<const LasRenderSnapshot> load() const {
    return m_value.load(std::memory_order_acquire);
  }
#else
  mutable std::mutex m_mutex;
  std::shared_ptr<const LasRenderSnapshot> m_value;

 public:
  void store(std::shared_ptr<const LasRenderSnapshot> value) {
    std::lock_guard lock(m_mutex);
    m_value = std::move(value);
  }

  std::shared_ptr<const LasRenderSnapshot> load() const {
    std::lock_guard lock(m_mutex);
    return m_value;
  }
#endif
};

class AsyncOctreeLASData {
 public:
  static constexpr size_t MAX_PREVIEW_POINTS = 500'000;

 private:
  Extent3D m_initial_bounds;
  Coordinate3D<double> m_coordinate_origin;
  GeoProjection m_projection;
  GeoProjection m_native_projection;
  size_t m_total_points = 0;
  bool m_point_format_has_rgb = false;
  std::atomic<bool> m_has_rgb_data{false};
  AtomicSnapshotPtr m_snapshot;
  std::atomic<bool> m_load_complete{false};
  std::atomic<bool> m_cancel{false};
  std::thread m_thread;

  void publish_snapshot(std::shared_ptr<const LasRenderSnapshot> snapshot) {
    m_snapshot.store(std::move(snapshot));
  }

 public:
  AsyncOctreeLASData(const fs::path& filename, AsyncProgressTracker progress_tracker,
                     std::vector<std::function<void()>> callbacks = {},
                     const std::string& target_crs_wkt = {})
      : m_projection("") {
#ifndef USE_PDAL
    laspp::LASReader reader(filename);
    m_initial_bounds = as_extent3d(reader.header().bounds());
    m_total_points = reader.num_points();
    m_point_format_has_rgb =
        octree_las_detail::las_point_format_has_rgb(reader.header().point_format());
    std::string wkt = reader_embedded_wkt(reader);
    if (!wkt.empty()) {
      m_projection = make_projection_from_wkt(wkt);
      m_native_projection = m_projection;
    }

    std::unique_ptr<OGRCoordinateTransformation> coord_transform =
        make_coord_transform(m_projection.to_string(), target_crs_wkt);
    if (coord_transform) {
      m_initial_bounds = reproject_extent3d_horizontal(m_initial_bounds, coord_transform.get());
      m_projection = make_projection_from_wkt(target_crs_wkt);
    }

    m_coordinate_origin = m_initial_bounds.center();

    m_thread = std::thread([this, filename, origin = m_coordinate_origin,
                            local_bounds = m_initial_bounds - m_coordinate_origin,
                            progress_tracker = std::move(progress_tracker),
                            callbacks = std::move(callbacks),
                            coord_transform = std::move(coord_transform)]() mutable {
      octree_las_detail::BenchTimer file_timer("load file", m_total_points);
      std::cerr << "[blaze bench] " << filename.string() << "  points=" << m_total_points
                << std::endl;

      laspp::LASReader reader(filename);
      ProgressTracker& root_tracker = *progress_tracker.tracker();
      ProgressTracker tracker = SUBTRACKER(0.0, 1.0, root_tracker);
      START_TRACKER(tracker, "load " + filename.filename().string());

      const size_t preview_stride =
          std::max(size_t{1}, (m_total_points + MAX_PREVIEW_POINTS - 1) / MAX_PREVIEW_POINTS);

      OctreePointVector converted;
      OctreePointVector preview;
      Extent3D bounds;
      bool preview_callbacks_fired = false;
      const auto publish_preview = [this, &preview_callbacks_fired, &callbacks](
                                       const OctreePointVector& preview_pts, size_t points_loaded,
                                       const Extent3D& loaded_bounds) {
        auto preview_snapshot = std::make_shared<LasRenderSnapshot>();
        preview_snapshot->preview_points = preview_pts;
        preview_snapshot->points_loaded = points_loaded;
        preview_snapshot->bounds = loaded_bounds;
        preview_snapshot->bounds_valid = true;
        publish_snapshot(std::move(preview_snapshot));
        if (!preview_callbacks_fired) {
          preview_callbacks_fired = true;
          for (const auto& callback : callbacks) {
            callback();
          }
        }
      };
      octree_las_detail::load_points_dispatch(reader, coord_transform.get(), origin, preview_stride,
                                              converted, preview, bounds, tracker, publish_preview,
                                              &m_cancel);

      if (m_cancel.load(std::memory_order_relaxed)) {
        return;
      }

      if (m_point_format_has_rgb) {
        const bool has_rgb =
            std::any_of(converted.begin(), converted.end(),
                        [](const OctreePoint& point) { return point.has_file_rgb != 0; });
        m_has_rgb_data.store(has_rgb, std::memory_order_release);
      }

      tracker.set_proportion(0.72);
      octree_las_detail::MonotonicProgress octree_progress(tracker);

      {
        octree_las_detail::BenchTimer octree_timer("build octree", converted.size());
        PointOctree octree(local_bounds);
        octree.insert_batch(
            std::move(converted),
            [&octree_progress](size_t done, size_t total) {
              octree_progress.set_proportion(0.72 + 0.26 * static_cast<double>(done) / total);
            },
            &m_cancel);
        if (m_cancel.load(std::memory_order_relaxed)) {
          return;
        }
        octree.shuffle_leaves();
        octree_progress.set_proportion(0.99);

        auto final_snapshot = std::make_shared<LasRenderSnapshot>();
        final_snapshot->octree = std::move(octree);
        final_snapshot->points_loaded = final_snapshot->octree.total_points();
        final_snapshot->bounds = bounds;
        final_snapshot->bounds_valid = true;
        publish_snapshot(std::move(final_snapshot));
      }

      m_load_complete.store(true, std::memory_order_release);

      tracker.set_proportion(1.0);
      if (m_cancel.load(std::memory_order_relaxed)) {
        return;
      }
      for (const auto& callback : callbacks) {
        callback();
      }
    });
#else
    (void)filename;
    (void)progress_tracker;
    (void)callbacks;
    (void)target_crs_wkt;
    Fail("Blaze3D octree LAS loading requires las++ (BLAZE_USE_PDAL=OFF)");
#endif
  }

  ~AsyncOctreeLASData() {
    // Always join: the load loop and octree build both poll m_cancel, so the
    // join returns promptly. Detaching would let the worker keep writing through
    // this object (and run callbacks on the owning LASLayer) after it is freed —
    // a use-after-free when a still-loading layer is removed.
    m_cancel.store(true, std::memory_order_release);
    if (m_thread.joinable()) {
      m_thread.join();
    }
  }

  std::shared_ptr<const LasRenderSnapshot> snapshot() const { return m_snapshot.load(); }

  Extent3D bounds() const {
    if (!load_complete()) {
      return m_initial_bounds;
    }
    const auto snap = snapshot();
    if (snap && snap->bounds_valid) {
      return snap->bounds;
    }
    return m_initial_bounds;
  }
  const Coordinate3D<double>& coordinate_origin() const { return m_coordinate_origin; }
  const GeoProjection& projection() const { return m_projection; }
  const GeoProjection& native_projection() const { return m_native_projection; }

  size_t points_loaded() const {
    const auto snap = snapshot();
    return snap ? snap->points_loaded : 0;
  }

  size_t total_points() const { return m_total_points; }
  bool point_format_has_rgb() const { return m_point_format_has_rgb; }
  bool has_rgb_data() const { return m_has_rgb_data.load(std::memory_order_acquire); }
  bool load_complete() const { return m_load_complete.load(std::memory_order_acquire); }
};
```


