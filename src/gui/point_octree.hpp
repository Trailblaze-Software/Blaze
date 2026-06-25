#pragma once

#include <algorithm>
#include <array>
#include <atomic>
#include <cmath>
#include <cstdint>
#include <functional>
#include <memory>
#include <random>
#include <vector>

#include "gui/frustum.hpp"
#include "utilities/coordinate.hpp"

// AoS layout: one struct per point, contiguous in m_points. Matches GPU interleaved
// attributes and allows zero-copy glBufferSubData slices per octree leaf.
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

// Fast Fisher-Yates shuffle with xorshift64 — shared by both classes.
inline void octree_shuffle_range(std::vector<OctreePoint>& points, size_t begin, size_t end) {
  if (end <= begin + 1) return;
  static thread_local uint64_t rng_state = std::random_device{}();
  for (size_t i = end - 1; i > begin; --i) {
    uint64_t x = rng_state;
    x ^= x << 13;
    x ^= x >> 7;
    x ^= x << 17;
    rng_state = x;
    std::swap(points[i], points[begin + static_cast<size_t>(x % (i - begin + 1))]);
  }
}

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
    octree_shuffle_range(points, begin_index, end_index);
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

  // Builds the octree from points (taking ownership). progress, if set, is
  // called with (points_processed, total). cancel, if set and observed true,
  // aborts the build promptly so a destructor join does not stall.
  void insert_batch(std::vector<OctreePoint>&& points,
                    const std::function<void(size_t, size_t)>& progress = {},
                    const std::atomic<bool>* cancel = nullptr);

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
    constexpr double DRAW_ALL_DISTANCE = 100.0;
    const double dist = std::max(10.0, lod_distance);
    const double clamped_quality = std::clamp(quality, 0.05, 64.0);
    const double desired_fraction =
        std::min(1.0, clamped_quality * std::pow(DRAW_ALL_DISTANCE / dist, 2.0));
    return std::max(size_t{1}, static_cast<size_t>(std::ceil(point_count * desired_fraction)));
  }

  // The frustum's clip matrix and camera_local must already be expressed in this
  // octree's file-local coordinates (the caller folds the layer offset into the
  // matrix), so node bounds are tested directly with no per-node translation.
  void collect_visible(const Frustum& frustum, double quality,
                       const Coordinate3D<double>& camera_local,
                       std::vector<VisibleNode>& out) const {
    out.clear();
    if (!m_root) {
      return;
    }
    collect_visible_recursive(*m_root, frustum, quality, camera_local, out);
  }

 private:
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

  void collect_visible_recursive(const PointOctreeNode& node, const Frustum& frustum,
                                 double quality, const Coordinate3D<double>& camera_local,
                                 std::vector<VisibleNode>& out) const {
    if (!frustum.intersects(node.bounds)) {
      return;
    }
    if (node.has_children()) {
      for (const auto& child : node.children) {
        if (child) {
          collect_visible_recursive(*child, frustum, quality, camera_local, out);
        }
      }
    }
    const size_t point_count = node.point_count();
    if (point_count == 0) {
      return;
    }
    const double lod_distance = lod_distance_to_node(node.bounds, camera_local);
    out.push_back({&node, node_draw_chunk_size(point_count, lod_distance, quality), lod_distance});
  }
};
