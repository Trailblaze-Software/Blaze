cmake_minimum_required(VERSION 3.20..3.26)

if(CMAKE_VERSION GREATER 3.24)
  cmake_policy(VERSION 3.20)
  cmake_policy(SET CMP0135 NEW)
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

message(STATUS "CMake Build Type: ${CMAKE_BUILD_TYPE}")

include(FetchContent)
if(NOT DEFINED BLAZE_FETCHCONTENT_BASE_DIR)
  set(FETCHCONTENT_BASE_DIR ${CMAKE_SOURCE_DIR}/deps)
else()
  set(FETCHCONTENT_BASE_DIR ${BLAZE_FETCHCONTENT_BASE_DIR})
endif()

option(BLAZE_CLI_ONLY "Build Blaze CLI only" OFF)
option(BLAZE_USE_PDAL "Use PDAL for Blaze LAS IO" OFF)
option(BLAZE_USE_VCPKG "Use vcpkg for dependency management on Windows" ON)

if(WIN32 AND BLAZE_USE_VCPKG)
  if(NOT BLAZE_CLI_ONLY)
    list(APPEND VCPKG_MANIFEST_FEATURES "gui")
  endif()

  if(BLAZE_USE_PDAL)
    list(APPEND VCPKG_MANIFEST_FEATURES "pdal")
  endif()

  set(X_VCPKG_APPLOCAL_DEPS_INSTALL
      TRUE
      CACHE BOOL "")
  if(${CMAKE_CXX_COMPILER} MATCHES ".*mingw.*")
    set(VCPKG_TARGET_TRIPLET "x64-mingw-dynamic")
    set(VCPKG_HOST_TRIPLET "x64-mingw-dynamic")
  endif()
  set(VCPKG_BUILD_TYPE "release")
  FetchContent_Declare(
    vcpkg
    GIT_REPOSITORY https://github.com/microsoft/vcpkg.git
    GIT_TAG 2024.12.16)
  FetchContent_MakeAvailable(vcpkg)
  # If vcpkg fails with 7z2409.7z "Is not archive", its download was corrupted.
  # Workaround: 1) Install 7-Zip (https://7-zip.org) and PowerShell; add both to
  # PATH. 2) Delete deps/vcpkg-src/downloads/7z2409.7z if present. 3) Before
  # running CMake: set VCPKG_FORCE_SYSTEM_BINARIES=1 4) Configure again. See
  # https://github.com/microsoft/vcpkg/issues/42987
  if(DEFINED ENV{VCPKG_FORCE_SYSTEM_BINARIES})
    message(
      STATUS
        "VCPKG_FORCE_SYSTEM_BINARIES is set; vcpkg will use system tools if available."
    )
  endif()
  include(${vcpkg_SOURCE_DIR}/scripts/buildsystems/vcpkg.cmake)
endif()

# Extract version from git tag or use provided version
if(NOT DEFINED BLAZE_VERSION)
  # Try to get version from git tag
  execute_process(
    COMMAND git describe --tags --exact-match --match "v*"
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    OUTPUT_VARIABLE GIT_TAG
    OUTPUT_STRIP_TRAILING_WHITESPACE ERROR_QUIET)
  if(GIT_TAG)
    # Remove 'v' prefix from tag (e.g., v0.0.1 -> 0.0.1)
    string(REGEX REPLACE "^v" "" BLAZE_VERSION "${GIT_TAG}")
    message(STATUS "Version from git tag: ${BLAZE_VERSION}")
  else()
    # Default version if no tag found
    set(BLAZE_VERSION "0.0.0-dev")
    message(STATUS "Using default version: ${BLAZE_VERSION}")
  endif()
else()
  message(STATUS "Version from CMake variable: ${BLAZE_VERSION}")
endif()

# Extract numeric version for CMake project() command CMake requires numeric
# format: major.minor.patch[.tweak] Strip any non-numeric suffixes (e.g.,
# "0.0.0-dev" -> "0.0.0")
string(REGEX MATCH "^([0-9]+\\.[0-9]+\\.[0-9]+(\\.[0-9]+)?)"
             BLAZE_VERSION_NUMERIC "${BLAZE_VERSION}")
if(NOT BLAZE_VERSION_NUMERIC)
  # Fallback to 0.0.0 if no valid numeric version found
  set(BLAZE_VERSION_NUMERIC "0.0.0")
  message(
    WARNING
      "Could not extract numeric version from '${BLAZE_VERSION}', using '${BLAZE_VERSION_NUMERIC}'"
  )
