#pragma once

#include <optional>
#include <vector>

#include "utilities/filesystem.hpp"

// PROJ's database (proj.db) is required for every EPSG lookup: parsing
// "EPSG:28355", turning a LAS file's GeoTIFF GeoKeys into WKT, identifying a
// WKT's EPSG code, etc. Without it those calls fail silently and blaze reports
// misleading errors like "LAS file ... has no embedded CRS" (issue #36).
//
// Windows and Linux builds find proj.db on their own (PROJ looks in
// ../share/proj relative to its DLL on Windows; Linux uses the system
// package). The macOS .app bundles libproj from Homebrew, whose compiled-in
// data path (/opt/homebrew/share/proj) does not exist on a clean Mac, so the
// packaging copies the data into the bundle and we point PROJ at it here.

// Directories, relative to `executable`, where a packaged build ships PROJ's
// data files. Ordered by preference.
std::vector<fs::path> bundled_proj_data_candidates(const fs::path& executable);

// If neither PROJ_DATA nor PROJ_LIB is set and one of the candidates for
// `executable` contains proj.db, prepend it to PROJ's search paths. Returns the
// directory that was added, or nullopt if nothing was changed. Call once at
// startup, before any OGR/PROJ use and before spawning worker threads.
std::optional<fs::path> configure_bundled_proj_data(const fs::path& executable);

// As above, for the currently running executable.
std::optional<fs::path> configure_bundled_proj_data();

// The directories PROJ currently searches for its data files.
std::vector<std::string> proj_search_paths();

// True if PROJ can resolve EPSG codes, i.e. it found a usable proj.db.
bool proj_database_available();
