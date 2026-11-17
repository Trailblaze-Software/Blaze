

# File polyline.hpp

[**File List**](files.md) **>** [**lib**](dir_c85d3e3c5052e9ad9ce18c6863244a25.md) **>** [**polyline**](dir_fb65ba27065765e3b5e423565f83186f.md) **>** [**polyline.hpp**](polyline_8hpp.md)

[Go to the documentation of this file](polyline_8hpp.md)


```C++
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
```


