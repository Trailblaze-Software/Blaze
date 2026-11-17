

# File proj\_data.hpp

[**File List**](files.md) **>** [**io**](dir_65bc51589f8002bfcb72faf47ab41180.md) **>** [**proj\_data.hpp**](proj__data_8hpp.md)

[Go to the documentation of this file](proj__data_8hpp.md)


```C++
#pragma once

#include <optional>
#include <string>
#include <vector>

#include "utilities/filesystem.hpp"

// PROJ needs proj.db for every EPSG lookup (parsing "EPSG:28355", converting a
// LAS file's GeoTIFF GeoKeys to WKT, ...). The macOS DMG ships Homebrew's
// libproj, whose compiled-in data dir doesn't exist on a clean Mac, so the
// packaging copies the data to <App>.app/Contents/Resources/proj and
// <prefix>/share/proj (scripts/macos-bundle-proj-data.sh) and the executables
// point PROJ at it here. See issue #36.

// If PROJ_DATA/PROJ_LIB are unset and a bundled proj.db exists next to
// `executable` (<exe>/../Resources/proj, or <exe>/../share/proj on macOS),
// prepend that directory to PROJ's search paths and return it. Call at startup
// before any PROJ use.
std::optional<fs::path> configure_bundled_proj_data(const fs::path& executable);
std::optional<fs::path> configure_bundled_proj_data();

std::vector<std::string> proj_search_paths();

// True if PROJ can resolve EPSG codes, i.e. it found a usable proj.db.
bool proj_database_available();
```


