#pragma once

#include <QMatrix4x4>
#include <QVector3D>
#include <QVector4D>
#include <cmath>

#include "utilities/coordinate.hpp"

// Leaf-only screen test using Qt's clip transform. Internal octree nodes are never
// culled here because their corner AABBs span far beyond the view while children
// remain visible.
struct Frustum {
  QMatrix4x4 m_clip;

  static Frustum from_matrix(const QMatrix4x4& matrix) {
    Frustum frustum;
    frustum.m_clip = matrix;
    return frustum;
  }

  // Permissive test for octree traversal: reject only when the whole AABB is behind
  // the camera. Strict leaf tests can drop distant subtrees when zoomed in close.
  bool intersects_branch(const Extent3D& bounds) const {
    const double xs[2] = {bounds.minx, bounds.maxx};
    const double ys[2] = {bounds.miny, bounds.maxy};
    const double zs[2] = {bounds.minz, bounds.maxz};
    for (const double x : xs) {
      for (const double y : ys) {
        for (const double z : zs) {
          const QVector4D clip = m_clip * QVector4D(static_cast<float>(x), static_cast<float>(y),
                                                    static_cast<float>(z), 1.0f);
          if (clip.w() > 1e-4f) {
            return true;
          }
        }
      }
    }
    return false;
  }

  bool intersects_leaf(const Extent3D& bounds) const {
    const double cx = 0.5 * (bounds.minx + bounds.maxx);
    const double cy = 0.5 * (bounds.miny + bounds.maxy);
    const double cz = 0.5 * (bounds.minz + bounds.maxz);
    const double half_diag = 0.5 * bounds.max_extent() * std::sqrt(3.0);

    const auto test_point = [&](double x, double y, double z) {
      const QVector3D ndc = m_clip.map(
          QVector3D(static_cast<float>(x), static_cast<float>(y), static_cast<float>(z)));
      if (!std::isfinite(ndc.x()) || !std::isfinite(ndc.y()) || !std::isfinite(ndc.z())) {
        return false;
      }
      constexpr float slack = 0.35f;
      return ndc.x() >= -1.0f - slack && ndc.x() <= 1.0f + slack && ndc.y() >= -1.0f - slack &&
             ndc.y() <= 1.0f + slack && ndc.z() >= -1.0f && ndc.z() <= 1.0f;
    };

    if (test_point(cx, cy, cz)) {
      return true;
    }

    // Small leaves: if the center misses, check a few bounds samples.
    if (half_diag <= 50.0) {
      const double xs[2] = {bounds.minx, bounds.maxx};
      const double ys[2] = {bounds.miny, bounds.maxy};
      const double zs[2] = {bounds.minz, bounds.maxz};
      for (const double x : xs) {
        for (const double y : ys) {
          for (const double z : zs) {
            if (test_point(x, y, z)) {
              return true;
            }
          }
        }
      }
      return false;
    }

    // Large buckets: keep unless the whole bounds block is clearly behind the camera.
    const double xs[2] = {bounds.minx, bounds.maxx};
    const double ys[2] = {bounds.miny, bounds.maxy};
    const double zs[2] = {bounds.minz, bounds.maxz};
    bool any_in_front = false;
    for (const double x : xs) {
      for (const double y : ys) {
        for (const double z : zs) {
          const QVector4D clip = m_clip * QVector4D(static_cast<float>(x), static_cast<float>(y),
                                                    static_cast<float>(z), 1.0f);
          if (clip.w() > 1e-4f) {
            any_in_front = true;
            break;
          }
        }
        if (any_in_front) {
          break;
        }
      }
      if (any_in_front) {
        break;
      }
    }
    return any_in_front;
  }
};
