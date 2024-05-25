#pragma once

#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

#include "contour/contour.hpp"
#include "utilities/coordinate.hpp"
#include "utilities/filesystem.hpp"
#include "utilities/timer.hpp"

inline Coordinate2D<double> vertex_from_dxf(std::ifstream &dxfFile) {
  std::string line;
  double x, y;
  while (std::getline(dxfFile, line)) {
    if (line == "10") {
      dxfFile >> x;
    } else if (line == "20") {
      dxfFile >> y;
    } else if (line == "0") {
      return {x, y};
    } else if (line == "") {
      continue;
    } else if (line == "8") {
      std::getline(dxfFile, line);
    } else {
      std::cout << "Unknown entity: " << line << std::endl;
    }
  }
  return {0, 0};
}

class Polyline {
 public:
  std::string layer;
  std::string name;
  std::vector<Coordinate2D<double>> vertices;

  void write_to_dxf(std::ofstream &dxfFile) {
    bool is_loop = (vertices[0] - vertices.back()).magnitude_sqd() < 1e-10;

    dxfFile << "0\nPOLYLINE\n";
    dxfFile << "8\n" << layer << "\n";
    dxfFile << "2\n" << name << "\n";
    dxfFile << "70\n" << (is_loop ? 1 : 0) << "\n";
    dxfFile << std::setprecision(10);
    for (size_t i = 0; i < vertices.size(); i++) {
      dxfFile << "0\nVERTEX\n";
      dxfFile << "8\n" << layer << "\n";
      dxfFile << "10\n" << vertices[i].x() << "\n";
      dxfFile << "20\n" << vertices[i].y() << "\n";
    }
    dxfFile << "0\nSEQEND\n";
  }

  static Polyline read_from_dxf(std::ifstream &dxfFile) {
    std::string line;
    std::string name;
    std::string layer;
    std::vector<Coordinate2D<double>> vertices;
    while (std::getline(dxfFile, line)) {
      if (line == "8") {
        std::getline(dxfFile, layer);
      } else if (line == "2") {
        std::getline(dxfFile, name);
      } else if (line == "70") {
        std::getline(dxfFile, line);
        bool is_loop = std::stoi(line);
        (void)is_loop;
      } else if (line == "0") {
        continue;
      } else if (line == "VERTEX") {
        vertices.push_back(vertex_from_dxf(dxfFile));
      } else {
        AssertEQ(line, "SEQEND");
        break;
      }
    }
    return Polyline{.layer = layer, .name = name, .vertices = vertices};
  }
};

inline void write_to_dxf(std::vector<Contour> contours, const fs::path &filename,
                         const ContourConfigs &contour_configs) {
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
    if (contour.points().size() > 1) {
      contour.to_polyline(contour_configs).write_to_dxf(dxfFile);
    }
  }

  dxfFile << "0\nENDSEC\n";

  // Write the footer section
  dxfFile << "0\nSECTION\n";
  dxfFile << "2\nEOF\n";
  dxfFile << "0\nENDSEC\n";

  // Close the DXF file
  dxfFile.close();
}

inline std::vector<Contour> read_dxf(const fs::path &filename) {
  TimeFunction timer("reading DXF " + filename.string());
  std::vector<Contour> contours;

  std::ifstream dxfFile(filename);
  if (!dxfFile.is_open()) {
    std::cerr << "Failed to open DXF file for reading\n";
    return contours;
  }

  std::string line;
  while (std::getline(dxfFile, line)) {
    if (line == "0") {
      std::getline(dxfFile, line);
      if (line == "POLYLINE") {
        contours.emplace_back(Contour::from_polyline(Polyline::read_from_dxf(dxfFile)));
      }
    }
  }

  dxfFile.close();
  return contours;
}

inline void write_to_crt(const std::string &filename) {
  TimeFunction timer("writing to CRT");

  std::ofstream crtFile(filename);
  if (!crtFile.is_open()) {
    std::cerr << "Failed to open CRT file for writing\n";
    return;
  }
  // ISOM 2017-2 and ISSprOM 2019-2 compliant :)
  // First column represents OOM symbol to create, second column is dxf layer name
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
