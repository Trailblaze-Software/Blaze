#include <gtest/gtest.h>

#include <cmath>
#include <filesystem>
#include <fstream>

#include "config_input/config_input.hpp"
#include "contour/contour.hpp"
#include "gdal_priv.h"
#include "io/gdal_init.hpp"
#include "io/gpkg.hpp"
#include "isom/colors.hpp"
#include "las/las_file.hpp"
#include "las/las_point.hpp"
#include "lib/grid/grid.hpp"
#include "ogr_srs_api.h"
#include "process.hpp"
#include "tif/tif.hpp"
#include "utilities/filesystem.hpp"
#include "utilities/progress_tracker.hpp"
#include "utilities/resources.hpp"

namespace fs = std::filesystem;

// Helper to get WGS84 WKT projection string using GDAL
std::string get_wgs84_wkt() {
  ensure_gdal_initialized();
  OGRSpatialReference srs;
  Assert(srs.importFromEPSG(4326) == OGRERR_NONE, "Failed to import EPSG:4326");
  char* wkt_ptr = nullptr;
  srs.exportToWkt(&wkt_ptr);
  Assert(wkt_ptr != nullptr, "Failed to export WKT from EPSG:4326");
  std::string wkt(wkt_ptr);
  CPLFree(wkt_ptr);
  Assert(!wkt.empty(), "WKT string must not be empty");
  return wkt;
}

// Helper to create a simple synthetic elevation grid
class TestGrid : public GeoGrid<double> {
 public:
  explicit TestGrid(const std::vector<std::vector<double>>& data)
      : GeoGrid<double>(data[0].size(), data.size(), GeoTransform(),
                        GeoProjection(get_wgs84_wkt())) {
    for (size_t i = 0; i < data.size(); i++) {
      for (size_t j = 0; j < data[0].size(); j++) {
        (*this)[{j, i}] = data[i][j];
      }
    }
  }
};

// Create a minimal config for testing
Config create_minimal_test_config(const fs::path& output_dir) {
  Config config = Config::Default();
  config.set_output_directory(output_dir);
  config.grid.bin_resolution = 1.0;
  config.grid.downsample_factor = 2;
  config.ground.outlier_removal_height_diff = 0.5;
  config.ground.min_ground_intensity = 0;
  config.ground.max_ground_intensity = 1000;
  config.border_width = 10.0;

  // Minimal contour config - use CMYKColor like the default config
  std::map<std::string, ContourConfig> contour_map;
  ContourConfig normal_contour;
  normal_contour.interval = 5.0;
  normal_contour.min_points = 3;
  normal_contour.color = CMYKColor(0, 56, 100, 18);  // brown
  normal_contour.width = 0.14;
  contour_map["normal"] = normal_contour;
  config.contours = ContourConfigs(contour_map);

  // Use default water config (already set from Config::Default())
  // Just ensure it has at least one config
  if (config.water.configs.empty()) {
    WaterConfigs water_configs;
    WaterConfig minor_water;
    minor_water.catchment = 0.03;
    minor_water.color = CMYKColor(100, 0, 0, 0);  // blue
    minor_water.width = 0.18;
    water_configs.configs["minor"] = minor_water;
    config.water = water_configs;
  }

  // Minimal vegetation config
  VegeHeightConfig tall_veg;
  tall_veg.name = "tall_veg";
  tall_veg.min_height = 2.0;
  tall_veg.max_height = 100.0;

  BlockingThresholdColorPair green_veg;
  green_veg.blocking_threshold = 0.1;
  green_veg.color = CMYKColor(100, 0, 100, 0);  // Green
  tall_veg.colors.push_back(green_veg);

  config.vege = VegeConfig{CMYKColor(0, 27, 79, 0),  // yellow
                           {tall_veg}};

  // Minimal render config
  config.render.scale = 1000;
  config.render.dpi = 300;

  return config;
}

