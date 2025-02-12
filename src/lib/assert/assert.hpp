#pragma once

#ifndef _MSC_VER
#define HAS_BUILTIN(x) __has_builtin(x)
#else
#define HAS_BUILTIN(x) 0
#endif

#include <iostream>
#include <optional>
#if defined(_MSC_VER) || HAS_BUILTIN(__builtin_source_location)
#include <source_location>
#else
#include <experimental/source_location>
namespace std {
using source_location = std::experimental::source_location;
}
#endif

#include <sstream>
#include <string>

#include "printing/to_string.hpp"

[[noreturn]] inline void unreachable() {
  // Uses compiler specific extensions if possible.
  // Even if no extension is used, undefined behavior is still raised by
  // an empty function body and the noreturn attribute.
#if defined(_MSC_VER) && !defined(__clang__)  // MSVC
  __assume(false);
#else  // GCC, Clang
  __builtin_unreachable();
#endif
}

#define Assert(condition, ...) \
  if (!(condition)) _Assert(condition, #condition, std::optional<std::string>(__VA_ARGS__));

inline void _Assert(bool condition, const std::string &condition_str,
                    const std::optional<std::string> &message,
                    const std::source_location &loc = std::source_location::current()) {
  if (!condition) {
    std::stringstream ss;
    ss << "Blaze assertion failed: " << condition_str << (message ? " " + *message : "") << "\n in "
       << loc.function_name() << " at " << loc.file_name() << ":" << loc.line() << std::endl;
    std::cerr << ss.str();
    throw std::runtime_error(ss.str());
  }
}

#define Fail(...)             \
  Assert(false, __VA_ARGS__); \
  unreachable()

#define Unimplemented(...) Assert(false, "Unimplemented");

template <typename A, typename B>
inline void _AssertBinOp(const A &a, const B &b, const std::string &a_str, const std::string &b_str,
                         bool result, const std::string &nop,
                         const std::source_location &loc = std::source_location::current()) {
  if (!result) {
    std::stringstream ss;
    ss << a << " " << nop << " " << b;
    _Assert(result, a_str + " " + nop + " " + b_str, ss.str(), loc);
  }
}

#define AssertBinOp(a, b, op, nop) \
  if (!((a)op(b))) _AssertBinOp(a, b, #a, #b, a op b, #nop)
#define AssertGE(expr, val) AssertBinOp(expr, val, >=, <)
#define AssertLE(expr, val) AssertBinOp(expr, val, <=, >)
#define AssertGT(expr, val) AssertBinOp(expr, val, >, <=)
#define AssertEQ(expr, val) AssertBinOp(expr, val, ==, !=)
#define AssertNE(expr, val) AssertBinOp(expr, val, !=, ==)
