#pragma once

#include <cstddef>
#include <cstdint>
#include <string>

namespace blaze::memory_tracker {

enum class Tag : uint8_t {
  LAS = 0,
  GRID = 1,
};

const char* tag_name(Tag tag);

void add_bytes(Tag tag, uint64_t bytes);
void remove_bytes(Tag tag, uint64_t bytes);

uint64_t total_bytes();
uint64_t tag_bytes(Tag tag);

// Compact, human-readable summary for progress displays.
// Example: "Mem: 1.8 GB (LAS 1.2 GB, Grids 512 MB)".
std::string format_summary();

}  // namespace blaze::memory_tracker
