

# File blaze\_output\_loader.hpp

[**File List**](files.md) **>** [**gui**](dir_99d0482cf009f9d97a0877749b817f19.md) **>** [**blaze\_output\_loader.hpp**](blaze__output__loader_8hpp.md)

[Go to the documentation of this file](blaze__output__loader_8hpp.md)


```C++
#pragma once

#include <algorithm>
#include <functional>
#include <memory>
#include <optional>
#include <set>
#include <sstream>
#include <string>
#include <vector>

#include "gui/layer.hpp"
#include "utilities/filesystem.hpp"
#include "utilities/progress_tracker.hpp"

struct BlazeOutputSet {
  fs::path root;
  std::optional<fs::path> filled_dem;
  std::optional<fs::path> smooth_ground;
  std::optional<fs::path> ground;
  std::optional<fs::path> slope;
  std::optional<fs::path> fine_slope;
  std::optional<fs::path> final_img;
  std::optional<fs::path> contours;
  std::optional<fs::path> streams;
};

struct BlazeOutputDiscovery {
  BlazeOutputSet outputs;
  std::vector<fs::path> search_roots;
  std::vector<fs::path> locations_with_outputs;
};

namespace detail {

inline bool is_blaze_output_filename(const std::string& name) {
  static const std::vector<std::string> KNOWN{
      "filled_dem.tif", "smooth_ground.tif",     "ground.tif",
      "slope.tif",      "fine_slope.tif",        "final_img.tif",
      "contours.gpkg",  "trimmed_contours.gpkg", "streams.gpkg"};
  return std::find(KNOWN.begin(), KNOWN.end(), name) != KNOWN.end();
}

inline void collect_search_roots(const fs::path& directory, std::vector<fs::path>& roots) {
  auto add_root = [&](const fs::path& candidate) {
    if (!fs::is_directory(candidate)) {
      return;
    }
    if (std::find(roots.begin(), roots.end(), candidate) == roots.end()) {
      roots.push_back(candidate);
    }
  };

  add_root(directory);
  add_root(directory / "combined");

  if (!fs::is_directory(directory)) {
    return;
  }

  std::error_code ec;
  for (const fs::directory_entry& entry : fs::directory_iterator(directory, ec)) {
    if (ec || !entry.is_directory()) {
      continue;
    }
    const fs::path subdir = entry.path();
    add_root(subdir);
    add_root(subdir / "combined");
  }
}

inline std::optional<fs::path> find_in_root(const fs::path& root,
                                            const std::vector<std::string>& names) {
  for (const std::string& name : names) {
    const fs::path candidate = root / name;
    if (fs::exists(candidate)) {
      return candidate;
    }
  }
  return std::nullopt;
}

inline int blaze_output_score(const BlazeOutputSet& outputs) {
  int score = 0;
  if (outputs.filled_dem) {
    score += 4;
  }
  if (outputs.contours) {
    score += 3;
  }
  if (outputs.final_img) {
    score += 2;
  }
  if (outputs.slope) {
    score += 1;
  }
  return score;
}

inline BlazeOutputSet discover_in_root(const fs::path& root) {
  BlazeOutputSet outputs;
  outputs.root = root;

  outputs.filled_dem = find_in_root(root, {"filled_dem.tif"});
  outputs.smooth_ground = find_in_root(root, {"smooth_ground.tif"});
  outputs.ground = find_in_root(root, {"ground.tif"});
  if (!outputs.filled_dem) {
    outputs.filled_dem = outputs.smooth_ground;
  }
  if (!outputs.filled_dem) {
    outputs.filled_dem = outputs.ground;
  }
  outputs.slope = find_in_root(root, {"slope.tif"});
  outputs.fine_slope = find_in_root(root, {"fine_slope.tif"});
  outputs.final_img = find_in_root(root, {"final_img.tif"});
  outputs.contours = find_in_root(root, {"contours.gpkg", "trimmed_contours.gpkg"});
  outputs.streams = find_in_root(root, {"streams.gpkg"});

  return outputs;
}

inline bool has_importable_outputs(const BlazeOutputSet& outputs) {
  return outputs.filled_dem.has_value() || outputs.contours.has_value();
}

inline bool is_combined_root(const fs::path& root) { return root.filename() == "combined"; }

inline void collect_locations_with_outputs(const fs::path& directory,
                                           std::vector<fs::path>& locations) {
  if (!fs::is_directory(directory)) {
    return;
  }

  auto note_if_outputs = [&](const fs::path& root) {
    if (!fs::is_directory(root)) {
      return;
    }
    const BlazeOutputSet candidate = discover_in_root(root);
    if (has_importable_outputs(candidate) &&
        std::find(locations.begin(), locations.end(), root) == locations.end()) {
      locations.push_back(root);
    }
  };

  note_if_outputs(directory);

  std::error_code ec;
  for (const fs::directory_entry& entry : fs::directory_iterator(directory, ec)) {
    if (ec) {
      continue;
    }
    if (entry.is_directory()) {
      note_if_outputs(entry.path());
      note_if_outputs(entry.path() / "combined");
      continue;
    }
    if (entry.is_regular_file() && is_blaze_output_filename(entry.path().filename().string())) {
      if (std::find(locations.begin(), locations.end(), directory) == locations.end()) {
        locations.push_back(directory);
      }
    }
  }
}

}  // namespace detail

inline BlazeOutputDiscovery discover_blaze_output_with_info(const fs::path& directory) {
  BlazeOutputDiscovery discovery;
  detail::collect_search_roots(directory, discovery.search_roots);
  detail::collect_locations_with_outputs(directory, discovery.locations_with_outputs);

  std::vector<BlazeOutputSet> candidates;
  candidates.reserve(discovery.search_roots.size());
  for (const fs::path& root : discovery.search_roots) {
    BlazeOutputSet candidate = detail::discover_in_root(root);
    if (detail::has_importable_outputs(candidate)) {
      candidates.push_back(std::move(candidate));
    }
  }

  const auto pick_best = [](const std::vector<BlazeOutputSet>& options) -> const BlazeOutputSet* {
    const BlazeOutputSet* best = nullptr;
    int best_score = -1;
    for (const BlazeOutputSet& candidate : options) {
      const int score = detail::blaze_output_score(candidate);
      if (score > best_score) {
        best_score = score;
        best = &candidate;
      }
    }
    return best;
  };

  std::vector<BlazeOutputSet> combined_candidates;
  combined_candidates.reserve(candidates.size());
  for (const BlazeOutputSet& candidate : candidates) {
    if (detail::is_combined_root(candidate.root)) {
      combined_candidates.push_back(candidate);
    }
  }

  if (const BlazeOutputSet* best = pick_best(combined_candidates)) {
    discovery.outputs = *best;
    return discovery;
  }

  std::vector<BlazeOutputSet> direct_candidates;
  direct_candidates.reserve(candidates.size());
  for (const BlazeOutputSet& candidate : candidates) {
    if (candidate.root == directory) {
      direct_candidates.push_back(candidate);
    }
  }
  if (const BlazeOutputSet* best = pick_best(direct_candidates)) {
    discovery.outputs = *best;
    return discovery;
  }

  std::vector<BlazeOutputSet> tile_candidates;
  tile_candidates.reserve(candidates.size());
  for (const BlazeOutputSet& candidate : candidates) {
    if (candidate.root.parent_path() == directory && !detail::is_combined_root(candidate.root)) {
      tile_candidates.push_back(candidate);
    }
  }
  if (tile_candidates.size() == 1) {
    discovery.outputs = tile_candidates.front();
    return discovery;
  }
  if (tile_candidates.size() > 1) {
    discovery.locations_with_outputs.clear();
    for (const BlazeOutputSet& candidate : tile_candidates) {
      discovery.locations_with_outputs.push_back(candidate.root);
    }
    discovery.outputs.root = directory;
    return discovery;
  }

  if (const BlazeOutputSet* best = pick_best(candidates)) {
    discovery.outputs = *best;
  } else {
    discovery.outputs.root = directory;
  }
  return discovery;
}

inline BlazeOutputSet discover_blaze_output(const fs::path& directory) {
  return discover_blaze_output_with_info(directory).outputs;
}

inline std::string format_blaze_output_discovery_error(const fs::path& directory,
                                                       const BlazeOutputDiscovery& discovery) {
  std::ostringstream message;
  message << "Could not find blaze outputs in:\n"
          << directory.string() << "\n\nExpected at least one of:\n"
          << "  filled_dem.tif (or smooth_ground.tif / ground.tif)\n"
          << "  contours.gpkg (or trimmed_contours.gpkg)\n"
          << "in the selected folder, a combined/ subfolder, or a tile subfolder.\n";

  if (!discovery.locations_with_outputs.empty()) {
    message << "\nFound partial outputs in:\n";
    for (const fs::path& location : discovery.locations_with_outputs) {
      message << "  " << location.string() << "\n";
    }
    if (discovery.locations_with_outputs.size() > 1 &&
        !detail::has_importable_outputs(discovery.outputs)) {
      message << "\nMultiple tile folders contain blaze outputs. Run the Combine step in Blaze, "
                 "or select one tile folder to import.";
    }
  } else if (fs::is_directory(directory)) {
    message << "\nNo blaze output files were found under this folder.";
    std::vector<std::string> child_dirs;
    std::error_code ec;
    for (const fs::directory_entry& entry : fs::directory_iterator(directory, ec)) {
      if (!ec && entry.is_directory()) {
        child_dirs.push_back(entry.path().filename().string());
      }
    }
    if (!child_dirs.empty()) {
      message << " Subfolders present: ";
      for (size_t i = 0; i < child_dirs.size(); ++i) {
        if (i > 0) {
          message << ", ";
        }
        message << child_dirs[i];
        if (i >= 9 && child_dirs.size() > 10) {
          message << ", ... (" << child_dirs.size() << " total)";
          break;
        }
      }
      message << ".";
    }
  } else {
    message << "\nThe selected path is not a directory.";
  }

  return message.str();
}

inline void append_flat_grid_dem_layers(
    std::vector<std::unique_ptr<Layer>>& layers, const BlazeOutputSet& outputs,
    const std::function<AsyncProgressTracker()>& progress_factory, const std::string& target_crs) {
  std::set<std::string> seen_paths;
  auto append = [&](const std::optional<fs::path>& dem_path) {
    if (!dem_path) {
      return;
    }
    const std::string key = dem_path->lexically_normal().string();
    if (!seen_paths.insert(key).second) {
      return;
    }
    auto layer =
        std::make_unique<DemLayer>(*dem_path, progress_factory(), std::nullopt, target_crs, true);
    layer->set_visible(false);
    layers.push_back(std::move(layer));
  };
  append(outputs.ground);
  append(outputs.smooth_ground);
  append(outputs.filled_dem);
}

// Single source of truth for viewer layers built from discovered blaze outputs.
// GUI import and any other callers should use this instead of duplicating layer setup.
inline std::vector<std::unique_ptr<Layer>> load_blaze_outputs(
    const BlazeOutputSet& outputs, const std::function<AsyncProgressTracker()>& progress_factory,
    const std::function<std::string()>& reference_crs_factory = [] { return std::string{}; }) {
  std::vector<std::unique_ptr<Layer>> layers;
  const std::string target_crs = reference_crs_factory();

  if (outputs.filled_dem) {
    if (outputs.final_img) {
      layers.push_back(std::make_unique<TexturedDemLayer>(*outputs.filled_dem, *outputs.final_img,
                                                          progress_factory(), target_crs));
    } else {
      layers.push_back(std::make_unique<DemLayer>(*outputs.filled_dem, progress_factory(),
                                                  std::nullopt, target_crs));
    }

    if (outputs.slope) {
      const fs::path& slope_dem =
          outputs.smooth_ground ? *outputs.smooth_ground : *outputs.filled_dem;
      auto slope_layer =
          std::make_unique<SlopeLayer>(slope_dem, *outputs.slope, progress_factory(), target_crs);
      if (outputs.final_img) {
        slope_layer->set_visible(false);
      }
      layers.push_back(std::move(slope_layer));
    }
  }

  if (outputs.fine_slope) {
    const fs::path ground_dem =
        outputs.ground ? *outputs.ground : outputs.fine_slope->parent_path() / "ground.tif";
    if (fs::exists(ground_dem)) {
      auto fine_slope_layer = std::make_unique<SlopeLayer>(ground_dem, *outputs.fine_slope,
                                                           progress_factory(), target_crs);
      if (outputs.final_img) {
        fine_slope_layer->set_visible(false);
      }
      layers.push_back(std::move(fine_slope_layer));
    }
  }

  append_flat_grid_dem_layers(layers, outputs, progress_factory, target_crs);

  if (outputs.contours) {
    layers.push_back(
        std::make_unique<ContourLayer>(*outputs.contours, progress_factory(), target_crs));
  }

  return layers;
}
```


