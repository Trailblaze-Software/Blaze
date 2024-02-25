#pragma once

#include <fstream>
#include <iomanip>
#include <iostream>

#include "contour/contour.hpp"
#include "utilities/timer.hpp"

inline void writeContour(std::ofstream &file, const Contour &contour) {
  file << "0\nPOLYLINE\n";
  file << "8\n101_Contour\n";  // Layer 0 (default layer)
  file << "70\n0\n";   // open polyline (0->1 for closed)
  file << std::setprecision(10);
  for (size_t i = 0; i < contour.points().size(); i++) {
    file << "0\nVERTEX\n";
    file << "8\n101_Contour\n";  // Layer 0 (default layer)
    file << "10\n" << contour.points()[i].x() << "\n";
    file << "20\n" << contour.points()[i].y() << "\n";
  }
  file << "0\nSEQEND\n";
}

inline void write_to_dxf(std::vector<Contour> contours, const std::string &filename) {
  TimeFunction timer("writing to DXF");
  // Open the DXF file for writing
  std::ofstream dxfFile(filename);
  if (!dxfFile.is_open()) {
    std::cerr << "Failed to open DXF file for writing\n";
    return;
  }

  // Write the header section
  dxfFile << "0\nSECTION\n";
  dxfFile << "2\nHEADER\n";
  // Additional header data can be written here if needed
  dxfFile << "0\nENDSEC\n";

  // Write the entities section
  dxfFile << "0\nSECTION\n";
  dxfFile << "2\nENTITIES\n";

  for (const auto &contour : contours) {
    writeContour(dxfFile, contour);
  }

  dxfFile << "0\nENDSEC\n";

  // Write the footer section
  dxfFile << "0\nSECTION\n";
  dxfFile << "2\nEOF\n";
  dxfFile << "0\nENDSEC\n";

  // Close the DXF file
  dxfFile.close();
}

inline void write_to_crt(const std::string &filename) {
  TimeFunction timer("writing to CRT");

  std::ofstream crtFile(filename);
  if (!crtFile.is_open()) {
    std::cerr << "Failed to open CRT file for writing\n";
    return;
  }
  //ISOM 2017-2 and ISSprOM 2019-2 compliant :)
  //Fst column represents OOM symbol to create, second column is dxf layer name
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