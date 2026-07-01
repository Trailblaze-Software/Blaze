#include <gtest/gtest.h>

#include <cmath>
#include <filesystem>
#include <vector>

#include "grid/grid.hpp"
#include "grid/img_grid.hpp"
#include "isom/colors.hpp"
#include "testing/output_dir.hpp"
#include "tif/tif.hpp"
#include "utilities/progress_tracker.hpp"
#include "vegetation/vector_vege_render.hpp"
#include "vegetation/vegetation_polygon.hpp"

namespace {

GeoTransform test_render_transform() { return GeoTransform({0.0, 0.0}, 1.0); }

GeoImgGrid make_transparent_grid(size_t width, size_t height) {
  GeoGrid<RGBColor> grid(width, height, test_render_transform(), GeoProjection());
  for (size_t y = 0; y < height; ++y) {
    for (size_t x = 0; x < width; ++x) {
      grid[{x, y}] = RGBColor(0, 0, 0, 0);
    }
  }
  return GeoImgGrid(grid);
}

bool colors_near(const RGBColor& actual, const RGBColor& expected, int tolerance = 2) {
  return std::abs(static_cast<int>(actual.getRed()) - static_cast<int>(expected.getRed())) <=
             tolerance &&
         std::abs(static_cast<int>(actual.getGreen()) - static_cast<int>(expected.getGreen())) <=
             tolerance &&
         std::abs(static_cast<int>(actual.getBlue()) - static_cast<int>(expected.getBlue())) <=
             tolerance;
}

VegePolygon make_rect_polygon(const std::string& layer, double xmin, double xmax, double ymin,
                              double ymax) {
  VegePolygon poly;
  poly.layer = layer;
  poly.name = layer_number(layer);
  poly.exterior_ring = {{xmin, ymax}, {xmax, ymax}, {xmax, ymin}, {xmin, ymin}, {xmin, ymax}};
  return poly;
}

VegeConfig vector_test_config() {
  VegeConfig config;
  config.background_color = ColorVariant(RGBColor(255, 220, 100, 255));

  VegeHeightConfig canopy;
  canopy.name = "canopy";
  canopy.min_height = 2.5;
  canopy.max_height = 100.0;
  canopy.colors.push_back({0.1, ColorVariant(RGBColor(40, 80, 40, 255)), "405_Forest", 0.0, 0.0});

  VegeHeightConfig green;
  green.name = "green";
  green.min_height = 0.5;
  green.max_height = 2.5;
  green.colors.push_back(
      {0.1, ColorVariant(RGBColor(100, 200, 100, 255)), "406_Slow_Running", 0.0, 0.0});
  green.colors.push_back({0.3, ColorVariant(RGBColor(50, 150, 50, 255)), "408_Walk", 0.0, 0.0});
  green.colors.push_back({0.5, ColorVariant(RGBColor(20, 100, 20, 255)), "410_Fight", 0.0, 0.0});

  config.height_configs.push_back(std::move(canopy));
  config.height_configs.push_back(std::move(green));
  return config;
}

RGBColor read_tif_pixel(const Geo<MultiBand<FlexGrid>>& grid, size_t row, size_t col) {
  return RGBColor(
      static_cast<unsigned char>(grid[0].get<std::byte>({(long long)col, (long long)row})),
      static_cast<unsigned char>(grid[1].get<std::byte>({(long long)col, (long long)row})),
      static_cast<unsigned char>(grid[2].get<std::byte>({(long long)col, (long long)row})),
      static_cast<unsigned char>(grid[3].get<std::byte>({(long long)col, (long long)row})));
}

}  // namespace

TEST(VectorVegeRender, BackgroundFillWithoutPolygons) {
  const VegeConfig config = vector_test_config();
  GeoImgGrid img(20, 20, test_render_transform(), GeoProjection());
  draw_vector_vegetation(img, config, {}, ProgressTracker());

  const RGBColor expected = to_rgb(config.background_color);
  EXPECT_TRUE(colors_near(img[{0, 0}], expected));
  EXPECT_TRUE(colors_near(img[{10, 10}], expected));
  EXPECT_TRUE(colors_near(img[{19, 19}], expected));
}

