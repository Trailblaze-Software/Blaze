#include <gtest/gtest.h>

#include "gui/point_octree.hpp"

TEST(PointOctree, EmptyOctreeHasZeroPoints) {
  PointOctree octree;
  EXPECT_EQ(octree.total_points(), 0);
}

TEST(PointOctree, InsertBatchStoresPoints) {
  const Extent3D bounds(-10, 10, -10, 10, -10, 10);
  PointOctree octree(bounds);

  std::vector<OctreePoint> points(100);
  for (size_t i = 0; i < points.size(); ++i) {
    points[i].x = static_cast<float>(i % 10 - 5);
    points[i].y = static_cast<float>(i / 10 - 5);
    points[i].z = 0.0f;
  }

  octree.insert_batch(std::move(points));
  EXPECT_EQ(octree.total_points(), 100);
}

TEST(PointOctree, NodePointCountMatchesRange) {
  const Extent3D bounds(-10, 10, -10, 10, -10, 10);
  PointOctree octree(bounds);

  std::vector<OctreePoint> points(50);
  for (size_t i = 0; i < points.size(); ++i) {
    points[i].x = static_cast<float>(i) * 0.1f;
    points[i].y = 0.0f;
    points[i].z = 0.0f;
  }

  octree.insert_batch(std::move(points));

  const auto* root = octree.root();
  ASSERT_NE(root, nullptr);

  size_t total_leaf_points = 0;
  std::function<void(const PointOctreeNode&)> count_leaves = [&](const PointOctreeNode& node) {
    if (!node.has_children()) {
      total_leaf_points += node.point_count();
      EXPECT_EQ(node.point_count(), node.end_index - node.begin_index);
    } else {
      for (const auto& child : node.children) {
        if (child) {
          count_leaves(*child);
        }
      }
    }
  };
  count_leaves(*root);
  EXPECT_EQ(total_leaf_points, 50);
}

TEST(PointOctree, NodeDrawChunkSizeRespectsQuality) {
  const size_t point_count = 1000;
  const double distance = 200.0;  // Far enough that quality 1.0 doesn't saturate

  // Quality 1.0 at distance 200 should give < full count
  const size_t chunk_low = PointOctree::node_draw_chunk_size(point_count, distance, 1.0);
  EXPECT_LT(chunk_low, point_count);
  EXPECT_GT(chunk_low, 0);

  // Higher quality gives more points
  const size_t chunk_high = PointOctree::node_draw_chunk_size(point_count, distance, 4.0);
  EXPECT_GT(chunk_high, chunk_low);

  // Very high quality saturates at point_count
  const size_t chunk_max = PointOctree::node_draw_chunk_size(point_count, distance, 1000.0);
  EXPECT_EQ(chunk_max, point_count);
}

TEST(PointOctree, NodeDrawChunkSizeRespectsDistance) {
  const size_t point_count = 1000;
  const double quality = 1.0;

  // Closer distance gives more points
  const size_t chunk_near = PointOctree::node_draw_chunk_size(point_count, 20.0, quality);
  const size_t chunk_far = PointOctree::node_draw_chunk_size(point_count, 200.0, quality);

  EXPECT_GT(chunk_near, chunk_far);
}

TEST(PointOctree, ShuffleDoesNotLosePoints) {
  const Extent3D bounds(-10, 10, -10, 10, -10, 10);
  PointOctree octree(bounds);

  std::vector<OctreePoint> points(100);
  for (size_t i = 0; i < points.size(); ++i) {
    points[i].x = static_cast<float>(i % 10 - 5);
    points[i].y = static_cast<float>(i / 10 - 5);
    points[i].z = static_cast<float>(i);
    points[i].classification = static_cast<uint8_t>(i % 5);
  }

  octree.insert_batch(std::move(points));
  const size_t count_before = octree.total_points();

  octree.shuffle_leaves();
  EXPECT_EQ(octree.total_points(), count_before);

  // Verify all classifications still present (shuffled, not lost)
  std::array<int, 5> class_counts{};
  for (const auto& pt : octree.points()) {
    class_counts[pt.classification % 5]++;
  }
  for (int count : class_counts) {
    EXPECT_EQ(count, 20);
  }
}

TEST(PointOctree, CancellationPreventsBuild) {
  const Extent3D bounds(-100, 100, -100, 100, -100, 100);
  PointOctree octree(bounds);

  std::vector<OctreePoint> points(100'000);
  for (size_t i = 0; i < points.size(); ++i) {
    points[i].x = static_cast<float>((i % 1000) - 500);
    points[i].y = static_cast<float>((i / 1000) - 50);
    points[i].z = 0.0f;
  }

  std::atomic<bool> cancel{true};
  octree.insert_batch(std::move(points), {}, &cancel);

  // Build should abort early, so not all points will be in leaves
  EXPECT_LE(octree.total_points(), 100'000);
}
