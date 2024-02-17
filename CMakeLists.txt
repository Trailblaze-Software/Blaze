cmake_minimum_required(VERSION 3.20..3.26)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(
  BLAZE
  VERSION 0.0.0
  LANGUAGES CXX)

find_package(PDAL REQUIRED)
find_package(GDAL REQUIRED)

set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fstrict-enums -Wall -Wextra -Wpedantic -Werror -g")

set(EXECUTABLE_NAME blaze)
set(UNIT_TESTS_NAME unit_tests)
include_directories(src src/lib)
add_executable(${EXECUTABLE_NAME})
add_executable(${UNIT_TESTS_NAME})


enable_testing()
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip)
FetchContent_MakeAvailable(googletest)
include(GoogleTest)

foreach(target ${EXECUTABLE_NAME} ${UNIT_TESTS_NAME})
    target_link_libraries(${target} PRIVATE ${PDAL_LIBRARIES} ${GDAL_LIBRARIES})
    target_include_directories(${target} PRIVATE ${PDAL_INCLUDE_DIRS} ${GDAL_INCLUDE_DIRS})
endforeach()
target_include_directories(${UNIT_TESTS_NAME} PRIVATE ${googletest_SOURCE_DIR}/googletest/include)
target_link_libraries(${UNIT_TESTS_NAME} PRIVATE gtest_main)

add_subdirectory(src)

gtest_discover_tests(${UNIT_TESTS_NAME})