endif()

project(
  BLAZE
  VERSION ${BLAZE_VERSION_NUMERIC}
  LANGUAGES CXX)
set(COPYRIGHT "Copyright (c) 2024 Trailblaze Software. All rights reserved.")

# Use the full version string (with suffixes) for compile definitions
add_compile_definitions(BLAZE_VERSION="${BLAZE_VERSION}")
execute_process(
  COMMAND git rev-parse HEAD
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  OUTPUT_VARIABLE GIT_COMMIT_HASH
  OUTPUT_STRIP_TRAILING_WHITESPACE)
add_compile_definitions(GIT_COMMIT_HASH="${GIT_COMMIT_HASH}")

if(BLAZE_USE_PDAL)
  add_compile_definitions(USE_PDAL)
  find_package(PDAL REQUIRED)
endif()
find_package(GDAL REQUIRED)

set(OpenMP_RUNTIME_MSVC "llvm")
find_package(OpenMP REQUIRED)

set(OpenCV_STATIC ON)
find_package(OpenCV REQUIRED COMPONENTS core imgproc imgcodecs)

set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
if(WIN32)
  if(${CMAKE_CXX_COMPILER} MATCHES ".*mingw.*")
    set(CMAKE_CXX_FLAGS
        "${CMAKE_CXX_FLAGS} -fstrict-enums -Wall -Wextra -Wpedantic -Werror")
  else()
    set(CMAKE_CXX_FLAGS
        "${CMAKE_CXX_FLAGS} /Wall /MP /wd5045 /wd4866 /wd4514 /wd4820 /wd4800 /wd4242 /wd4244 /wd4365 /wd5027 /wd4626 /wd5219 /wd4623 /wd4267 /wd4710 /wd4711 /wd4625 /wd5026 /wd4464"
    )
    if(CMAKE_VERSION VERSION_LESS 3.30)
      set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /openmp:llvm")
    endif()
  endif()
  add_compile_definitions(NOMINMAX NOGDI)
elseif(UNIX)
  set(CMAKE_CXX_FLAGS
      "${CMAKE_CXX_FLAGS} -fstrict-enums -Wall -Wextra -Wpedantic -Werror")
else()
  message(FATAL_ERROR "Unsupported platform")
endif()

if(NOT BLAZE_CLI_ONLY)
  set(CMAKE_AUTOUIC ON)
  set(CMAKE_AUTOMOC ON)
endif()

set(LIBRARY_NAME blaze_lib)
set(CLI_EXE_NAME blaze-cli)
set(UNIT_TESTS_NAME unit_tests)
include_directories(src src/lib)
add_library(${LIBRARY_NAME})
if(WIN32)
  configure_file(packaging/resources.rc.in resources.rc @ONLY)
  add_executable(${CLI_EXE_NAME} ${CMAKE_CURRENT_BINARY_DIR}/resources.rc)
else()
  add_executable(${CLI_EXE_NAME})
endif()
add_executable(${UNIT_TESTS_NAME})

