#include "crs_self_check.hpp"

#include <exception>
#include <string>

#include "io/crs.hpp"
#include "io/proj_data.hpp"
#include "las/las_file.hpp"

int run_crs_self_check(const std::vector<fs::path>& las_files, std::ostream& out) {
  bool ok = true;

  out << "PROJ search paths:\n";
  for (const std::string& path : proj_search_paths()) {
    std::error_code ec;
    const bool has_db = fs::exists(fs::path(path) / "proj.db", ec);
    out << "  " << path << (has_db ? "  (proj.db found)" : "") << "\n";
  }

  const bool db_ok = proj_database_available();
  out << "PROJ database: " << (db_ok ? "OK" : "NOT FOUND") << "\n";
  ok = ok && db_ok;

  const UserCrsParseResult parsed = try_user_crs_to_wkt("EPSG:28355");
  out << "Resolve 'EPSG:28355': " << (parsed.ok ? "OK" : "FAILED (" + parsed.error + ")") << "\n";
  ok = ok && parsed.ok;

  for (const fs::path& file : las_files) {
#ifndef USE_PDAL
    try {
      laspp::LASReader reader(file);
      const std::string wkt = reader_horizontal_wkt(reader);
      if (wkt.empty()) {
        out << "Embedded CRS of " << file.string() << ": FAILED (none could be read)\n";
        ok = false;
      } else {
        OGRSpatialReference srs;
        srs.importFromWkt(wkt.c_str());
        const char* name = srs.GetName();
        const char* code = srs.GetAuthorityCode(nullptr);
        out << "Embedded CRS of " << file.string() << ": OK (" << (name ? name : "unnamed")
            << (code ? std::string(", EPSG:") + code : std::string{}) << ")\n";
      }
    } catch (const std::exception& e) {
      out << "Embedded CRS of " << file.string() << ": FAILED (" << e.what() << ")\n";
      ok = false;
    }
#else
    out << "Embedded CRS of " << file.string() << ": SKIPPED (PDAL build)\n";
#endif
  }

  out << (ok ? "CRS check passed" : "CRS check FAILED") << std::endl;
  return ok ? 0 : 1;
}
