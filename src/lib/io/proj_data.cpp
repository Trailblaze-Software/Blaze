#include "proj_data.hpp"

#include <cpl_string.h>
#include <ogr_spatialref.h>
#include <ogr_srs_api.h>

#include <system_error>

#include "utilities/env.hpp"
#include "utilities/resources.hpp"

std::optional<fs::path> configure_bundled_proj_data(const fs::path& executable) {
  if (blaze::get_env("PROJ_DATA") || blaze::get_env("PROJ_LIB")) return std::nullopt;

  // <App>.app/Contents/MacOS/<exe> -> <App>.app/Contents/Resources/proj
  const fs::path dir = executable.parent_path().parent_path() / "Resources" / "proj";
  std::error_code ec;
  if (!fs::exists(dir / "proj.db", ec)) return std::nullopt;

  CPLStringList paths;
  paths.AddString(dir.string().c_str());
  for (const std::string& existing : proj_search_paths()) paths.AddString(existing.c_str());
  OSRSetPROJSearchPaths(paths.List());
  return dir;
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
