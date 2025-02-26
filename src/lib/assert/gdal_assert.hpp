#pragma once

#include <cpl_error.h>

#include <source_location>

#include "assert/assert.hpp"
#include "ogr_core.h"
#define GDALAssert(expr) _GDALAssert(expr, #expr)

inline void _GDALAssert(CPLErr expr, const std::string &expr_string,
                        const std::source_location &loc = std::source_location::current()) {
  if (expr != CE_None)
    _Assert(expr == CE_None, expr_string, "GDAL result: " + std::to_string(expr), loc);
}

inline void _GDALAssert(OGRErr expr, const std::string &expr_string,
                        const std::source_location &loc = std::source_location::current()) {
  if (expr != OGRERR_NONE)
    _Assert(expr == CE_None, expr_string, "OGRERR result: " + std::to_string(expr), loc);
}
