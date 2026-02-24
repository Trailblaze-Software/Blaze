#include <gtest/gtest.h>

#include <cmath>
#include <limits>
#include <sstream>
#include <string>

#include "las/las_file.hpp"

// =============================================================================
// BorderType stream output tests
// =============================================================================

TEST(BorderType, StreamOutput) {
  std::ostringstream os;

  os << BorderType::N;
  EXPECT_EQ(os.str(), "N");
  os.str("");

  os << BorderType::NE;
  EXPECT_EQ(os.str(), "NE");
  os.str("");

  os << BorderType::E;
  EXPECT_EQ(os.str(), "E");
  os.str("");

  os << BorderType::SE;
  EXPECT_EQ(os.str(), "SE");
  os.str("");

  os << BorderType::S;
  EXPECT_EQ(os.str(), "S");
  os.str("");

  os << BorderType::SW;
  EXPECT_EQ(os.str(), "SW");
  os.str("");

  os << BorderType::W;
  EXPECT_EQ(os.str(), "W");
  os.str("");

  os << BorderType::NW;
  EXPECT_EQ(os.str(), "NW");
}

// =============================================================================
// border_ranges tests
// =============================================================================

TEST(BorderRanges, North) {
  Extent2D box{0.0, 100.0, 0.0, 100.0};
  Extent2D r = border_ranges(box, BorderType::N, 10.0);
  EXPECT_DOUBLE_EQ(r.minx, 0.0);
  EXPECT_DOUBLE_EQ(r.maxx, 100.0);
  EXPECT_DOUBLE_EQ(r.miny, 90.0);  // maxy - border_width
  EXPECT_DOUBLE_EQ(r.maxy, 100.0);
}

TEST(BorderRanges, South) {
  Extent2D box{0.0, 100.0, 0.0, 100.0};
  Extent2D r = border_ranges(box, BorderType::S, 10.0);
  EXPECT_DOUBLE_EQ(r.minx, 0.0);
  EXPECT_DOUBLE_EQ(r.maxx, 100.0);
  EXPECT_DOUBLE_EQ(r.miny, 0.0);
  EXPECT_DOUBLE_EQ(r.maxy, 10.0);  // miny + border_width
}

TEST(BorderRanges, East) {
  Extent2D box{0.0, 100.0, 0.0, 100.0};
  Extent2D r = border_ranges(box, BorderType::E, 10.0);
  EXPECT_DOUBLE_EQ(r.minx, 90.0);  // maxx - border_width
  EXPECT_DOUBLE_EQ(r.maxx, 100.0);
  EXPECT_DOUBLE_EQ(r.miny, 0.0);
  EXPECT_DOUBLE_EQ(r.maxy, 100.0);
}

TEST(BorderRanges, West) {
  Extent2D box{0.0, 100.0, 0.0, 100.0};
  Extent2D r = border_ranges(box, BorderType::W, 10.0);
  EXPECT_DOUBLE_EQ(r.minx, 0.0);
  EXPECT_DOUBLE_EQ(r.maxx, 10.0);  // minx + border_width
  EXPECT_DOUBLE_EQ(r.miny, 0.0);
  EXPECT_DOUBLE_EQ(r.maxy, 100.0);
}

TEST(BorderRanges, NorthEast) {
  Extent2D box{0.0, 100.0, 0.0, 100.0};
  Extent2D r = border_ranges(box, BorderType::NE, 10.0);
  EXPECT_DOUBLE_EQ(r.minx, 90.0);
  EXPECT_DOUBLE_EQ(r.maxx, 100.0);
  EXPECT_DOUBLE_EQ(r.miny, 90.0);
  EXPECT_DOUBLE_EQ(r.maxy, 100.0);
}

TEST(BorderRanges, SouthWest) {
  Extent2D box{0.0, 100.0, 0.0, 100.0};
  Extent2D r = border_ranges(box, BorderType::SW, 10.0);
  EXPECT_DOUBLE_EQ(r.minx, 0.0);
  EXPECT_DOUBLE_EQ(r.maxx, 10.0);
  EXPECT_DOUBLE_EQ(r.miny, 0.0);
  EXPECT_DOUBLE_EQ(r.maxy, 10.0);
}

