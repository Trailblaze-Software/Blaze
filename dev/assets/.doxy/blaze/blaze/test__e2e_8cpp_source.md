

# File test\_e2e.cpp

[**File List**](files.md) **>** [**src**](dir_68267d1309a1af8e8297ef4c3efbcdba.md) **>** [**tests**](dir_d93a1d4020dea85bb71b237545b5e722.md) **>** [**test\_e2e.cpp**](test__e2e_8cpp.md)

[Go to the documentation of this file](test__e2e_8cpp.md)


```C++
#include <gtest/gtest.h>

#include <cmath>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>

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
  if (should_have_vegetation) {
    ASSERT_TRUE(fs::exists(vege_tif_path)) << "vege_color.tif was not created.";
  } else {
    // If it doesn't exist, that's also a pass.
    if (!fs::exists(vege_tif_path)) {
      return;
    }
  }

  // Common code: read and validate TIF
  auto grid = read_tif(vege_tif_path);
  ASSERT_GE(grid.size(), 3);
  const auto& r_band = grid[0];
  const auto& g_band = grid[1];
  const auto& b_band = grid[2];
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

  // Check pixels based on expected behavior
  if (should_have_vegetation) {
    // Since vegetation points are added across the whole area, most pixels should be vegetation
    // color Pixels can be either background or vegetation colors, but we expect mostly vegetation
    size_t vegetation_pixel_count = 0;
    size_t background_pixel_count = 0;
    size_t invalid_pixel_count = 0;

    for (size_t i = 0; i < grid.height(); ++i) {
      for (size_t j = 0; j < grid.width(); ++j) {
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
            invalid_pixel_count++;
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

    size_t total_pixels = grid.width() * grid.height();
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

  // Read and validate TIF
  auto grid = read_tif(raw_vege_tif_path);
  if (is_smoothed) {
    // Smoothed version is single-band float
    ASSERT_EQ(grid.size(), 1) << "Smoothed raw vege TIF should have 1 band";
    const auto& band = grid[0];

    if (should_have_vegetation) {
      // Every pixel should have a value >= 0.0 and <= 1.0 (blocked proportion)
      for (size_t i = 0; i < band.height(); ++i) {
        for (size_t j = 0; j < band.width(); ++j) {
          float value = band.get<float>({(long long)j, (long long)i});
          if (value < 0.0f || value > 1.0f) {
            FAIL() << "Pixel at (" << j << ", " << i
                   << ") has invalid blocked proportion value: " << value
                   << " (expected 0.0 to 1.0)";
          }
          // With vegetation, we expect at least some pixels to have non-zero values
          // But we can't require all to be > 0 since some areas might not have vegetation
        }
      }
    } else {
      // All pixels should be 0.0 (no vegetation)
      for (size_t i = 0; i < band.height(); ++i) {
        for (size_t j = 0; j < band.width(); ++j) {
          float value = band.get<float>({(long long)j, (long long)i});
          if (value != 0.0f) {
            FAIL() << "Pixel at (" << j << ", " << i
                   << ") should be 0.0 (no vegetation) but is: " << value;
          }
        }
      }
    }
  } else {
    // Raw version is two-band: band 0 = value, band 1 = validity mask
    ASSERT_EQ(grid.size(), 2) << "Raw vege TIF should have 2 bands (value and validity)";
    const auto& value_band = grid[0];
    const auto& validity_band = grid[1];

    if (should_have_vegetation) {
      // For unsmoothed raw vege: verify that cells with vegetation points have valid blocked
      // proportion This checks "has vege point if and only if has valid blocked proportion" Note:
      // We don't compare to vege_color here because vege_color uses smoothed data which spreads
      // values
      bool has_valid_vegetation = false;
      for (size_t i = 0; i < value_band.height(); ++i) {
        for (size_t j = 0; j < value_band.width(); ++j) {
          float value = value_band.get<float>({(long long)j, (long long)i});
          float validity = validity_band.get<float>({(long long)j, (long long)i});

          if (validity == 255.0f) {
            // Valid value means there are vegetation points - should be in range [0.0, 1.0]
            if (value < 0.0f || value > 1.0f) {
              FAIL() << "Pixel at (" << j << ", " << i
                     << ") has invalid blocked proportion value: " << value
                     << " (expected 0.0 to 1.0)";
            }
            if (value > 0.0f) {
              has_valid_vegetation = true;
            }
            // Note: validity = 255 means there are vegetation points in this cell
            // The blocked proportion should be > 0 if there are points in the height range
          } else if (validity != 0.0f) {
            FAIL() << "Pixel at (" << j << ", " << i << ") has invalid validity mask: " << validity
                   << " (expected 0.0 or 255.0)";
          }
          // validity = 0 means no vegetation points in this cell (which is correct)
        }
      }
      ASSERT_TRUE(has_valid_vegetation)
          << "Raw vegetation TIF should contain at least some valid vegetation data";
    } else {
      // All pixels should be nullopt (validity = 0) or have value = 0.0
      for (size_t i = 0; i < value_band.height(); ++i) {
        for (size_t j = 0; j < value_band.width(); ++j) {
          float value = value_band.get<float>({(long long)j, (long long)i});
          float validity = validity_band.get<float>({(long long)j, (long long)i});

          if (validity == 255.0f) {
            // If valid, value should be 0.0 (no vegetation)
            if (value != 0.0f) {
              FAIL() << "Pixel at (" << j << ", " << i
                     << ") should be 0.0 (no vegetation) but is: " << value;
            }
          } else if (validity != 0.0f) {
            FAIL() << "Pixel at (" << j << ", " << i << ") has invalid validity mask: " << validity
                   << " (expected 0.0 or 255.0)";
          }
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
  const char* keep_output = std::getenv("BLAZE_KEEP_TEST_OUTPUT");
  bool should_keep_output = (keep_output != nullptr && std::string(keep_output) != "0");

  fs::path test_output_dir = fs::temp_directory_path() / ("blaze_e2e_" + params.name);
  if (fs::exists(test_output_dir)) fs::remove_all(test_output_dir);
  fs::create_directories(test_output_dir);

  Config config = create_minimal_test_config(test_output_dir);
  Extent2D extent = {0, 100, 0, 100};
  LASData las_data =
      create_synthetic_las_data_ext(extent, params.height_function, params.with_vegetation);

  ProgressTracker tracker;
  process_las_data(las_data, test_output_dir, config, std::move(tracker));

  EXPECT_TRUE(fs::exists(test_output_dir / "ground.tif"));

  fs::path contours_path = test_output_dir / "contours.gpkg";
  EXPECT_TRUE(fs::exists(contours_path));
  std::vector<Contour> contours = read_gpkg(contours_path);

  if (params.expect_contours) {
    EXPECT_GT(contours.size(), 0);
  } else {
    EXPECT_EQ(contours.size(), 0);
    auto ground_grid = read_tif(test_output_dir / "ground.tif");
    const auto& band = ground_grid[0];
    // For flat terrain tests, check that elevation matches the expected value
    // (102.5m to avoid being exactly on a 5.0m contour interval)
    double expected_elevation = params.height_function(0, 0);
    for (size_t i = 0; i < band.height(); ++i) {
      for (size_t j = 0; j < band.width(); ++j) {
        if (band.get<double>({(long long)j, (long long)i}) != std::numeric_limits<double>::max()) {
          EXPECT_NEAR(band.get<double>({(long long)j, (long long)i}), expected_elevation, 1e-6);
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
```


