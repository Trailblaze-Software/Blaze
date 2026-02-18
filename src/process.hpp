#include <cmath>

#include "config_input/config_input.hpp"
#include "las/las_file.hpp"

class ProgressTracker;

inline size_t round_up(double x) { return std::ceil(1e-6 + std::abs(x)); }

void process_las_file(const fs::path& las_file, const Config& config, ProgressTracker tracker);
void process_las_data(LASData& las_file, const fs::path& output_dir, const Config& config,
                      ProgressTracker tracker);