TEST(BorderRanges, SouthEast) {
  Extent2D box{0.0, 100.0, 0.0, 100.0};
  Extent2D r = border_ranges(box, BorderType::SE, 10.0);
  EXPECT_DOUBLE_EQ(r.minx, 90.0);
  EXPECT_DOUBLE_EQ(r.maxx, 100.0);
  EXPECT_DOUBLE_EQ(r.miny, 0.0);
  EXPECT_DOUBLE_EQ(r.maxy, 10.0);
}

TEST(BorderRanges, NorthWest) {
  Extent2D box{0.0, 100.0, 0.0, 100.0};
  Extent2D r = border_ranges(box, BorderType::NW, 10.0);
  EXPECT_DOUBLE_EQ(r.minx, 0.0);
  EXPECT_DOUBLE_EQ(r.maxx, 10.0);
  EXPECT_DOUBLE_EQ(r.miny, 90.0);
  EXPECT_DOUBLE_EQ(r.maxy, 100.0);
}

// =============================================================================
// external_border_ranges tests
// =============================================================================

TEST(ExternalBorderRanges, North) {
  Extent2D box{0.0, 100.0, 0.0, 100.0};
  Extent2D r = external_border_ranges(box, BorderType::N, 10.0);
  EXPECT_DOUBLE_EQ(r.minx, 0.0);
  EXPECT_DOUBLE_EQ(r.maxx, 100.0);
  EXPECT_DOUBLE_EQ(r.miny, 100.0);  // maxy
  EXPECT_DOUBLE_EQ(r.maxy, 110.0);  // maxy + border_width
}

TEST(ExternalBorderRanges, South) {
  Extent2D box{0.0, 100.0, 0.0, 100.0};
  Extent2D r = external_border_ranges(box, BorderType::S, 10.0);
  EXPECT_DOUBLE_EQ(r.minx, 0.0);
  EXPECT_DOUBLE_EQ(r.maxx, 100.0);
  EXPECT_DOUBLE_EQ(r.miny, -10.0);  // miny - border_width
  EXPECT_DOUBLE_EQ(r.maxy, 0.0);    // miny
}

TEST(ExternalBorderRanges, East) {
  Extent2D box{0.0, 100.0, 0.0, 100.0};
  Extent2D r = external_border_ranges(box, BorderType::E, 10.0);
  EXPECT_DOUBLE_EQ(r.minx, 100.0);  // maxx
  EXPECT_DOUBLE_EQ(r.maxx, 110.0);  // maxx + border_width
  EXPECT_DOUBLE_EQ(r.miny, 0.0);
  EXPECT_DOUBLE_EQ(r.maxy, 100.0);
}

TEST(ExternalBorderRanges, West) {
  Extent2D box{0.0, 100.0, 0.0, 100.0};
  Extent2D r = external_border_ranges(box, BorderType::W, 10.0);
  EXPECT_DOUBLE_EQ(r.minx, -10.0);  // minx - border_width
  EXPECT_DOUBLE_EQ(r.maxx, 0.0);    // minx
  EXPECT_DOUBLE_EQ(r.miny, 0.0);
  EXPECT_DOUBLE_EQ(r.maxy, 100.0);
}

