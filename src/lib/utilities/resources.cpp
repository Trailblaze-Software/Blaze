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
#ifdef __APPLE__
#include <mach-o/dyld.h>
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
#ifdef __APPLE__
  char stack_buffer[4096];
  uint32_t size = sizeof(stack_buffer);
  std::vector<char> heap_buffer;
  char* buf_ptr = stack_buffer;
  if (_NSGetExecutablePath(buf_ptr, &size) != 0) {
    heap_buffer.resize(size);
    buf_ptr = heap_buffer.data();
    if (_NSGetExecutablePath(buf_ptr, &size) != 0) {
      Fail("Could not get executable path on macOS");
    }
  }
  fs::path path(buf_ptr);
#endif
#ifdef __linux__
  char buffer[PATH_MAX];
  ssize_t len = readlink("/proc/self/exe", buffer, sizeof(buffer) - 1);
  if (len != -1) {
    buffer[len] = '\0';
  }
  fs::path path(buffer);
#endif
  // First candidate, "<exe>/../../share/assets": on Linux/Windows the installed
  // <prefix>/share/assets; on a macOS .app it resolves to
  // MyApp.app/Contents/share/assets. The macOS packaging deliberately copies the
  // assets THERE (scripts/macos-bundle-assets.sh) so the app is self-contained:
  // a downloaded app runs under Gatekeeper App Translocation from a random temp
  // dir with NO sibling share/, and only this in-bundle path survives. Do not
  // remove it as "dead Linux code" — it is what keeps the GUI from aborting at
  // launch on a clean Mac.
  std::vector<fs::path> asset_paths = {path.parent_path().parent_path() / "share" / "assets"};
#ifdef __APPLE__
  // Fallback for a non-translocated launch straight from the DMG/install tree:
  // assets sitting next to the bundle at <prefix>/share/assets, four directory
  // levels above the executable (MyApp.app/Contents/MacOS/<exe>).
  asset_paths.push_back(path.parent_path().parent_path().parent_path().parent_path() / "share" /
                        "assets");
#endif
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
#ifdef __APPLE__
  const char* home_dir = getenv("HOME");
  if (home_dir == nullptr) {
    Fail("Could not get local macOS data directory");
  }
  fs::path path = fs::path(home_dir) / "Library" / "Application Support" / "blaze";
  fs::create_directories(path);
  return path;
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
  Fail("Unsupported platform for get_local_data_dir");
}

fs::path LocalDataRetriever::get_local_data(const fs::path& asset) {
  return get_local_data_dir() / asset;
}