set(ALL_EXECUTABLES ${CLI_EXE_NAME} ${UNIT_TESTS_NAME})
if(NOT BLAZE_CLI_ONLY)

  set(GUI_EXE_NAME Blaze)
  list(APPEND ALL_EXECUTABLES ${GUI_EXE_NAME})
  find_package(Qt6 REQUIRED COMPONENTS Widgets Concurrent Core Svg OpenGL
                                       OpenGLWidgets)
  if(WIN32)
    qt_standard_project_setup()
  endif()

  if(WIN32)
    qt_add_executable(${GUI_EXE_NAME} WIN32
                      ${CMAKE_CURRENT_BINARY_DIR}/resources.rc)
  else()
    qt_add_executable(${GUI_EXE_NAME})
  endif()
  target_precompile_headers(${GUI_EXE_NAME} PRIVATE src/precompiled_headers.hpp)
  target_link_libraries(${GUI_EXE_NAME} PRIVATE Qt6::Widgets Qt6::Concurrent
                                                Qt6::Svg)
  set_target_properties(${GUI_EXE_NAME} PROPERTIES WIN32_EXECUTABLE ON
                                                   MACOSX_BUNDLE ON)

  qt_import_plugins(${GUI_EXE_NAME} INCLUDE_BY_TYPE imageformats
                    Qt6::QTiffPlugin)

  if(WIN32)
    add_custom_command(
      TARGET ${GUI_EXE_NAME}
      POST_BUILD
      COMMAND Qt6::windeployqt ARGS $<TARGET_FILE:${GUI_EXE_NAME}>)
  endif()

  set(GUI_3D_EXE_NAME Blaze3D)
  list(APPEND ALL_EXECUTABLES ${GUI_3D_EXE_NAME})
  if(WIN32)
    qt_add_executable(${GUI_3D_EXE_NAME} WIN32
                      ${CMAKE_CURRENT_BINARY_DIR}/resources.rc)
  else()
    qt_add_executable(${GUI_3D_EXE_NAME})
  endif()
  target_precompile_headers(${GUI_3D_EXE_NAME} PRIVATE
                            src/precompiled_headers.hpp)
  target_link_libraries(
    ${GUI_3D_EXE_NAME} PRIVATE Qt6::Widgets Qt6::Concurrent Qt6::OpenGL
                               Qt6::OpenGLWidgets)
  set_target_properties(${GUI_3D_EXE_NAME} PROPERTIES WIN32_EXECUTABLE ON
                                                      MACOSX_BUNDLE ON)

  qt_import_plugins(${GUI_3D_EXE_NAME} INCLUDE_BY_TYPE imageformats
                    Qt6::QTiffPlugin)

  if(WIN32)
    add_custom_command(
      TARGET ${GUI_3D_EXE_NAME}
      POST_BUILD
      COMMAND Qt6::windeployqt ARGS $<TARGET_FILE:${GUI_3D_EXE_NAME}>)
  endif()
endif()
set(ALL_TARGETS ${ALL_EXECUTABLES} ${LIBRARY_NAME})

if(CMAKE_CROSSCOMPILING)
  message(" -- Cross compiling - disabling tests")
else()
  enable_testing()
endif()

set(LASPP_BUILD_TESTS OFF)
FetchContent_Declare(
  las++
  GIT_REPOSITORY https://github.com/Trailblaze-Software/laspp.git
  GIT_TAG 78f13d018de9ba593e76bc2030c2c4a64d6497b7)
set(LASPP_DEBUG_ASSERTS OFF)
FetchContent_MakeAvailable(las++)
target_link_libraries(${LIBRARY_NAME} PUBLIC las++)

set(INSTALL_GTEST OFF)
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

foreach(target ${ALL_TARGETS})
  if(BLAZE_USE_PDAL)
    target_link_libraries(${target} PRIVATE ${PDAL_LIBRARIES})
    target_include_directories(${target} PRIVATE ${PDAL_INCLUDE_DIRS})
  endif()
  target_link_libraries(
    ${target} PRIVATE ${GDAL_LIBRARIES} OpenMP::OpenMP_CXX
                      nlohmann_json::nlohmann_json ${OpenCV_LIBS})
  target_include_directories(${target} PRIVATE ${GDAL_INCLUDE_DIRS}
                                               ${OpenCV_INCLUDE_DIRS})
endforeach()

foreach(target ${ALL_EXECUTABLES})
  target_link_libraries(${target} PRIVATE ${LIBRARY_NAME})
endforeach()

target_include_directories(${UNIT_TESTS_NAME}
                           PRIVATE ${googletest_SOURCE_DIR}/googletest/include)
target_link_libraries(${UNIT_TESTS_NAME} PRIVATE gtest_main)
add_test(NAME ${UNIT_TESTS_NAME} COMMAND ${UNIT_TESTS_NAME})

add_subdirectory(src)

gtest_discover_tests(${UNIT_TESTS_NAME})

include(GNUInstallDirs)

