#include "resources.hpp"

#include "assert/assert.hpp"

#ifdef __WIN32__
#include <winsock2.h>
// Don't reorder
#include <windows.h>
#endif
#ifdef __linux__
#include <linux/limits.h>
#include <unistd.h>
#endif

fs::path get_asset_dir() {
#ifdef __WIN32__
  char buffer[MAX_PATH];
  GetModuleFileNameA(NULL, buffer, MAX_PATH);
  fs::path path(buffer);
#endif
#ifdef __linux__
  char buffer[PATH_MAX];
  ssize_t len = readlink("/proc/self/exe", buffer, sizeof(buffer) - 1);
  if (len != -1) {
    buffer[len] = '\0';
  }
  fs::path path(buffer);
#endif
  Assert(fs::exists(path.parent_path() / "assets"), "Could not find asset directory");
  return path.parent_path() / "assets";
}

fs::path AssetRetriever::get_asset(const fs::path& asset) { return get_asset_dir() / asset; }
