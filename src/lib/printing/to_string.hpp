#pragma once

#include <iomanip>
#include <iostream>
#include <map>
#include <optional>
#include <set>
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

template <typename T>
inline std::ostream& operator<<(std::ostream& os, const std::set<T>& set) {
  os << "{";
  for (const T& elem : set) {
    os << elem << ", ";
  }
  return os << "}";
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

inline std::string double_to_string(double d, int precision = 2) {
  std::ostringstream ss;
  ss << std::fixed << std::setprecision(precision) << std::noshowpoint << d;
  // Remove trailing zeros
  std::string s = ss.str();
  s.erase(s.find_last_not_of('0') + 1, std::string::npos);
  if (s.back() == '.') {
    s.pop_back();
  }
  return s;
}
