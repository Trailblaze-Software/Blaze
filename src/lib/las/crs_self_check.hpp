#pragma once

#include <ostream>
#include <vector>

#include "utilities/filesystem.hpp"

// Diagnostic behind the `--check-crs` flag of blaze-cli and Blaze. Reports
// PROJ's search paths, checks that an EPSG code can be resolved, and that each
// given LAS/LAZ file's embedded CRS (WKT or GeoTIFF GeoKeys) can be read.
// Returns 0 if everything resolved, 1 otherwise. Used by the macOS packaging
// CI to prove the bundled app can find PROJ's data on a machine without
// Homebrew (issue #36), and handy for users to paste into bug reports.
int run_crs_self_check(const std::vector<fs::path>& las_files, std::ostream& out);
