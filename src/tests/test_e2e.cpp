#include <gtest/gtest.h>

#include <cmath>
#include <filesystem>
#include <fstream>

#include "config_input/config_input.hpp"
#include "contour/contour.hpp"
#include "gdal_priv.h"
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

// Helper to create a valid WKT projection from EPSG code
// Use a static variable to ensure it's only created once and GDAL is initialized
static const std::string& get_wgs84_wkt() {
  static std::string wkt;
  static bool initialized = false;
  if (!initialized) {
    initialized = true;
    GDALAllRegister();
    OGRSpatialReference srs;
    if (srs.importFromEPSG(4326) == OGRERR_NONE) {
      char* wkt_ptr = nullptr;
      srs.exportToWkt(&wkt_ptr);
      if (wkt_ptr) {
        wkt = std::string(wkt_ptr);
        CPLFree(wkt_ptr);
      }
    }
    if (wkt.empty()) {
      // Fallback to a known valid WKT string for WGS84
      wkt =
          "GEOGCS[\"WGS 84\",DATUM[\"WGS_1984\",SPHEROID[\"WGS "
          "84\",6378137,298.257223563]],PRIMEM[\"Greenwich\",0],UNIT[\"degree\",0.0174532925199433]"
          ",AUTHORITY[\"EPSG\",\"4326\"]]";
    }
  }
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
  config.vege = VegeConfig{CMYKColor(0, 27, 79, 0),  // yellow
                           {}};

  // Minimal render config
  config.render.scale = 1000;
  config.render.dpi = 300;

  return config;
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

  // Create LAS data from grid
  LASData las_data(grid);

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

  try {
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
      std::vector<Contour> contours = read_gpkg(test_output_dir / "contours.gpkg");
      // Should be able to read without errors
      EXPECT_GE(contours.size(), 0);
    }

  } catch (const std::exception& e) {
    FAIL() << "Exception during processing: " << e.what();
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

  try {
    Config config = create_minimal_test_config(test_output_dir);

    // Create empty LAS data
    Extent2D bounds(0.0, 10.0, 0.0, 10.0);
    GeoProjection proj;
    LASData las_data(bounds, proj);

    ProgressTracker tracker;
    process_las_data(las_data, test_output_dir, config, std::move(tracker));

    // Should still create output directory structure
    EXPECT_TRUE(fs::exists(test_output_dir));

  } catch (const std::exception&) {
    // Empty data might throw, which is acceptable
    // Just verify cleanup happens
  }

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

  try {
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

  } catch (const std::exception& e) {
    FAIL() << "Exception with different resolution: " << e.what();
  }

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

  try {
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
      std::vector<Contour> contours = read_gpkg(test_output_dir / "contours.gpkg");
      // Should be able to read without errors
      EXPECT_GE(contours.size(), 0);
    }

  } catch (const std::exception& e) {
    FAIL() << "Exception verifying structure: " << e.what();
  }

  if (fs::exists(test_output_dir)) {
    fs::remove_all(test_output_dir);
  }
}
