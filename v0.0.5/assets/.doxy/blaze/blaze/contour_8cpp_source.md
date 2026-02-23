

# File contour.cpp

[**File List**](files.md) **>** [**contour**](dir_168d7404e8aa1148a0abea8bd7ba0546.md) **>** [**contour.cpp**](contour_8cpp.md)

[Go to the documentation of this file](contour_8cpp.md)


```C++
#include "contour.hpp"

#include <string>

#include "polyline/polyline.hpp"
#include "utilities/coordinate.hpp"

Polyline Contour::to_polyline(const ContourConfigs& configs) const {
  Polyline polyline;
  polyline.layer = configs.layer_name_from_height(m_height);
  polyline.name = std::to_string(m_height);
  polyline.vertices = m_points;
  return polyline;
}

Contour Contour::from_polyline(const Polyline& polyline) {
  try {
    return Contour(std::stod(polyline.name), std::vector<Coordinate2D<double>>(polyline.vertices));
  } catch (std::invalid_argument&) {
    std::cerr << "Invalid contour name: \"" << polyline.name << "\", should be height."
              << std::endl;
    return Contour(0, std::vector<Coordinate2D<double>>());
  }
}
```


