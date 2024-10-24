cmake_minimum_required(VERSION 3.20..3.26)

if(CMAKE_VERSION GREATER 3.24)
  cmake_policy(VERSION 3.20)
  cmake_policy(SET CMP0135 NEW)
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)
if(NOT DEFINED FETCHCONTENT_BASE_DIR)
  set(FETCHCONTENT_BASE_DIR ${CMAKE_BINARY_DIR}/deps)
endif()

if(WIN32)
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
    GIT_TAG 2024.09.30)
  FetchContent_MakeAvailable(vcpkg)
  # execute_process( COMMAND ${vcpkg_SOURCE_DIR}/vcpkg.exe install pdal)
  # message(" -- PDAL install: ${pdal_install}")
  include(${vcpkg_SOURCE_DIR}/scripts/buildsystems/vcpkg.cmake)
  # set(CMAKE_TOOLCHAIN_FILE
  # "${vcpkg_SOURCE_DIR}/scripts/buildsystems/vcpkg.cmake")
endif()

project(
  BLAZE
  VERSION 0.0.0
  LANGUAGES CXX)
set(COPYRIGHT "Copyright (c) 2024 Trailblaze Software. All rights reserved.")

add_compile_definitions(BLAZE_VERSION="${PROJECT_VERSION}")
execute_process(
  COMMAND git rev-parse HEAD
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  OUTPUT_VARIABLE GIT_COMMIT_HASH
  OUTPUT_STRIP_TRAILING_WHITESPACE)
add_compile_definitions(GIT_COMMIT_HASH="${GIT_COMMIT_HASH}")

find_package(PDAL REQUIRED)
find_package(GDAL REQUIRED)
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
        "${CMAKE_CXX_FLAGS} /openmp:llvm /Wall /MP /wd5045 /wd4866 /wd4514 /wd4820 /wd4800 /wd4242 /wd4244 /wd4365 /wd5027 /wd4626 /wd5219 /wd4623 /wd4267 /wd4710 /wd4711"
    )
  endif()
  add_compile_definitions(NOMINMAX NOGDI)
elseif(UNIX)
  set(CMAKE_CXX_FLAGS
      "${CMAKE_CXX_FLAGS} -fstrict-enums -Wall -Wextra -Wpedantic -Werror")
else()
  message(FATAL_ERROR "Unsupported platform")
endif()

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

set(LIBRARY_NAME blaze_lib)
set(CLI_EXE_NAME blaze-cli)
set(GUI_EXE_NAME Blaze)
set(UNIT_TESTS_NAME unit_tests)
include_directories(src src/lib)
add_library(${LIBRARY_NAME})
add_executable(${CLI_EXE_NAME} assets/resources.rc)
add_executable(${UNIT_TESTS_NAME})

find_package(Qt6 REQUIRED COMPONENTS Widgets Concurrent)
if(WIN32)
  qt_standard_project_setup()
endif()

if(WIN32)
  qt_add_executable(${GUI_EXE_NAME} WIN32 assets/resources.rc)
else()
  qt_add_executable(${GUI_EXE_NAME})
endif()
target_precompile_headers(${GUI_EXE_NAME} INTERFACE src/precompiled_headers.hpp)
target_link_libraries(${GUI_EXE_NAME} PRIVATE Qt6::Widgets Qt6::Concurrent)
set_target_properties(${GUI_EXE_NAME} PROPERTIES WIN32_EXECUTABLE ON
                                                 MACOSX_BUNDLE ON)
if(WIN32)
  add_custom_command(
    TARGET ${GUI_EXE_NAME}
    POST_BUILD
    COMMAND Qt6::windeployqt ARGS $<TARGET_FILE:${GUI_EXE_NAME}>)
endif()

if(CMAKE_CROSSCOMPILING)
  message(" -- Cross compiling - disabling tests")
else()
  enable_testing()
endif()

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

FetchContent_Declare(
  au_units
  URL https://github.com/aurora-opensource/au/releases/download/0.3.4/au-0.3.4.tar.gz
)
FetchContent_MakeAvailable(au_units)

foreach(target ${CLI_EXE_NAME} ${GUI_EXE_NAME} ${UNIT_TESTS_NAME})
  target_link_libraries(${target} PRIVATE ${LIBRARY_NAME})
endforeach()

foreach(target ${CLI_EXE_NAME} ${GUI_EXE_NAME} ${UNIT_TESTS_NAME}
               ${LIBRARY_NAME})
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
install(
  TARGETS ${GUI_EXE_NAME}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(TARGETS ${LIBRARY_NAME} DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(FILES "config.json" DESTINATION .)

install(FILES $<TARGET_RUNTIME_DLLS:${CLI_EXE_NAME}> TYPE BIN)

if(NOT WIN32)
  set(ENTRY_NAME "blaze")
  configure_file(${PROJECT_SOURCE_DIR}/assets/Blaze.desktop.in
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
  install(SCRIPT ${deploy_script})
endif()

if(WIN32)
  set(CPACK_GENERATOR "NSIS;ZIP")
elseif(UNIX)
  set(CPACK_GENERATOR "STGZ;TGZ;DEB;RPM")
endif()
set(CPACK_PACKAGE_NAME "Blaze")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Blaze LIDAR mapping tool")
set(CPACK_PACKAGE_VENDOR "Trailblaze Software")
set(CPACK_RESOURCE_FILE_LICENSE "${PROJECT_SOURCE_DIR}/LICENSE")
set(CPACK_PACKAGE_HOMEPAGE_URL "https://github.com/Trailblaze-Software/blaze")
set(CPACK_PACKAGE_ICON "${PROJECT_SOURCE_DIR}/assets/images\\\\blaze.ico")
set(CPACK_PACKAGE_CONTACT "Ryan Stocks ryan.stocks00@gmail.com")
set(CPACK_PACKAGE_EXECUTABLES
    "bin/Blaze" "${PROJECT_SOURCE_DIR}/assets/images\\\\blaze.ico"
    "bin/blaze-cli" "${PROJECT_SOURCE_DIR}/assets/images\\\\blaze.ico")

set(CPACK_NSIS_MODIFY_PATH "ON")
set(CPACK_NSIS_ENABLE_UNINSTALL_BEFORE_INSTALL "ON")
set(CPACK_NSIS_DISPLAY_NAME "Blaze")
set(CPACK_NSIS_URL_INFO_ABOUT "https://github.com/Trailblaze-Software/blaze")
set(CPACK_NSIS_MENU_LINKS "bin/Blaze.exe" "Blaze")
set(CPACK_NSIS_MUI_ICON "${PROJECT_SOURCE_DIR}/assets/images\\\\blaze.ico")

set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)

include(CPack)
