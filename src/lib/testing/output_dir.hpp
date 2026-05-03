#pragma once

#include <gtest/gtest.h>

#include <algorithm>
#include <atomic>
#include <cstdint>
#include <filesystem>
#include <random>
#include <sstream>
#include <string>
#include <string_view>

#ifdef _WIN32
#include <process.h>
#define BLAZE_TEST_GETPID _getpid
#else
#include <unistd.h>
#define BLAZE_TEST_GETPID getpid
#endif

namespace blaze::test {

// Build a filesystem-safe version of `s` by replacing characters that are
// problematic in paths (slashes, colons, etc.) with underscores. This matters
// for parameterized test names like "E2E_New/E2ETerrainTest.ProcessTerrain/..."
// which contain '/'.
inline std::string sanitize_for_path(std::string_view s) {
  std::string out(s);
  for (char& c : out) {
    if (c == '/' || c == '\\' || c == ':' || c == ' ' || c == '<' || c == '>' || c == '|' ||
        c == '"' || c == '?' || c == '*') {
      c = '_';
    }
  }
  return out;
}

// Returns a path under the system temp directory that is unique for this test
// run. Uniqueness is ensured by combining:
//   - an optional caller-supplied label (for readability),
//   - the current gtest test suite + test name if running inside a gtest case,
//   - the process id (so concurrent `ctest -j` or CI shards don't collide),
//   - a process-local monotonic counter (so multiple dirs within one test
//     don't reuse the same name),
//   - a random suffix (belt-and-braces against exotic schedulers).
//
// The directory is NOT created; callers remain responsible for create/remove.
inline std::filesystem::path unique_test_output_dir(std::string_view label = {}) {
  const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();

  std::ostringstream oss;
  oss << "blaze_test";
  if (!label.empty()) {
    oss << "_" << sanitize_for_path(label);
  }
  if (info != nullptr) {
    oss << "_" << sanitize_for_path(info->test_suite_name()) << "."
        << sanitize_for_path(info->name());
  }
  oss << "_pid" << static_cast<unsigned long long>(BLAZE_TEST_GETPID());

  static std::atomic<std::uint64_t> counter{0};
  oss << "_" << counter.fetch_add(1, std::memory_order_relaxed);

  // Random suffix: seeded once per process from std::random_device so two
  // processes with the same PID reuse (e.g. after PID wrap) still diverge.
  static thread_local std::mt19937_64 rng{[] {
    std::random_device rd;
    return (static_cast<std::uint64_t>(rd()) << 32) | rd();
  }()};
  oss << "_" << std::hex << rng();

  return std::filesystem::temp_directory_path() / oss.str();
}

// Variant that appends `extension` (e.g. ".gpkg") to the unique path. Useful
// for tests that write a single file instead of a directory tree.
inline std::filesystem::path unique_test_output_path(std::string_view label,
                                                     std::string_view extension) {
  std::filesystem::path p = unique_test_output_dir(label);
  if (!extension.empty()) {
    p += std::string(extension);
  }
  return p;
}

}  // namespace blaze::test

#undef BLAZE_TEST_GETPID
