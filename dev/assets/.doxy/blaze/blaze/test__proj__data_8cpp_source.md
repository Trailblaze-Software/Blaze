

# File test\_proj\_data.cpp

[**File List**](files.md) **>** [**io**](dir_65bc51589f8002bfcb72faf47ab41180.md) **>** [**tests**](dir_48b62e9add78df78566b95ab9cc595a8.md) **>** [**test\_proj\_data.cpp**](test__proj__data_8cpp.md)

[Go to the documentation of this file](test__proj__data_8cpp.md)


```C++
#include <gtest/gtest.h>

#include <string>
#include <thread>
#include <vector>

#include "io/crs.hpp"
#include "io/proj_data.hpp"
#include "las/las_file.hpp"
#include "testing/output_dir.hpp"
#include "utilities/env.hpp"

#ifndef USE_PDAL
namespace {

// LAS 1.2 file whose CRS (EPSG:28355) is stored only as GeoTIFF GeoKeys, like
// NSW Spatial Services downloads (issue #36). Reading it needs proj.db.
const fs::path k_fixture = fs::path(BLAZE_TEST_DATA_DIR) / "geokeys_only_gda94_mga55.laz";

std::string fixture_epsg() {
  laspp::LASReader reader(k_fixture);
  OGRSpatialReference srs;
  if (srs.importFromWkt(reader_embedded_wkt(reader).c_str()) != OGRERR_NONE) return {};
  srs.AutoIdentifyEPSG();
  const char* code = srs.GetAuthorityCode(nullptr);
  return code ? code : "";
}

void set_search_paths(const std::vector<std::string>& paths) {
  std::vector<const char*> c_paths;
  for (const std::string& p : paths) c_paths.push_back(p.c_str());
  c_paths.push_back(nullptr);
  OSRSetPROJSearchPaths(c_paths.data());
}

// Points PROJ at an empty directory (as on a clean Mac) for the test's scope.
struct NoProjData {
  std::vector<std::string> saved = proj_search_paths();
  fs::path empty = blaze::test::unique_test_output_path("no_proj_data", "");
  NoProjData() {
    fs::create_directories(empty);
    set_search_paths({empty.string()});
  }
  ~NoProjData() { set_search_paths(saved); }
};

// GDAL keeps a PROJ context per thread, and a context that has already opened
// proj.db keeps it open, so search path changes only show on a new thread.
template <typename Fn>
void on_fresh_thread(Fn fn) {
  std::thread(fn).join();
}

}  // namespace

TEST(ProjData, GeoKeysOnlyLasHasEmbeddedCrs) { EXPECT_EQ(fixture_epsg(), "28355"); }

TEST(ProjData, MissingProjDbHidesEmbeddedCrs) {
  NoProjData no_data;
  on_fresh_thread([] {
    EXPECT_FALSE(proj_database_available());
    EXPECT_EQ(fixture_epsg(), "");
    const UserCrsParseResult parsed = try_user_crs_to_wkt("EPSG:28355");
    EXPECT_NE(parsed.error.find("proj.db"), std::string::npos) << parsed.error;
  });
}

TEST(ProjData, ConfigureUsesDataInsideAppBundle) {
  if (blaze::get_env("PROJ_DATA") || blaze::get_env("PROJ_LIB")) GTEST_SKIP();
  fs::path proj_db;
  for (const std::string& dir : proj_search_paths()) {
    if (fs::exists(fs::path(dir) / "proj.db")) proj_db = fs::path(dir) / "proj.db";
  }
  ASSERT_FALSE(proj_db.empty()) << "test host has no proj.db";

  const fs::path contents = blaze::test::unique_test_output_path("bundle", "") / "Contents";
  fs::create_directories(contents / "MacOS");
  fs::create_directories(contents / "Resources" / "proj");
  fs::copy_file(proj_db, contents / "Resources" / "proj" / "proj.db");
  const fs::path exe = contents / "MacOS" / "Blaze";

  NoProjData no_data;
  ASSERT_EQ(configure_bundled_proj_data(exe), contents / "Resources" / "proj");
  on_fresh_thread([] { EXPECT_EQ(fixture_epsg(), "28355"); });
}
#endif

TEST(ProjData, BareEpsgCodeIsAccepted) {
  const UserCrsParseResult bare = try_user_crs_to_wkt("28355");
  ASSERT_TRUE(bare.ok) << bare.error;
  EXPECT_EQ(bare.wkt, try_user_crs_to_wkt("EPSG:28355").wkt);
  EXPECT_NE(try_user_crs_to_wkt("not a crs").error.find("Expected an EPSG code"),
            std::string::npos);
}
```


