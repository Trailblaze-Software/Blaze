

# File binned\_points.hpp

[**File List**](files.md) **>** [**las**](dir_50e4ddd575fc604ec1609997d931fab5.md) **>** [**binned\_points.hpp**](binned__points_8hpp.md)

[Go to the documentation of this file](binned__points_8hpp.md)


```C++
#pragma once

#include <omp.h>

#include <atomic>
#include <span>
#include <vector>

#include "grid/grid.hpp"
#include "las/las_file.hpp"
#include "las/las_point.hpp"
#include "utilities/progress_tracker.hpp"
#include "utilities/tracked_allocator.hpp"

class BinnedPoints : public Geo<Grid<std::span<LASPoint>>> {
  blaze::memory_tracker::LasVector<LASPoint> m_storage;

 public:
  BinnedPoints(LASData& las_file, double bin_resolution, unsigned int downsample_factor,
               ProgressTracker&& progress_tracker)
      : Geo<Grid<std::span<LASPoint>>>(
            num_cells_by_distance(las_file.width() + downsample_factor * bin_resolution,
                                  bin_resolution),
            num_cells_by_distance(las_file.height() + downsample_factor * bin_resolution,
                                  bin_resolution),
            GeoTransform(las_file.top_left().round_NW(bin_resolution * downsample_factor),
                         bin_resolution),
            GeoProjection(las_file.projection())) {
    const size_t cols = this->width();
    const size_t rows = this->height();
    const size_t num_points = las_file.n_points();
    const long long n = static_cast<long long>(num_points);

    const Extent2D extent = *this->extent();
    const GeoTransform& transform = this->transform();
    std::atomic<size_t> num_out_of_bounds{0};

    // ---- Phase 1: sort points by grid row ----

    std::vector<std::vector<size_t>> thread_hists;
    std::vector<std::vector<size_t>> thread_write_starts;
    std::vector<size_t> row_counts(rows, 0);
    std::vector<size_t> row_offsets(rows + 1, 0);
    size_t total_points = 0;
    blaze::memory_tracker::LasVector<LASPoint> row_sorted;

    START_TRACKER("binning LAS points");

    std::atomic<long long> points_done{0};
    const long long progress_step = std::max(1LL, n / 1000);
    const auto report_points_done = [&](ProgressTracker& tracker) {
      const long long done = points_done.fetch_add(1, std::memory_order_relaxed) + 1;
      if (done % progress_step == 0 || done == n) {
        tracker.report_parallel_progress(static_cast<double>(done) / static_cast<double>(n));
      }
    };

    {
      ProgressTracker count_tracker = progress_tracker.subtracker(0.0, 0.20, "count rows");
      START_TRACKER(count_tracker, "counting points per row");
      points_done.store(0, std::memory_order_relaxed);

#pragma omp parallel
      {
#pragma omp single
        {
          thread_hists.assign(static_cast<size_t>(omp_get_num_threads()),
                              std::vector<size_t>(rows, 0));
        }
#pragma omp barrier
        const int thread_idx = omp_get_thread_num();
        std::vector<size_t>& hist = thread_hists[static_cast<size_t>(thread_idx)];

        // Pass 1a: count points per row. Static schedule: each thread owns a slice of
        // indices and its histogram bucket (must match pass 1b).
#pragma omp for schedule(static) nowait
        for (long long i = 0; i < n; i++) {
          const LASPoint& point = las_file[static_cast<size_t>(i)];
          if (!extent.contains(point.x(), point.y())) {
            num_out_of_bounds.fetch_add(1, std::memory_order_relaxed);
            report_points_done(count_tracker);
            continue;
          }
          auto pixel = transform.projection_to_pixel(Coordinate2D<double>(point.x(), point.y()));
          if (pixel.x() < 0 || pixel.x() >= static_cast<double>(cols) || pixel.y() < 0 ||
              pixel.y() >= static_cast<double>(rows)) {
            num_out_of_bounds.fetch_add(1, std::memory_order_relaxed);
            report_points_done(count_tracker);
            continue;
          }
          auto cell = pixel.round_down();
          if (!this->in_bounds(cell)) {
            num_out_of_bounds.fetch_add(1, std::memory_order_relaxed);
            report_points_done(count_tracker);
            continue;
          }
          hist[cell.y()]++;
          report_points_done(count_tracker);
        }
      }
    }

    for (const auto& h : thread_hists)
      for (size_t row = 0; row < rows; row++) row_counts[row] += h[row];

    for (size_t row = 0; row < rows; row++)
      row_offsets[row + 1] = row_offsets[row] + row_counts[row];
    total_points = row_offsets[rows];

    row_sorted.resize(total_points);

    thread_write_starts.resize(thread_hists.size());
    for (size_t t = 0; t < thread_hists.size(); t++) thread_write_starts[t].resize(rows);
    for (size_t row = 0; row < rows; row++) {
      size_t running = row_offsets[row];
      for (size_t t = 0; t < thread_hists.size(); t++) {
        thread_write_starts[t][row] = running;
        running += thread_hists[t][row];
      }
    }

    {
      ProgressTracker sort_tracker = progress_tracker.subtracker(0.20, 0.50, "sort rows");
      START_TRACKER(sort_tracker, "sorting points by row");
      points_done.store(0, std::memory_order_relaxed);

#pragma omp parallel
      {
        const int thread_idx = omp_get_thread_num();
        auto write_heads = thread_write_starts[static_cast<size_t>(thread_idx)];

        // Pass 1b: place points into row-sorted array (static schedule; see pass 1a).
#pragma omp for schedule(static) nowait
        for (long long i = 0; i < n; i++) {
          const LASPoint& point = las_file[static_cast<size_t>(i)];
          if (!extent.contains(point.x(), point.y())) {
            report_points_done(sort_tracker);
            continue;
          }
          auto pixel = transform.projection_to_pixel(Coordinate2D<double>(point.x(), point.y()));
          if (pixel.x() < 0 || pixel.x() >= static_cast<double>(cols) || pixel.y() < 0 ||
              pixel.y() >= static_cast<double>(rows)) {
            report_points_done(sort_tracker);
            continue;
          }
          auto cell = pixel.round_down();
          if (!this->in_bounds(cell)) {
            report_points_done(sort_tracker);
            continue;
          }
          row_sorted[write_heads[cell.y()]++] = point;
          report_points_done(sort_tracker);
        }
      }
    }

    las_file.release_points();

    // ---- Phase 2: within each row, bin by fine cell ----

    {
      ProgressTracker place_tracker = progress_tracker.subtracker(0.50, 1.0, "place cells");
      START_TRACKER(place_tracker, "placing points into cells");

      m_storage.resize(total_points);

      const long long row_count = static_cast<long long>(rows);
      std::atomic<long long> rows_done{0};
      const long long row_progress_step = std::max(1LL, row_count / 500);

#pragma omp parallel
      {
        std::vector<size_t> row_cell_counts(cols);
        std::vector<size_t> col_offsets(cols);

#pragma omp for schedule(dynamic, 1) nowait
        for (long long r = 0; r < row_count; r++) {
          size_t row = static_cast<size_t>(r);
          if (row_offsets[row + 1] == row_offsets[row]) {
            const long long done = rows_done.fetch_add(1, std::memory_order_relaxed) + 1;
            if (done % row_progress_step == 0 || done == row_count) {
              place_tracker.report_parallel_progress(static_cast<double>(done) /
                                                     static_cast<double>(rows));
            }
            continue;
          }

          std::fill(row_cell_counts.begin(), row_cell_counts.end(), 0);
          for (size_t i = row_offsets[row]; i < row_offsets[row + 1]; i++) {
            auto pixel = transform.projection_to_pixel(
                Coordinate2D<double>(row_sorted[i].x(), row_sorted[i].y()));
            row_cell_counts[pixel.round_down().x()]++;
          }

          size_t offset = row_offsets[row];
          for (size_t col = 0; col < cols; col++) {
            col_offsets[col] = offset;
            offset += row_cell_counts[col];
          }
          auto wh = col_offsets;

          for (size_t i = row_offsets[row]; i < row_offsets[row + 1]; i++) {
            const LASPoint& point = row_sorted[i];
            auto pixel = transform.projection_to_pixel(Coordinate2D<double>(point.x(), point.y()));
            m_storage[wh[pixel.round_down().x()]++] = point;
          }

          LASPoint* base = m_storage.data();
          for (size_t col = 0; col < cols; col++) {
            (*this)[{col, row}] =
                std::span<LASPoint>(base + col_offsets[col], row_cell_counts[col]);
          }

          const long long done = rows_done.fetch_add(1, std::memory_order_relaxed) + 1;
          if (done % row_progress_step == 0 || done == row_count) {
            place_tracker.report_parallel_progress(static_cast<double>(done) /
                                                   static_cast<double>(rows));
          }
        }
      }
    }

    row_sorted.clear();
    row_sorted.shrink_to_fit();

    if (num_out_of_bounds.load(std::memory_order_relaxed) > 0) {
      std::cerr << "Warning: " << num_out_of_bounds.load(std::memory_order_relaxed)
                << " points were out of bounds and were not included in the processing.\n";
    }
  }

  // Bounding extent of non-empty cells in projection coordinates.
  // Uses cell corners (not centers) so slice() includes edge cells fully.
  Extent2D data_extent() const {
    Extent2D ext;
    bool any = false;
    for (size_t row = 0; row < this->height(); row++) {
      for (size_t col = 0; col < this->width(); col++) {
        if (!(*this)[{col, row}].empty()) {
          any = true;
          auto c0 = this->transform().pixel_to_projection(
              {static_cast<double>(col), static_cast<double>(row)});
          auto c1 = this->transform().pixel_to_projection(
              {static_cast<double>(col + 1), static_cast<double>(row + 1)});
          ext.grow(Extent2D{std::min(c0.x(), c1.x()), std::max(c0.x(), c1.x()),
                            std::min(c0.y(), c1.y()), std::max(c0.y(), c1.y())});
        }
      }
    }
    if (!any) {
      const Extent2D grid_ext = *this->extent();
      return {grid_ext.minx, grid_ext.minx, grid_ext.miny, grid_ext.miny};
    }
    return ext;
  }
};
```


