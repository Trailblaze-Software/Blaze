#pragma once

#include <vector>

#include "config_input/config_input.hpp"
#include "utilities/filesystem.hpp"
#include "utilities/progress_tracker.hpp"

void run_with_config(const Config& config, const std::vector<fs::path>& additional_las_files,
                     ProgressTracker&& tracker);
