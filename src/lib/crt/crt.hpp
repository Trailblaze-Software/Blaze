#pragma once

#include <fstream>

#include "utilities/filesystem.hpp"
#include "utilities/timer.hpp"

inline void write_to_crt(const fs::path& filename) {
  TimeFunction timer("writing to CRT");

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
  crtFile << "304 304_Crossable_Watercourse\n";
  crtFile << "313 313_Prominent_Water_Feature\n";
  crtFile << "401 401_Open_Land\n";
  crtFile << "403 403_Rough_Open_Land\n";
  crtFile << "405 405_Forest\n";
  crtFile << "406 406_Vegetation:_Slow_Running\n";
  crtFile << "407 407_Vegetation:_Slow_Running,_Good_Visibility\n";
  crtFile << "408 408_Vegetation:_Walk\n";
  crtFile << "409 409_Vegetation:_Walk,_Good_Visibility\n";
  crtFile << "410 410_Vegetation:_Fight\n";
  crtFile << "419 419_Prominent_Vegetation_Feature\n";
  crtFile << "531 531_Prominent_Man-made_Feature-X\n";

  crtFile.close();
}