// Create synthetic LAS data from a simple grid
LASData create_synthetic_las_data_ext(const Extent2D& extent,
                                      const std::function<double(double, double)>& height_function,
                                      bool with_vegetation) {
  const std::string proj_str = get_wgs84_wkt();
  Assert(!proj_str.empty(), "get_wgs84_wkt() must return a non-empty string");

  LASData las_data(extent, GeoProjection(proj_str));

  // Generate ground points
  for (double x = extent.minx; x < extent.maxx; x += 2.0) {
    for (double y = extent.miny; y < extent.maxy; y += 2.0) {
      double z = height_function(x, y);
      las_data.insert(LASPoint(x, y, z, 1000, LASClassification::Ground));
    }
  }

  // Generate vegetation points if requested
  if (with_vegetation) {
    for (double x = extent.minx + 5.0; x < extent.maxx - 5.0; x += 5.0) {
      for (double y = extent.miny + 5.0; y < extent.maxy - 5.0; y += 5.0) {
        double ground_z = height_function(x, y);
        double vege_z = ground_z + 5.0;  // 5m tall vegetation
        las_data.insert(LASPoint(x, y, vege_z, 1000, LASClassification::HighVegetation));
      }
    }
  }

  return las_data;
}

// Create synthetic LAS data from a simple grid
LASData create_synthetic_las_data() {
  // Create a simple 10x10 grid with a hill in the middle
  std::vector<std::vector<double>> data(10, std::vector<double>(10, 10.0));
  // Add a hill
  for (size_t i = 3; i < 7; i++) {
    for (size_t j = 3; j < 7; j++) {
      double dist = std::sqrt((i - 5.0) * (i - 5.0) + (j - 5.0) * (j - 5.0));
      data[i][j] = 10.0 + std::max(0.0, 5.0 - dist);
    }
  }

  TestGrid grid(data);

  // Get projection string before creating LASData (workaround for projection being lost in move)
  const std::string proj_str = get_wgs84_wkt();
  Assert(!proj_str.empty(), "get_wgs84_wkt() must return a non-empty string");

  // Create LAS data from grid using explicit projection
  std::unique_ptr<Extent2D> extent = grid.extent();
  LASData las_data(*extent, GeoProjection(proj_str));

  // Copy the grid data into LASData
  for (size_t i = 0; i < grid.height(); i++) {
    for (size_t j = 0; j < grid.width(); j++) {
      Coordinate2D<double> coord =
          grid.transform().pixel_to_projection({(double)j + 0.5, (double)i + 0.5});
      las_data.insert(
          LASPoint(coord.x(), coord.y(), grid[{j, i}], 1000, LASClassification::Ground));
    }
  }

  return las_data;
}

// Test end-to-end processing with synthetic data
TEST(E2E, ProcessSyntheticData) {
  fs::path test_output_dir = fs::temp_directory_path() / "blaze_e2e_test";

  // Clean up if exists
  if (fs::exists(test_output_dir)) {
    fs::remove_all(test_output_dir);
  }
  fs::create_directories(test_output_dir);

  // Create config
  Config config = create_minimal_test_config(test_output_dir);

  // Create synthetic LAS data
  LASData las_data = create_synthetic_las_data();

  // Process the data
  ProgressTracker tracker;
  process_las_data(las_data, test_output_dir, config, std::move(tracker));

  // Verify outputs were created (some may not exist if data is too sparse)
  // At minimum, the output directory should exist
  EXPECT_TRUE(fs::exists(test_output_dir));

  // Check for key output files (may not all exist depending on data)
  bool has_ground = fs::exists(test_output_dir / "ground.tif");
  bool has_smooth = fs::exists(test_output_dir / "smooth_ground.tif");
  bool has_contours = fs::exists(test_output_dir / "contours.gpkg");

  // At least some outputs should be created
  EXPECT_TRUE(has_ground || has_smooth || has_contours);

  // If files exist, verify they're not empty
  if (has_ground) {
    EXPECT_GT(fs::file_size(test_output_dir / "ground.tif"), 0);
  }
  if (has_smooth) {
    EXPECT_GT(fs::file_size(test_output_dir / "smooth_ground.tif"), 0);
  }
  if (has_contours) {
    EXPECT_GT(fs::file_size(test_output_dir / "contours.gpkg"), 0);
  }

  // Verify contours can be read back if file exists
  if (fs::exists(test_output_dir / "contours.gpkg")) {
    // If file exists, it must be valid and readable
    std::vector<Contour> contours = read_gpkg(test_output_dir / "contours.gpkg");
    // Should be able to read without errors
    EXPECT_GE(contours.size(), 0);
  }

  // Clean up
  if (fs::exists(test_output_dir)) {
    fs::remove_all(test_output_dir);
  }
}

