

# File memory\_tracker.hpp

[**File List**](files.md) **>** [**lib**](dir_c85d3e3c5052e9ad9ce18c6863244a25.md) **>** [**utilities**](dir_f68f3bc40609949e989ead5b0b6dedfd.md) **>** [**memory\_tracker.hpp**](memory__tracker_8hpp.md)

[Go to the documentation of this file](memory__tracker_8hpp.md)


```C++
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
```


