#include <gtest/gtest.h>

#include "las/elvis_filename.hpp"
#include "las/las_file.hpp"

namespace {
const Extent2D k_oberon_tile = {760000.0, 762000.0, 6234000.0, 6236000.0};
}

TEST(ElvisFilename, GDA94ForOlderCaptures) {
  EXPECT_EQ(elvis_filename_epsg("Oberon201311-PHO3-C0-AHD_7606234_55_0002_0002.laz", k_oberon_tile),
            28355);
}

TEST(ElvisFilename, GDA2020FromYear2020) {
  EXPECT_EQ(elvis_filename_epsg("ACT2020-12ppm-C3-ELL_6756082_55_0001_0001.las",
                                {675000.0, 675999.9, 6082000.0, 6082999.9}),
            7855);
}

TEST(ElvisFilename, RejectsBoundsOutsideNamedTile) {
  EXPECT_EQ(elvis_filename_epsg("Oberon201311-PHO3-C0-AHD_7606234_55_0002_0002.laz",
                                {0.0, 100.0, 0.0, 100.0}),
            std::nullopt);
}

TEST(ElvisFilename, RejectsOtherNames) {
  EXPECT_EQ(elvis_filename_epsg("survey_7606234.laz", k_oberon_tile), std::nullopt);
  EXPECT_EQ(elvis_filename_epsg("Oberon201311-PHO3-C0-AHD_7606234_99_0002_0002.laz", k_oberon_tile),
            std::nullopt);
}

#ifndef USE_PDAL
// A real file with no CRS at all, named like its ELVIS source tile.
TEST(ElvisFilename, ReaderFallsBackToFileName) {
  const fs::path file =
      fs::path(BLAZE_TEST_DATA_DIR) / "Araluen201804-LID2-C3-AHD_7686048_55_0002_0002.laz";
  laspp::LASReader reader(file);
  EXPECT_EQ(reader_embedded_wkt(reader), "");
  OGRSpatialReference srs;
  ASSERT_EQ(srs.importFromWkt(reader_embedded_wkt(reader, file).c_str()), OGRERR_NONE);
  EXPECT_STREQ(srs.GetAuthorityCode(nullptr), "28355");
}
#endif
