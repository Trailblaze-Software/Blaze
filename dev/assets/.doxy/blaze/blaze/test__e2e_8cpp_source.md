

# File test\_e2e.cpp

[**File List**](files.md) **>** [**src**](dir_68267d1309a1af8e8297ef4c3efbcdba.md) **>** [**tests**](dir_d93a1d4020dea85bb71b237545b5e722.md) **>** [**test\_e2e.cpp**](test__e2e_8cpp.md)

[Go to the documentation of this file](test__e2e_8cpp.md)


```C++
#include <gtest/gtest.h>

#include <cmath>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <numbers>

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
#include "testing/env.hpp"
#include "testing/output_dir.hpp"
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

// Create a minimal config for testing
Config create_minimal_test_config(const fs::path& output_dir) {
  Config config = Config::Default();
  config.set_output_directory(output_dir);
  config.grid.bin_resolution = 1.0;
  config.grid.downsample_factor = 2;
  config.grid.vegetation_grid_resolution = 1.0;
  config.grid.contour_dem_resolution = 2.0;
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
  green_veg.blocking_threshold = 0.01;
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
  for (double x = extent.minx; x < extent.maxx; x += 1.0) {
    for (double y = extent.miny; y < extent.maxy; y += 1.0) {
      double z = height_function(x, y);
      las_data.insert(LASPoint(x, y, z, 1000, LASClassification::Ground));
    }
  }

  // Generate vegetation points if requested
  if (with_vegetation) {
    // Use denser vegetation points (2m intervals) to ensure they're detected
    // after binning and low-pass filtering
    for (double x = extent.minx + 2.0; x < extent.maxx - 2.0; x += 2.0) {
      for (double y = extent.miny + 2.0; y < extent.maxy - 2.0; y += 2.0) {
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

  GeoGrid<double> grid(data, GeoTransform(), GeoProjection(get_wgs84_wkt()));

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
  fs::path test_output_dir = blaze::test::unique_test_output_dir();

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
  process_las_data(las_data, test_output_dir, config, ProgressTracker());

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
    std::vector<Contour> contours = read_gpkg(test_output_dir / "contours.gpkg", ProgressTracker());
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
  fs::path test_output_dir = blaze::test::unique_test_output_dir();

  if (fs::exists(test_output_dir)) {
    fs::remove_all(test_output_dir);
  }
  fs::create_directories(test_output_dir);

  Config config = create_minimal_test_config(test_output_dir);

  // Create empty LAS data
  Extent2D bounds = {0.0, 10.0, 0.0, 10.0};
  GeoProjection proj;
  LASData las_data(bounds, proj);

  process_las_data(las_data, test_output_dir, config, ProgressTracker());

  // Should still create output directory structure
  EXPECT_TRUE(fs::exists(test_output_dir));

  if (fs::exists(test_output_dir)) {
    fs::remove_all(test_output_dir);
  }
}

// Test processing with different grid resolutions
TEST(E2E, ProcessDifferentResolutions) {
  fs::path test_output_dir = blaze::test::unique_test_output_dir();

  if (fs::exists(test_output_dir)) {
    fs::remove_all(test_output_dir);
  }
  fs::create_directories(test_output_dir);

  Config config = create_minimal_test_config(test_output_dir);

  // Test with different bin resolution
  config.grid.bin_resolution = 0.5;
  config.grid.downsample_factor = 1;
  config.grid.vegetation_grid_resolution = 0.5;
  config.grid.contour_dem_resolution = 0.5;

  LASData las_data = create_synthetic_las_data();

  process_las_data(las_data, test_output_dir, config, ProgressTracker());

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
  fs::path test_output_dir = blaze::test::unique_test_output_dir();

  if (fs::exists(test_output_dir)) {
    fs::remove_all(test_output_dir);
  }
  fs::create_directories(test_output_dir);

  Config config = create_minimal_test_config(test_output_dir);
  LASData las_data = create_synthetic_las_data();

  process_las_data(las_data, test_output_dir, config, ProgressTracker());

  // Verify TIF files can be read
  if (fs::exists(test_output_dir / "ground.tif")) {
    auto ground_grid = read_tif(test_output_dir / "ground.tif", ProgressTracker());
    EXPECT_GT(ground_grid.width(), 0);
    EXPECT_GT(ground_grid.height(), 0);
  }

  // Verify GPKG files can be read
  if (fs::exists(test_output_dir / "contours.gpkg")) {
    std::vector<Contour> contours = read_gpkg(test_output_dir / "contours.gpkg", ProgressTracker());
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
  if (should_have_vegetation) {
    ASSERT_TRUE(fs::exists(vege_tif_path)) << "vege_color.tif was not created.";
  } else {
    // If it doesn't exist, that's also a pass.
    if (!fs::exists(vege_tif_path)) {
      return;
    }
  }

  // Common code: read and validate TIF
  auto grid = read_tif(vege_tif_path, ProgressTracker());
  ASSERT_GE(grid.size(), 3);
  const auto& r_band = grid[0];
  const auto& g_band = grid[1];
  const auto& b_band = grid[2];
  const bool has_alpha = grid.size() >= 4;
  const auto& a_band = has_alpha ? grid[3] : grid[0];
  RGBColor background = to_cmyk(config.vege.background_color).toRGB();

  // Determine expected vegetation color(s) from config
  std::vector<RGBColor> expected_vege_colors;
  for (const VegeHeightConfig& vege_config : config.vege.height_configs) {
    for (const BlockingThresholdColorPair& color_pair : vege_config.colors) {
      expected_vege_colors.push_back(to_rgb(color_pair.color));
    }
  }
  ASSERT_FALSE(expected_vege_colors.empty()) << "No vegetation colors configured.";

  // Helper lambda to get pixel RGB color
  auto get_pixel_color = [&](size_t i, size_t j) -> RGBColor {
    return RGBColor(
        static_cast<unsigned char>(r_band.get<std::byte>({(long long)j, (long long)i})),
        static_cast<unsigned char>(g_band.get<std::byte>({(long long)j, (long long)i})),
        static_cast<unsigned char>(b_band.get<std::byte>({(long long)j, (long long)i})));
  };

  // Helper lambda to check if a pixel matches a color
  auto matches_color = [](const RGBColor& pixel, const RGBColor& expected) {
    return pixel.getRed() == expected.getRed() && pixel.getGreen() == expected.getGreen() &&
           pixel.getBlue() == expected.getBlue();
  };

  auto is_masked_exterior = [&](size_t i, size_t j) -> bool {
    if (!has_alpha) {
      return false;
    }
    return a_band.get<std::byte>({(long long)j, (long long)i}) == std::byte{0};
  };

  // Check pixels based on expected behavior
  if (should_have_vegetation) {
    // Since vegetation points are added across the whole area, most pixels should be vegetation
    // color Pixels can be either background or vegetation colors, but we expect mostly vegetation
    size_t vegetation_pixel_count = 0;
    size_t background_pixel_count = 0;

    for (size_t i = 0; i < grid.height(); ++i) {
      for (size_t j = 0; j < grid.width(); ++j) {
        if (is_masked_exterior(i, j)) {
          continue;
        }
        RGBColor pixel = get_pixel_color(i, j);
        bool matches_background = matches_color(pixel, background);
        bool matches_vege = false;

        if (matches_background) {
          background_pixel_count++;
        } else {
          for (const RGBColor& vege_color : expected_vege_colors) {
            if (matches_color(pixel, vege_color)) {
              matches_vege = true;
              vegetation_pixel_count++;
              break;
            }
          }
          if (!matches_vege) {
            FAIL() << "Pixel at (" << j << ", " << i
                   << ") does not match expected color (background or vegetation). Got RGB("
                   << static_cast<int>(pixel.getRed()) << ", " << static_cast<int>(pixel.getGreen())
                   << ", " << static_cast<int>(pixel.getBlue()) << "), expected background RGB("
                   << static_cast<int>(background.getRed()) << ", "
                   << static_cast<int>(background.getGreen()) << ", "
                   << static_cast<int>(background.getBlue()) << ") or vegetation color RGB("
                   << static_cast<int>(expected_vege_colors[0].getRed()) << ", "
                   << static_cast<int>(expected_vege_colors[0].getGreen()) << ", "
                   << static_cast<int>(expected_vege_colors[0].getBlue()) << ")";
          }
        }
      }
    }

    const size_t total_pixels = vegetation_pixel_count + background_pixel_count;
    ASSERT_GT(total_pixels, 0u) << "No non-transparent pixels found in vege_color.tif";
    double vegetation_ratio = static_cast<double>(vegetation_pixel_count) / total_pixels;

    // Expect at least 50% of pixels to be vegetation color (allowing for edges and smoothing
    // effects)
    ASSERT_GE(vegetation_ratio, 0.5)
        << "Expected at least 50% of pixels to be vegetation color, but got "
        << (vegetation_ratio * 100.0) << "% (vegetation: " << vegetation_pixel_count
        << ", background: " << background_pixel_count << ", total: " << total_pixels << ")";
  } else {
    // All pixels must be background
    for (size_t i = 0; i < grid.height(); ++i) {
      for (size_t j = 0; j < grid.width(); ++j) {
        if (is_masked_exterior(i, j)) {
          continue;
        }
        RGBColor pixel = get_pixel_color(i, j);
        if (!matches_color(pixel, background)) {
          FAIL() << "Pixel at (" << j << ", " << i
                 << ") should be background color but is not. Got RGB("
                 << static_cast<int>(pixel.getRed()) << ", " << static_cast<int>(pixel.getGreen())
                 << ", " << static_cast<int>(pixel.getBlue()) << "), expected RGB("
                 << static_cast<int>(background.getRed()) << ", "
                 << static_cast<int>(background.getGreen()) << ", "
                 << static_cast<int>(background.getBlue()) << ")";
        }
      }
    }
  }
}

// Helper to verify raw vegetation TIF (blocked proportion)
void verify_raw_vegetation_tif(const fs::path& raw_vege_tif_path, bool should_have_vegetation,
                               const Config& config) {
  // Find the corresponding vege config by matching the filename
  std::string filename = raw_vege_tif_path.stem().string();
  bool is_smoothed = filename.find("smoothed_") == 0;
  std::string vege_name = is_smoothed ? filename.substr(9) : filename;

  const VegeHeightConfig* vege_config = nullptr;
  for (const VegeHeightConfig& vc : config.vege.height_configs) {
    if (vc.name == vege_name) {
      vege_config = &vc;
      break;
    }
  }
  ASSERT_NE(vege_config, nullptr) << "No vegetation config found for name: " << vege_name;

  if (should_have_vegetation) {
    ASSERT_TRUE(fs::exists(raw_vege_tif_path))
        << "Raw vegetation TIF " << raw_vege_tif_path << " was not created.";
  } else {
    // If it doesn't exist, that's also a pass.
    if (!fs::exists(raw_vege_tif_path)) {
      return;
    }
  }

  // Raw and smoothed vegetation exports are stored as a single-band Byte raster.
  // Values are 0..255 representing blocked proportion 0..1, with 0 also used
  // for "no data" at export time (by design).
  auto grid = read_tif(raw_vege_tif_path, ProgressTracker());
  ASSERT_EQ(grid.size(), 1) << "Raw vege TIF should have 1 band (Byte)";
  const auto& value_band = grid[0];

  bool has_any_nonzero = false;
  for (size_t i = 0; i < value_band.height(); ++i) {
    for (size_t j = 0; j < value_band.width(); ++j) {
      const std::byte value = value_band.get<std::byte>({(long long)j, (long long)i});
      const int v = static_cast<unsigned char>(value);
      if (v != 0) {
        has_any_nonzero = true;
        break;
      }
    }
    if (has_any_nonzero) break;
  }

  if (should_have_vegetation) {
    ASSERT_TRUE(has_any_nonzero) << "Expected some non-zero vegetation values.";
  } else {
    // With no vegetation, the blocked-proportion should export as all zeros.
    for (size_t i = 0; i < value_band.height(); ++i) {
      for (size_t j = 0; j < value_band.width(); ++j) {
        const std::byte value = value_band.get<std::byte>({(long long)j, (long long)i});
        const int v = static_cast<unsigned char>(value);
        if (v != 0) {
          FAIL() << "Pixel at (" << j << ", " << i << ") should be 0 (no vegetation) but is: " << v;
        }
      }
    }
  }
}

struct TerrainTestParams {
  std::string name;
  std::function<double(double, double)> height_function;
  bool with_vegetation;
  bool expect_contours;

  friend std::ostream& operator<<(std::ostream& os, const TerrainTestParams& params) {
    os << params.name;
    return os;
  }
};

class E2ETerrainTest : public ::testing::TestWithParam<TerrainTestParams> {
 public:
  // Ensure GDAL is initialized once before any tests run (thread-safe)
  static void SetUpTestSuite() { ensure_gdal_initialized(); }
};

TEST_P(E2ETerrainTest, ProcessTerrain) {
  const TerrainTestParams& params = GetParam();
  // Check if we should keep output files (check early so files are preserved even on test failure)
  const char* keep_output = blaze::test::get_env("BLAZE_KEEP_TEST_OUTPUT");
  bool should_keep_output = (keep_output != nullptr && std::string(keep_output) != "0");

  fs::path test_output_dir = blaze::test::unique_test_output_dir(params.name);
  if (fs::exists(test_output_dir)) fs::remove_all(test_output_dir);
  fs::create_directories(test_output_dir);

  Config config = create_minimal_test_config(test_output_dir);
  Extent2D extent = {0, 100, 0, 100};
  LASData las_data =
      create_synthetic_las_data_ext(extent, params.height_function, params.with_vegetation);

  process_las_data(las_data, test_output_dir, config, ProgressTracker());

  EXPECT_TRUE(fs::exists(test_output_dir / "ground.tif"));

  fs::path contours_path = test_output_dir / "contours.gpkg";
  EXPECT_TRUE(fs::exists(contours_path));
  std::vector<Contour> contours = read_gpkg(contours_path, ProgressTracker());

  if (params.expect_contours) {
    EXPECT_GT(contours.size(), 0);
  } else {
    EXPECT_EQ(contours.size(), 0);
    auto ground_grid = read_tif(test_output_dir / "ground.tif", ProgressTracker());
    const auto& band = ground_grid[0];
    // For flat terrain tests, check that elevation matches the expected value
    // (102.5m to avoid being exactly on a 5.0m contour interval)
    double expected_elevation = params.height_function(0, 0);
    for (size_t i = 0; i < band.height(); ++i) {
      for (size_t j = 0; j < band.width(); ++j) {
        if (band.get<double>({(long long)j, (long long)i}) != std::numeric_limits<double>::max()) {
          const double elevation = band.get<double>({(long long)j, (long long)i});
          if (std::isfinite(elevation)) {
            EXPECT_NEAR(elevation, expected_elevation, 1e-6);
          }
        }
      }
    }
  }

  verify_vegetation_tif(test_output_dir / "vege_color.tif", params.with_vegetation, config);

  // Verify raw vegetation TIFs for each height config
  for (const VegeHeightConfig& vege_config : config.vege.height_configs) {
    fs::path raw_vege_path = test_output_dir / "raw_vege" / (vege_config.name + ".tif");
    verify_raw_vegetation_tif(raw_vege_path, params.with_vegetation, config);

    fs::path smoothed_vege_path =
        test_output_dir / "raw_vege" / ("smoothed_" + vege_config.name + ".tif");
    verify_raw_vegetation_tif(smoothed_vege_path, params.with_vegetation, config);
  }

  // Check contour properties based on terrain type
  if (params.expect_contours && contours.size() > 0) {
    // Check based on test name to determine expected behavior
    if (params.name.find("Hill") != std::string::npos) {
      // Hill terrain should have ALL closed loops
      for (const Contour& contour : contours) {
        EXPECT_TRUE(contour.is_loop()) << "Hill terrain should have all contours as closed loops, "
                                          "but found an open contour at height "
                                       << contour.height();
      }
    } else if (params.name.find("Slope") != std::string::npos) {
      // Slope terrain should have ALL open lines
      for (const Contour& contour : contours) {
        EXPECT_FALSE(contour.is_loop()) << "Slope terrain should have all contours as open lines, "
                                           "but found a closed loop at height "
                                        << contour.height();
      }
    }
  }

  // Keep output files if BLAZE_KEEP_TEST_OUTPUT environment variable is set
  if (should_keep_output) {
    std::cout << "Test output kept at: " << test_output_dir << std::endl;
  } else {
    fs::remove_all(test_output_dir);
  }
}

INSTANTIATE_TEST_SUITE_P(
    E2E_New, E2ETerrainTest,
    ::testing::Values(
        TerrainTestParams{"FlatTerrainGroundOnly", [](double, double) { return 102.5; }, false,
                          false},
        TerrainTestParams{"FlatTerrainWithVegetation", [](double, double) { return 102.5; }, true,
                          false},
        TerrainTestParams{"SlopedTerrainGroundOnly",
                          [](double x, double) { return 100.0 + x * 0.2; }, false, true},
        TerrainTestParams{"SlopedTerrainWithVegetation",
                          [](double x, double) { return 100.0 + x * 0.2; }, true, true},
        TerrainTestParams{"HillTerrainGroundOnly",
                          [](double x, double y) {
                            double dist = std::sqrt(std::pow(x - 50, 2) + std::pow(y - 50, 2));
                            return 99.0 + std::max(0.0, 20.0 - dist * 0.5);
                          },
                          false, true},
        TerrainTestParams{"HillTerrainWithVegetation",
                          [](double x, double y) {
                            double dist = std::sqrt(std::pow(x - 50, 2) + std::pow(y - 50, 2));
                            return 99.0 + std::max(0.0, 20.0 - dist * 0.5);
                          },
                          true, true}));

// Test ground estimation on slopes in all directions
TEST(E2E, GroundEstimationSlopes) {
  // Check if we should keep output files (check early so files are preserved even on test failure)
  const char* keep_output = blaze::test::get_env("BLAZE_KEEP_TEST_OUTPUT");
  bool should_keep_output = (keep_output != nullptr && std::string(keep_output) != "0");

  fs::path test_output_dir = blaze::test::unique_test_output_dir("slope");

  // Clean up if exists
  if (fs::exists(test_output_dir)) {
    fs::remove_all(test_output_dir);
  }
  fs::create_directories(test_output_dir);

  Config config = create_minimal_test_config(test_output_dir);
  config.grid.bin_resolution = 5.0;
  config.grid.vegetation_grid_resolution = config.grid.bin_resolution;

  const int downsample_factor = 1;
  config.grid.downsample_factor = downsample_factor;
  config.grid.contour_dem_resolution = config.grid.bin_resolution * downsample_factor;

  const double base_elevation = 100.0;
  const double test_area_size = 50.0;  // 50m x 50m test area
  const double point_spacing = 0.5;    // 0.5m spacing for dense point cloud

  // Test angles: flat (0°), 25°, and 45°
  std::vector<double> angles_deg = {0.0, 25.0, 45.0};

  // Define all 8 directions plus flat
  struct DirectionTest {
    std::string name;
    std::function<double(double, double, double)> height_func;  // (x, y, slope_ratio)
  };

  std::vector<DirectionTest> directions = {
      {"Flat", [=](double /*x*/, double /*y*/, double /*slope_ratio*/) { return base_elevation; }},
      {"North",
       [=](double /*x*/, double y, double slope_ratio) {
         return base_elevation + (test_area_size - y) * slope_ratio;
       }},
      {"South", [=](double /*x*/, double y,
                    double slope_ratio) { return base_elevation + y * slope_ratio; }},
      {"East", [=](double x, double /*y*/,
                   double slope_ratio) { return base_elevation + x * slope_ratio; }},
      {"West",
       [=](double x, double /*y*/, double slope_ratio) {
         return base_elevation + (test_area_size - x) * slope_ratio;
       }},
      {"NE",
       [=](double x, double y, double slope_ratio) {
         return base_elevation + (x + (test_area_size - y)) * slope_ratio / std::sqrt(2.0);
       }},
      {"NW",
       [=](double x, double y, double slope_ratio) {
         return base_elevation +
                ((test_area_size - x) + (test_area_size - y)) * slope_ratio / std::sqrt(2.0);
       }},
      {"SE",
       [=](double x, double y, double slope_ratio) {
         return base_elevation + (x + y) * slope_ratio / std::sqrt(2.0);
       }},
      {"SW",
       [=](double x, double y, double slope_ratio) {
         return base_elevation + ((test_area_size - x) + y) * slope_ratio / std::sqrt(2.0);
       }},
  };

  // Store statistics for summary table
  struct TestStats {
    std::string direction;
    double angle;
    int downsample_factor;
    double avg_error;
    double std_dev;
    int valid_samples;
  };
  std::vector<TestStats> all_stats;

  // Loop over angles and directions
  for (double angle_deg : angles_deg) {
    const double angle_rad = angle_deg * std::numbers::pi / 180.0;
    const double slope_ratio = std::tan(angle_rad);  // rise over run (0 for flat)

    for (const auto& dir : directions) {
      // Skip non-flat directions when angle is 0
      if (angle_deg == 0.0 && dir.name != "Flat") {
        continue;
      }
      // Skip flat when angle is not 0
      if (angle_deg != 0.0 && dir.name == "Flat") {
        continue;
      }

      // Create extent for this test
      Extent2D extent{0.0, test_area_size, 0.0, test_area_size};
      const std::string proj_str = get_wgs84_wkt();
      LASData las_data(extent, GeoProjection(proj_str));

      // Generate ground points with the slope
      for (double x = extent.minx + 0.5 * point_spacing; x <= extent.maxx; x += point_spacing) {
        for (double y = extent.miny + 0.5 * point_spacing; y <= extent.maxy; y += point_spacing) {
          double z = dir.height_func(x, y, slope_ratio);
          las_data.insert(LASPoint(x, y, z, 1000, LASClassification::Ground));
        }
      }

      // Process the data
      fs::path output_dir = test_output_dir / (dir.name + "_" + std::to_string((int)angle_deg) +
                                               "deg_ds" + std::to_string(downsample_factor));
      fs::create_directories(output_dir);
      process_las_data(las_data, output_dir, config, ProgressTracker());

      // Read back the ground estimate
      fs::path ground_file = output_dir / "ground.tif";
      if (!fs::exists(ground_file)) {
        // If ground.tif doesn't exist, try smooth_ground.tif
        ground_file = output_dir / "smooth_ground.tif";
      }

      if (fs::exists(ground_file)) {
        Geo<MultiBand<FlexGrid>> tif_data = read_tif(ground_file, ProgressTracker());
        GeoGrid<double> ground_grid(tif_data.width(), tif_data.height(),
                                    GeoTransform(tif_data.transform()),
                                    GeoProjection(tif_data.projection()));
        ground_grid.fill_from(tif_data[0]);

        // Verbose per-case output (banner, per-sample rows, and stats) is gated behind an env var
        // so normal CI runs don't produce huge logs. Set BLAZE_TEST_VERBOSE=1 to enable.
        // Unset or "0" is treated as disabled, matching the BLAZE_KEEP_TEST_OUTPUT convention.
        // The final summary table is always printed.
        const char* verbose_env = blaze::test::get_env("BLAZE_TEST_VERBOSE");
        const bool verbose = (verbose_env != nullptr && std::string(verbose_env) != "0");

        if (verbose) {
          std::cout << "\n========================================\n";
          std::cout << "Direction: " << dir.name << ", Angle: " << angle_deg
                    << "°, Downsample: " << downsample_factor << "\n";
          std::cout << "========================================\n";
          std::cout << std::fixed << std::setprecision(4);
          std::cout << std::setw(10) << "X" << std::setw(10) << "Y" << std::setw(12) << "Expected Z"
                    << std::setw(12) << "Estimated Z" << std::setw(12) << "Error" << std::endl;
          std::cout << "----------------------------------------\n";
        }

        // Sample all grid cells
        int valid_samples = 0;
        double max_abs_error = 0.0;
        double total_signed_error = 0.0;
        std::vector<double> signed_errors;

        // Sample at grid cell centers, but skip cells too close to edges
        // Skip cells within downsample_factor pixels from each edge
        // (since each pixel in the downsampled grid represents downsample_factor * bin_resolution
        // meters)
        size_t edge_padding = downsample_factor;

        for (size_t i = edge_padding; i < ground_grid.height() - edge_padding; i++) {
          for (size_t j = edge_padding; j < ground_grid.width() - edge_padding; j++) {
            // Get the projection coordinate for this grid cell center
            Coordinate2D<double> pixel_center(static_cast<double>(j) + 0.5,
                                              static_cast<double>(i) + 0.5);
            Coordinate2D<double> proj_coord =
                ground_grid.transform().pixel_to_projection(pixel_center);

            double x = proj_coord.x();
            double y = proj_coord.y();
            double expected_z = dir.height_func(x, y, slope_ratio);
            double estimated_z = ground_grid[{j, i}];

            // Skip invalid values (NaN or infinity)
            if (std::isfinite(estimated_z)) {
              double signed_error =
                  estimated_z - expected_z;  // Positive = overestimate, negative = underestimate
              double abs_error = std::abs(signed_error);
              max_abs_error = std::max(max_abs_error, abs_error);
              total_signed_error += signed_error;
              signed_errors.push_back(signed_error);
              valid_samples++;

              if (verbose) {
                std::cout << std::setw(10) << x << std::setw(10) << y << std::setw(12) << expected_z
                          << std::setw(12) << estimated_z << std::setw(12) << signed_error
                          << std::endl;
              }

              const double baseline_tolerance = 1e-6;  // meters
              double tolerance = std::max(baseline_tolerance, 0.4 * std::abs(slope_ratio));
              EXPECT_NEAR(estimated_z, expected_z, tolerance)
                  << "Direction: " << dir.name << ", Angle: " << angle_deg << "°, Position: (" << x
                  << ", " << y << "), Expected: " << expected_z << ", Got: " << estimated_z;
            }
          }
        }

        if (verbose) {
          std::cout << "----------------------------------------\n";
        }
        if (valid_samples > 0) {
          double avg_signed_error = total_signed_error / valid_samples;

          // Calculate standard deviation of signed errors
          double variance = 0.0;
          for (double error : signed_errors) {
            double diff = error - avg_signed_error;
            variance += diff * diff;
          }
          double std_dev = std::sqrt(variance / valid_samples);

          if (verbose) {
            std::cout << "Valid samples: " << valid_samples << "\n";
            std::cout << "Average error: " << avg_signed_error << " m\n";
            std::cout << "Std deviation: " << std_dev << " m\n";
            std::cout << "Max abs error: " << max_abs_error << " m\n";
          }

          // Check that average absolute error is less than or equal to 0.4 * slope
          double max_avg_error = 0.4 * std::abs(slope_ratio);
          EXPECT_LE(std::abs(avg_signed_error), max_avg_error)
              << "Direction: " << dir.name << ", Angle: " << angle_deg << "°, Average error "
              << avg_signed_error << " exceeds threshold " << max_avg_error;

          // Check that standard deviation is less than or equal to 0.001
          EXPECT_LE(std_dev, 0.001)
              << "Direction: " << dir.name << ", Angle: " << angle_deg << "°, Standard deviation "
              << std_dev << " exceeds threshold 0.001";

          // Store statistics for summary table
          all_stats.push_back(
              {dir.name, angle_deg, downsample_factor, avg_signed_error, std_dev, valid_samples});
        } else {
          ADD_FAILURE() << "No valid samples found for Direction: " << dir.name
                        << ", Angle: " << angle_deg << "°, Downsample: " << downsample_factor
                        << ". All sampled cells were non-finite, indicating a processing failure.";
        }
        if (verbose) {
          std::cout << "========================================\n\n";
        }
      } else {
        // If neither file exists, that's also a problem
        ADD_FAILURE() << "Neither ground.tif nor smooth_ground.tif exists for " << dir.name << " "
                      << angle_deg << "° (downsample=" << downsample_factor << ")";
      }
    }
  }

  // Print summary table
  if (!all_stats.empty()) {
    std::cout << "\n==================================================\n";
    std::cout << "Ground Estimation Error Summary Table\n";
    std::cout << "==================================================\n";
    std::cout << std::fixed << std::setprecision(4);
    std::cout << std::setw(10) << "Direction" << std::setw(8) << "Angle" << std::setw(6) << "DS"
              << std::setw(12) << "Avg Error" << std::setw(12) << "Std Dev" << std::setw(10)
              << "Samples" << std::endl;
    std::cout << "--------------------------------------------------\n";

    for (const auto& stats : all_stats) {
      std::cout << std::setw(10) << stats.direction << std::setw(8) << stats.angle << std::setw(6)
                << stats.downsample_factor << std::setw(12) << stats.avg_error << std::setw(12)
                << stats.std_dev << std::setw(10) << stats.valid_samples << std::endl;
    }
    std::cout << "==================================================\n\n";
  }

  // Keep output files if BLAZE_KEEP_TEST_OUTPUT environment variable is set
  if (should_keep_output) {
    std::cout << "Test output kept at: " << test_output_dir << std::endl;
  } else if (fs::exists(test_output_dir)) {
    fs::remove_all(test_output_dir);
  }
}

// ---- write_to_image_tif explicit bounds tests ----------------------------

// Helper: read back a single-band byte TIF and return its pixel values.
static std::vector<uint8_t> read_byte_tif_pixels(const fs::path& path) {
  ensure_gdal_initialized();
  GDALDataset* ds = static_cast<GDALDataset*>(GDALOpen(path.string().c_str(), GA_ReadOnly));
  Assert(ds != nullptr, "Failed to open TIF: " + path.string());
  GDALRasterBand* band = ds->GetRasterBand(1);
  int w = band->GetXSize(), h = band->GetYSize();
  std::vector<uint8_t> pixels(static_cast<size_t>(w * h));
  CPLErr err = band->RasterIO(GF_Read, 0, 0, w, h, pixels.data(), w, h, GDT_Byte, 0, 0);
  Assert(err == CE_None, "RasterIO failed for: " + path.string());
  GDALClose(ds);
  return pixels;
}

// With explicit bounds [pi/2 (min), 0 (max)]:
//   flat     (slope = 0)    -> pixel 255 (bright, no cliff)
//   vertical (slope = pi/2) -> pixel 0   (dark, cliff)
TEST(WriteToImageTif, AbsoluteSlopeBounds) {
  fs::path tmp = blaze::test::unique_test_output_dir("slope_bounds");
  fs::create_directories(tmp);
  fs::path out = tmp / "test_slope.tif";

  GeoGrid<double> grid(3, 3, GeoTransform(), GeoProjection());

  ProgressTracker progress_tracker;

  // Flat: all zeros -> pixel should be 255.
  for (size_t i = 0; i < 3; i++)
    for (size_t j = 0; j < 3; j++) grid[{j, i}] = 0.0;

  {
    ProgressTracker write_tracker = SUBTRACKER(0.0, 0.33);
    write_to_image_tif(grid, out, std::move(write_tracker),
                       std::optional<double>(std::numbers::pi / 2), std::optional<double>(0.0));
  }
  {
    auto pixels = read_byte_tif_pixels(out);
    for (auto p : pixels) EXPECT_EQ(p, 255) << "flat grid should produce all-255 pixels";
  }

  // Fully vertical: all pi/2 -> pixel should be 0.
  for (size_t i = 0; i < 3; i++)
    for (size_t j = 0; j < 3; j++) grid[{j, i}] = std::numbers::pi / 2;

  write_to_image_tif(grid, out, SUBTRACKER(0.33, 0.66), std::optional<double>(std::numbers::pi / 2),
                     std::optional<double>(0.0));
  {
    auto pixels = read_byte_tif_pixels(out);
    for (auto p : pixels) EXPECT_EQ(p, 0) << "vertical grid should produce all-zero pixels";
  }

  // Mid-point: pi/4 -> pixel should be 127 (truncation of 255 * 0.5).
  for (size_t i = 0; i < 3; i++)
    for (size_t j = 0; j < 3; j++) grid[{j, i}] = std::numbers::pi / 4;

  write_to_image_tif(grid, out, SUBTRACKER(0.66, 1.0), std::optional<double>(std::numbers::pi / 2),
                     std::optional<double>(0.0));
  {
    auto pixels = read_byte_tif_pixels(out);
    for (auto p : pixels) EXPECT_EQ(p, 127) << "45-degree slope should produce pixel 127";
  }

  fs::remove_all(tmp);
}

TEST(WriteToImageTif, NodataPixelsMapToZero) {
  fs::path tmp = blaze::test::unique_test_output_dir("slope_nodata");
  fs::create_directories(tmp);
  fs::path out = tmp / "test_nodata.tif";

  GeoGrid<double> grid(3, 3, GeoTransform(), GeoProjection());
  const double nan = std::numeric_limits<double>::quiet_NaN();
  grid[{0, 0}] = 0.0;
  grid[{1, 0}] = 0.0;
  grid[{2, 0}] = nan;
  grid[{0, 1}] = 0.0;
  grid[{1, 1}] = 0.0;
  grid[{2, 1}] = nan;
  grid[{0, 2}] = nan;
  grid[{1, 2}] = nan;
  grid[{2, 2}] = nan;

  write_to_image_tif(grid, out, ProgressTracker(), std::optional<double>(std::numbers::pi / 2),
                     std::optional<double>(0.0));
  auto pixels = read_byte_tif_pixels(out);
  ASSERT_EQ(pixels.size(), 9u);
  EXPECT_EQ(pixels[2], 0);
  EXPECT_EQ(pixels[5], 0);
  EXPECT_EQ(pixels[6], 0);
  EXPECT_EQ(pixels[7], 0);
  EXPECT_EQ(pixels[8], 0);
  EXPECT_EQ(pixels[0], 255);
  EXPECT_EQ(pixels[4], 255);

  fs::remove_all(tmp);
}

// Without explicit bounds the original per-tile behaviour is preserved:
// min is always mapped to 0, max always to 255.
TEST(WriteToImageTif, PerTileBoundsDefault) {
  fs::path tmp = blaze::test::unique_test_output_dir("slope_per_tile");
  fs::create_directories(tmp);
  fs::path out = tmp / "test_pertile.tif";

  GeoGrid<double> grid(3, 3, GeoTransform(), GeoProjection());
  // Arbitrary range [2, 4].
  for (size_t i = 0; i < 3; i++)
    for (size_t j = 0; j < 3; j++) grid[{j, i}] = (j == 0 && i == 0) ? 2.0 : 4.0;

  write_to_image_tif(grid, out, ProgressTracker());
  auto pixels = read_byte_tif_pixels(out);

  // The minimum value (2.0) should map to 0, maximum (4.0) to 255.
  EXPECT_EQ(pixels[0], 0);    // top-left has value 2.0 (min)
  EXPECT_EQ(pixels[1], 255);  // next pixel has value 4.0 (max)

  fs::remove_all(tmp);
}

TEST(WriteToImageTif, ConstantGrid) {
  fs::path tmp = blaze::test::unique_test_output_dir("constant_grid");
  fs::create_directories(tmp);
  fs::path out = tmp / "test_constant.tif";

  GeoGrid<double> grid(2, 2, GeoTransform(), GeoProjection());
  for (size_t i = 0; i < 2; i++)
    for (size_t j = 0; j < 2; j++) grid[{j, i}] = 42.0;

  write_to_image_tif(grid, out, ProgressTracker());
  auto pixels = read_byte_tif_pixels(out);
  for (auto p : pixels) {
    EXPECT_EQ(p, 0) << "constant grid should map to zero, not NaN";
  }

  fs::remove_all(tmp);
}
```


