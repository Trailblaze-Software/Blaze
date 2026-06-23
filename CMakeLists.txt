cmake_minimum_required(VERSION 3.20..3.26)

if(CMAKE_VERSION GREATER 3.24)
  cmake_policy(VERSION 3.20)
  cmake_policy(SET CMP0135 NEW)
endif()

# Propagate CMP0091 NEW into FetchContent subdirectories whose own
# cmake_minimum_required() predates 3.15 (notably googletest 1.15.x, which
# declares VERSION 3.13). Without this, googletest's targets run under CMP0091
# OLD on MSVC and MSVC_RUNTIME_LIBRARY is silently ignored for them. This is a
# defensive correctness fix; the MSBuild default of /MD happens to match what we
# want, but relying on the default is fragile.
set(CMAKE_POLICY_DEFAULT_CMP0091 NEW)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(CMAKE_BUILD_TYPE STREQUAL "")
  set(CMAKE_BUILD_TYPE "Release")
endif()
message(STATUS "CMake Build Type: ${CMAKE_BUILD_TYPE}")

include(FetchContent)
if(NOT DEFINED BLAZE_FETCHCONTENT_BASE_DIR)
  set(FETCHCONTENT_BASE_DIR ${CMAKE_SOURCE_DIR}/deps)
else()
  # Resolve to absolute so unexpanded shell vars like $(pwd) don't reach ninja
  get_filename_component(FETCHCONTENT_BASE_DIR "${BLAZE_FETCHCONTENT_BASE_DIR}"
                         ABSOLUTE)
endif()

option(BLAZE_CLI_ONLY "Build Blaze CLI only" OFF)
option(BLAZE_BUILD_3D_GUI "Build Blaze3D GUI application" ON)
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

  # Disable vcpkg's *build-tree* app-local DLL deployment. It injects an
  # applocal.ps1 POST_BUILD step into every executable target, all of which copy
  # dependent DLLs into the same shared build/<config> directory. When Blaze and
  # Blaze3D build in parallel (cmake --build --parallel), these steps race and
  # one fails with "The process cannot access the file 'brotlicommon.dll'
  # because it is being used by another process" — and applocal.ps1 (unlike our
  # own copies) is not error-tolerant, so the whole post-build chain exits 1
  # (MSB3073). We already copy the full vcpkg bin dir ourselves in
  # cmake/FindDependencyDLLs.cmake, wrapping each copy in try/catch so a file
  # locked by a racing sibling target is skipped (the target holding the lock
  # finishes the copy), which is lock-tolerant and a superset of what applocal
  # deploys, so the build tree loses nothing. X_VCPKG_APPLOCAL_DEPS_INSTALL
  # stays TRUE so the *installed*/packaged GUI binaries still get their deps.
  set(VCPKG_APPLOCAL_DEPS OFF)

  set(VCPKG_BUILD_TYPE "release")
  FetchContent_Declare(
    vcpkg
    GIT_REPOSITORY https://github.com/microsoft/vcpkg.git
    GIT_TAG 2025.12.12)
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
  find_package(PDAL REQUIRED CONFIG)
endif()
find_package(GDAL REQUIRED)

set(OpenMP_RUNTIME_MSVC "llvm")
find_package(OpenMP REQUIRED)

set(OpenCV_STATIC ON)
find_package(OpenCV REQUIRED COMPONENTS core imgproc imgcodecs)

