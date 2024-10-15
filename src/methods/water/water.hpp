#include <queue>

#include "grid/grid.hpp"
#include "utilities/coordinate.hpp"
#include "utilities/timer.hpp"

struct PriorityPoint {
  double priority;
  Coordinate2D<size_t> coord;

  bool operator<(const PriorityPoint& other) const { return priority < other.priority; }
};

GeoGrid<double> fill_depressions(const GeoGrid<double>& grid) {
  TimeFunction timer("fill depressions");
  GeoGrid<double> result(grid.width(), grid.height(), GeoTransform(grid.transform()),
                         GeoProjection(grid.projection()));
  result.copy_from(grid);

  std::priority_queue<PriorityPoint> queue;
  GeoGrid<bool> filled(grid.width(), grid.height(), GeoTransform(grid.transform()),
                       GeoProjection(grid.projection()));
  filled.fill(false);

  for (size_t i = 0; i < grid.height() - 1; i++) {
    for (Coordinate2D<size_t> coord :
         {Coordinate2D<size_t>{0, i}, Coordinate2D<size_t>{grid.width() - 1, i + 1}}) {
      queue.push({-grid[coord], coord});
      filled[coord] = true;
    }
  }

  for (size_t j = 0; j < grid.width() - 1; j++) {
    for (Coordinate2D<size_t> coord :
         {Coordinate2D<size_t>{j, 0}, Coordinate2D<size_t>{j + 1, grid.height() - 1}}) {
      queue.push({-grid[coord], coord});
      filled[coord] = true;
    }
  }

  while (!queue.empty()) {
    PriorityPoint current = queue.top();
    queue.pop();

    for (Direction2D dir : ALL_DIRECTIONS) {
      Coordinate2D<size_t> neighbour = current.coord + dir;
      if (!filled.in_bounds(neighbour) || filled[neighbour]) {
        continue;
      }
      if (result[neighbour] <= result[current.coord]) {
        result[neighbour] = result[current.coord] + 1e-7;
      }
      queue.push({-grid[neighbour], neighbour});
      filled[neighbour] = true;
    }
  }

  for (size_t i = 0; i < grid.height(); i++) {
    for (size_t j = 0; j < grid.width(); j++) {
      Assert((filled[{j, i}]), "Not all cells were filled");
    }
  }
  return result;
}

#define SQ(x) ((x) * (x))

GeoGrid<double> catchment_size(const GeoGrid<double>& ground) {
  TimeFunction timer("catchment size");
  GeoGrid<double> filled = fill_depressions(ground);

  GeoGrid<double> result(ground.width(), ground.height(), GeoTransform(ground.transform()),
                         GeoProjection(ground.projection()));

  std::vector<std::pair<double, Coordinate2D<size_t>>> cells;
  for (size_t i = 0; i < filled.height(); i++) {
    for (size_t j = 0; j < filled.width(); j++) {
      cells.emplace_back(filled[{j, i}], Coordinate2D<size_t>{j, i});
      result[{j, i}] = 0;
    }
  }
  std::sort(cells.begin(), cells.end(),
            [](const auto& a, const auto& b) { return a.first > b.first; });

  for (const auto& [_, coord] : cells) {
    Coordinate2D<size_t> steepest_neighbour = coord;
    double steepest_slope = 0;
    for (Direction2D dir : ALL_DIRECTIONS) {
      Coordinate2D<size_t> neighbour = coord + dir;
      if (!ground.in_bounds(neighbour)) {
        continue;
      }
      double slope = (filled[coord] - filled[neighbour]) /
                     std::sqrt(SQ(dir.dx() * filled.dx()) + SQ(dir.dy() * filled.dy()));
      if (slope > steepest_slope) {
        steepest_slope = slope;
        steepest_neighbour = neighbour;
      }
    }
    if (steepest_slope > 0)
      result[steepest_neighbour] += result[coord] + std::abs(filled.dx() * filled.dy());
  }

  return result;
}

GeoGrid<bool> streams(const GeoGrid<double>& ground) {
  TimeFunction timer("streams");
  GeoGrid<double> catchment = catchment_size(ground);

  GeoGrid<bool> result(ground.width(), ground.height(), GeoTransform(ground.transform()),
                       GeoProjection(ground.projection()));

  for (size_t i = 0; i < ground.height(); i++) {
    for (size_t j = 0; j < ground.width(); j++) {
      result[{j, i}] = catchment[{j, i}] > 10000;
    }
  }

  return result;
}

std::vector<Coordinate2D<size_t>> stream_path(const GeoGrid<bool>& stream, GeoGrid<bool>& visited,
                                              const GeoGrid<double>& heights,
                                              const Coordinate2D<size_t>& start,
                                              std::queue<Coordinate2D<size_t>>& queue) {
  std::vector<Coordinate2D<size_t>> result;
  result.push_back(start);
  visited[start] = true;

  while (true) {
    Coordinate2D<size_t> last_point = result.back();
    std::vector<Coordinate2D<size_t>> unvisited_neighbours;
    for (Direction2D dir : ALL_DIRECTIONS) {
      Coordinate2D<size_t> neighbour = last_point + dir;
      if (stream.in_bounds(neighbour) && stream[neighbour] && !visited[neighbour] &&
          heights[neighbour] > heights[last_point]) {
        unvisited_neighbours.push_back(neighbour);
      }
    }
    if (unvisited_neighbours.size() == 0) {
      break;
    }
    result.push_back(unvisited_neighbours.back());
    visited[unvisited_neighbours.back()] = true;
    unvisited_neighbours.pop_back();
    for (const Coordinate2D<size_t>& neighbour : unvisited_neighbours) {
      queue.push(neighbour);
    }
  }

  return result;
}

std::vector<std::vector<Coordinate2D<double>>> stream_paths(const GeoGrid<double>& grid) {
  TimeFunction timer("stream paths");
  GeoGrid<bool> stream = streams(grid);
  GeoGrid<double> filled = fill_depressions(grid);

  std::vector<std::vector<Coordinate2D<size_t>>> result;
  GeoGrid<bool> visited(grid.width(), grid.height(), GeoTransform(grid.transform()),
                        GeoProjection(grid.projection()));
  visited.fill(false);

  std::vector<std::pair<double, Coordinate2D<size_t>>> stream_cells;
  for (size_t i = 0; i < grid.height(); i++) {
    for (size_t j = 0; j < grid.width(); j++) {
      if (stream[{j, i}]) {
        stream_cells.emplace_back(filled[{j, i}], Coordinate2D<size_t>{j, i});
      }
    }
  }

  std::sort(stream_cells.begin(), stream_cells.end(),
            [](const auto& a, const auto& b) { return a.first < b.first; });

  std::queue<Coordinate2D<size_t>> starting_points;

  for (size_t i = 0; i < stream_cells.size(); i++) {
    while (!starting_points.empty()) {
      if (visited[starting_points.front()]) {
        starting_points.pop();
        continue;
      }
      result.push_back(
          stream_path(stream, visited, filled, starting_points.front(), starting_points));
    }
    if (!visited[stream_cells[i].second]) {
      starting_points.push(stream_cells[i].second);
    }
  }

  std::vector<std::vector<Coordinate2D<double>>> projected_result;
  for (const std::vector<Coordinate2D<size_t>>& path : result) {
    std::vector<Coordinate2D<double>> projected_path;
    for (const Coordinate2D<size_t>& coord : path) {
      projected_path.push_back(grid.transform().pixel_to_projection(Coordinate2D<double>(0.5, 0.5) + coord));
    }
    projected_result.push_back(projected_path);
  }

  return projected_result;
}
