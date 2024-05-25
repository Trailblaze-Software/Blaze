#pragma once

#include <iostream>
#include <sstream>
#include <string>

#define Assert(condition, message) _Assert(condition, #condition, message, __FILE__, __LINE__)

inline void _Assert(bool condition, const std::string &condition_str, const std::string &message,
                    const std::string &file, int line) {
  if (!condition) {
    std::stringstream ss;
    ss << "Assertion failed: " << condition_str << " " << message << " at " << file << ":" << line
       << std::endl;
    std::cerr << ss.str();
    throw std::runtime_error(ss.str());
  }
}

using std::to_string;

inline std::string to_string(const std::string &str) { return str; }

#define Fail(message)     \
  Assert(false, message); \
  __builtin_unreachable()
#define AssertGE(expr, val)                                                                  \
  _Assert(expr >= val, #expr " < " #val, to_string(expr) + " < " + to_string(val), __FILE__, \
          __LINE__)
#define AssertEQ(expr, val)                                                                    \
  _Assert(expr == val, #expr " != " #val, to_string(expr) + " != " + to_string(val), __FILE__, \
          __LINE__)
