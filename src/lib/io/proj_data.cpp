#include "proj_data.hpp"

#include <cpl_string.h>
#include <ogr_spatialref.h>
#include <ogr_srs_api.h>

#include <system_error>

#include "utilities/env.hpp"
#include "utilities/resources.hpp"

std::optional<fs::path> configure_bundled_proj_data(const fs::path& executable) {
  if (blaze::get_env("PROJ_DATA") || blaze::get_env("PROJ_LIB")) return std::nullopt;

  const fs::path prefix = executable.parent_path().parent_path();
  // <App>.app/Contents/MacOS/<exe> -> <App>.app/Contents/Resources/proj
  std::vector<fs::path> candidates = {prefix / "Resources" / "proj"};
#ifdef __APPLE__
  // DMG's <prefix>/bin/blaze-cli -> <prefix>/share/proj. Not on Linux, where
  // /usr/share/proj belongs to the system PROJ.
  candidates.push_back(prefix / "share" / "proj");
#endif
  for (const fs::path& dir : candidates) {
    std::error_code ec;
    if (!fs::exists(dir / "proj.db", ec)) continue;
    CPLStringList paths;
    paths.AddString(dir.string().c_str());
    for (const std::string& existing : proj_search_paths()) paths.AddString(existing.c_str());
    OSRSetPROJSearchPaths(paths.List());
    return dir;
  }
  return std::nullopt;
}

std::optional<fs::path> configure_bundled_proj_data() {
  return configure_bundled_proj_data(get_executable_path());
}

std::vector<std::string> proj_search_paths() {
  std::vector<std::string> result;
  char** paths = OSRGetPROJSearchPaths();
  for (char** p = paths; p && *p; ++p) result.emplace_back(*p);
  CSLDestroy(paths);
  return result;
}

bool proj_database_available() {
  OGRSpatialReference srs;
  return srs.importFromEPSG(4326) == OGRERR_NONE;
}
