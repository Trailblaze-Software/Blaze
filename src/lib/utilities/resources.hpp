#pragma once

#include "utilities/filesystem.hpp"

class AssetRetriever {
 public:
  static fs::path get_asset(const fs::path& asset);
};
