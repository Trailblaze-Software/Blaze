cmake_minimum_required(VERSION 3.20..3.26)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(
  BLAZE
  VERSION 0.0.0
  LANGUAGES CXX)

find_package(PDAL REQUIRED)
find_package(GDAL REQUIRED)

set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fstrict-enums -Wall -Wextra -Wpedantic -Werror -g")

set(EXECUTABLE_NAME blaze)
include_directories(src src/lib)
add_executable(${EXECUTABLE_NAME})

add_subdirectory(src)
