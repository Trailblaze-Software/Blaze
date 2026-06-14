#pragma once

#include <omp.h>

#include <algorithm>
#include <array>
#include <atomic>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <functional>
#include <memory>
#include <random>
#include <thread>
#include <vector>

#include "gui/frustum.hpp"
#include "utilities/coordinate.hpp"

class PointOctreeNode;

// AoS layout: one struct per point, contiguous in m_points. Matches GPU interleaved
// attributes and allows zero-copy glBufferSubData slices per octree leaf (Displaz-style).
struct OctreePoint {
  float x;
  float y;
  float z;
  uint16_t intensity = 0;
  uint8_t classification = 0;
  uint8_t file_r = 0;
  uint8_t file_g = 0;
  uint8_t file_b = 0;
  uint8_t has_file_rgb = 0;
};

class PointOctreeNode {
 public:
  static constexpr size_t MAX_POINTS = 32'000;
  static constexpr int MAX_DEPTH = 20;

  Extent3D bounds;
  size_t begin_index = 0;
  size_t end_index = 0;
  std::array<std::unique_ptr<PointOctreeNode>, 8> children;
  int depth = 0;

  size_t point_count() const { return end_index - begin_index; }

  bool has_children() const {
    return std::any_of(children.begin(), children.end(),
                       [](const auto& child) { return child != nullptr; });
  }

  int child_index(const OctreePoint& point) const {
    const double midx = (bounds.minx + bounds.maxx) * 0.5;
    const double midy = (bounds.miny + bounds.maxy) * 0.5;
    const double midz = (bounds.minz + bounds.maxz) * 0.5;
    int index = 0;
    if (point.x >= midx) index |= 1;
    if (point.y >= midy) index |= 2;
    if (point.z >= midz) index |= 4;
    return index;
  }

  void ensure_child(int idx) {
    if (children[static_cast<size_t>(idx)]) {
      return;
    }
    const double midx = (bounds.minx + bounds.maxx) * 0.5;
    const double midy = (bounds.miny + bounds.maxy) * 0.5;
    const double midz = (bounds.minz + bounds.maxz) * 0.5;
    const double minx = (idx & 1) ? midx : bounds.minx;
    const double maxx = (idx & 1) ? bounds.maxx : midx;
    const double miny = (idx & 2) ? midy : bounds.miny;
    const double maxy = (idx & 2) ? bounds.maxy : midy;
    const double minz = (idx & 4) ? midz : bounds.minz;
    const double maxz = (idx & 4) ? bounds.maxz : midz;
    children[static_cast<size_t>(idx)] = std::make_unique<PointOctreeNode>();
    children[static_cast<size_t>(idx)]->bounds = Extent3D(minx, maxx, miny, maxy, minz, maxz);
    children[static_cast<size_t>(idx)]->depth = depth + 1;
  }

  void shuffle_range(std::vector<OctreePoint>& points) const {
    if (end_index <= begin_index + 1) {
      return;
    }
    static thread_local std::mt19937 rng{std::random_device{}()};
    std::shuffle(points.begin() + static_cast<std::ptrdiff_t>(begin_index),
                 points.begin() + static_cast<std::ptrdiff_t>(end_index), rng);
  }

  void shuffle_recursive(std::vector<OctreePoint>& points) {
    shuffle_range(points);
    for (const auto& child : children) {
      if (child) {
        child->shuffle_recursive(points);
      }
    }
  }
};

class PointOctree {
  std::unique_ptr<PointOctreeNode> m_root;
  std::vector<OctreePoint> m_points;
  size_t m_total_points = 0;

  // Displaz expands the data AABB to a cube so octree splits are unbiased on each axis.
  static Extent3D cubic_root_bounds(const Extent3D& data_bounds) {
    const double cx = 0.5 * (data_bounds.minx + data_bounds.maxx);
    const double cy = 0.5 * (data_bounds.miny + data_bounds.maxy);
    const double cz = 0.5 * (data_bounds.minz + data_bounds.maxz);
    const double dx = data_bounds.maxx - data_bounds.minx;
    const double dy = data_bounds.maxy - data_bounds.miny;
    const double dz = data_bounds.maxz - data_bounds.minz;
    double half = 0.5 * std::max({dx, dy, dz});
    if (half < 1e-3) {
      half = 0.5;
    }
    return {cx - half, cx + half, cy - half, cy + half, cz - half, cz + half};
  }

 public:
  PointOctree() {
    m_root = std::make_unique<PointOctreeNode>();
    m_root->bounds = Extent3D(0.0, 1.0, 0.0, 1.0, 0.0, 1.0);
  }

  explicit PointOctree(const Extent3D& bounds) {
    m_root = std::make_unique<PointOctreeNode>();
    m_root->bounds = cubic_root_bounds(bounds);
  }

  size_t total_points() const { return m_total_points; }
  const PointOctreeNode* root() const { return m_root.get(); }
  const std::vector<OctreePoint>& points() const { return m_points; }