TEST(VectorVegeRender, HigherPriorityGreenCoversForest) {
  const VegeConfig config = vector_test_config();
  const RGBColor forest_color = to_rgb(config.height_configs[0].colors[0].color);
  const RGBColor walk_color = to_rgb(config.height_configs[1].colors[1].color);
  const RGBColor background = to_rgb(config.background_color);

  std::vector<VegePolygon> polygons = {
      make_rect_polygon("405_Forest", 2.0, 18.0, -18.0, -2.0),
      make_rect_polygon("408_Walk", 8.0, 12.0, -12.0, -8.0),
  };

  GeoImgGrid img(20, 20, test_render_transform(), GeoProjection());
  draw_vector_vegetation(img, config, polygons, ProgressTracker());

  EXPECT_TRUE(colors_near(img[{10, 10}], walk_color));
  EXPECT_TRUE(colors_near(img[{4, 4}], forest_color));
  EXPECT_TRUE(colors_near(img[{0, 0}], background));
}

TEST(VectorVegeRender, OpenLandUsesBackgroundColor) {
  const VegeConfig config = vector_test_config();
  const RGBColor open_color = to_rgb(config.background_color);

  std::vector<VegePolygon> polygons = {
      make_rect_polygon("403_Rough_Open_Land", 4.0, 10.0, -10.0, -4.0)};

  GeoImgGrid img(20, 20, test_render_transform(), GeoProjection());
  draw_vector_vegetation(img, config, polygons, ProgressTracker());

  EXPECT_TRUE(colors_near(img[{6, 6}], open_color));
  EXPECT_TRUE(colors_near(img[{0, 0}], open_color));
}

TEST(VectorVegeRender, UnknownLayerIsSkipped) {
  const VegeConfig config = vector_test_config();
  const RGBColor background = to_rgb(config.background_color);
  std::vector<VegePolygon> polygons = {make_rect_polygon("999_Unknown", 2.0, 18.0, -18.0, -2.0)};

  GeoImgGrid img(20, 20, test_render_transform(), GeoProjection());
  draw_vector_vegetation(img, config, polygons, ProgressTracker());

  EXPECT_TRUE(colors_near(img[{10, 10}], background));
}

TEST(VectorVegeRender, AllGreenLayersRenderDistinctColors) {
  const VegeConfig config = vector_test_config();
  const RGBColor slow_color = to_rgb(config.height_configs[1].colors[0].color);
  const RGBColor walk_color = to_rgb(config.height_configs[1].colors[1].color);
  const RGBColor fight_color = to_rgb(config.height_configs[1].colors[2].color);

  std::vector<VegePolygon> polygons = {
      make_rect_polygon("406_Slow_Running", 2.0, 6.0, -6.0, -2.0),
      make_rect_polygon("408_Walk", 8.0, 12.0, -6.0, -2.0),
      make_rect_polygon("410_Fight", 14.0, 18.0, -6.0, -2.0),
  };

  GeoImgGrid img(20, 20, test_render_transform(), GeoProjection());
  draw_vector_vegetation(img, config, polygons, ProgressTracker());

  EXPECT_TRUE(colors_near(img[{4, 4}], slow_color));
  EXPECT_TRUE(colors_near(img[{10, 4}], walk_color));
  EXPECT_TRUE(colors_near(img[{16, 4}], fight_color));
}

TEST(VectorVegeRender, PolygonHoleLeavesBackgroundInterior) {
  const VegeConfig config = vector_test_config();
  VegePolygon forest = make_rect_polygon("405_Forest", 2.0, 18.0, -18.0, -2.0);
  forest.holes.push_back({{8.0, -8.0}, {12.0, -8.0}, {12.0, -12.0}, {8.0, -12.0}, {8.0, -8.0}});

  GeoImgGrid img(20, 20, test_render_transform(), GeoProjection());
  draw_vector_vegetation(img, config, {forest}, ProgressTracker());

  const RGBColor background = to_rgb(config.background_color);
  const RGBColor forest_color = to_rgb(config.height_configs[0].colors[0].color);
  EXPECT_TRUE(colors_near(img[{10, 10}], background));
  EXPECT_TRUE(colors_near(img[{4, 4}], forest_color));
}

TEST(VectorVegeRender, DefaultLayerNamesMapFromConfig) {
  VegeConfig config;
  config.background_color = ColorVariant(RGBColor(255, 255, 255, 255));

  VegeHeightConfig green;
  green.name = "green";
  green.colors.push_back({0.1, ColorVariant(RGBColor(120, 180, 120, 255)), "", 0.0, 0.0});
  green.colors.push_back({0.3, ColorVariant(RGBColor(80, 140, 80, 255)), "", 0.0, 0.0});
  green.colors.push_back({0.5, ColorVariant(RGBColor(40, 100, 40, 255)), "", 0.0, 0.0});
  config.height_configs.push_back(std::move(green));

  const auto colors = vege_layer_colors(config);
  ASSERT_TRUE(colors.contains("406_Slow_Running"));
  ASSERT_TRUE(colors.contains("408_Walk"));
  ASSERT_TRUE(colors.contains("410_Fight"));

  std::vector<VegePolygon> polygons = {make_rect_polygon("408_Walk", 4.0, 10.0, -10.0, -4.0)};
  GeoImgGrid img(20, 20, test_render_transform(), GeoProjection());
  draw_vector_vegetation(img, config, polygons, ProgressTracker());

  EXPECT_TRUE(colors_near(img[{6, 6}], to_rgb(colors.at("408_Walk"))));
}

