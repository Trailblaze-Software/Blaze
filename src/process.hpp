#include <cmath>
#include <limits>
#include <stdexcept>

#include "config_input/config_input.hpp"
#include "las/las_file.hpp"

class ProgressTracker;

inline size_t num_cells_by_distance(double x, double dx) {
  if (dx == 0.0) {
    throw std::invalid_argument("num_cells_by_distance: cell size cannot be zero");
  }
  const double abs_x = std::abs(x);
  const double abs_dx = std::abs(dx);
  const double cells = abs_x / abs_dx;
  // Use a minimum epsilon to ensure we always round up by at least 1,
  // handling rounding errors and edge cases like 0.0
  constexpr double min_epsilon = 1e-6;
  const double relative_epsilon = std::numeric_limits<double>::epsilon() * cells;
  const double epsilon = std::max(min_epsilon, relative_epsilon);
  return static_cast<size_t>(std::ceil(cells + epsilon));
}

void process_las_file(const fs::path& las_file, const Config& config, ProgressTracker tracker);
void process_las_data(LASData& las_file, const fs::path& output_dir, const Config& config,
                      ProgressTracker tracker);
