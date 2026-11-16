#include "proj_data.hpp"

#include <cpl_string.h>
#include <ogr_spatialref.h>
#include <ogr_srs_api.h>

#include <string>
#include <system_error>

#include "utilities/env.hpp"
#include "utilities/resources.hpp"

std::vector<fs::path> bundled_proj_data_candidates(const fs::path& executable) {
  const fs::path exe_dir = executable.parent_path();
  // Inside a macOS .app: <App>.app/Contents/MacOS/<exe> -> Contents/Resources/proj.
  // Lives inside the bundle, so it survives Gatekeeper App Translocation. Not
  // gated on __APPLE__ so the lookup is unit-tested on every platform; the
  // directory simply never exists elsewhere.
  std::vector<fs::path> candidates = {exe_dir.parent_path() / "Resources" / "proj"};
#ifdef __APPLE__
  // blaze-cli in the DMG/install tree: <prefix>/bin/blaze-cli -> <prefix>/share/proj.
  // Apple-only: on Linux this would be e.g. /usr/share/proj, which belongs to
  // the system PROJ and must not be preferred over its own defaults.
  candidates.push_back(exe_dir.parent_path() / "share" / "proj");
#endif
  return candidates;
}

std::optional<fs::path> configure_bundled_proj_data(const fs::path& executable) {
  // An explicit user/environment setting always wins.
  if (blaze::get_env("PROJ_DATA") || blaze::get_env("PROJ_LIB")) return std::nullopt;

  for (const fs::path& candidate : bundled_proj_data_candidates(executable)) {
    std::error_code ec;
    if (!fs::exists(candidate / "proj.db", ec)) continue;

    const std::string dir = candidate.string();
    CPLStringList paths;
    paths.AddString(dir.c_str());
    // Keep PROJ's existing search paths (user-writable grid dir, etc.) after ours.
    for (const std::string& existing : proj_search_paths()) {
      if (existing != dir) paths.AddString(existing.c_str());
    }
    OSRSetPROJSearchPaths(paths.List());
    return candidate;
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
