#include <stdexcept>

#include "config_input/config_input.hpp"
#include "las/las_file.hpp"

class ProgressTracker;

// Thrown when ground.use_only_ground_class is set but a tile has no
// ground-classified points, e.g. unclassified or photogrammetric data (issue
// #35). The GUI offers to re-run with use_only_ground_class turned off.
struct NoGroundPointsError : std::runtime_error {
  using std::runtime_error::runtime_error;
};

void process_las_file(const fs::path& las_file, const Config& config,
                      ProgressTracker&& progress_tracker);
void process_las_data(LASData& las_file, const fs::path& output_dir, const Config& config,
                      ProgressTracker&& progress_tracker);
