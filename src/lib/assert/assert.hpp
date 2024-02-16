#pragma once

#include <iostream>
#include <sstream>
#define Assert(condition, message) _Assert(condition, #condition, message, __FILE__, __LINE__)

inline void _Assert(bool condition, const std::string& condition_str, const std::string& message, const std::string& file, int line) {
  if (!condition) {
    std::stringstream ss;
    ss << "Assertion failed: " << condition_str << " " << message << " at " << file << ":" << line << std::endl;
    std::cerr << ss.str();
    throw std::runtime_error(ss.str());
  }
}

#define Fail(message) Assert(false, message)

