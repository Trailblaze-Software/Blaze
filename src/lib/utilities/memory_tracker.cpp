#include "utilities/memory_tracker.hpp"

#include <algorithm>
#include <array>
#include <atomic>
#include <sstream>

#include "utilities/trace_recorder.hpp"

namespace blaze::memory_tracker {
namespace {

constexpr size_t k_num_tags = 2;

using Counter = std::atomic<uint64_t>;

static std::array<Counter, k_num_tags> g_bytes{};

void record_memory_counters();

static std::string format_bytes(uint64_t bytes) {
  constexpr double KB = 1024.0;
  constexpr double MB = 1024.0 * 1024.0;
  constexpr double GB = 1024.0 * 1024.0 * 1024.0;

  std::ostringstream ss;
  ss.setf(std::ios::fixed);
  ss.precision(1);

  if (bytes >= static_cast<uint64_t>(GB * 10.0)) {
    ss.precision(0);
    ss << (static_cast<double>(bytes) / GB) << " GB";
  } else if (bytes >= static_cast<uint64_t>(GB)) {
    ss << (static_cast<double>(bytes) / GB) << " GB";
  } else if (bytes >= static_cast<uint64_t>(MB)) {
    ss << (static_cast<double>(bytes) / MB) << " MB";
  } else if (bytes >= static_cast<uint64_t>(KB)) {
    ss << (static_cast<double>(bytes) / KB) << " KB";
  } else {
    ss.precision(0);
    ss << bytes << " B";
  }
  return ss.str();
}

}  // namespace

const char* tag_name(Tag tag) {
  switch (tag) {
    case Tag::LAS:
      return "LAS";
    case Tag::GRID:
      return "Grids";
  }
  return "Other";
}

void add_bytes(Tag tag, uint64_t bytes) {
  if (bytes == 0) return;
  g_bytes[static_cast<size_t>(tag)].fetch_add(bytes, std::memory_order_relaxed);
  record_memory_counters();
}

void remove_bytes(Tag tag, uint64_t bytes) {
  if (bytes == 0) return;
  g_bytes[static_cast<size_t>(tag)].fetch_sub(bytes, std::memory_order_relaxed);
  record_memory_counters();
}

uint64_t total_bytes() {
  uint64_t total = 0;
  for (size_t i = 0; i < k_num_tags; ++i) {
    total += g_bytes[i].load(std::memory_order_relaxed);
  }
  return total;
}

uint64_t tag_bytes(Tag tag) {
  return g_bytes[static_cast<size_t>(tag)].load(std::memory_order_relaxed);
}

namespace {

void record_memory_counters() {
  if (!blaze::trace::enabled()) {
    return;
  }
  blaze::trace::memory_counters(total_bytes(), tag_bytes(Tag::LAS), tag_bytes(Tag::GRID));
}

}  // namespace

std::string format_summary() {
  const uint64_t total = total_bytes();
  if (total == 0) {
    return "Mem: 0 B";
  }

  struct Entry {
    Tag tag;
    uint64_t bytes;
  };

  std::array<Entry, k_num_tags> entries{
      Entry{Tag::LAS, tag_bytes(Tag::LAS)},
      Entry{Tag::GRID, tag_bytes(Tag::GRID)},
  };

  std::sort(entries.begin(), entries.end(),
            [](const Entry& a, const Entry& b) { return a.bytes > b.bytes; });

  std::ostringstream ss;
  ss << "Mem: " << format_bytes(total);

  int printed = 0;
  for (const auto& e : entries) {
    if (e.bytes == 0) continue;
    if (printed == 0) {
      ss << " (";
    } else {
      ss << ", ";
    }
    ss << tag_name(e.tag) << " " << format_bytes(e.bytes);
    ++printed;
    if (printed >= 2) break;
  }
  if (printed > 0) {
    ss << ")";
  }
  return ss.str();
}

}  // namespace blaze::memory_tracker