install(
  TARGETS ${CLI_EXE_NAME}
  BUNDLE DESTINATION .
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(TARGETS ${LIBRARY_NAME} DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(DIRECTORY "assets" DESTINATION ${CMAKE_INSTALL_DATADIR})

install(FILES $<TARGET_RUNTIME_DLLS:${CLI_EXE_NAME}> TYPE BIN)

if(NOT BLAZE_CLI_ONLY)
  install(
    TARGETS ${GUI_EXE_NAME}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT GUI)
  install(
    TARGETS ${GUI_3D_EXE_NAME}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT GUI)
  if(NOT WIN32)
    set(ENTRY_NAME "blaze")
    configure_file(${PROJECT_SOURCE_DIR}/packaging/Blaze.desktop.in
                   ${CMAKE_CURRENT_BINARY_DIR}/${ENTRY_NAME}.desktop)
    install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${ENTRY_NAME}.desktop
            DESTINATION ${CMAKE_INSTALL_DATADIR}/applications)

    install(FILES assets/images/${ENTRY_NAME}_icon.png
            DESTINATION ${CMAKE_INSTALL_DATADIR}/icons)
  endif()

  if(WIN32)
    qt_generate_deploy_app_script(
      TARGET
      ${GUI_EXE_NAME}
      OUTPUT_SCRIPT
      deploy_script
      NO_UNSUPPORTED_PLATFORM_ERROR
      DEPLOY_TOOL_OPTIONS
      # workaround for https://github.com/microsoft/vcpkg/issues/17840 or
      # https://github.com/microsoft/vcpkg/issues/36250
      $<$<CONFIG:DEBUG>:--qtpaths
      ${WINDOWS_DEPENDENCY_VCPKG_DIR}/tools/Qt6/bin/qtpaths.debug.bat>)
    install(SCRIPT ${deploy_script} COMPONENT GUI)
    qt_generate_deploy_app_script(
      TARGET
      ${GUI_3D_EXE_NAME}
      OUTPUT_SCRIPT
      deploy_script_3D
      NO_UNSUPPORTED_PLATFORM_ERROR
      DEPLOY_TOOL_OPTIONS
      $<$<CONFIG:DEBUG>:--qtpaths
      ${WINDOWS_DEPENDENCY_VCPKG_DIR}/tools/Qt6/bin/qtpaths.debug.bat>)
    install(SCRIPT ${deploy_script_3D} COMPONENT GUI)

  endif()
endif()

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH}
                      ${CMAKE_CURRENT_SOURCE_DIR}/packaging)

if(WIN32)
  set(CPACK_GENERATOR "NSIS;ZIP")
  file(TO_NATIVE_PATH "${PROJECT_SOURCE_DIR}/packaging/Blaze.nsi"
       CPACK_NSIS_NSI_PATH)
  file(TO_NATIVE_PATH "${PROJECT_SOURCE_DIR}/assets/images/blaze.ico"
       CPACK_NSIS_MUI_ICON)
  if(VCPKG_TARGET_TRIPLET MATCHES "arm64")
    set(CPACK_SYSTEM_NAME "win64-arm64")
  else()
    set(CPACK_SYSTEM_NAME "win64-x64")
  endif()
elseif(UNIX)
  set(CPACK_GENERATOR "STGZ;TGZ;DEB;RPM")
  set(CPACK_SYSTEM_NAME "${CMAKE_SYSTEM_NAME}-${CMAKE_SYSTEM_PROCESSOR}")
endif()
set(CPACK_PACKAGE_NAME "Blaze")
set(CPACK_PACKAGE_FILE_NAME
    "${CPACK_PACKAGE_NAME}-${PROJECT_VERSION}-${CPACK_SYSTEM_NAME}")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Blaze LIDAR mapping tool")
set(CPACK_PACKAGE_VENDOR "Trailblaze Software")
set(CPACK_RESOURCE_FILE_LICENSE "${PROJECT_SOURCE_DIR}/LICENSE")
set(CPACK_PACKAGE_HOMEPAGE_URL "https://Trailblaze-Software.github.io/Blaze/")
set(CPACK_PACKAGE_CONTACT "Ryan Stocks ryan.stocks00@gmail.com")
set(CPACK_PACKAGE_EXECUTABLES "bin/Blaze" "Blaze" "bin/Blaze3D" "Blaze3D"
                              "bin/blaze-cli" "blaze-cli")

# set(CPACK_NSIS_MODIFY_PATH "ON")
set(CPACK_NSIS_ENABLE_UNINSTALL_BEFORE_INSTALL "ON")
set(CPACK_NSIS_DISPLAY_NAME "Blaze")
set(CPACK_NSIS_URL_INFO_ABOUT "https://Trailblaze-Software.github.io/Blaze/")
set(CPACK_NSIS_MENU_LINKS "bin/Blaze.exe" "Blaze" "bin/Blaze3D.exe" "Blaze3D")
set(CPACK_NSIS_MUI_ICON "${CPACK_NSIS_MUI_ICON}")
set(CPACK_DEBIAN_PACKAGE_DEPENDS "qt6-image-formats-plugins")

set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)

include(CPack)
