#pragma once

#include <vector>

#include "utilities/filesystem.hpp"

class Config;
class ProgressTracker;

void run_with_config(const Config& config, const std::vector<fs::path>& additional_las_files,
                     ProgressTracker&& tracker);
