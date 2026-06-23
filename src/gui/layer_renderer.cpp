#include "gui/layer_renderer.hpp"

std::unique_ptr<LayerRenderer> LayerRenderer::create(std::shared_ptr<Layer> layer,
                                                     const Coordinate3D<double>& offset) {
  if (auto las_layer = std::dynamic_pointer_cast<LASLayer>(layer)) {
    return std::make_unique<OctreeLASLayerRenderer>(las_layer, offset);
  }
  if (auto dem_layer = std::dynamic_pointer_cast<DemLayer>(layer)) {
    return std::make_unique<MeshLayerRenderer>(
        dem_layer, [dem_layer]() -> const AsyncRasterData* { return &dem_layer->raster(); },
        offset);
  }
  if (auto slope_layer = std::dynamic_pointer_cast<SlopeLayer>(layer)) {
    return std::make_unique<MeshLayerRenderer>(
        slope_layer, [slope_layer]() -> const AsyncRasterData* { return &slope_layer->raster(); },
        offset);
  }
  if (auto textured_layer = std::dynamic_pointer_cast<TexturedDemLayer>(layer)) {
    return std::make_unique<MeshLayerRenderer>(
        textured_layer,
        [textured_layer]() -> const AsyncRasterData* { return &textured_layer->raster(); }, offset,
        true);
  }
  if (auto contour_layer = std::dynamic_pointer_cast<ContourLayer>(layer)) {
    return std::make_unique<ContourLayerRenderer>(contour_layer, offset);
  }
  return nullptr;
}
