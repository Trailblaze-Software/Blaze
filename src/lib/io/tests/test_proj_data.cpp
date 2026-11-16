#include <gtest/gtest.h>

#include <fstream>
#include <sstream>
#include <string>
#include <thread>
#include <vector>

#include "io/crs.hpp"
#include "io/proj_data.hpp"
#include "las/crs_self_check.hpp"
#include "las/las_file.hpp"
#include "testing/output_dir.hpp"
#include "utilities/env.hpp"

namespace {

// LAS 1.2 file whose CRS (GDA94 / MGA zone 55) is stored only as GeoTIFF
// GeoKeys, like NSW Spatial Services downloads (issue #36).
const fs::path k_geokeys_fixture = fs::path(BLAZE_TEST_DATA_DIR) / "geokeys_only_gda94_mga55.laz";

// Points PROJ at the given search paths for the duration of a test, then
// restores whatever was configured before.
class ScopedProjSearchPaths {
 public:
  explicit ScopedProjSearchPaths(const std::vector<std::string>& paths)
      : m_saved(proj_search_paths()) {
    set(paths);
  }
  ~ScopedProjSearchPaths() { set(m_saved); }
  ScopedProjSearchPaths(const ScopedProjSearchPaths&) = delete;
  ScopedProjSearchPaths& operator=(const ScopedProjSearchPaths&) = delete;

  static void set(const std::vector<std::string>& paths) {
    std::vector<const char*> c_paths;
    for (const std::string& p : paths) c_paths.push_back(p.c_str());
    c_paths.push_back(nullptr);
    OSRSetPROJSearchPaths(c_paths.data());
  }

 private:
  std::vector<std::string> m_saved;
};

// GDAL keeps one PROJ context per thread and PROJ keeps proj.db open once a
// context has used it, so changing the search paths doesn't affect a thread
// that has already done a CRS lookup. Run `fn` on a new thread, which gets a
// fresh context built from the current search paths - like a freshly launched
// app.
template <typename Fn>
void run_on_fresh_thread(Fn fn) {
  std::thread t(fn);
  t.join();
}

fs::path find_proj_db() {
  for (const std::string& dir : proj_search_paths()) {
    if (fs::exists(fs::path(dir) / "proj.db")) return fs::path(dir) / "proj.db";
  }
  return {};
}

std::string epsg_of(const std::string& wkt) {
  OGRSpatialReference srs;
  if (srs.importFromWkt(wkt.c_str()) != OGRERR_NONE) return {};
  srs.AutoIdentifyEPSG();
  const char* code = srs.GetAuthorityCode(nullptr);
  return code ? code : "";
}

}  // namespace

// The LAS reading below uses blaze's own LAS reader (laspp); PDAL builds read
// LAS files differently, so those parts are skipped there.
#ifndef USE_PDAL
TEST(ProjData, GeoKeysOnlyLasHasEmbeddedCrs) {
  ASSERT_TRUE(fs::exists(k_geokeys_fixture)) << k_geokeys_fixture;
  laspp::LASReader reader(k_geokeys_fixture);
  EXPECT_FALSE(reader.wkt().has_value());
  ASSERT_TRUE(reader.geo_keys().has_value());
  const std::string wkt = reader_embedded_wkt(reader);
  ASSERT_FALSE(wkt.empty()) << "GeoKeys could not be converted - is proj.db reachable?";
  EXPECT_EQ(epsg_of(wkt), "28355");
}
#endif

TEST(ProjData, SelfCheckPassesWithProjData) {
  std::ostringstream out;
  EXPECT_EQ(run_crs_self_check({k_geokeys_fixture}, out), 0) << out.str();
}

