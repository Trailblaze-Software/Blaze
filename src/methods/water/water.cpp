#include "water.hpp"

#include <queue>

#include "config_input/config_input.hpp"
#include "grid/grid.hpp"
#include "utilities/coordinate.hpp"
#include "utilities/timer.hpp"

struct PriorityPoint {
  double priority;
  Coordinate2D<size_t> coord;

  bool operator<(const PriorityPoint& other) const { return priority < other.priority; }
};

#define SQ(x) ((x) * (x))

std::optional<Coordinate2D<size_t>> flows_to(const GeoGrid<double>& grid,
                                             const Coordinate2D<size_t>& coord) {
  double slope = 0;
  Coordinate2D<size_t> min_neighbour = coord;
  for (Direction2D dir : ALL_DIRECTIONS) {
    Coordinate2D<size_t> neighbour = coord + dir;
    if (!grid.in_bounds(neighbour)) {
      continue;
    }
    double neighbour_slope = (grid[coord] - grid[neighbour]) /
                             std::sqrt(SQ(dir.dx() * grid.dx()) + SQ(dir.dy() * grid.dy()));
    if (neighbour_slope > slope) {
      slope = neighbour_slope;
      min_neighbour = neighbour;
    }
  }
  return slope == 0 ? std::nullopt : std::make_optional(min_neighbour);
}

