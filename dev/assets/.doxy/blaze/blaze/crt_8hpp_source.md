

# File crt.hpp

[**File List**](files.md) **>** [**crt**](dir_c47672f86e16ff8bd68ad864d5061fa3.md) **>** [**crt.hpp**](crt_8hpp.md)

[Go to the documentation of this file](crt_8hpp.md)


```C++
#pragma once

#include <fstream>

#include "utilities/filesystem.hpp"
#include "utilities/progress_tracker.hpp"

inline void write_to_crt(const fs::path& filename, ProgressTracker&& progress_tracker) {
  START_TRACKER("writing CRT " + filename.filename().string());
  std::ofstream crtFile(filename);
  if (!crtFile.is_open()) {
    std::cerr << "Failed to open CRT file for writing\n";
    return;
  }
  // ISOM 2017-2 and ISSprOM 2019-2 compliant :)
  // First column represents OOM symbol to create, second column is layer name
  crtFile << "101 101_Contour\n";
  crtFile << "102 102_Index_Contour\n";
  crtFile << "103 103_Form_Line\n";
  crtFile << "109 109_Small_Knoll\n";
  crtFile << "111 111_Small_Depression\n";
  crtFile << "115 115_Prominent_Landform_Feature\n";
  crtFile << "201 201_Impassable_Cliff\n";
  crtFile << "202 202_Cliff\n";
  crtFile << "204 204_Boulder\n";
  crtFile << "205 205_Large_Boulder\n";
  crtFile << "206 206_Gigantic_Boulder_Or_Rock_Pillar\n";
  crtFile << "301 301_Uncrossable_Body_Of_Water\n";
  crtFile << "302 302_Shallow_Body_Of_Water\n";
  crtFile << "304 streams\n";
  crtFile << "313 313_Prominent_Water_Feature\n";
  crtFile << "401 401_Open_Land\n";
  crtFile << "403 403_Rough_Open_Land\n";
  crtFile << "405 405_Forest\n";
  // Layer names must match those written to GPKG (see config layer / vegetation.crt).
  crtFile << "406 406_Slow_Running\n";
  crtFile << "407 407_Vegetation:_Slow_Running,_Good_Visibility\n";
  crtFile << "408 408_Walk\n";
  crtFile << "409 409_Vegetation:_Walk,_Good_Visibility\n";
  crtFile << "410 410_Fight\n";
  crtFile << "419 419_Prominent_Vegetation_Feature\n";
  crtFile << "531 531_Prominent_Man-made_Feature-X\n";
  crtFile.close();
}

inline void write_vegetation_crt(const fs::path& filename, ProgressTracker&& progress_tracker) {
  START_TRACKER("writing vegetation CRT " + filename.filename().string());
  std::ofstream crtFile(filename);
  if (!crtFile.is_open()) {
    std::cerr << "Failed to open vegetation CRT file for writing\n";
    return;
  }
  // ISOM 2017-2 and ISSprOM 2019-2 vegetation symbols
  crtFile << "403 403_Rough_Open_Land\n";
  crtFile << "405 405_Forest\n";
  crtFile << "406 406_Slow_Running\n";
  crtFile << "408 408_Walk\n";
  crtFile << "410 410_Fight\n";
  crtFile.close();
}
```


