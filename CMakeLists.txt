cmake_minimum_required(VERSION 3.20..3.26)

if(CMAKE_VERSION GREATER 3.24)
  cmake_policy(VERSION 3.20)
  cmake_policy(SET CMP0135 NEW)
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)
set(FETCHCONTENT_BASE_DIR ${CMAKE_SOURCE_DIR}/deps)

if(WIN32 AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
  FetchContent_Declare(
    vcpkg
    GIT_REPOSITORY https://github.com/microsoft/vcpkg.git
    GIT_TAG 2024.09.30)
  FetchContent_MakeAvailable(vcpkg)
  set(CMAKE_TOOLCHAIN_FILE
      "${vcpkg_SOURCE_DIR}/scripts/buildsystems/vcpkg.cmake")
endif()

project(
  BLAZE
  VERSION 0.0.0
  LANGUAGES CXX)

find_package(PDAL REQUIRED)
find_package(GDAL REQUIRED)
find_package(OpenMP REQUIRED)

set(OpenCV_STATIC ON)
find_package(OpenCV REQUIRED COMPONENTS core imgproc imgcodecs)

set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
if(WIN32)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /openmp:llvm /Wall")
  add_compile_definitions(NOMINMAX)
elseif(UNIX)
  set(CMAKE_CXX_FLAGS
      "${CMAKE_CXX_FLAGS} -fstrict-enums -Wall -Wextra -Wpedantic -Werror")
else()
  message(FATAL_ERROR "Unsupported platform")
endif()

set(LIBRARY_NAME blaze_lib)
set(EXECUTABLE_NAME blaze)
set(UNIT_TESTS_NAME unit_tests)
include_directories(src src/lib)
add_library(${LIBRARY_NAME})
add_executable(${EXECUTABLE_NAME})
add_executable(${UNIT_TESTS_NAME})

if(CMAKE_CROSSCOMPILING)
  message(" -- Cross compiling - disabling tests")
else()
  enable_testing()
endif()

FetchContent_Declare(
  googletest
  URL "https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip"
)
FetchContent_MakeAvailable(googletest)
include(GoogleTest)

FetchContent_Declare(
  nlohmann_json
  URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz)
FetchContent_MakeAvailable(nlohmann_json)

FetchContent_Declare(
  au_units
  URL https://github.com/aurora-opensource/au/releases/download/0.3.4/au-0.3.4.tar.gz
)
FetchContent_MakeAvailable(au_units)

foreach(target ${EXECUTABLE_NAME} ${UNIT_TESTS_NAME})
  target_link_libraries(${target} PRIVATE ${LIBRARY_NAME})
endforeach()

foreach(target ${EXECUTABLE_NAME} ${UNIT_TESTS_NAME} ${LIBRARY_NAME})
  target_link_libraries(
    ${target} PRIVATE ${PDAL_LIBRARIES} ${GDAL_LIBRARIES} OpenMP::OpenMP_CXX
                      nlohmann_json::nlohmann_json ${OpenCV_LIBS})
  target_include_directories(
    ${target} PRIVATE ${PDAL_INCLUDE_DIRS} ${GDAL_INCLUDE_DIRS}
                      ${au_units_SOURCE_DIR} ${OpenCV_INCLUDE_DIRS})
endforeach()

target_include_directories(${UNIT_TESTS_NAME}
                           PRIVATE ${googletest_SOURCE_DIR}/googletest/include)
target_link_libraries(${UNIT_TESTS_NAME} PRIVATE gtest_main)

add_subdirectory(src)

gtest_discover_tests(${UNIT_TESTS_NAME})