TEST(ExternalBorderRanges, Corners) {
  Extent2D box{0.0, 100.0, 0.0, 100.0};

  Extent2D ne = external_border_ranges(box, BorderType::NE, 10.0);
  EXPECT_DOUBLE_EQ(ne.minx, 100.0);
  EXPECT_DOUBLE_EQ(ne.maxx, 110.0);
  EXPECT_DOUBLE_EQ(ne.miny, 100.0);
  EXPECT_DOUBLE_EQ(ne.maxy, 110.0);

  Extent2D se = external_border_ranges(box, BorderType::SE, 10.0);
  EXPECT_DOUBLE_EQ(se.minx, 100.0);
  EXPECT_DOUBLE_EQ(se.maxx, 110.0);
  EXPECT_DOUBLE_EQ(se.miny, -10.0);
  EXPECT_DOUBLE_EQ(se.maxy, 0.0);

  Extent2D sw = external_border_ranges(box, BorderType::SW, 10.0);
  EXPECT_DOUBLE_EQ(sw.minx, -10.0);
  EXPECT_DOUBLE_EQ(sw.maxx, 0.0);
  EXPECT_DOUBLE_EQ(sw.miny, -10.0);
  EXPECT_DOUBLE_EQ(sw.maxy, 0.0);

  Extent2D nw = external_border_ranges(box, BorderType::NW, 10.0);
  EXPECT_DOUBLE_EQ(nw.minx, -10.0);
  EXPECT_DOUBLE_EQ(nw.maxx, 0.0);
  EXPECT_DOUBLE_EQ(nw.miny, 100.0);
  EXPECT_DOUBLE_EQ(nw.maxy, 110.0);
}

// =============================================================================
// round function tests
// =============================================================================

TEST(LASRound, BasicRounding) {
  EXPECT_EQ(round(5.4), 5);
  EXPECT_EQ(round(5.5), 6);
  EXPECT_EQ(round(5.6), 6);
  EXPECT_EQ(round(-5.4), -5);
  EXPECT_EQ(round(-5.5), -6);
}

TEST(LASRound, WithResolution) {
  EXPECT_EQ(round(17.0, 10.0), 20);
  EXPECT_EQ(round(12.0, 10.0), 10);
  EXPECT_EQ(round(15.0, 10.0), 20);
  EXPECT_EQ(round(25.0, 10.0), 30);
}

TEST(LASRound, WithSmallResolution) {
  EXPECT_EQ(round(2.3, 0.5), 2);
  EXPECT_EQ(round(2.5, 0.5), 2);
}

// =============================================================================
// average function tests
// =============================================================================

TEST(Average, Integers) {
  EXPECT_EQ(average(4, 6), 5);
  EXPECT_EQ(average(0, 10), 5);
  EXPECT_EQ(average(-5, 5), 0);
}

TEST(Average, Doubles) {
  EXPECT_DOUBLE_EQ(average(1.0, 3.0), 2.0);
  EXPECT_DOUBLE_EQ(average(0.0, 0.0), 0.0);
  EXPECT_DOUBLE_EQ(average(-10.0, 10.0), 0.0);
}

// =============================================================================
// unique_coord_name tests
// =============================================================================

TEST(UniqueCoordName, BasicOutput) {
  Extent2D box{100.0, 200.0, 300.0, 400.0};
  std::string name = unique_coord_name(box);
  // Values are rounded to nearest 10: 100, 300, 200, 400
  EXPECT_FALSE(name.empty());
  // Should contain coordinate-based values separated by underscores
  EXPECT_TRUE(name.find("_") != std::string::npos);
}

TEST(UniqueCoordName, DifferentBoxesProduceDifferentNames) {
  Extent2D box1{0.0, 100.0, 0.0, 100.0};
  Extent2D box2{100.0, 200.0, 100.0, 200.0};
  EXPECT_NE(unique_coord_name(box1), unique_coord_name(box2));
}

TEST(UniqueCoordName, SameBoxProducesSameName) {
  Extent2D box{50.0, 150.0, 50.0, 150.0};
  EXPECT_EQ(unique_coord_name(box), unique_coord_name(box));
}

// =============================================================================
// LASFile basic tests (using LASData which inherits from LASFile)
// =============================================================================

TEST(LASData, ConstructFromExtent) {
  Extent2D bounds{100.0, 200.0, 300.0, 400.0};
  LASData data(bounds, GeoProjection("EPSG:2193"));

  EXPECT_EQ(data.n_points(), 0u);
}

