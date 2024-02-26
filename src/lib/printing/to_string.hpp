#pragma once

#include <iostream>
#include <map>
#include <optional>
#include <vector>

template <typename T>
inline std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec) {
  os << "[";
  for (size_t i = 0; i < vec.size(); i++) {
    os << vec[i];
    if (i < vec.size() - 1) {
      os << ", ";
    }
  }
  return os << "]";
}

template <typename T, typename U>
inline std::ostream& operator<<(std::ostream& os, const std::pair<T, U>& pair) {
  return os << "(" << pair.first << ", " << pair.second << ")";
}

template <typename T>
inline std::ostream& operator<<(std::ostream& os, const std::optional<T>& op) {
  if (op.has_value()) {
    return os << "Some(" << op.value() << ")";
  }
  return os << "None";
}

template <typename T, typename U>
inline std::ostream& operator<<(std::ostream& os, const std::map<T, U> m) {
  os << "{";
  for (const auto& [k, v] : m) {
    os << "(" << k << ": " << v;
  }
  return os << "}";
}
