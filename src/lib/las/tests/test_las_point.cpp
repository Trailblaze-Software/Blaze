#include <gtest/gtest.h>

#include <sstream>

#include "las/las_point.hpp"

// =============================================================================
// LASClassification tests
// =============================================================================

TEST(LASClassification, Values) {
  EXPECT_EQ(static_cast<uint8_t>(LASClassification::CreatedNeverClassified), 0);
  EXPECT_EQ(static_cast<uint8_t>(LASClassification::Unclassified), 1);
  EXPECT_EQ(static_cast<uint8_t>(LASClassification::Ground), 2);
  EXPECT_EQ(static_cast<uint8_t>(LASClassification::LowVegetation), 3);
  EXPECT_EQ(static_cast<uint8_t>(LASClassification::MediumVegetation), 4);
  EXPECT_EQ(static_cast<uint8_t>(LASClassification::HighVegetation), 5);
  EXPECT_EQ(static_cast<uint8_t>(LASClassification::Building), 6);
  EXPECT_EQ(static_cast<uint8_t>(LASClassification::LowPoint), 7);
  EXPECT_EQ(static_cast<uint8_t>(LASClassification::ModelKeyPoint), 8);
  EXPECT_EQ(static_cast<uint8_t>(LASClassification::Water), 9);
}

TEST(LASClassification, StreamOutput) {
  std::ostringstream os;
  os << LASClassification::Ground;
  EXPECT_EQ(os.str(), "Ground");

  os.str("");
  os << LASClassification::HighVegetation;
  EXPECT_EQ(os.str(), "HighVegetation");

  os.str("");
  os << LASClassification::Building;
  EXPECT_EQ(os.str(), "Building");

  os.str("");
  os << LASClassification::Water;
  EXPECT_EQ(os.str(), "Water");
}

// =============================================================================
// LASPoint tests
// =============================================================================

TEST(LASPoint, Construction) {
  LASPoint p(100.5, 200.3, 50.7, 1000, LASClassification::Ground);
  EXPECT_DOUBLE_EQ(p.x(), 100.5);
  EXPECT_DOUBLE_EQ(p.y(), 200.3);
  EXPECT_DOUBLE_EQ(p.z(), 50.7);
  EXPECT_EQ(p.intensity(), 1000);
  EXPECT_EQ(p.classification(), LASClassification::Ground);
}

TEST(LASPoint, DefaultConstruction) {
  LASPoint p;
  // Should not crash
  (void)p;
}

TEST(LASPoint, MutableAccessors) {
  LASPoint p(0, 0, 0, 0, LASClassification::Unclassified);
  p.x() = 10.0;
  p.y() = 20.0;
  p.z() = 30.0;
  p.intensity() = 500;
  p.classification() = LASClassification::HighVegetation;

  EXPECT_DOUBLE_EQ(p.x(), 10.0);
  EXPECT_DOUBLE_EQ(p.y(), 20.0);
  EXPECT_DOUBLE_EQ(p.z(), 30.0);
  EXPECT_EQ(p.intensity(), 500);
  EXPECT_EQ(p.classification(), LASClassification::HighVegetation);
}

TEST(LASPoint, InheritsCoordinate3D) {
  LASPoint p(1.0, 2.0, 3.0, 100, LASClassification::Ground);
  // LASPoint inherits from Coordinate3D<double> which inherits from Coordinate2D<double>
  // Test that coordinate operations work
  EXPECT_DOUBLE_EQ(p.x(), 1.0);
  EXPECT_DOUBLE_EQ(p.y(), 2.0);
  EXPECT_DOUBLE_EQ(p.z(), 3.0);

  // Test magnitude from Coordinate2D (only x,y)
  double mag = p.magnitude();
  EXPECT_NEAR(mag, std::sqrt(1.0 + 4.0), 1e-10);
}

TEST(LASPoint, StreamOutput) {
  LASPoint p(1.5, 2.5, 3.5, 42, LASClassification::Building);
  std::ostringstream os;
  os << p;
  std::string result = os.str();
  EXPECT_TRUE(result.find("LASPoint") != std::string::npos);
  EXPECT_TRUE(result.find("1.5") != std::string::npos);
  EXPECT_TRUE(result.find("2.5") != std::string::npos);
  EXPECT_TRUE(result.find("3.5") != std::string::npos);
}

TEST(LASPoint, AllClassifications) {
  // Ensure all classification values can be constructed
  LASClassification classes[] = {
      LASClassification::CreatedNeverClassified,
      LASClassification::Unclassified,
      LASClassification::Ground,
      LASClassification::LowVegetation,
      LASClassification::MediumVegetation,
      LASClassification::HighVegetation,
      LASClassification::Building,
      LASClassification::LowPoint,
      LASClassification::ModelKeyPoint,
      LASClassification::Water,
  };
  for (auto cls : classes) {
    LASPoint p(0, 0, 0, 0, cls);
    EXPECT_EQ(p.classification(), cls);
  }
}
