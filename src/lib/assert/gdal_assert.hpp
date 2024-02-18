#pragma once

#include <gdal/cpl_error.h>

#include <iostream>
#include <stdexcept>
#define GDALAssert(expr) _GDALAssert(expr, #expr, __LINE__, __FILE__)

inline void _GDALAssert(CPLErr expr, const std::string &expr_string, int line,
                        const std::string &file) {
  if (expr != CE_None) {
    std::string err_string =
        "GDALAssert failed: '" + expr_string + "'\n" + file + ":L" + std::to_string(line);
    std::cout << err_string << std::endl;
    throw std::runtime_error(err_string);
  }
}
