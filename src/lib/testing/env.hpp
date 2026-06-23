#pragma once

#include "utilities/env.hpp"

namespace blaze::test {

inline const char* get_env(const char* name) { return blaze::get_env(name); }

}  // namespace blaze::test
