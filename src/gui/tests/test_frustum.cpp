#include <gtest/gtest.h>

#include <QMatrix4x4>

#include "gui/frustum.hpp"

TEST(Frustum, IntersectsFullyInsideAABB) {
  QMatrix4x4 identity;
  identity.setToIdentity();
  const Frustum frustum = Frustum::from_matrix(identity);

  const Extent3D inside_box(-0.5, 0.5, -0.5, 0.5, -0.5, 0.5);
  EXPECT_TRUE(frustum.intersects(inside_box));
}

TEST(Frustum, RejectsAABBBehindNearPlane) {
  QMatrix4x4 proj;
  proj.setToIdentity();
  proj.perspective(45.0f, 1.0f, 1.0f, 100.0f);

  QMatrix4x4 view;
  view.setToIdentity();
  view.lookAt(QVector3D(0, 0, 10), QVector3D(0, 0, 0), QVector3D(0, 1, 0));

  const Frustum frustum = Frustum::from_matrix(proj * view);

  // Box behind the camera (z > 10)
  const Extent3D behind_box(-1, 1, -1, 1, 11, 15);
  EXPECT_FALSE(frustum.intersects(behind_box));
}

TEST(Frustum, IntersectsPartiallyVisibleAABB) {
  QMatrix4x4 proj;
  proj.setToIdentity();
  proj.perspective(45.0f, 1.0f, 1.0f, 100.0f);

  QMatrix4x4 view;
  view.setToIdentity();
  view.lookAt(QVector3D(0, 0, 5), QVector3D(0, 0, 0), QVector3D(0, 1, 0));

  const Frustum frustum = Frustum::from_matrix(proj * view);

  // Large box that spans across frustum boundary
  const Extent3D spanning_box(-10, 10, -10, 10, -10, 10);
  EXPECT_TRUE(frustum.intersects(spanning_box));
}

TEST(Frustum, RejectsAABBToTheLeft) {
  QMatrix4x4 proj;
  proj.setToIdentity();
  proj.perspective(45.0f, 1.0f, 1.0f, 100.0f);

  QMatrix4x4 view;
  view.setToIdentity();
  view.lookAt(QVector3D(0, 0, 5), QVector3D(0, 0, 0), QVector3D(0, 1, 0));

  const Frustum frustum = Frustum::from_matrix(proj * view);

  // Box far to the left of the view frustum
  const Extent3D left_box(-100, -50, -1, 1, -5, -1);
  EXPECT_FALSE(frustum.intersects(left_box));
}

TEST(Frustum, IntersectsAABBAtFrustumEdge) {
  QMatrix4x4 proj;
  proj.setToIdentity();
  proj.perspective(60.0f, 1.0f, 0.1f, 100.0f);

  QMatrix4x4 view;
  view.setToIdentity();
  view.lookAt(QVector3D(0, 0, 0), QVector3D(0, 0, -1), QVector3D(0, 1, 0));

  const Frustum frustum = Frustum::from_matrix(proj * view);

  // Box at the right edge of frustum (should be visible)
  const Extent3D edge_box(0.8, 1.2, -0.5, 0.5, -2, -1);
  EXPECT_TRUE(frustum.intersects(edge_box));
}

TEST(Frustum, HandlesZeroSizeAABB) {
  QMatrix4x4 identity;
  identity.setToIdentity();
  const Frustum frustum = Frustum::from_matrix(identity);

  // Point-like AABB (zero volume)
  const Extent3D point_box(0, 0, 0, 0, 0, 0);
  EXPECT_TRUE(frustum.intersects(point_box));
}

TEST(Frustum, ConservativeTestIncludesPartialOverlap) {
  QMatrix4x4 proj;
  proj.setToIdentity();
  proj.perspective(45.0f, 1.0f, 1.0f, 50.0f);

  QMatrix4x4 view;
  view.setToIdentity();
  view.lookAt(QVector3D(0, 0, 10), QVector3D(0, 0, 0), QVector3D(0, 1, 0));

  const Frustum frustum = Frustum::from_matrix(proj * view);

  // Box partially intersecting frustum
  const Extent3D partial_box(-2, 2, -2, 2, -2, 2);
  EXPECT_TRUE(frustum.intersects(partial_box));
}
