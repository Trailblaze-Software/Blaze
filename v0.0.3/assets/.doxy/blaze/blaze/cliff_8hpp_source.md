

# File cliff.hpp

[**File List**](files.md) **>** [**cliff**](dir_e3f0ccf1ba301864d78f3797f9c90139.md) **>** [**cliff.hpp**](cliff_8hpp.md)

[Go to the documentation of this file](cliff_8hpp.md)


```C++

#include <memory>

#include "grid/grid.hpp"
#include "utilities/coordinate.hpp"

class ContourPoint : public Coordinate2D<double> {
  double m_height;
  std::shared_ptr<ContourPoint> m_next;
  std::shared_ptr<ContourPoint> m_prev;
  std::shared_ptr<ContourPoint> m_down;
  std::shared_ptr<ContourPoint> m_up;
  double m_slope;

 public:
  ContourPoint(double x, double y, double height)
      : Coordinate2D<double>(x, y), m_height(height), m_slope(0) {}

  void set_next(std::shared_ptr<ContourPoint> next) { m_next = next; }
  void set_previous(std::shared_ptr<ContourPoint> prev) { m_prev = prev; }

  void find_up_down(const GeoGrid<std::vector<std::shared_ptr<ContourPoint>>>& point_grid) {
    Coordinate2D<size_t> pixel = point_grid.transform().projection_to_pixel(*this);

    double closest_down = std::numeric_limits<double>::max();
    double closest_up = std::numeric_limits<double>::max();

    for (int dx : {-1, 0, 1}) {
      for (int dy : {-1, 0, 1}) {
        Coordinate2D<size_t> neighbor_pixel = pixel + Coordinate2D<size_t>(dx, dy);
        if (point_grid.in_bounds(neighbor_pixel)) {
          for (const std::shared_ptr<ContourPoint>& neighbor_point : point_grid[neighbor_pixel]) {
            if (neighbor_point->height() < m_height) {
              double dist = (*this - *neighbor_point).magnitude_sqd();
              if (dist < closest_down) {
                closest_down = dist;
                m_down = neighbor_point;
              }
            } else if (neighbor_point->height() > m_height) {
              double dist = (*this - *neighbor_point).magnitude_sqd();
              if (dist < closest_up) {
                closest_up = dist;
                m_up = neighbor_point;
              }
            }
          }
        }
      }
    }
    if (m_down && m_up) {
      m_slope = (m_up->height() - m_down->height()) / (*m_up - *m_down).magnitude();
    }
  }

  double height() const { return m_height; }
  double slope() const { return m_slope; }
};
```


