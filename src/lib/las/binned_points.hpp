#pragma once

#include <atomic>
#include <span>
#include <vector>

#include "grid/grid.hpp"
#include "las/las_file.hpp"
#include "las/las_point.hpp"
#include "utilities/progress_tracker.hpp"

class BinnedPoints : public Geo<Grid<std::span<LASPoint>>> {
  std::vector<LASPoint> m_storage;

 public:
  BinnedPoints(LASData& las_file, double bin_resolution, unsigned int downsample_factor,
               ProgressTracker progress)
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
    std::vector<LASPoint> row_sorted;

    progress.text_update("Counting points per row...");

#pragma omp parallel
    {
      std::vector<size_t> hist(rows, 0);
      int thread_idx = -1;

      // Pass 1a: count points per row.
#pragma omp for nowait
      for (long long i = 0; i < n; i++) {
        const LASPoint& point = las_file[static_cast<size_t>(i)];
        if (!extent.contains(point.x(), point.y())) {
          num_out_of_bounds.fetch_add(1, std::memory_order_relaxed);
          continue;
        }
        auto pixel = transform.projection_to_pixel(Coordinate2D<double>(point.x(), point.y()));
        if (pixel.x() < 0 || pixel.x() >= static_cast<double>(cols) || pixel.y() < 0 ||
            pixel.y() >= static_cast<double>(rows)) {
          num_out_of_bounds.fetch_add(1, std::memory_order_relaxed);
          continue;
        }
        auto cell = pixel.round_down();
        if (!this->in_bounds(cell)) {
          num_out_of_bounds.fetch_add(1, std::memory_order_relaxed);
          continue;
        }
        hist[cell.y()]++;
      }

#pragma omp critical
      {
        thread_idx = static_cast<int>(thread_hists.size());
        thread_hists.push_back(std::move(hist));
      }

#pragma omp barrier

#pragma omp single
      {
        for (const auto& h : thread_hists)
          for (size_t row = 0; row < rows; row++) row_counts[row] += h[row];

        for (size_t row = 0; row < rows; row++)
          row_offsets[row + 1] = row_offsets[row] + row_counts[row];
        total_points = row_offsets[rows];

        progress.set_proportion(0.25);
        progress.text_update("Sorting points by row...");

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
      }
      // implicit barrier

      // Pass 1b: place points into row-sorted array.
      auto write_heads = thread_write_starts[thread_idx];

#pragma omp for nowait
      for (long long i = 0; i < n; i++) {
        const LASPoint& point = las_file[static_cast<size_t>(i)];
        if (!extent.contains(point.x(), point.y())) continue;
        auto pixel = transform.projection_to_pixel(Coordinate2D<double>(point.x(), point.y()));
        if (pixel.x() < 0 || pixel.x() >= static_cast<double>(cols) || pixel.y() < 0 ||
            pixel.y() >= static_cast<double>(rows))
          continue;
        auto cell = pixel.round_down();
        if (!this->in_bounds(cell)) continue;
        row_sorted[write_heads[cell.y()]++] = point;
      }
    }

    progress.set_proportion(0.50);

    // ---- Phase 2: within each row, bin by fine cell ----

    progress.text_update("Placing points into cells...");

    m_storage.resize(total_points);

#pragma omp parallel
    {
      std::vector<size_t> row_cell_counts(cols);
      std::vector<size_t> col_offsets(cols);

#pragma omp for nowait
      for (long long r = 0; r < static_cast<long long>(rows); r++) {
        size_t row = static_cast<size_t>(r);
        if (row_offsets[row + 1] == row_offsets[row]) continue;

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
          (*this)[{col, row}] = std::span<LASPoint>(base + col_offsets[col], row_cell_counts[col]);
        }
      }
    }

    progress.set_proportion(1.0);

    if (num_out_of_bounds.load(std::memory_order_relaxed) > 0) {
      std::cerr << "Warning: " << num_out_of_bounds.load(std::memory_order_relaxed)
                << " points were out of bounds and were not included in the processing.\n";
    }
  }
};