  void insert_batch(std::vector<OctreePoint>&& points,
                    const std::function<void(size_t, size_t)>& progress = {}) {
    m_points = std::move(points);
    m_total_points = m_points.size();
    if (m_points.empty() || !m_root) {
      return;
    }

    std::atomic<size_t> processed{0};
    const size_t total = m_total_points;

    auto report_build_progress = [&](double expand_fraction) {
      if (!progress) {
        return;
      }
      const double expand_frac = std::clamp(expand_fraction, 0.0, 1.0);
      const double build_frac =
          total > 0 ? static_cast<double>(processed.load(std::memory_order_relaxed)) / total : 1.0;
      const double combined = 0.35 * expand_frac + 0.65 * build_frac;
      progress(static_cast<size_t>(combined * total), total);
    };

    std::vector<BuildJob> jobs;
    jobs.reserve(256);
    jobs.push_back({m_root.get(), 0, m_total_points});

    const size_t target_jobs = static_cast<size_t>(std::max(1, omp_get_max_threads())) * 4;
    size_t expand_idx = 0;
    while (expand_idx < jobs.size() && jobs.size() < target_jobs) {
      BuildJob& job = jobs[expand_idx];
      if (job.end <= job.begin || job.end - job.begin <= kParallelBuildMinPoints ||
          job.node->depth >= PointOctreeNode::MAX_DEPTH ||
          job.end - job.begin <= PointOctreeNode::MAX_POINTS) {
        ++expand_idx;
        if (expand_idx % 4 == 0) {
          report_build_progress(static_cast<double>(expand_idx) / std::max(jobs.size(), size_t{1}));
        }
        continue;
      }
      BuildJob split_job = job;
      jobs[expand_idx] = std::move(jobs.back());
      jobs.pop_back();
      split_subtree_job(*split_job.node, split_job.begin, split_job.end, m_points, jobs);
      if (expand_idx % 4 == 0) {
        report_build_progress(static_cast<double>(expand_idx) / std::max(jobs.size(), size_t{1}));
      }
    }
    report_build_progress(1.0);

    std::atomic<bool> build_done{false};
    std::thread progress_thread;
    if (progress) {
      progress_thread = std::thread([&]() {
        while (!build_done.load(std::memory_order_acquire)) {
          report_build_progress(1.0);
          std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }
      });
    }

#pragma omp parallel for schedule(dynamic)
    for (ptrdiff_t job_idx = 0; job_idx < static_cast<ptrdiff_t>(jobs.size()); ++job_idx) {
      BuildJob job = jobs[static_cast<size_t>(job_idx)];
      if (job.end <= job.begin) {
        continue;
      }
      build_subtree_sequential(*job.node, job.begin, job.end, m_points, processed, total, progress);
    }

    build_done.store(true, std::memory_order_release);
    if (progress_thread.joinable()) {
      progress_thread.join();
    }
    if (progress) {
      progress(total, total);
    }
  }

  void shuffle_leaves() {
    if (m_root) {
      m_root->shuffle_recursive(m_points);
    }
  }

  struct VisibleNode {
    const PointOctreeNode* node = nullptr;
    size_t chunk_size = 1;
    double lod_distance = 0.0;
  };

  static size_t node_draw_chunk_size(size_t point_count, double lod_distance, double quality) {
    if (point_count <= 1) {
      return point_count;
    }
    constexpr double kDrawAllDistance = 100.0;
    const double dist = std::max(10.0, lod_distance);
    const double clamped_quality = std::clamp(quality, 0.05, 64.0);
    const double desired_fraction =
        std::min(1.0, clamped_quality * std::pow(kDrawAllDistance / dist, 2.0));
    return std::max(size_t{1}, static_cast<size_t>(std::ceil(point_count * desired_fraction)));
  }

  void collect_visible(const Frustum& frustum, double projection_scale, double quality,
                       const Coordinate3D<double>& scene_offset,
                       const Coordinate3D<double>& file_origin,
                       const Coordinate3D<double>& camera_local,
                       std::vector<VisibleNode>& out) const {
    (void)projection_scale;
    out.clear();
    if (!m_root) {
      return;
    }
    collect_visible_recursive(*m_root, frustum, quality, scene_offset, file_origin, camera_local,
                              out);
  }

 private:
  struct BuildJob {
    PointOctreeNode* node = nullptr;
    size_t begin = 0;
    size_t end = 0;
  };

  static constexpr size_t kParallelBuildMinPoints = 64'000;

  static void shuffle_range(std::vector<OctreePoint>& points, size_t begin, size_t end) {
    if (end <= begin + 1) {
      return;
    }
    static thread_local std::mt19937 rng{std::random_device{}()};
    std::shuffle(points.begin() + static_cast<std::ptrdiff_t>(begin),
                 points.begin() + static_cast<std::ptrdiff_t>(end), rng);
  }