// Test that processing handles empty data gracefully
TEST(E2E, ProcessEmptyData) {
  fs::path test_output_dir = fs::temp_directory_path() / "blaze_e2e_test_empty";

  if (fs::exists(test_output_dir)) {
    fs::remove_all(test_output_dir);
  }
  fs::create_directories(test_output_dir);

  Config config = create_minimal_test_config(test_output_dir);

  // Create empty LAS data
  Extent2D bounds = {0.0, 10.0, 0.0, 10.0};
  GeoProjection proj;
  LASData las_data(bounds, proj);

  ProgressTracker tracker;
  process_las_data(las_data, test_output_dir, config, std::move(tracker));

  // Should still create output directory structure
  EXPECT_TRUE(fs::exists(test_output_dir));

  if (fs::exists(test_output_dir)) {
    fs::remove_all(test_output_dir);
  }
}

// Test processing with different grid resolutions
TEST(E2E, ProcessDifferentResolutions) {
  fs::path test_output_dir = fs::temp_directory_path() / "blaze_e2e_test_res";

  if (fs::exists(test_output_dir)) {
    fs::remove_all(test_output_dir);
  }
  fs::create_directories(test_output_dir);

  Config config = create_minimal_test_config(test_output_dir);

  // Test with different bin resolution
  config.grid.bin_resolution = 0.5;
  config.grid.downsample_factor = 1;

  LASData las_data = create_synthetic_las_data();

  ProgressTracker tracker;
  process_las_data(las_data, test_output_dir, config, std::move(tracker));

  // Both files should be created
  fs::path ground_file = test_output_dir / "ground.tif";
  fs::path smooth_file = test_output_dir / "smooth_ground.tif";

  // List directory contents for debugging
  std::string dir_contents;
  if (fs::exists(test_output_dir)) {
    for (const auto& entry : fs::directory_iterator(test_output_dir)) {
      dir_contents += entry.path().filename().string() + " ";
    }
  }

  EXPECT_TRUE(fs::exists(ground_file))
      << "ground.tif was not created. Output directory contents: " << dir_contents;

  EXPECT_TRUE(fs::exists(smooth_file))
      << "smooth_ground.tif was not created. Output directory contents: " << dir_contents;

  if (fs::exists(test_output_dir)) {
    fs::remove_all(test_output_dir);
  }
}

// Test that output files have valid structure
TEST(E2E, VerifyOutputStructure) {
  fs::path test_output_dir = fs::temp_directory_path() / "blaze_e2e_test_structure";

  if (fs::exists(test_output_dir)) {
    fs::remove_all(test_output_dir);
  }
  fs::create_directories(test_output_dir);

  Config config = create_minimal_test_config(test_output_dir);
  LASData las_data = create_synthetic_las_data();

  ProgressTracker tracker;
  process_las_data(las_data, test_output_dir, config, std::move(tracker));

  // Verify TIF files can be read
  if (fs::exists(test_output_dir / "ground.tif")) {
    auto ground_grid = read_tif(test_output_dir / "ground.tif");
    EXPECT_GT(ground_grid.width(), 0);
    EXPECT_GT(ground_grid.height(), 0);
  }

  // Verify GPKG files can be read
  if (fs::exists(test_output_dir / "contours.gpkg")) {
    // If file exists, it must be valid and readable
    std::vector<Contour> contours = read_gpkg(test_output_dir / "contours.gpkg");
    // Should be able to read without errors
    EXPECT_GE(contours.size(), 0);
  }

  if (fs::exists(test_output_dir)) {
    fs::remove_all(test_output_dir);
  }
}

