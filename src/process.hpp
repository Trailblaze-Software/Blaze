#include "config_input/config_input.hpp"
#include "las/las_file.hpp"

class ProgressTracker;

void process_las_file(const fs::path& las_file, const Config& config, ProgressTracker tracker);
void process_las_data(LASData& las_file, const fs::path& output_dir, const Config& config,
                      ProgressTracker tracker);
