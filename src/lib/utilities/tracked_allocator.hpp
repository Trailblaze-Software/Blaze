#pragma once

#include <cstddef>
#include <cstdint>
#include <limits>
#include <memory>
#include <new>
#include <type_traits>
#include <vector>

#include "utilities/memory_tracker.hpp"

namespace blaze::memory_tracker {

template <typename T, Tag MemoryTag>
class TrackedAllocator {
 public:
  using value_type = T;
  using size_type = std::size_t;
  using difference_type = std::ptrdiff_t;
  using propagate_on_container_copy_assignment = std::true_type;
  using propagate_on_container_move_assignment = std::true_type;
  using propagate_on_container_swap = std::true_type;
  using is_always_equal = std::true_type;

  TrackedAllocator() noexcept = default;

  template <typename U>
  TrackedAllocator(const TrackedAllocator<U, MemoryTag>&) noexcept {}

  T* allocate(size_type count) {
    if (count > max_size()) {
      throw std::bad_alloc();
    }
    void* memory = ::operator new(count * sizeof(T));
    add_bytes(MemoryTag, static_cast<uint64_t>(count) * sizeof(T));
    return static_cast<T*>(memory);
  }

  void deallocate(T* pointer, size_type count) noexcept {
    remove_bytes(MemoryTag, static_cast<uint64_t>(count) * sizeof(T));
    ::operator delete(pointer);
  }

  size_type max_size() const noexcept { return std::numeric_limits<size_type>::max() / sizeof(T); }

  template <typename U>
  struct rebind {
    using other = TrackedAllocator<U, MemoryTag>;
  };
};

template <typename T, typename U, Tag MemoryTag>
bool operator==(const TrackedAllocator<T, MemoryTag>&,
                const TrackedAllocator<U, MemoryTag>&) noexcept {
  return true;
}

template <typename T, typename U, Tag MemoryTag>
bool operator!=(const TrackedAllocator<T, MemoryTag>& lhs,
                const TrackedAllocator<U, MemoryTag>& rhs) noexcept {
  return !(lhs == rhs);
}

template <typename T, Tag MemoryTag>
using TrackedVector = std::vector<T, TrackedAllocator<T, MemoryTag>>;

template <typename T>
using GridVector = TrackedVector<T, Tag::GRID>;

template <typename T>
using LasVector = TrackedVector<T, Tag::LAS>;

}  // namespace blaze::memory_tracker