// Helper to verify vegetation TIF
void verify_vegetation_tif(const fs::path& vege_tif_path, bool should_have_vegetation,
                           const Config& config) {
  if (!should_have_vegetation) {
    if (fs::exists(vege_tif_path)) {
      auto grid = read_tif(vege_tif_path);
      ASSERT_GE(grid.size(), 3);
      const auto& r_band = grid[0];
      const auto& g_band = grid[1];
      const auto& b_band = grid[2];

      RGBColor background = to_cmyk(config.vege.background_color).toRGB();

      for (size_t i = 0; i < grid.height(); ++i) {
        for (size_t j = 0; j < grid.width(); ++j) {
          if (r_band.get<std::byte>({(long long)j, (long long)i}) !=
                  (std::byte)background.getRed() ||
              g_band.get<std::byte>({(long long)j, (long long)i}) !=
                  (std::byte)background.getGreen() ||
              b_band.get<std::byte>({(long long)j, (long long)i}) !=
                  (std::byte)background.getBlue()) {
            FAIL() << "Vegetation TIF should not contain data, but does.";
          }
        }
      }
    }
    // If it doesn't exist, that's also a pass.
  } else {
    ASSERT_TRUE(fs::exists(vege_tif_path)) << "vege_color.tif was not created.";
    auto grid = read_tif(vege_tif_path);
    ASSERT_GE(grid.size(), 3);
    const auto& r_band = grid[0];
    const auto& g_band = grid[1];
    const auto& b_band = grid[2];

    RGBColor background = to_cmyk(config.vege.background_color).toRGB();
    bool has_data = false;
    for (size_t i = 0; i < grid.height(); ++i) {
      for (size_t j = 0; j < grid.width(); ++j) {
        if (r_band.get<std::byte>({(long long)j, (long long)i}) != (std::byte)background.getRed() ||
            g_band.get<std::byte>({(long long)j, (long long)i}) !=
                (std::byte)background.getGreen() ||
            b_band.get<std::byte>({(long long)j, (long long)i}) !=
                (std::byte)background.getBlue()) {
          has_data = true;
          break;
        }
      }
      if (has_data) break;
    }
    ASSERT_TRUE(has_data) << "Vegetation TIF was created but is empty.";
  }
}

// === Flat Terrain Tests ===
TEST(E2E_New, FlatTerrainGroundOnly) {
  fs::path test_output_dir = fs::temp_directory_path() / "blaze_e2e_flat_ground";
  if (fs::exists(test_output_dir)) fs::remove_all(test_output_dir);
  fs::create_directories(test_output_dir);

  Config config = create_minimal_test_config(test_output_dir);
  Extent2D extent = {0, 100, 0, 100};
  LASData las_data =
      create_synthetic_las_data_ext(extent, [](double, double) { return 100.0; }, false);

  ProgressTracker tracker;
  process_las_data(las_data, test_output_dir, config, std::move(tracker));

  EXPECT_TRUE(fs::exists(test_output_dir / "ground.tif"));
  verify_vegetation_tif(test_output_dir / "vege_color.tif", false, config);

  fs::remove_all(test_output_dir);
}

TEST(E2E_New, FlatTerrainWithVegetation) {
  fs::path test_output_dir = fs::temp_directory_path() / "blaze_e2e_flat_vege";
  if (fs::exists(test_output_dir)) fs::remove_all(test_output_dir);
  fs::create_directories(test_output_dir);

  Config config = create_minimal_test_config(test_output_dir);
  Extent2D extent = {0, 100, 0, 100};
  LASData las_data =
      create_synthetic_las_data_ext(extent, [](double, double) { return 100.0; }, true);

  ProgressTracker tracker;
  process_las_data(las_data, test_output_dir, config, std::move(tracker));

  EXPECT_TRUE(fs::exists(test_output_dir / "ground.tif"));
  verify_vegetation_tif(test_output_dir / "vege_color.tif", true, config);

  fs::remove_all(test_output_dir);
}