TEST(VectorVegeTif, SaveAndReadPreservesRenderedColors) {
  const VegeConfig config = vector_test_config();
  std::vector<VegePolygon> polygons = {
      make_rect_polygon("405_Forest", 2.0, 18.0, -18.0, -2.0),
      make_rect_polygon("408_Walk", 8.0, 12.0, -12.0, -8.0),
  };

  GeoImgGrid img(20, 20, test_render_transform(), GeoProjection());
  draw_vector_vegetation(img, config, polygons, ProgressTracker());

  const fs::path path = blaze::test::unique_test_output_path("vector_vege", ".tif");
  const GeoGrid<RGBColor> extent_ref(20, 20, test_render_transform(), GeoProjection());
  const Extent2D extent = *extent_ref.extent();
  img.save_to(path, extent, ProgressTracker());

  auto grid = read_tif(path, ProgressTracker());
  ASSERT_GE(grid.size(), 3u);
  std::error_code ec;
  std::filesystem::remove(path, ec);

  const RGBColor forest_color = to_rgb(config.height_configs[0].colors[0].color);
  const RGBColor walk_color = to_rgb(config.height_configs[1].colors[1].color);
  const RGBColor background = to_rgb(config.background_color);

  EXPECT_TRUE(colors_near(read_tif_pixel(grid, 10, 10), walk_color));
  EXPECT_TRUE(colors_near(read_tif_pixel(grid, 4, 4), forest_color));
  EXPECT_TRUE(colors_near(read_tif_pixel(grid, 0, 0), background));
}

TEST(VectorVegeOverlay, TransparentOverlayPreservesVectorBackground) {
  const VegeConfig config = vector_test_config();
  const RGBColor background = to_rgb(config.background_color);
  std::vector<VegePolygon> polygons = {make_rect_polygon("408_Walk", 4.0, 16.0, -16.0, -4.0)};

  GeoImgGrid img(20, 20, test_render_transform(), GeoProjection());
  draw_vector_vegetation(img, config, polygons, ProgressTracker());

  const RGBColor before = img[{10, 10}];
  GeoImgGrid overlay = make_transparent_grid(20, 20);
  img.draw(overlay, ProgressTracker(), GeoGridCompositeMode::OpaqueCopy);

  EXPECT_TRUE(colors_near(img[{10, 10}], before));
  EXPECT_TRUE(colors_near(img[{0, 0}], background));
}

TEST(VectorVegeOverlay, OpaqueOverlayPixelReplacesBackground) {
  const VegeConfig config = vector_test_config();
  const RGBColor background = to_rgb(config.background_color);
  GeoImgGrid img(20, 20, test_render_transform(), GeoProjection());
  draw_vector_vegetation(img, config, {}, ProgressTracker());

  const RGBColor water_color(0, 0, 255, 255);
  GeoImgGrid overlay = make_transparent_grid(20, 20);
  overlay.draw_filled_polygon(
      PolygonWithHoles{{{8.0, -8.0}, {12.0, -8.0}, {12.0, -12.0}, {8.0, -12.0}, {8.0, -8.0}}, {}},
      water_color);

  img.draw(overlay, ProgressTracker(), GeoGridCompositeMode::OpaqueCopy);

  EXPECT_TRUE(colors_near(img[{10, 10}], water_color));
  EXPECT_TRUE(colors_near(img[{0, 0}], background));
}

TEST(VectorVegeOverlay, DrawWithTransparentForegroundDoesNotTintBackground) {
  const VegeConfig config = vector_test_config();
  const RGBColor background = to_rgb(config.background_color);
  GeoImgGrid img(10, 10, test_render_transform(), GeoProjection());
  draw_vector_vegetation(img, config, {}, ProgressTracker());

  const GeoImgGrid transparent_overlay = make_transparent_grid(10, 10);
  img.draw(transparent_overlay, ProgressTracker());

  EXPECT_TRUE(colors_near(img[{5, 5}], background));
}
