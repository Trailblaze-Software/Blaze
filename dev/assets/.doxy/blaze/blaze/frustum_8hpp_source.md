

# File frustum.hpp

[**File List**](files.md) **>** [**gui**](dir_99d0482cf009f9d97a0877749b817f19.md) **>** [**frustum.hpp**](frustum_8hpp.md)

[Go to the documentation of this file](frustum_8hpp.md)


```C++
#pragma once

#include <QMatrix4x4>
#include <QVector4D>
#include <array>

#include "utilities/coordinate.hpp"

// Frustum culling for octree traversal. The six clip-space planes are extracted
// from the combined projection*view (clip) matrix using the Gribb-Hartmann
// method. A node is kept when its AABB is not fully outside any single plane.
// This is exact (no NDC divide, so it is valid for nodes behind the eye) and
// needs no slack tuning, unlike a screen-space corner heuristic.
struct Frustum {
  // Each plane is (a, b, c, d): a point is inside when a*x + b*y + c*z + d >= 0.
  std::array<QVector4D, 6> m_planes;

  static Frustum from_matrix(const QMatrix4x4& clip) {
    // QMatrix4x4::operator()(row, col) addresses the mathematical row/col.
    const auto row = [&clip](int r) {
      return QVector4D(clip(r, 0), clip(r, 1), clip(r, 2), clip(r, 3));
    };
    const QVector4D r0 = row(0);
    const QVector4D r1 = row(1);
    const QVector4D r2 = row(2);
    const QVector4D r3 = row(3);
    Frustum f;
    f.m_planes[0] = r3 + r0;  // left
    f.m_planes[1] = r3 - r0;  // right
    f.m_planes[2] = r3 + r1;  // bottom
    f.m_planes[3] = r3 - r1;  // top
    f.m_planes[4] = r3 + r2;  // near
    f.m_planes[5] = r3 - r2;  // far
    return f;
  }

  // Conservative AABB test: returns false only when the box is fully outside
  // (in the negative half-space of) some plane.
  bool intersects(const Extent3D& bounds) const {
    const float minx = static_cast<float>(bounds.minx);
    const float miny = static_cast<float>(bounds.miny);
    const float minz = static_cast<float>(bounds.minz);
    const float maxx = static_cast<float>(bounds.maxx);
    const float maxy = static_cast<float>(bounds.maxy);
    const float maxz = static_cast<float>(bounds.maxz);
    for (const QVector4D& plane : m_planes) {
      // Pick the corner furthest along the plane normal (the "positive vertex").
      const float px = plane.x() > 0.0f ? maxx : minx;
      const float py = plane.y() > 0.0f ? maxy : miny;
      const float pz = plane.z() > 0.0f ? maxz : minz;
      if (plane.x() * px + plane.y() * py + plane.z() * pz + plane.w() < 0.0f) {
        return false;
      }
    }
    return true;
  }
};
```