// === Sloped Terrain Tests ===
TEST(E2E_New, SlopedTerrainGroundOnly) {
  fs::path test_output_dir = fs::temp_directory_path() / "blaze_e2e_sloped_ground";
  if (fs::exists(test_output_dir)) fs::remove_all(test_output_dir);
  fs::create_directories(test_output_dir);

  Config config = create_minimal_test_config(test_output_dir);
  Extent2D extent = {0, 100, 0, 100};
  LASData las_data = create_synthetic_las_data_ext(
      extent, [](double x, double) { return 100.0 + x * 0.2; }, false);

  ProgressTracker tracker;
  process_las_data(las_data, test_output_dir, config, std::move(tracker));

  EXPECT_TRUE(fs::exists(test_output_dir / "ground.tif"));
  EXPECT_TRUE(fs::exists(test_output_dir / "contours.gpkg"));
  verify_vegetation_tif(test_output_dir / "vege_color.tif", false, config);

  fs::remove_all(test_output_dir);
}

TEST(E2E_New, SlopedTerrainWithVegetation) {
  fs::path test_output_dir = fs::temp_directory_path() / "blaze_e2e_sloped_vege";
  if (fs::exists(test_output_dir)) fs::remove_all(test_output_dir);
  fs::create_directories(test_output_dir);

  Config config = create_minimal_test_config(test_output_dir);
  Extent2D extent = {0, 100, 0, 100};
  LASData las_data =
      create_synthetic_las_data_ext(extent, [](double x, double) { return 100.0 + x * 0.2; }, true);

  ProgressTracker tracker;
  process_las_data(las_data, test_output_dir, config, std::move(tracker));

  EXPECT_TRUE(fs::exists(test_output_dir / "ground.tif"));
  EXPECT_TRUE(fs::exists(test_output_dir / "contours.gpkg"));
  verify_vegetation_tif(test_output_dir / "vege_color.tif", true, config);

  fs::remove_all(test_output_dir);
}

// === Hill Terrain Tests ===
TEST(E2E_New, HillTerrainGroundOnly) {
  fs::path test_output_dir = fs::temp_directory_path() / "blaze_e2e_hill_ground";
  if (fs::exists(test_output_dir)) fs::remove_all(test_output_dir);
  fs::create_directories(test_output_dir);

  Config config = create_minimal_test_config(test_output_dir);
  Extent2D extent = {0, 100, 0, 100};
  LASData las_data = create_synthetic_las_data_ext(
      extent,
      [](double x, double y) {
        double dist = std::sqrt(std::pow(x - 50, 2) + std::pow(y - 50, 2));
        return 100.0 + std::max(0.0, 20.0 - dist * 0.5);
      },
      false);

  ProgressTracker tracker;
  process_las_data(las_data, test_output_dir, config, std::move(tracker));

  EXPECT_TRUE(fs::exists(test_output_dir / "ground.tif"));
  EXPECT_TRUE(fs::exists(test_output_dir / "contours.gpkg"));
  verify_vegetation_tif(test_output_dir / "vege_color.tif", false, config);

  fs::remove_all(test_output_dir);
}

TEST(E2E_New, HillTerrainWithVegetation) {
  fs::path test_output_dir = fs::temp_directory_path() / "blaze_e2e_hill_vege";
  if (fs::exists(test_output_dir)) fs::remove_all(test_output_dir);
  fs::create_directories(test_output_dir);

  Config config = create_minimal_test_config(test_output_dir);
  Extent2D extent = {0, 100, 0, 100};
  LASData las_data = create_synthetic_las_data_ext(
      extent,
      [](double x, double y) {
        double dist = std::sqrt(std::pow(x - 50, 2) + std::pow(y - 50, 2));
        return 100.0 + std::max(0.0, 20.0 - dist * 0.5);
      },
      true);

  ProgressTracker tracker;
  process_las_data(las_data, test_output_dir, config, std::move(tracker));

  EXPECT_TRUE(fs::exists(test_output_dir / "ground.tif"));
  EXPECT_TRUE(fs::exists(test_output_dir / "contours.gpkg"));
  verify_vegetation_tif(test_output_dir / "vege_color.tif", true, config);

  fs::remove_all(test_output_dir);
}
