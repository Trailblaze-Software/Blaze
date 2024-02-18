#pragma once

#include <fstream>
#include <iomanip>
#include <iostream>

#include "contour/contour.hpp"
#include "utilities/timer.hpp"

inline void writeLine(std::ofstream &file, double x1, double y1, double x2, double y2) {
  file << "0\nLINE\n";
  file << "8\n0\n";  // Layer 0 (default layer)
  file << "10\n" << x1 << "\n";
  file << "20\n" << y1 << "\n";
  file << "11\n" << x2 << "\n";
  file << "21\n" << y2 << "\n";
}

// Function to write a circle to the DXF file
inline void writeCircle(std::ofstream &file, double cx, double cy, double radius) {
  file << "0\nCIRCLE\n";
  file << "8\n0\n";  // Layer 0 (default layer)
  file << "10\n" << cx << "\n";
  file << "20\n" << cy << "\n";
  file << "40\n" << radius << "\n";  // Radius of the circle
}

inline void writeContour(std::ofstream &file, const Contour &contour) {
  file << "0\nPOLYLINE\n";
  file << "8\n0\n";   // Layer 0 (default layer)
  file << "70\n0\n";  // open polyline (0->1 for closed)
  file << std::setprecision(10);
  for (size_t i = 0; i < contour.points().size(); i++) {
    file << "0\nVERTEX\n";
    file << "8\n0\n";  // Layer 0 (default layer)
    file << "10\n" << contour.points()[i].x() << "\n";
    file << "20\n" << contour.points()[i].y() << "\n";
  }
  file << "0\nSEQEND\n";
}

inline void write_to_dxf(const std::string &filename) {
  TimeFunction timer("writing to dxf");
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

  // Write some example entities (a line and a circle)
  writeLine(dxfFile, 0.0, 0.0, 10.0, 10.0);
  writeCircle(dxfFile, 20.0, 20.0, 5.0);

  // End the entities section
  dxfFile << "0\nENDSEC\n";

  // Write the footer section
  dxfFile << "0\nSECTION\n";
  dxfFile << "2\nEOF\n";
  dxfFile << "0\nENDSEC\n";

  // Close the DXF file
  dxfFile.close();
}

inline void write_to_dxf(std::vector<Contour> contours, const std::string &filename) {
  TimeFunction timer("writing to dxf");
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