// Reproduces issue #36: when PROJ can't find proj.db, GeoKey-only files look
// like they have no CRS and every override is rejected.
TEST(ProjData, MissingProjDbBreaksCrsLookups) {
  const fs::path empty_dir = blaze::test::unique_test_output_path("no_proj_data", "");
  fs::create_directories(empty_dir);
  ScopedProjSearchPaths scoped({empty_dir.string()});

  run_on_fresh_thread([&] {
    EXPECT_FALSE(proj_database_available());
    EXPECT_FALSE(try_user_crs_to_wkt("EPSG:28355").ok);
#ifndef USE_PDAL
    laspp::LASReader reader(k_geokeys_fixture);
    EXPECT_TRUE(reader_embedded_wkt(reader).empty());
#endif

    const UserCrsParseResult parsed = try_user_crs_to_wkt("EPSG:28355");
    EXPECT_NE(parsed.error.find("proj.db"), std::string::npos) << parsed.error;

    std::ostringstream out;
    EXPECT_EQ(run_crs_self_check({k_geokeys_fixture}, out), 1);
    EXPECT_NE(out.str().find("NOT FOUND"), std::string::npos) << out.str();
  });
}

TEST(ProjData, ConfigureFindsDataInsideAppBundle) {
  if (blaze::get_env("PROJ_DATA") || blaze::get_env("PROJ_LIB")) {
    GTEST_SKIP() << "PROJ_DATA/PROJ_LIB set; configure_bundled_proj_data defers to it";
  }
  const fs::path proj_db = find_proj_db();
  ASSERT_FALSE(proj_db.empty()) << "test host has no proj.db";

  // Fake <root>/Blaze.app/Contents/{MacOS/Blaze, Resources/proj/proj.db}.
  const fs::path root = blaze::test::unique_test_output_path("fake_bundle", "");
  const fs::path contents = root / "Blaze.app" / "Contents";
  fs::create_directories(contents / "MacOS");
  fs::create_directories(contents / "Resources" / "proj");
  fs::copy_file(proj_db, contents / "Resources" / "proj" / "proj.db",
                fs::copy_options::overwrite_existing);
  std::ofstream(contents / "MacOS" / "Blaze").put('\0');

  const fs::path empty_dir = root / "empty";
  fs::create_directories(empty_dir);
  ScopedProjSearchPaths scoped({empty_dir.string()});
  run_on_fresh_thread([] { EXPECT_FALSE(proj_database_available()); });

  const std::optional<fs::path> used = configure_bundled_proj_data(contents / "MacOS" / "Blaze");
  ASSERT_TRUE(used.has_value());
  EXPECT_EQ(*used, contents / "Resources" / "proj");
  run_on_fresh_thread([&] {
    EXPECT_TRUE(proj_database_available());
    EXPECT_TRUE(try_user_crs_to_wkt("EPSG:28355").ok);
#ifndef USE_PDAL
    laspp::LASReader reader(k_geokeys_fixture);
    EXPECT_EQ(epsg_of(reader_embedded_wkt(reader)), "28355");
#endif
  });
}

TEST(ProjData, ConfigureIsNoOpWithoutBundledData) {
  const fs::path root = blaze::test::unique_test_output_path("no_bundle", "");
  fs::create_directories(root / "bin");
  EXPECT_FALSE(configure_bundled_proj_data(root / "bin" / "blaze-cli").has_value());
}

TEST(ProjData, BareEpsgCodeIsAccepted) {
  const UserCrsParseResult bare = try_user_crs_to_wkt("28355");
  ASSERT_TRUE(bare.ok) << bare.error;
  EXPECT_EQ(epsg_of(bare.wkt), "28355");
  EXPECT_EQ(bare.wkt, try_user_crs_to_wkt("EPSG:28355").wkt);
}

TEST(ProjData, InvalidCrsGetsFormatHint) {
  const UserCrsParseResult parsed = try_user_crs_to_wkt("not a crs");
  EXPECT_FALSE(parsed.ok);
  EXPECT_NE(parsed.error.find("Expected an EPSG code"), std::string::npos) << parsed.error;
}
