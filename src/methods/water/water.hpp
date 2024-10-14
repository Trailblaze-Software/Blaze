#include "grid/grid.hpp"
#include "utilities/timer.hpp"

#include <queue>

struct PriorityPoint {
  double priority;
  Coordinate2D<size_t> coord;

  bool operator<(const PriorityPoint &other) const { return priority < other.priority; }
};

GeoGrid<double> fill_depressions(const GeoGrid<double> &grid) {
  TimeFunction timer("fill depressions");
  GeoGrid<double> result(grid.width(), grid.height(), GeoTransform(grid.transform()),
                         GeoProjection(grid.projection()));
  result.copy_from(grid);

  std::priority_queue<PriorityPoint> queue;
  GeoGrid<bool> filled(grid.width(), grid.height(), GeoTransform(grid.transform()),
                       GeoProjection(grid.projection()));

  for(size_t i = 0; i < grid.height() - 1; i++) {
    queue.push({grid[{0, i}], {0, i}});
    queue.push({grid[{grid.width() - 1, i+1}], {grid.width() - 1, i+1}});
    filled[{0, i}] = true;
    filled[{grid.width() - 1, i+1}] = true;
  }

  for(size_t j = 0; j < grid.width() - 1; j++) {
    queue.push({grid[{j+1, 0}], {j+1, 0}});
    queue.push({grid[{j, grid.height() - 1}], {j, grid.height() - 1}});
    filled[{j+1, 0}] = true;
    filled[{j, grid.height() - 1}] = true;
  }

  while(!queue.empty()) {
    PriorityPoint current = queue.top();
    queue.pop();

    (void)current;
  }

  return result;
}