GeoGrid<double> fill_depressions(const GeoGrid<double>& grid,
                                 const std::vector<Coordinate2D<size_t>>& sinks) {
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

  for (const Coordinate2D<size_t>& sink : sinks) {
    queue.push({-grid[sink], sink});
    filled[sink] = true;
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
std::vector<Coordinate2D<size_t>> identify_sinks(const GeoGrid<double>& grid, double depth,
                                                 double min_area) {
  TimeFunction timer("identify sinks");
  GeoGrid<double> filled = fill_depressions(grid);

  std::vector<Coordinate2D<size_t>> sinks;
  GeoGrid<bool> visited(grid.width(), grid.height(), GeoTransform(grid.transform()),
                        GeoProjection(grid.projection()));
  visited.fill(false);

  for (size_t i = 0; i < grid.height(); i++) {
    for (size_t j = 0; j < grid.width(); j++) {
      if (filled[{j, i}] >= grid[{j, i}] + depth) {
        double min_height = grid[{j, i}];
        Coordinate2D<size_t> sink = {j, i};
        double area = 0;
        std::queue<Coordinate2D<size_t>> queue;
        queue.push({j, i});
        visited[{j, i}] = true;
        while (!queue.empty()) {
          Coordinate2D<size_t> current = queue.front();
          queue.pop();
          area += std::abs(grid.dx() * grid.dy());
          if (grid[current] < min_height) {
            min_height = grid[current];
            sink = current;
          }
          for (Direction2D dir : ALL_DIRECTIONS) {
            Coordinate2D<size_t> neighbour = current + dir;
            if (!grid.in_bounds(neighbour) || visited[neighbour]) {
              continue;
            }
            if (filled[neighbour] >= grid[neighbour] + depth) {
              queue.push(neighbour);
              visited[neighbour] = true;
            }
          }
        }
        if (area > min_area) {
          sinks.push_back(sink);
        }
      }
    }
  }

  return sinks;
}
GeoGrid<double> catchment_size(const GeoGrid<double>& filled) {
  TimeFunction timer("catchment size");

  GeoGrid<double> result(filled.width(), filled.height(), GeoTransform(filled.transform()),
                         GeoProjection(filled.projection()));

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
    std::optional<Coordinate2D<size_t>> steepest_neighbour = flows_to(filled, coord);
    if (steepest_neighbour)
      result[*steepest_neighbour] += result[coord] + std::abs(filled.dx() * filled.dy());
  }

  return result;
}
GeoGrid<bool> streams(const GeoGrid<double>& filled_ground, const GeoGrid<double>& catchment,
                      double minimum_catchment) {
  TimeFunction timer("streams");

  GeoGrid<bool> result(filled_ground.width(), filled_ground.height(),
                       GeoTransform(filled_ground.transform()),
                       GeoProjection(filled_ground.projection()));

  for (size_t i = 0; i < filled_ground.height(); i++) {
    for (size_t j = 0; j < filled_ground.width(); j++) {
      result[{j, i}] = catchment[{j, i}] > 1000000 * minimum_catchment;
    }
  }

  return result;
}
std::vector<Coordinate2D<size_t>> stream_path(
    const GeoGrid<bool>& stream, GeoGrid<bool>& visited, const GeoGrid<double>& heights,
    std::vector<Coordinate2D<size_t>>&& start,
    std::queue<std::vector<Coordinate2D<size_t>>>& queue_of_starts) {
  for (const Coordinate2D<size_t>& coord : start) visited[coord] = true;

  while (true) {
    Coordinate2D<size_t> last_point = start.back();
    std::vector<Coordinate2D<size_t>> unvisited_neighbours;
    for (Direction2D dir : ALL_DIRECTIONS) {
      Coordinate2D<size_t> neighbour = last_point + dir;
      if (stream.in_bounds(neighbour) && stream[neighbour] && !visited[neighbour]) {
        std::optional<Coordinate2D<size_t>> flow = flows_to(heights, neighbour);
        if (flow && flow.value() == last_point) {
          unvisited_neighbours.push_back(neighbour);
        }
      }
    }
    if (unvisited_neighbours.size() == 0) {
      break;
    } else if (unvisited_neighbours.size() == 1) {
      start.push_back(unvisited_neighbours.back());
      visited[unvisited_neighbours.back()] = true;
    } else {
      for (const Coordinate2D<size_t>& neighbour : unvisited_neighbours) {
        queue_of_starts.push({last_point, neighbour});
      }
      break;
    }
  }
  return start;
}
std::vector<Coordinate2D<double>> smoothify(const std::vector<Coordinate2D<double>>& path) {
  std::vector<Coordinate2D<double>> result;
  for (size_t i = 0; i < path.size(); i++) {
    if (i == 0 || i == path.size() - 1) {
      result.push_back(path[i]);
    } else {
      Coordinate2D<double> sum = path[i - 1] + path[i] + path[i + 1];
      result.push_back({sum.x() / 3, sum.y() / 3});
    }
  }
  return result;
}
std::vector<Stream> stream_paths(const GeoGrid<double>& grid, const WaterConfigs& config,
                                 bool already_filled) {
  TimeFunction timer("stream paths");

  std::optional<GeoGrid<double>> local_filled;
  if (!already_filled) {
    std::vector<Coordinate2D<size_t>> sinks = identify_sinks(grid);
    local_filled.emplace(fill_depressions(grid, sinks));
  }
  const GeoGrid<double>& filled = local_filled ? *local_filled : grid;

  GeoGrid<double> catchment = catchment_size(filled);
  GeoGrid<bool> stream = streams(filled, catchment, config.minimum_catchment());

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

  std::queue<std::vector<Coordinate2D<size_t>>> starting_points;

  for (size_t i = 0; i < stream_cells.size(); i++) {
    while (!starting_points.empty()) {
      if (visited[starting_points.front().back()]) {
        starting_points.pop();
        continue;
      }
      std::vector<Coordinate2D<size_t>> cur_stream =
          stream_path(stream, visited, filled, std::move(starting_points.front()), starting_points);
      if (cur_stream.size() > 1) result.push_back(cur_stream);
      starting_points.pop();
    }
    if (!visited[stream_cells[i].second]) {
      starting_points.push({stream_cells[i].second});
    }
  }

  std::vector<Stream> projected_result;
  for (const std::vector<Coordinate2D<size_t>>& path : result) {
    std::vector<Coordinate2D<double>> projected_path;
    for (const Coordinate2D<size_t>& coord : path) {
      projected_path.push_back(
          grid.transform().pixel_to_projection(Coordinate2D<double>(0.5, 0.5) + coord));
    }
    projected_result.emplace_back(Stream{smoothify(projected_path), catchment[path.back()]});
  }

  return projected_result;
}
