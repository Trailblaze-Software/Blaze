#include "config_input/config_input.hpp"

class ProgressTracker;

void process_las_file(const fs::path& las_file, const Config& config, ProgressTracker tracker);