TEST(LASData, InsertAndAccess) {
  Extent2D bounds{0.0, 100.0, 0.0, 100.0};
  LASData data(bounds, GeoProjection());

  LASPoint p1(10.0, 20.0, 30.0, 500, LASClassification::Ground);
  LASPoint p2(50.0, 60.0, 70.0, 600, LASClassification::HighVegetation);
  data.insert(p1);
  data.insert(p2);

  EXPECT_EQ(data.n_points(), 2u);
  EXPECT_DOUBLE_EQ(data[0].x(), 10.0);
  EXPECT_DOUBLE_EQ(data[0].y(), 20.0);
  EXPECT_DOUBLE_EQ(data[0].z(), 30.0);
  EXPECT_DOUBLE_EQ(data[1].x(), 50.0);
  EXPECT_DOUBLE_EQ(data[1].y(), 60.0);
}

TEST(LASData, InsertUpdatesBounds) {
  Extent2D bounds{0.0, 0.0, 0.0, 0.0};
  LASData data(bounds, GeoProjection());

  data.insert(LASPoint(10.0, 20.0, 5.0, 100, LASClassification::Ground));
  data.insert(LASPoint(50.0, 60.0, 15.0, 200, LASClassification::Ground));
  data.insert(LASPoint(30.0, 40.0, 10.0, 150, LASClassification::Ground));

  const Extent3D& b = data.bounds();
  EXPECT_DOUBLE_EQ(b.minx, 10.0);
  EXPECT_DOUBLE_EQ(b.maxx, 50.0);
  EXPECT_DOUBLE_EQ(b.miny, 20.0);
  EXPECT_DOUBLE_EQ(b.maxy, 60.0);
  EXPECT_DOUBLE_EQ(b.minz, 5.0);
  EXPECT_DOUBLE_EQ(b.maxz, 15.0);
}

TEST(LASData, IntensityRange) {
  Extent2D bounds{0.0, 100.0, 0.0, 100.0};
  LASData data(bounds, GeoProjection());

  data.insert(LASPoint(0, 0, 0, 100, LASClassification::Ground));
  data.insert(LASPoint(0, 0, 0, 500, LASClassification::Ground));
  data.insert(LASPoint(0, 0, 0, 300, LASClassification::Ground));

  auto range = data.intensity_range();
  EXPECT_EQ(range.first, 100);
  EXPECT_EQ(range.second, 500);
}

TEST(LASData, Iterator) {
  Extent2D bounds{0.0, 100.0, 0.0, 100.0};
  LASData data(bounds, GeoProjection());

  data.insert(LASPoint(1.0, 0, 0, 0, LASClassification::Ground));
  data.insert(LASPoint(2.0, 0, 0, 0, LASClassification::Ground));
  data.insert(LASPoint(3.0, 0, 0, 0, LASClassification::Ground));

  double sum = 0;
  for (const LASPoint& p : data) {
    sum += p.x();
  }
  EXPECT_DOUBLE_EQ(sum, 6.0);
}

TEST(LASData, PushBack) {
  Extent2D bounds{0.0, 100.0, 0.0, 100.0};
  LASData data(bounds, GeoProjection());

  LASPoint p(5.0, 10.0, 15.0, 42, LASClassification::Water);
  data.push_back(p);
  EXPECT_EQ(data.n_points(), 1u);
  EXPECT_EQ(data[0].classification(), LASClassification::Water);
}

TEST(LASData, MutableAccess) {
  Extent2D bounds{0.0, 100.0, 0.0, 100.0};
  LASData data(bounds, GeoProjection());

  data.insert(LASPoint(1.0, 2.0, 3.0, 100, LASClassification::Ground));
  data[0].classification() = LASClassification::Building;
  EXPECT_EQ(data[0].classification(), LASClassification::Building);
}

// =============================================================================
// LASFile accessor tests (via LASData)
// =============================================================================

