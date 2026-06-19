#pragma once

#include <QMatrix4x4>
#include <algorithm>

#include "utilities/coordinate.hpp"

inline double deg2rad(double deg) { return deg * M_PI / 180.0f; }

inline double rad2deg(double rad) { return rad * 180.0f / M_PI; }

class Camera {
  QVector3D m_position;
  QVector3D m_direction;
  QVector3D m_up;

  Coordinate3D<double> m_world_offset;

  int m_width;
  int m_height;
  double m_device_pixel_ratio = 1.0;

  // Scene bounding sphere in camera-local coords (relative to world_offset).
  // Used to keep the far plane large enough that in-view geometry is never
  // culled when the focal distance shrinks on zoom-in. Radius <= 0 means unset.
  QVector3D m_scene_center;
  float m_scene_radius = 0.0f;

  double m_fov = 45.0f;

 public:
  Camera(int width, int height)
      : m_position(1, 1, 1),
        m_direction(-1, -1, -1),
        m_up(0, 0, 1),
        m_width(width),
        m_height(height) {}

  Camera(const QVector3D& position, const QVector3D& direction, const QVector3D& up)
      : m_position(position), m_direction(direction), m_up(up) {}

  void move(const QVector3D& direction) { m_position += direction; }
  void move_towards(const QVector3D& world_pos, double distance, bool shrink_direction = false) {
    QVector3D direction = world_pos - m_position;
    m_position += direction.normalized() * distance;
    if (shrink_direction) {
      if (distance < 0 || (m_direction.length() > 1 && m_direction.length() > distance))
        m_direction -= m_direction.normalized() * distance;
      else
        m_direction = m_direction.normalized();
    }
  }

  const Coordinate3D<double>& world_offset() const { return m_world_offset; }
  Coordinate3D<double>& world_offset() { return m_world_offset; }

  void set_screen_size(int width, int height) {
    m_width = width;
    m_height = height;
  }

  void set_device_pixel_ratio(double ratio) { m_device_pixel_ratio = ratio > 0.0 ? ratio : 1.0; }

  void set_scene_bounds(const QVector3D& center, float radius) {
    m_scene_center = center;
    m_scene_radius = radius;
  }

  // Framebuffer height in physical pixels (gl_PointSize is in physical pixels).
  double framebuffer_height() const { return m_height * m_device_pixel_ratio; }

  void reset_to_origin() {
    m_position = QVector3D(1, 1, 1);
    m_direction = QVector3D(-1, -1, -1);
    m_up = QVector3D(0, 0, 1);
  }

  QVector3D view_right() const { return QVector3D::crossProduct(m_up, m_direction).normalized(); }
  QVector3D view_up() const {
    return QVector3D::crossProduct(m_direction, view_right()).normalized();
  }
  QVector3D planar_direction() const {
    return QVector3D(m_direction.x(), m_direction.y(), 0).normalized();
  }

  void pan(double dx, double dy) {
    m_position += (view_right() * dx + view_up() * dy) * m_direction.length();
  }

  void fly(double dx, double dy, double dz) {
    m_position += (planar_direction() * dx + view_right() * dy + m_up * dz) * m_direction.length();
  }

  void zoom_to_fit(const Extent3D& extent) {
    if (extent.max_extent() <= 0 || m_width <= 0 || m_height <= 0) {
      return;
    }
    double max_extent = extent.max_extent();
    QVector3D qcenter(extent.maxx + extent.minx, extent.maxy + extent.miny,
                      extent.maxz + extent.minz);
    qcenter /= 2;
    m_position = qcenter - 10 * m_direction.normalized() * max_extent;

    QMatrix4x4 proj = proj_matrix();

    float zoom_out_amount = 0.0f;
    for (size_t i = 0; i < 2; i++) {
      for (size_t j = 0; j < 2; j++) {
        for (size_t k = 0; k < 2; k++) {
          QVector3D corner(i == 0 ? extent.minx : extent.maxx, j == 0 ? extent.miny : extent.maxy,
                           k == 0 ? extent.minz : extent.maxz);
          QVector3D screen_pos = proj.map(corner);
          zoom_out_amount = std::max(zoom_out_amount,
                                     std::max(std::abs(screen_pos.x()), std::abs(screen_pos.y())));
        }
      }
    }

    m_position = qcenter - m_direction.normalized() * 10 * max_extent * zoom_out_amount;
    m_direction = qcenter - m_position;
  }

