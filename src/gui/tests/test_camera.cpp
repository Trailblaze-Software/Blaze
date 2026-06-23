#include <gtest/gtest.h>

#include <QPointF>
#include <QVector3D>
#include <cmath>

#include "gui/camera.hpp"

namespace {

constexpr double kTol = 1e-4;

QVector3D focal_point(const Camera& camera) { return camera.position() + camera.direction(); }

}  // namespace

TEST(Camera, PanToTargetMovesFocalPointToTarget) {
  Camera camera(800, 600);
  const QVector3D target(12.0f, -3.0f, 7.0f);
  const float focal_distance = camera.direction().length();

  camera.pan_to_target(target);

  const QVector3D focal_after = focal_point(camera);
  EXPECT_NEAR(focal_after.x(), target.x(), kTol);
  EXPECT_NEAR(focal_after.y(), target.y(), kTol);
  EXPECT_NEAR(focal_after.z(), target.z(), kTol);
  EXPECT_NEAR(camera.direction().length(), focal_distance, kTol);
}

TEST(Camera, PanToTargetNoOpWhenAlreadyCentered) {
  Camera camera(800, 600);
  const QVector3D before_pos = camera.position();
  const QVector3D before_dir = camera.direction();

  camera.pan_to_target(focal_point(camera));

  EXPECT_EQ(camera.position(), before_pos);
  EXPECT_EQ(camera.direction(), before_dir);
}

TEST(Camera, LookAtTargetReorientsWithoutMovingPosition) {
  Camera camera(800, 600);
  const QVector3D before_pos = camera.position();
  const QVector3D target(0.0f, 0.0f, 0.0f);

  camera.look_at_target(target);

  EXPECT_EQ(camera.position(), before_pos);
  const QVector3D dir = camera.direction().normalized();
  const QVector3D expected = (target - before_pos).normalized();
  EXPECT_NEAR(dir.x(), expected.x(), kTol);
  EXPECT_NEAR(dir.y(), expected.y(), kTol);
  EXPECT_NEAR(dir.z(), expected.z(), kTol);
}

TEST(Camera, ProjectWorldToScreenRoundTripsWithUnproject) {
  Camera camera(1024, 768);
  camera.set_scene_bounds(QVector3D(0, 0, 0), 1000.0f);
  const QVector3D world = camera.position() + camera.direction() * 0.5f;

  const auto screen = camera.project_world_to_screen(world);
  ASSERT_TRUE(screen.has_value());
  ASSERT_GE(screen->x(), 0.0);
  ASSERT_GE(screen->y(), 0.0);
  ASSERT_LE(screen->x(), camera.screen_width());
  ASSERT_LE(screen->y(), camera.screen_height());

  const QVector3D unprojected = camera.unproject(*screen);
  const QVector3D view_dir = (unprojected - camera.position()).normalized();
  const QVector3D to_world = (world - camera.position()).normalized();
  EXPECT_NEAR(view_dir.x(), to_world.x(), 0.02);
  EXPECT_NEAR(view_dir.y(), to_world.y(), 0.02);
  EXPECT_NEAR(view_dir.z(), to_world.z(), 0.02);
}

TEST(Camera, ProjectWorldToScreenBehindCameraReturnsSentinel) {
  Camera camera(800, 600);
  const QVector3D behind = camera.position() - camera.direction();

  const auto screen = camera.project_world_to_screen(behind);
  EXPECT_FALSE(screen.has_value());
}
