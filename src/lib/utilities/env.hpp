#pragma once

#include <cstdlib>
#include <cstring>
#include <iostream>

#if defined(__linux__)
#include <dirent.h>
#include <unistd.h>
#endif

namespace blaze {

// Wrapper around std::getenv that silences MSVC's C4996 "getenv is unsafe" warning.
inline const char* get_env(const char* name) {
#ifdef _WIN32
#pragma warning(push)
#pragma warning(disable : 4996)
#endif
  const char* value = std::getenv(name);
#ifdef _WIN32
#pragma warning(pop)
#endif
  return value;
}

#if defined(__linux__)
inline bool linux_prime_on_demand_configured() {
  FILE* file = std::fopen("/etc/prime-discrete", "r");
  if (!file) {
    return false;
  }
  char mode[64] = {};
  const bool read = std::fgets(mode, static_cast<int>(sizeof(mode)), file) != nullptr;
  std::fclose(file);
  if (!read) {
    return false;
  }
  char* end = mode + std::strlen(mode);
  while (end > mode && (end[-1] == '\n' || end[-1] == '\r' || end[-1] == ' ')) {
    --end;
  }
  *end = '\0';
  return std::strcmp(mode, "on-demand") == 0;
}

inline bool linux_has_multiple_drm_render_nodes() {
  DIR* dir = opendir("/dev/dri");
  if (!dir) {
    return false;
  }
  int render_nodes = 0;
  while (const dirent* entry = readdir(dir)) {
    if (std::strncmp(entry->d_name, "renderD", 7) == 0) {
      ++render_nodes;
      if (render_nodes >= 2) {
        break;
      }
    }
  }
  closedir(dir);
  return render_nodes >= 2;
}

inline bool linux_should_enable_discrete_gpu_offload() {
  if (get_env("BLAZE_USE_IGPU")) {
    return false;
  }
  return get_env("BLAZE_USE_DGPU") || linux_prime_on_demand_configured();
}
#endif

// Route OpenGL rendering to the discrete GPU when the display is on integrated
// graphics (Linux PRIME / NVIDIA render offload). Must run before QApplication.
// Auto-enabled when /etc/prime-discrete is "on-demand" (Ubuntu nvidia-prime).
// Set BLAZE_USE_DGPU=1 to force on other distros; BLAZE_USE_IGPU=1 to opt out.
inline void enable_discrete_gpu_offload() {
#if defined(__linux__)
  if (!linux_should_enable_discrete_gpu_offload()) {
    return;
  }

  if (!get_env("__NV_PRIME_RENDER_OFFLOAD") && access("/dev/nvidia0", F_OK) == 0) {
    setenv("__NV_PRIME_RENDER_OFFLOAD", "1", 0);
    setenv("__GLX_VENDOR_LIBRARY_NAME", "nvidia", 0);
    setenv("__VK_LAYER_NV_optimus", "NVIDIA_only", 0);
    constexpr const char* k_nvidia_egl_vendor = "/usr/share/glvnd/egl_vendor.d/10_nvidia.json";
    if (access(k_nvidia_egl_vendor, F_OK) == 0) {
      setenv("__EGL_VENDOR_LIBRARY_FILENAMES", k_nvidia_egl_vendor, 0);
    }
    std::cerr << "Blaze3D: enabling NVIDIA PRIME render offload for OpenGL\n";
    return;
  }

  if (!get_env("DRI_PRIME") && linux_has_multiple_drm_render_nodes()) {
    setenv("DRI_PRIME", "1", 0);
    std::cerr << "Blaze3D: enabling Mesa PRIME render offload (DRI_PRIME=1) for OpenGL\n";
  }
#endif
}

}  // namespace blaze
