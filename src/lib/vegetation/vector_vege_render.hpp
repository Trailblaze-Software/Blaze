#pragma once

#include <algorithm>
#include <map>
#include <string>
#include <vector>

#include "grid/img_grid.hpp"
#include "vegetation/vegetation_polygon.hpp"

// Fill `img` with vector vegetation polygons on a white CMYK base, batched by CRT layer.
inline void draw_vector_vegetation(GeoImgGrid& img, const VegeConfig& vege_config,
                                   const std::vector<VegePolygon>& vege_polygons,
                                   ProgressTracker&& progress_tracker) {
  const std::map<std::string, ColorVariant> vege_layer_color_map = vege_layer_colors(vege_config);
  img.fill(to_rgb(CMYKColor(0, 0, 0, 0)));

  std::vector<const VegePolygon*> sorted_polygons;
  sorted_polygons.reserve(vege_polygons.size());
  for (const VegePolygon& poly : vege_polygons) {
    sorted_polygons.push_back(&poly);
  }
  std::stable_sort(sorted_polygons.begin(), sorted_polygons.end(),
                   [](const VegePolygon* a, const VegePolygon* b) {
                     return vege_layer_draw_priority(a->layer) < vege_layer_draw_priority(b->layer);
                   });

  struct LayerBatch {
    std::vector<PolygonWithHoles> polygons;
    ColorVariant color;
  };
  std::vector<LayerBatch> batches;
  for (size_t i = 0; i < sorted_polygons.size();) {
    const std::string& layer = sorted_polygons[i]->layer;
    const auto color_it = vege_layer_color_map.find(layer);
    if (color_it == vege_layer_color_map.end()) {
      ++i;
      continue;
    }

    LayerBatch batch;
    batch.color = color_it->second;
    batch.polygons.reserve(sorted_polygons.size() - i);
    while (i < sorted_polygons.size() && sorted_polygons[i]->layer == layer) {
      batch.polygons.push_back({sorted_polygons[i]->exterior_ring, sorted_polygons[i]->holes});
      ++i;
    }
    batches.push_back(std::move(batch));
  }

  const size_t batch_count = batches.size();
  for (size_t batch_index = 0; batch_index < batch_count; ++batch_index) {
    ProgressTracker batch_tracker =
        progress_tracker.subtracker(static_cast<double>(batch_index) / batch_count,
                                    static_cast<double>(batch_index + 1) / batch_count);
    img.rasterize_filled_polygons(batches[batch_index].polygons, batches[batch_index].color,
                                  std::move(batch_tracker));
  }
}