# System OpenCV packages (apt, Homebrew) and vcpkg (VCPKG_BUILD_TYPE=release)
# only ship release libraries. OpenCV's debug_build_guard ABI (enabled by _DEBUG
# on MSVC or _GLIBCXX_DEBUG on GCC) is incompatible with those libs. Use
# config-time generator expression so multi-config generators (MSVC/Xcode) also
# apply this in Debug.
add_compile_definitions($<$<CONFIG:Debug>:CV_IGNORE_DEBUG_BUILD_GUARD>)

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
  find_package(Qt6 REQUIRED COMPONENTS Widgets Concurrent Core OpenGL)
  find_package(Qt6OpenGLWidgets REQUIRED)

  # Qt < 6.9.2 injects "-framework AGL" into WrapOpenGL's link interface
  # (Qt6::Gui depends on it transitively). AGL was removed from the macOS 26
  # SDK, so linking any Qt GUI target fails with "framework 'AGL' not found".
  # Strip AGL out of the imported target; it's unused legacy Carbon OpenGL.
  # Fixed upstream in qtbase commit cdb33c3d (6.9.2+), but filtering here keeps
  # older Qt and Homebrew Qt building too. No-op on non-Apple platforms and on
  # Qt versions that don't create the target.
  if(APPLE AND TARGET WrapOpenGL::WrapOpenGL)
    get_target_property(_wrap_opengl_libs WrapOpenGL::WrapOpenGL
                        INTERFACE_LINK_LIBRARIES)
    if(_wrap_opengl_libs)
      list(FILTER _wrap_opengl_libs EXCLUDE REGEX "AGL")
      set_target_properties(
        WrapOpenGL::WrapOpenGL PROPERTIES INTERFACE_LINK_LIBRARIES
                                          "${_wrap_opengl_libs}")
    endif()
  endif()

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
  target_link_libraries(${GUI_EXE_NAME} PRIVATE Qt6::Widgets Qt6::Concurrent)
  set_target_properties(${GUI_EXE_NAME} PROPERTIES WIN32_EXECUTABLE ON
                                                   MACOSX_BUNDLE ON)

  qt_import_plugins(${GUI_EXE_NAME} INCLUDE_BY_TYPE imageformats
                    Qt6::QTiffPlugin)

  if(BLAZE_BUILD_3D_GUI)
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
  endif()

  if(WIN32)
    # Deploy Qt runtime dependencies from a single target to avoid race
    # conditions when Blaze and Blaze3D build in parallel. windeployqt uses
    # QFile::copy() which fails when the destination file already exists, so
    # running it per-target causes non-deterministic failures when both try to
    # deploy to the same output directory. --force overwrites files from the
    # first invocation; --no-compiler-runtime skips vc_redist.x64.exe which is
    # not needed in the build tree.
    if(BLAZE_BUILD_3D_GUI)
      add_custom_target(
        deploy_qt ALL
        COMMAND Qt6::windeployqt --force --no-compiler-runtime
                $<TARGET_FILE:${GUI_EXE_NAME}>
        COMMAND Qt6::windeployqt --force --no-compiler-runtime
                $<TARGET_FILE:${GUI_3D_EXE_NAME}>
        COMMENT "Deploying Qt runtime dependencies")
      add_dependencies(deploy_qt ${GUI_EXE_NAME} ${GUI_3D_EXE_NAME})
    else()
      add_custom_target(
        deploy_qt ALL
        COMMAND Qt6::windeployqt --force --no-compiler-runtime
                $<TARGET_FILE:${GUI_EXE_NAME}>
        COMMENT "Deploying Qt runtime dependencies")
      add_dependencies(deploy_qt ${GUI_EXE_NAME})
    endif()
  endif()
endif()
set(ALL_TARGETS ${ALL_EXECUTABLES} ${LIBRARY_NAME})

if(CMAKE_CROSSCOMPILING)
  message(" -- Cross compiling - disabling tests")
else()
  enable_testing()
endif()

set(LASPP_BUILD_TESTS
    OFF
    CACHE BOOL "" FORCE)
set(LASPP_DEBUG_ASSERTS
    OFF
    CACHE BOOL "" FORCE)
FetchContent_Declare(
  las++
  GIT_REPOSITORY https://github.com/Trailblaze-Software/laspp.git
  GIT_TAG e8834593bb430072a22224bb495746460e99900f)
FetchContent_MakeAvailable(las++)
target_link_libraries(${LIBRARY_NAME} PUBLIC las++)

set(INSTALL_GTEST OFF)
# Match the shared CRT (/MD) used by the rest of the project on MSVC; without
# this, googletest defaults to /MT and the linker cannot resolve gtest symbols
# (LNK2001 on MakeAndRegisterTestInfo, etc.).
set(gtest_force_shared_crt
    ON
    CACHE BOOL "" FORCE)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip)
FetchContent_MakeAvailable(googletest)
include(GoogleTest)

# Apple clang raises -Wcharacter-conversion (promoted to error) on the char8_t
# -> char32_t implicit cast inside gtest-printers.h. The flag name is not
# individually suppressible on all Apple clang versions, so demote -Werror to a
# warning for the gtest target only.
target_compile_options(gtest
                       PRIVATE $<$<CXX_COMPILER_ID:AppleClang>:-Wno-error>)

