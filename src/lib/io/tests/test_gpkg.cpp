#include <gtest/gtest.h>

#include <fstream>
#include <vector>

#include "contour/contour.hpp"
#include "io/gpkg.hpp"
#include "polyline/polyline.hpp"
#include "utilities/coordinate.hpp"
#include "utilities/filesystem.hpp"

// Test GPKGWriter basic functionality
TEST(GPKG, WriteAndReadContours) {
  // Create a temporary file path
  fs::path test_file = fs::temp_directory_path() / "test_contours.gpkg";

  // Clean up if file exists
  if (fs::exists(test_file)) {
    fs::remove(test_file);
  }

  // Create a simple projection string (WGS84)
  std::string projection =
      R"(GEOGCS["WGS 84",DATUM["WGS_1984",SPHEROID["WGS 84",6378137,298.257223563]],PRIMEM["Greenwich",0],UNIT["degree",0.0174532925199433]])";

  // Write contours
  {
    GPKGWriter writer(test_file.string(), projection);

    // Create test contours
    std::vector<Coordinate2D<double>> points1 = {
        Coordinate2D<double>(0.0, 0.0), Coordinate2D<double>(1.0, 0.0),
        Coordinate2D<double>(1.0, 1.0), Coordinate2D<double>(0.0, 1.0)};

    std::vector<Coordinate2D<double>> points2 = {Coordinate2D<double>(2.0, 2.0),
                                                 Coordinate2D<double>(3.0, 2.0),
                                                 Coordinate2D<double>(3.0, 3.0)};

    Polyline polyline1;
    polyline1.layer = "test_layer";
    polyline1.name = "contour_1";
    polyline1.vertices = points1;

    Polyline polyline2;
    polyline2.layer = "test_layer";
    polyline2.name = "contour_2";
    polyline2.vertices = points2;

    writer.write_polyline(polyline1, {{"elevation", 10.0}});
    writer.write_polyline(polyline2, {{"elevation", 20.0}});
  }

  // Read contours back
  std::vector<Contour> contours = read_gpkg(test_file);

  // Verify we got the contours back
  EXPECT_EQ(contours.size(), 2);

  // Check first contour
  EXPECT_DOUBLE_EQ(contours[0].height(), 10.0);
  EXPECT_EQ(contours[0].points().size(), 4);

  // Check second contour
  EXPECT_DOUBLE_EQ(contours[1].height(), 20.0);
  EXPECT_EQ(contours[1].points().size(), 3);

  // Clean up
  if (fs::exists(test_file)) {
    fs::remove(test_file);
  }
}

// Test GPKGWriter with multiple layers
TEST(GPKG, MultipleLayers) {
  fs::path test_file = fs::temp_directory_path() / "test_multilayer.gpkg";

  if (fs::exists(test_file)) {
    fs::remove(test_file);
  }

  std::string projection =
      R"(GEOGCS["WGS 84",DATUM["WGS_1984",SPHEROID["WGS 84",6378137,298.257223563]],PRIMEM["Greenwich",0],UNIT["degree",0.0174532925199433]])";

  {
    GPKGWriter writer(test_file.string(), projection);

    Polyline polyline1;
    polyline1.layer = "layer1";
    polyline1.name = "line1";
    polyline1.vertices = {Coordinate2D<double>(0.0, 0.0), Coordinate2D<double>(1.0, 1.0)};

    Polyline polyline2;
    polyline2.layer = "layer2";
    polyline2.name = "line2";
    polyline2.vertices = {Coordinate2D<double>(2.0, 2.0), Coordinate2D<double>(3.0, 3.0)};

    writer.write_polyline(polyline1);
    writer.write_polyline(polyline2);
  }

  // Read back - should get both layers
  std::vector<Contour> contours = read_gpkg(test_file);
  EXPECT_GE(contours.size(), 2);

  if (fs::exists(test_file)) {
    fs::remove(test_file);
  }
}

// Test GPKGWriter with different field types
TEST(GPKG, DifferentFieldTypes) {
  fs::path test_file = fs::temp_directory_path() / "test_fields.gpkg";

  if (fs::exists(test_file)) {
    fs::remove(test_file);
  }

  std::string projection =
      R"(GEOGCS["WGS 84",DATUM["WGS_1984",SPHEROID["WGS 84",6378137,298.257223563]],PRIMEM["Greenwich",0],UNIT["degree",0.0174532925199433]])";

  {
    GPKGWriter writer(test_file.string(), projection);

    Polyline polyline;
    polyline.layer = "test";
    polyline.name = "test_line";
    polyline.vertices = {Coordinate2D<double>(0.0, 0.0), Coordinate2D<double>(1.0, 1.0)};

    // Test with int, double, and string fields
    writer.write_polyline(
        polyline, {{"elevation", 100.0}, {"id", 42}, {"name_str", std::string("test_name")}});
  }

  // File should exist and be readable
  EXPECT_TRUE(fs::exists(test_file));

  std::vector<Contour> contours = read_gpkg(test_file);
  EXPECT_GE(contours.size(), 1);

  if (fs::exists(test_file)) {
    fs::remove(test_file);
  }
}

// Test read_gpkg with non-existent file
TEST(GPKG, ReadNonExistentFile) {
  fs::path test_file = fs::temp_directory_path() / "nonexistent.gpkg";

  // Ensure file doesn't exist
  if (fs::exists(test_file)) {
    fs::remove(test_file);
  }

  std::vector<Contour> contours = read_gpkg(test_file);

  // Should return empty vector, not crash
  EXPECT_EQ(contours.size(), 0);
}

// Test read_gpkg with empty file (if possible)
// This test might fail if GDAL requires valid GPKG structure
// but it's good to test error handling
TEST(GPKG, ReadEmptyFile) {
  fs::path test_file = fs::temp_directory_path() / "empty.gpkg";

  if (fs::exists(test_file)) {
    fs::remove(test_file);
  }

  // Create empty file
  std::ofstream ofs(test_file.string());
  ofs.close();

  // Should handle gracefully
  std::vector<Contour> contours = read_gpkg(test_file);

  // Should return empty or handle error gracefully
  // (exact behavior depends on GDAL implementation)

  if (fs::exists(test_file)) {
    fs::remove(test_file);
  }
}