  void rotate_view(double dx, double dy) { rotate_around_center(dx, dy, m_position); }

  double current_altitude_angle() const {
    return std::asin(m_direction.z() / m_direction.length());
  }

  double projection_scale() const { return m_height / (2.0f * std::tan(deg2rad(m_fov) / 2)); }

  double fov_rad() const { return deg2rad(m_fov); }

 private:
  double bound_rotation(double current_angle, double angle, double min_angle, double max_angle) {
    if (current_angle + angle > max_angle) {
      angle = max_angle - current_angle;
    } else if (current_angle + angle < min_angle) {
      angle = min_angle - current_angle;
    }
    return angle;
  }

 public:
  void rotate_around_center(double dx, double dy,
                            const std::optional<QVector3D>& center = std::nullopt) {
    QVector3D cor = center.value_or(m_position + m_direction);

    QMatrix4x4 rotation;
    rotation.rotate(-dx, m_up);
    double angle_to_rotate =
        bound_rotation(rad2deg(current_altitude_angle()), -dy, -90 + 1e-2, 90 - 1e-2);
    rotation.rotate(-angle_to_rotate, view_right());
    m_direction = rotation.map(m_direction);
    m_position = cor - (m_position - cor).length() * m_direction.normalized();
  }

  // Reorient the view to look at target without moving the camera position.
  // The target becomes the orbit pivot (m_position + m_direction).
  void look_at_target(const QVector3D& target) {
    const QVector3D offset = target - m_position;
    if (offset.lengthSquared() < 1e-8f) {
      return;
    }
    m_direction = offset;
  }

  // Projection (perspective) matrix only — no view transform.
  QMatrix4x4 projection_matrix() const {
    QMatrix4x4 proj;
    const double view_distance = std::max(static_cast<double>(m_direction.length()), 0.1);
    const float near_plane =
        static_cast<float>(std::clamp(view_distance * 0.002, 0.01, view_distance * 0.1));
    double far_plane = view_distance * 50.0;
    // Extend the far plane to enclose the whole scene so distant-but-visible
    // nodes are not culled when the focal distance shrinks on zoom-in.
    if (m_scene_radius > 0.0f) {
      const double dist_to_center = (m_position - m_scene_center).length();
      far_plane = std::max(far_plane, dist_to_center + m_scene_radius * 1.05 + 1.0);
    }
    proj.perspective(m_fov, (double)m_width / m_height, near_plane, static_cast<float>(far_plane));
    return proj;
  }

  // View (eye/lookAt) matrix only.
  QMatrix4x4 view_matrix() const {
    QMatrix4x4 view;
    view.lookAt(m_position, m_position + m_direction, m_up);
    return view;
  }

  QMatrix4x4 proj_matrix() const { return projection_matrix() * view_matrix(); }

  int screen_width() const { return m_width; }
  int screen_height() const { return m_height; }

  struct PickRay {
    QVector3D origin;
    QVector3D direction;
  };

  PickRay pick_ray(const QPointF& screen_pos) const {
    const QRect viewport(0, 0, m_width, m_height);
    QMatrix4x4 identity;
    identity.setToIdentity();
    const QMatrix4x4 proj = proj_matrix();
    const float win_y = static_cast<float>(m_height) - static_cast<float>(screen_pos.y());
    const QVector3D win_near(static_cast<float>(screen_pos.x()), win_y, 0.0f);
    const QVector3D win_far(static_cast<float>(screen_pos.x()), win_y, 1.0f);
    const QVector3D origin = win_near.unproject(proj, identity, viewport);
    const QVector3D far_pt = win_far.unproject(proj, identity, viewport);
    const QVector3D direction = (far_pt - origin).normalized();
    return {origin, direction};
  }

  QVector3D unproject(const QPointF& screen_pos) const {
    QVector3D screen(screen_pos.x(), m_height - screen_pos.y(), 0);
    return screen.unproject(proj_matrix(), QMatrix4x4(), QRect(0, 0, m_width, m_height));
  }

  const QVector3D& position() const { return m_position; }
  const QVector3D& direction() const { return m_direction; }
  const QVector3D& up() const { return m_up; }
  QVector3D focal_point() const { return m_position + m_direction; }
};
