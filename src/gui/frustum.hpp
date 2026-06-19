#pragma once

#include <QMatrix4x4>
#include <QVector3D>
#include <QVector4D>
#include <cmath>

#include "utilities/coordinate.hpp"

// Frustum culling for octree traversal.
struct Frustum {
  QMatrix4x4 m_clip;

  static Frustum from_matrix(const QMatrix4x4& matrix) {
    Frustum f;
    f.m_clip = matrix;
    return f;
  }

  // Permissive test: only cull when entire AABB is behind camera.
  bool intersects_branch(const Extent3D& bounds) const {
    const float xs[2] = {static_cast<float>(bounds.minx), static_cast<float>(bounds.maxx)};
    const float ys[2] = {static_cast<float>(bounds.miny), static_cast<float>(bounds.maxy)};
    const float zs[2] = {static_cast<float>(bounds.minz), static_cast<float>(bounds.maxz)};
    for (const float x : xs)
      for (const float y : ys)
        for (const float z : zs) {
          const QVector4D c = m_clip * QVector4D(x, y, z, 1.0f);
          if (c.w() > 1e-4f) return true;
        }
    return false;
  }

  // Leaf test: NDC center + corner checks. Permissive — only culls
  // leaves clearly outside the view, leaving the rest for the GPU.
  bool intersects_leaf(const Extent3D& bounds) const {
    constexpr float kSlack = 0.35f;
    const float cx = static_cast<float>(0.5 * (bounds.minx + bounds.maxx));
    const float cy = static_cast<float>(0.5 * (bounds.miny + bounds.maxy));
    const float cz = static_cast<float>(0.5 * (bounds.minz + bounds.maxz));
    const double half_diag = 0.5 * bounds.max_extent() * std::sqrt(3.0);

    const QVector3D ndc = m_clip.map(QVector3D(cx, cy, cz));
    if (std::isfinite(ndc.x()) && std::isfinite(ndc.y()) && std::isfinite(ndc.z())) {
      if (ndc.x() >= -1.0f - kSlack && ndc.x() <= 1.0f + kSlack && ndc.y() >= -1.0f - kSlack &&
          ndc.y() <= 1.0f + kSlack && ndc.z() >= -1.0f && ndc.z() <= 1.0f)
        return true;
    }

    if (half_diag <= 50.0) {
      const float xs[2] = {static_cast<float>(bounds.minx), static_cast<float>(bounds.maxx)};
      const float ys[2] = {static_cast<float>(bounds.miny), static_cast<float>(bounds.maxy)};
      const float zs[2] = {static_cast<float>(bounds.minz), static_cast<float>(bounds.maxz)};
      for (const float x : xs)
        for (const float y : ys)
          for (const float z : zs) {
            const QVector3D cn = m_clip.map(QVector3D(x, y, z));
            if (std::isfinite(cn.x()) && std::isfinite(cn.y()) && std::isfinite(cn.z()) &&
                cn.x() >= -1.0f - kSlack && cn.x() <= 1.0f + kSlack && cn.y() >= -1.0f - kSlack &&
                cn.y() <= 1.0f + kSlack && cn.z() >= -1.0f && cn.z() <= 1.0f)
              return true;
          }
      return false;
    }

    // Large leaf: keep if any corner is in front of the camera.
    const float xs[2] = {static_cast<float>(bounds.minx), static_cast<float>(bounds.maxx)};
    const float ys[2] = {static_cast<float>(bounds.miny), static_cast<float>(bounds.maxy)};
    const float zs[2] = {static_cast<float>(bounds.minz), static_cast<float>(bounds.maxz)};
    for (const float x : xs)
      for (const float y : ys)
        for (const float z : zs) {
          if ((m_clip * QVector4D(x, y, z, 1.0f)).w() > 1e-4f) return true;
        }
    return false;
  }
};
