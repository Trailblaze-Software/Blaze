#pragma once

#include <string>
#include <vector>

#include "utilities/coordinate.hpp"

class Polyline {
 public:
  std::string layer;
  std::string name;
  std::vector<Coordinate2D<double>> vertices;
};
