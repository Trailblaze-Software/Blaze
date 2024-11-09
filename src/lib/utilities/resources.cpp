#include "resources.hpp"

#include "assert/assert.hpp"
#include "printing/to_string.hpp"

#if defined(__WIN32__) || defined(_WIN32)
#include <winsock2.h>
// Don't reorder
#include <KnownFolders.h>
#include <shlobj.h>
#include <windows.h>
#endif
#ifdef __linux__
#include <linux/limits.h>
#include <unistd.h>
#endif

fs::path get_asset_dir() {
#if defined(__WIN32__) || defined(_WIN32)
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
  std::vector<fs::path> asset_paths = {path.parent_path().parent_path() / "share" / "assets"};
  while (path.has_parent_path() && path.parent_path() != path) {
    path = path.parent_path();
    asset_paths.push_back(path / "assets");
  }
  for (fs::path asset_path : asset_paths) {
    if (fs::exists(asset_path)) {
      return asset_path;
    }
  }
  Fail("Could not find asset directory. Tried " + to_string(asset_paths));
}

fs::path AssetRetriever::get_asset(const fs::path& asset) { return get_asset_dir() / asset; }

fs::path get_local_data_dir() {
#if defined(__WIN32__) || defined(_WIN32)
  PWSTR path = nullptr;
  HRESULT hr = SHGetKnownFolderPath(FOLDERID_LocalAppData, 0, nullptr, &path);

  if (SUCCEEDED(hr)) {
    std::wstring ws(path);
    CoTaskMemFree(path);
    fs::path data_path = fs::path(std::string(ws.begin(), ws.end())) / "blaze";
    fs::create_directories(data_path);
    return data_path;
  }
  Fail("Could not get local windows data directory");
#endif
#ifdef __linux__
  const char* home_dir = getenv("HOME");
  if (home_dir == nullptr) {
    Fail("Could not get local linux data directory");
  }
  fs::path path = fs::path(home_dir) / ".local" / "share" / "blaze";
  fs::create_directories(path);
  return path;
#endif
}

fs::path LocalDataRetriever::get_local_data(const fs::path& asset) {
  return get_local_data_dir() / asset;
}
