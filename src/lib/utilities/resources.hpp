#pragma once

#include "utilities/filesystem.hpp"

class AssetRetriever {
 public:
  static fs::path get_asset(const fs::path& asset);
};

class LocalDataRetriever {
 public:
  static fs::path get_local_data(const fs::path& asset);
};