TEST(LASFile, TopLeft) {
  Extent2D bounds{100.0, 200.0, 300.0, 400.0};
  LASData data(bounds, GeoProjection());
  // top_left uses m_bounds which starts with z=max/min from constructor
  // After inserting a point, bounds will update
  data.insert(LASPoint(100.0, 400.0, 0.0, 0, LASClassification::Ground));
  data.insert(LASPoint(200.0, 300.0, 0.0, 0, LASClassification::Ground));

  auto tl = data.top_left();
  EXPECT_DOUBLE_EQ(tl.x(), data.bounds().minx);
  EXPECT_DOUBLE_EQ(tl.y(), data.bounds().maxy);
}

TEST(LASFile, WidthHeight) {
  Extent2D bounds{0.0, 0.0, 0.0, 0.0};
  LASData data(bounds, GeoProjection());

  data.insert(LASPoint(10.0, 20.0, 0.0, 0, LASClassification::Ground));
  data.insert(LASPoint(60.0, 80.0, 0.0, 0, LASClassification::Ground));

  EXPECT_DOUBLE_EQ(data.width(), 50.0);
  EXPECT_DOUBLE_EQ(data.height(), 60.0);
}

TEST(LASFile, HeightRange) {
  Extent2D bounds{0.0, 0.0, 0.0, 0.0};
  LASData data(bounds, GeoProjection());

  data.insert(LASPoint(0, 0, 5.0, 0, LASClassification::Ground));
  data.insert(LASPoint(0, 0, 25.0, 0, LASClassification::Ground));
  data.insert(LASPoint(0, 0, 15.0, 0, LASClassification::Ground));

  auto range = data.height_range();
  EXPECT_DOUBLE_EQ(range.first, 5.0);
  EXPECT_DOUBLE_EQ(range.second, 25.0);
}

TEST(LASFile, ExportBounds) {
  // export_bounds averages m_bounds and m_original_bounds
  Extent2D bounds{100.0, 200.0, 300.0, 400.0};
  LASData data(bounds, GeoProjection());

  // The original_bounds is set from the constructor's bounds
  // After insert, m_bounds will grow but m_original_bounds stays
  data.insert(LASPoint(90.0, 290.0, 0.0, 0, LASClassification::Ground));
  data.insert(LASPoint(210.0, 410.0, 0.0, 0, LASClassification::Ground));

  Extent2D eb = data.export_bounds();
  // original bounds (from constructor) has z set but 2D is from extent
  // Depending on how m_original_bounds is set, we check the average
  // m_original_bounds minx = from constructor, m_bounds.minx = 90.0 (from point)
  // The constructor takes Extent2D and creates Extent3D with z=max/min sentinels
  // So m_original_bounds.minx should be derived from Extent2D{100,200,300,400}
  // but looking at constructor: LASFile(Extent2D bounds, GeoProjection) makes
  //   m_bounds = Extent3D(bounds, double::max, double::min)
  // Then insert grows m_bounds. So:
  //   m_bounds.minx = min(original, 90) = some initial value
  // After insert(90,290,...): m_bounds.minx=90, m_bounds.miny=290
  // After insert(210,410,...): m_bounds.maxx=210, m_bounds.maxy=410
  // m_original_bounds was set from Extent3D(bounds, sentinels) where bounds={100,200,300,400}
  // So m_original_bounds.minx=100, maxx=200, miny=300, maxy=400
  // export_bounds = average(m_bounds, m_original_bounds)
  EXPECT_DOUBLE_EQ(eb.minx, average(90.0, 100.0));
  EXPECT_DOUBLE_EQ(eb.maxx, average(210.0, 200.0));
  EXPECT_DOUBLE_EQ(eb.miny, average(290.0, 300.0));
  EXPECT_DOUBLE_EQ(eb.maxy, average(410.0, 400.0));
}

TEST(LASFile, Projection) {
  Extent2D bounds{0.0, 1.0, 0.0, 1.0};
  LASData data(bounds, GeoProjection("EPSG:2193"));
  EXPECT_EQ(data.projection().to_string(), "EPSG:2193");
}