FetchContent_Declare(
  nlohmann_json
  GIT_REPOSITORY https://github.com/nlohmann/json.git
  GIT_TAG v3.11.3)
FetchContent_MakeAvailable(nlohmann_json)

foreach(target ${ALL_TARGETS})
  if(BLAZE_USE_PDAL)
    # PDAL CONFIG mode provides PDAL_LIBRARIES, PDAL_INCLUDE_DIRS, etc.
    target_link_libraries(${target} PRIVATE ${PDAL_LIBRARIES})
    target_include_directories(${target} PRIVATE ${PDAL_INCLUDE_DIRS})
    if(PDAL_DEFINITIONS)
      target_compile_definitions(${target} PRIVATE ${PDAL_DEFINITIONS})
    endif()
  endif()
  target_link_libraries(
    ${target} PRIVATE GDAL::GDAL OpenMP::OpenMP_CXX
                      nlohmann_json::nlohmann_json ${OpenCV_LIBS})
  target_include_directories(${target} PRIVATE ${GDAL_INCLUDE_DIRS}
                                               ${OpenCV_INCLUDE_DIRS})
endforeach()

foreach(target ${ALL_EXECUTABLES})
  target_link_libraries(${target} PRIVATE ${LIBRARY_NAME})
endforeach()

# Find and copy OpenMP DLL for Windows/MSVC builds. Attach to the library so it
# runs once when the lib is built; all executables link the lib and use the same
# output dir, so they get the DLL without duplicate post-build steps.
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/FindOpenMPDLL.cmake)
find_openmp_dll(${LIBRARY_NAME})

# Find and copy DLLs for Windows builds. Handles both vcpkg and non-vcpkg
# builds. vcpkg doesn't automatically copy DLLs to build directories, only to
# install directories. Copy to all executables to ensure DLLs are available when
# tests run.
if(WIN32)
  include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/FindDependencyDLLs.cmake)
  find_and_copy_dependency_dlls(${ALL_EXECUTABLES})
endif()

# Find and copy PROJ data files to build output directory PROJ automatically
# searches ../share/proj/ relative to the binary Attach to the library so it
# runs once when the lib is built; all executables link the lib and use the same
# output dir, so they get the data files without duplicate post-build steps.
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/FindProjData.cmake)
find_proj_data(${LIBRARY_NAME})

# BEFORE PRIVATE so FetchContent's gtest headers are searched *before* the
# broader include dirs added in the foreach() above (notably GDAL's include
# directory, which on the no-vcpkg Windows build points to conda's shared
# C:\Program Files\Miniconda3\Library\include — a directory that turns out to
# ship its own older <gtest/gtest.h>). Without BEFORE, the test .cpp files
# compiled against the older header (e.g. MakeAndRegisterTestInfo took `const
# char*` as its first argument in gtest <=1.14, vs. `std::string` in 1.15+), and
# the resulting LNK2001 unresolved external symbol errors blamed
# MakeAndRegisterTestInfo and ReportInvalidTestSuiteType because the gtest.lib
# built from FetchContent's 1.15.2 source has different mangled names.
target_include_directories(${UNIT_TESTS_NAME} BEFORE
                           PRIVATE ${googletest_SOURCE_DIR}/googletest/include)
# unit_tests.cpp defines its own main(); link only gtest (not gtest_main) to
# avoid a duplicate-symbol error.
target_link_libraries(${UNIT_TESTS_NAME} PRIVATE gtest)

add_subdirectory(src)

# unit_tests links blaze_lib and (when Blaze3D is enabled) Qt6::Gui. On Windows
# and macOS the transitive runtime deps are not reliably loadable at link time,
# so gtest_discover_tests must not execute the binary during the build — only
# when ctest runs, after POST_BUILD DLL deployment / rpath setup.
gtest_discover_tests(
  ${UNIT_TESTS_NAME} DISCOVERY_TIMEOUT 120 DISCOVERY_MODE PRE_TEST
  WORKING_DIRECTORY "$<TARGET_FILE_DIR:${UNIT_TESTS_NAME}>")

include(GNUInstallDirs)
# Ensure assets land at <prefix>/share/assets. GNUInstallDirs may leave
# CMAKE_INSTALL_DATADIR unset depending on CMake version/platform; copying
# DATAROOTDIR alone is not enough when both are still empty at configure time.
if(NOT CMAKE_INSTALL_DATADIR)
  set(CMAKE_INSTALL_DATADIR "${CMAKE_INSTALL_DATAROOTDIR}")
