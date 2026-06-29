

# File polygon.hpp

[**File List**](files.md) **>** [**geometry**](dir_da4e387dad6145fce42efe284fbecf2d.md) **>** [**polygon.hpp**](polygon_8hpp.md)

[Go to the documentation of this file](polygon_8hpp.md)


```C++
#pragma once

#include <cmath>
#include <optional>
#include <vector>

#include "assert/assert.hpp"
#include "utilities/coordinate.hpp"

// Compute the signed area of a polygon ring using the shoelace formula.
// Returns positive for CCW orientation, negative for CW.
inline double signed_area(const std::vector<Coordinate2D<double>>& ring) {
  if (ring.size() < 3) return 0.0;
  double area = 0.0;
  for (size_t i = 0; i < ring.size(); i++) {
    size_t j = (i + 1) % ring.size();
    area += ring[i].x() * ring[j].y();
    area -= ring[j].x() * ring[i].y();
  }
  return area * 0.5;
}

// Determine if a point is inside a polygon ring (ray casting algorithm).
inline bool point_in_ring(const Coordinate2D<double>& point,
                          const std::vector<Coordinate2D<double>>& ring) {
  if (ring.size() < 3) return false;
  bool inside = false;
  size_t n = ring.size();
  for (size_t i = 0, j = n - 1; i < n; j = i++) {
    double xi = ring[i].x(), yi = ring[i].y();
    double xj = ring[j].x(), yj = ring[j].y();
    if (((yi > point.y()) != (yj > point.y())) &&
        (point.x() < (xj - xi) * (point.y() - yi) / (yj - yi) + xi)) {
      inside = !inside;
    }
  }
  return inside;
}

// Reverse a ring's point order (CW ↔ CCW).
inline std::vector<Coordinate2D<double>> reverse_ring(
    const std::vector<Coordinate2D<double>>& ring) {
  return {ring.rbegin(), ring.rend()};
}

struct PolygonWithHoles {
  std::vector<Coordinate2D<double>> exterior;
  std::vector<std::vector<Coordinate2D<double>>> holes;
};

inline bool point_in_polygon_with_holes(const Coordinate2D<double>& point,
                                        const PolygonWithHoles& poly) {
  if (!point_in_ring(point, poly.exterior)) {
    return false;
  }
  for (const std::vector<Coordinate2D<double>>& hole : poly.holes) {
    if (point_in_ring(point, hole)) {
      return false;
    }
  }
  return true;
}

// CCW axis-aligned rectangle from an extent (for clipping/intersection).
inline PolygonWithHoles polygon_from_extent(const Extent2D& extent) {
  return {{{extent.minx, extent.miny},
           {extent.maxx, extent.miny},
           {extent.maxx, extent.maxy},
           {extent.minx, extent.maxy},
           {extent.minx, extent.miny}},
          {}};
}

inline Extent2D ring_extent(const std::vector<Coordinate2D<double>>& ring) {
  Extent2D ext;
  for (const Coordinate2D<double>& p : ring) {
    ext.grow({p.x(), p.x(), p.y(), p.y()});
  }
  return ext;
}

inline bool extent_contains(const Extent2D& outer, const Extent2D& inner) {
  return outer.minx <= inner.minx && inner.maxx <= outer.maxx && outer.miny <= inner.miny &&
         inner.maxy <= outer.maxy;
}

// Exterior CCW (positive signed area); interior rings CW (negative signed area).
inline void normalize_polygon(PolygonWithHoles& poly) {
  if (signed_area(poly.exterior) < 0) {
    poly.exterior = reverse_ring(poly.exterior);
  }
  for (auto& hole : poly.holes) {
    if (signed_area(hole) > 0) {
      hole = reverse_ring(hole);
    }
  }
}

inline void dedupe_consecutive_ring_vertices(std::vector<Coordinate2D<double>>& ring,
                                             double tolerance = 1e-9) {
  if (ring.size() < 2) {
    return;
  }
  std::vector<Coordinate2D<double>> cleaned;
  cleaned.reserve(ring.size());
  for (const Coordinate2D<double>& vertex : ring) {
    if (!cleaned.empty()) {
      const double dx = vertex.x() - cleaned.back().x();
      const double dy = vertex.y() - cleaned.back().y();
      if (dx * dx + dy * dy < tolerance * tolerance) {
        continue;
      }
    }
    cleaned.push_back(vertex);
  }
  ring = std::move(cleaned);
}

// Snap vertices near axis-aligned extent edges (e.g. tile seams, clip bounds).
inline void snap_ring_to_extent(std::vector<Coordinate2D<double>>& ring, const Extent2D& extent,
                                double tolerance) {
  for (Coordinate2D<double>& vertex : ring) {
    double x = vertex.x();
    double y = vertex.y();
    const double dx_min = std::abs(x - extent.minx);
    const double dx_max = std::abs(x - extent.maxx);
    if (dx_min <= tolerance && dx_min <= dx_max) {
      x = extent.minx;
    } else if (dx_max <= tolerance) {
      x = extent.maxx;
    }
    const double dy_min = std::abs(y - extent.miny);
    const double dy_max = std::abs(y - extent.maxy);
    if (dy_min <= tolerance && dy_min <= dy_max) {
      y = extent.miny;
    } else if (dy_max <= tolerance) {
      y = extent.maxy;
    }
    vertex = Coordinate2D<double>(x, y);
  }
  dedupe_consecutive_ring_vertices(ring, tolerance);
}

inline void snap_polygon_to_extents(PolygonWithHoles& poly, const std::vector<Extent2D>& extents,
                                    double tolerance) {
  for (const Extent2D& extent : extents) {
    snap_ring_to_extent(poly.exterior, extent, tolerance);
    for (std::vector<Coordinate2D<double>>& hole : poly.holes) {
      snap_ring_to_extent(hole, extent, tolerance);
    }
  }
}

// Intersection of segment (a1,a2) with the infinite line through (b1,b2).
// Returns true and writes the intersection point to `out` when the segment
// crosses the line (t in [0,1]). The clip edge is treated as a line — the
// intersection may lie beyond the b1-b2 segment itself.
inline bool segment_intersection(const Coordinate2D<double>& a1, const Coordinate2D<double>& a2,
                                 const Coordinate2D<double>& b1, const Coordinate2D<double>& b2,
                                 Coordinate2D<double>& out) {
  double dx_a = a2.x() - a1.x();
  double dy_a = a2.y() - a1.y();
  double dx_b = b2.x() - b1.x();
  double dy_b = b2.y() - b1.y();
  double cross = dx_a * dy_b - dy_a * dx_b;
  if (std::abs(cross) < 1e-20) return false;  // parallel
  double t = ((b1.x() - a1.x()) * dy_b - (b1.y() - a1.y()) * dx_b) / cross;
  if (t < 0.0 || t > 1.0) return false;
  out = Coordinate2D<double>(a1.x() + t * dx_a, a1.y() + t * dy_a);
  return true;
}

// Check if a point is to the left of the directed edge from `from` to `to`.
inline bool is_left_of(const Coordinate2D<double>& from, const Coordinate2D<double>& to,
                       const Coordinate2D<double>& point) {
  return ((to.x() - from.x()) * (point.y() - from.y()) -
          (to.y() - from.y()) * (point.x() - from.x())) >= 0;
}

// Sutherland-Hodgman polygon clipping: clip `subject` against `clip` polygon.
// Both must be CCW simple polygons. Returns the intersection polygon (CCW).
inline std::vector<Coordinate2D<double>> intersect_polygons(
    const std::vector<Coordinate2D<double>>& subject,
    const std::vector<Coordinate2D<double>>& clip) {
  if (subject.size() < 3 || clip.size() < 3) return {};

  std::vector<Coordinate2D<double>> output = subject;
  for (size_t e = 0; e < clip.size(); e++) {
    const auto& edge_from = clip[e];
    const auto& edge_to = clip[(e + 1) % clip.size()];
    std::vector<Coordinate2D<double>> input = std::move(output);
    output.clear();
    if (input.empty()) return {};
    for (size_t i = 0; i < input.size(); i++) {
      const auto& cur = input[i];
      const auto& prev = input[(i + input.size() - 1) % input.size()];
      bool cur_inside = is_left_of(edge_from, edge_to, cur);
      bool prev_inside = is_left_of(edge_from, edge_to, prev);
      if (cur_inside) {
        if (!prev_inside) {
          Coordinate2D<double> inter;
          if (segment_intersection(prev, cur, edge_from, edge_to, inter)) {
            output.push_back(inter);
          }
        }
        output.push_back(cur);
      } else if (prev_inside) {
        Coordinate2D<double> inter;
        if (segment_intersection(prev, cur, edge_from, edge_to, inter)) {
          output.push_back(inter);
        }
      }
    }
  }
  return output;
}

// Clip a simple (no holes) polygon to an axis-aligned extent via Sutherland-Hodgman.
inline std::vector<PolygonWithHoles> clip_polygon_hole_free_to_extent(const PolygonWithHoles& poly,
                                                                      const Extent2D& bounds) {
  Assert(poly.holes.empty());
  const PolygonWithHoles clip_rect = polygon_from_extent(bounds);
  std::vector<Coordinate2D<double>> exterior =
      intersect_polygons(poly.exterior, clip_rect.exterior);
  if (exterior.size() < 3) {
    return {};
  }
  PolygonWithHoles clipped;
  clipped.exterior = std::move(exterior);
  normalize_polygon(clipped);
  return {clipped};
}
```


