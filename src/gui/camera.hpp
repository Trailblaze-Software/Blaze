#pragma once

#include <QMatrix4x4>

#include "utilities/coordinate.hpp"

inline double deg2rad(double deg) { return deg * M_PI / 180.0f; }

inline double rad2deg(double rad) { return rad * 180.0f / M_PI; }

class Camera {
 public:
  Camera(int width, int height)
      : m_position(1, 1, 1),
        m_direction(-1, -1, -1),
        m_up(0, 0, 1),
        m_width(width),
        m_height(height) {}

  Camera(const QVector3D &position, const QVector3D &direction, const QVector3D &up)
      : m_position(position), m_direction(direction), m_up(up) {}

  void move(const QVector3D &direction) { m_position += direction; }
  void move_towards(const QVector3D &world_pos, double distance, bool shrink_direction = false) {
    QVector3D direction = world_pos - m_position;
    m_position += direction.normalized() * distance;
    if (shrink_direction) {
      if (distance < 0 || (m_direction.length() > 1 && m_direction.length() > distance))
        m_direction -= m_direction.normalized() * distance;
      else
        m_direction = m_direction.normalized();
    }
  }

  void set_screen_size(int width, int height) {
    m_width = width;
    m_height = height;
  }

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

  void zoom_to_fit(const Extent3D &extent) {
    // Coordinate3D<double> center = extent.center();
    double max_extent = extent.max_extent();
    QVector3D qcenter(extent.maxx - extent.minx, extent.maxy - extent.miny,
                      extent.maxz - extent.minz);
    qcenter /= 2;
    m_position = qcenter + 10 * m_direction.normalized() * max_extent;

    QMatrix4x4 proj = proj_matrix();

    float zoom_out_amount = 0.0f;
    for (size_t i = 0; i < 2; i++) {
      for (size_t j = 0; j < 2; j++) {
        for (size_t k = 0; k < 2; k++) {
          QVector3D corner(i == 0 ? 0 : extent.maxx - extent.minx,
                           j == 0 ? 0 : extent.maxy - extent.miny,
                           k == 0 ? 0 : extent.maxz - extent.minz);
          QVector3D screen_pos = proj.map(corner);
          zoom_out_amount = std::max(zoom_out_amount,
                                     std::max(std::abs(screen_pos.x()), std::abs(screen_pos.y())));
        }
      }
    }

    m_position = qcenter - m_direction.normalized() * 10 * max_extent * zoom_out_amount;
    m_direction = qcenter - m_position;
    std::cout << "New position: " << m_position.x() << " " << m_position.y() << " "
              << m_position.z() << std::endl;
    std::cout << "New direction: " << m_direction.x() << " " << m_direction.y() << " "
              << m_direction.z() << std::endl;
  }

  void rotate_view(double dx, double dy) { rotate_around_center(dx, dy, m_position); }

  double current_altitude_angle() const {
    return std::asin(m_direction.z() / m_direction.length());
  }

  double projection_scale() const { return m_height / (2.0f * std::tan(deg2rad(m_fov) / 2)); }

 private:
  double bound_rotation(double current_angle, double angle, double min_angle, double max_angle) {
    std::cout << "Bounding rotation: " << current_angle << " " << angle << " " << min_angle << " "
              << max_angle << std::endl;
    if (current_angle + angle > max_angle) {
      angle = max_angle - current_angle;
    } else if (current_angle + angle < min_angle) {
      angle = min_angle - current_angle;
    }
    return angle;
  }

 public:
  void rotate_around_center(double dx, double dy,
                            const std::optional<QVector3D> &center = std::nullopt) {
    QVector3D cor = center.value_or(m_position + m_direction);

    QMatrix4x4 rotation;
    rotation.rotate(-dx, m_up);
    double angle_to_rotate =
        bound_rotation(rad2deg(current_altitude_angle()), -dy, -90 + 1e-2, 90 - 1e-2);
    rotation.rotate(-angle_to_rotate, view_right());
    m_direction = rotation.map(m_direction);
    m_position = cor - (m_position - cor).length() * m_direction.normalized();
  }

  QMatrix4x4 proj_matrix() const {
    QMatrix4x4 proj;
    proj.perspective(m_fov, (double)m_width / m_height, 1e-2, 1e5);
    proj.lookAt(m_position, m_position + m_direction, m_up);
    return proj;
  }

  QVector3D unproject(const QPointF &screen_pos) const {
    QVector3D screen(screen_pos.x(), m_height - screen_pos.y(), 0);
    return screen.unproject(proj_matrix(), QMatrix4x4(), QRect(0, 0, m_width, m_height));
  }

  const QVector3D &position() const { return m_position; }
  const QVector3D &direction() const { return m_direction; }
  const QVector3D &up() const { return m_up; }

 private:
  QVector3D m_position;
  QVector3D m_direction;
  QVector3D m_up;

  int m_width;
  int m_height;

  double m_fov = 45.0f;
};
