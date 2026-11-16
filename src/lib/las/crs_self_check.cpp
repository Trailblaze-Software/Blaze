#include "crs_self_check.hpp"

#include <iostream>
#include <string>

#include "io/proj_data.hpp"
#include "las/las_file.hpp"

int run_crs_self_check(const std::vector<fs::path>& las_files) {
  for (const std::string& path : proj_search_paths())
    std::cout << "PROJ search path: " << path << "\n";
  bool ok = proj_database_available();
  std::cout << "PROJ database: " << (ok ? "OK" : "NOT FOUND") << "\n";
  for (const fs::path& file : las_files) {
    std::string wkt;
#ifndef USE_PDAL
    try {
      wkt = reader_horizontal_wkt(laspp::LASReader(file));
    } catch (const std::exception& e) {
      std::cout << e.what() << "\n";
    }
#endif
    std::cout << "Embedded CRS of " << file.string() << ": "
              << (wkt.empty() ? "NOT READABLE" : "OK") << "\n";
    ok = ok && !wkt.empty();
  }
  return ok ? 0 : 1;
}