endif()
if(NOT CMAKE_INSTALL_DATADIR)
  set(CMAKE_INSTALL_DATADIR "share")
endif()

install(
  TARGETS ${CLI_EXE_NAME}
  BUNDLE DESTINATION .
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(TARGETS ${LIBRARY_NAME} DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(DIRECTORY "assets" DESTINATION ${CMAKE_INSTALL_DATADIR})

install(FILES $<TARGET_RUNTIME_DLLS:${CLI_EXE_NAME}> TYPE BIN)

# Install PROJ data files for installed builds
install_proj_data()

if(NOT BLAZE_CLI_ONLY)
  install(
    TARGETS ${GUI_EXE_NAME}
    BUNDLE DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT GUI)
  if(BLAZE_BUILD_3D_GUI)
    install(
      TARGETS ${GUI_3D_EXE_NAME}
      BUNDLE DESTINATION .
      RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
      LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
      ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT GUI)
  endif()
  if(UNIX AND NOT APPLE)
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
    if(BLAZE_BUILD_3D_GUI)
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
endif()

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH}
                      ${CMAKE_CURRENT_SOURCE_DIR}/packaging)

if(WIN32)
  set(CPACK_GENERATOR "NSIS;ZIP")
  # Convert to native path and escape for CMake config file We need 8
  # backslashes in CMake variable so CPack writes 4 backslashes to file CMake
  # reads 4 backslashes as 2, which becomes 1 in the actual value This avoids \U
  # being interpreted as an escape sequence
  file(TO_NATIVE_PATH "${PROJECT_SOURCE_DIR}/packaging/Blaze.nsi"
       _nsis_path_temp)
  # Replace each backslash with 8 backslashes (\\\\\\\\\\\\\\\\)
  string(REGEX REPLACE "\\\\" "\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\"
                       CPACK_NSIS_NSI_PATH "${_nsis_path_temp}")
  file(TO_NATIVE_PATH "${PROJECT_SOURCE_DIR}/assets/images/blaze.ico"
       _icon_path_temp)
  string(REGEX REPLACE "\\\\" "\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\"
                       CPACK_NSIS_MUI_ICON "${_icon_path_temp}")
  if(VCPKG_TARGET_TRIPLET MATCHES "arm64")
    set(CPACK_SYSTEM_NAME "win64-arm64")
  else()
    set(CPACK_SYSTEM_NAME "win64-x64")
  endif()
elseif(APPLE)
  set(CPACK_GENERATOR "DragNDrop")
  set(CPACK_SYSTEM_NAME "macOS-${CMAKE_SYSTEM_PROCESSOR}")
  set(CPACK_DMG_VOLUME_NAME "Blaze")
  set(CPACK_DMG_FORMAT "UDZO")
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
set(_cpack_executables "bin/Blaze" "Blaze" "bin/blaze-cli" "blaze-cli")
if(NOT BLAZE_CLI_ONLY AND BLAZE_BUILD_3D_GUI)
  list(APPEND _cpack_executables "bin/Blaze3D" "Blaze3D")
endif()
set(CPACK_PACKAGE_EXECUTABLES ${_cpack_executables})

# set(CPACK_NSIS_MODIFY_PATH "ON")
set(CPACK_NSIS_ENABLE_UNINSTALL_BEFORE_INSTALL "ON")
set(CPACK_NSIS_DISPLAY_NAME "Blaze")
# Use a fixed registry key (not version-specific) so uninstall-before-install
# works across versions
set(CPACK_PACKAGE_INSTALL_REGISTRY_KEY "Blaze")
set(CPACK_NSIS_URL_INFO_ABOUT "https://Trailblaze-Software.github.io/Blaze/")
set(_cpack_nsis_links "bin/Blaze.exe" "Blaze")
if(NOT BLAZE_CLI_ONLY AND BLAZE_BUILD_3D_GUI)
  list(APPEND _cpack_nsis_links "bin/Blaze3D.exe" "Blaze3D")
endif()
set(CPACK_NSIS_MENU_LINKS ${_cpack_nsis_links})
set(CPACK_NSIS_MUI_ICON "${CPACK_NSIS_MUI_ICON}")
set(CPACK_DEBIAN_PACKAGE_DEPENDS "qt6-image-formats-plugins")

set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)

include(CPack)
