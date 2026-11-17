#pragma once

#include <vector>

#include "utilities/filesystem.hpp"

// --check-crs for blaze-cli and Blaze: print PROJ's search paths, whether
// proj.db is usable and whether each file's embedded CRS can be read. Returns
// 0 if all OK. Used by the macOS packaging CI (issue #36) and for bug reports.
int run_crs_self_check(const std::vector<fs::path>& las_files);