  static void partition_range(PointOctreeNode& node, std::vector<OctreePoint>& points, size_t begin,
                              size_t end, std::array<size_t, 9>& child_ends) {
    const size_t count = end - begin;
    std::vector<OctreePoint> temp(count);
    std::array<size_t, 8> bucket_counts{};
    for (size_t i = begin; i < end; ++i) {
      ++bucket_counts[static_cast<size_t>(node.child_index(points[i]))];
    }
    child_ends[0] = begin;
    for (int i = 0; i < 8; ++i) {
      child_ends[static_cast<size_t>(i + 1)] =
          child_ends[static_cast<size_t>(i)] + bucket_counts[static_cast<size_t>(i)];
    }
    std::array<size_t, 8> write_pos = {child_ends[0], child_ends[1], child_ends[2], child_ends[3],
                                       child_ends[4], child_ends[5], child_ends[6], child_ends[7]};
    for (size_t i = begin; i < end; ++i) {
      temp[i - begin] = points[i];
    }
    for (size_t i = 0; i < count; ++i) {
      const int child = node.child_index(temp[i]);
      points[write_pos[static_cast<size_t>(child)]++] = temp[i];
    }
  }

  static void split_subtree_job(PointOctreeNode& node, size_t begin, size_t end,
                                std::vector<OctreePoint>& points, std::vector<BuildJob>& out_jobs) {
    shuffle_range(points, begin, end);
    node.begin_index = 0;
    node.end_index = 0;

    std::array<size_t, 9> child_ends{};
    partition_range(node, points, begin, end, child_ends);

    for (int i = 0; i < 8; ++i) {
      const size_t child_begin = child_ends[static_cast<size_t>(i)];
      const size_t child_end = child_ends[static_cast<size_t>(i + 1)];
      if (child_begin == child_end) {
        continue;
      }
      node.ensure_child(i);
      out_jobs.push_back({node.children[static_cast<size_t>(i)].get(), child_begin, child_end});
    }
  }

  static void build_subtree_sequential(PointOctreeNode& node, size_t begin, size_t end,
                                       std::vector<OctreePoint>& points,
                                       std::atomic<size_t>& processed, size_t total,
                                       const std::function<void(size_t, size_t)>& progress) {
    (void)total;
    (void)progress;
    if (end <= begin) {
      return;
    }

    const size_t count = end - begin;
    if (count <= PointOctreeNode::MAX_POINTS || node.depth >= PointOctreeNode::MAX_DEPTH) {
      node.begin_index = begin;
      node.end_index = end;
      processed.fetch_add(count, std::memory_order_relaxed);
      return;
    }

    std::vector<BuildJob> child_jobs;
    child_jobs.reserve(8);
    split_subtree_job(node, begin, end, points, child_jobs);
    for (auto& child_job : child_jobs) {
      build_subtree_sequential(*child_job.node, child_job.begin, child_job.end, points, processed,
                               total, progress);
    }
  }

  static double lod_distance_to_node(const Extent3D& bounds,
                                     const Coordinate3D<double>& camera_local) {
    const Coordinate3D<double> center(0.5 * (bounds.minx + bounds.maxx),
                                      0.5 * (bounds.miny + bounds.maxy),
                                      0.5 * (bounds.minz + bounds.maxz));
    const double dx = center.x() - camera_local.x();
    const double dy = center.y() - camera_local.y();
    const double dz = center.z() - camera_local.z();
    const double camera_distance = std::sqrt(dx * dx + dy * dy + dz * dz);
    const double diag_radius = 0.5 * bounds.max_extent() * std::sqrt(3.0);
    return std::max(10.0, camera_distance - diag_radius);
  }

  static Extent3D to_scene_local(const Extent3D& file_bounds,
                                 const Coordinate3D<double>& file_origin,
                                 const Coordinate3D<double>& scene_offset) {
    const double dx = file_origin.x() - scene_offset.x();
    const double dy = file_origin.y() - scene_offset.y();
    const double dz = file_origin.z() - scene_offset.z();
    return {file_bounds.minx + dx, file_bounds.maxx + dx, file_bounds.miny + dy,
            file_bounds.maxy + dy, file_bounds.minz + dz, file_bounds.maxz + dz};
  }

  void collect_visible_recursive(const PointOctreeNode& node, const Frustum& frustum,
                                 double quality, const Coordinate3D<double>& scene_offset,
                                 const Coordinate3D<double>& file_origin,
                                 const Coordinate3D<double>& camera_local,
                                 std::vector<VisibleNode>& out) const {
    const Extent3D local_bounds = to_scene_local(node.bounds, file_origin, scene_offset);

    if (node.has_children()) {
      for (const auto& child : node.children) {
        if (!child) {
          continue;
        }
        const Extent3D child_bounds = to_scene_local(child->bounds, file_origin, scene_offset);
        if (!frustum.intersects_branch(child_bounds)) {
          continue;
        }
        collect_visible_recursive(*child, frustum, quality, scene_offset, file_origin, camera_local,
                                  out);
      }
    }

    const size_t point_count = node.point_count();
    if (point_count == 0) {
      return;
    }
    if (!frustum.intersects_leaf(local_bounds)) {
      return;
    }
    const double lod_distance = lod_distance_to_node(local_bounds, camera_local);
    out.push_back({&node, node_draw_chunk_size(point_count, lod_distance, quality), lod_distance});
  }
};
