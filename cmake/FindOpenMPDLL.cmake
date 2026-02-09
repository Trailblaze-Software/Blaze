# FindOpenMPDLL.cmake Finds the OpenMP DLL required for LLVM OpenMP runtime on
# Windows
#
# This function searches for the OpenMP DLL and sets up installation/copying for
# the specified targets.
#
# Usage: find_openmp_dll(<target1> [<target2> ...])
#
# The function will: 1. Search for the DLL near the OpenMP library location 2.
# Search in vcpkg directories (if using vcpkg) 3. Search in Visual Studio
# directories (for local development) 4. Install the DLL and copy it to target
# output directories

function(find_openmp_dll)
  if(NOT WIN32
     OR NOT MSVC
     OR NOT OpenMP_CXX_FOUND)
    return()
  endif()

  set(OpenMP_DLL "")

  # Determine architecture
  if(CMAKE_VS_PLATFORM_NAME STREQUAL "x64"
     OR CMAKE_GENERATOR_PLATFORM STREQUAL "x64"
     OR CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(ARCH_SUBDIR "x64")
  else()
    set(ARCH_SUBDIR "x86")
  endif()

  # Collect search paths
  set(SEARCH_PATHS)

  # 1. Search near the OpenMP library location
  foreach(lib ${OpenMP_CXX_LIBRARIES})
    if(lib MATCHES "libomp\\.lib$")
      get_filename_component(lib_dir "${lib}" DIRECTORY)
      list(APPEND SEARCH_PATHS "${lib_dir}" "${lib_dir}/../bin"
           "${lib_dir}/../../bin" "${lib_dir}/../${ARCH_SUBDIR}")
    endif()
  endforeach()

  # 1. Search in vcpkg directories (common in CI)
  if(DEFINED VCPKG_ROOT)
    list(APPEND SEARCH_PATHS
         "${VCPKG_ROOT}/installed/${VCPKG_TARGET_TRIPLET}/bin"
         "${VCPKG_ROOT}/installed/${VCPKG_TARGET_TRIPLET}/tools/openmp")
  endif()
  if(DEFINED CMAKE_TOOLCHAIN_FILE AND CMAKE_TOOLCHAIN_FILE MATCHES "vcpkg")
    get_filename_component(vcpkg_toolchain_dir "${CMAKE_TOOLCHAIN_FILE}"
                           DIRECTORY)
    get_filename_component(vcpkg_root "${vcpkg_toolchain_dir}/.." ABSOLUTE)
    if(EXISTS "${vcpkg_root}/installed")
      file(GLOB vcpkg_triplets "${vcpkg_root}/installed/*")
      foreach(triplet ${vcpkg_triplets})
        if(IS_DIRECTORY "${triplet}")
          list(APPEND SEARCH_PATHS "${triplet}/bin" "${triplet}/tools/openmp")
        endif()
      endforeach()
    endif()
  endif()

  # 1. Search in Visual Studio directories
  foreach(vs_base "C:/Program Files/Microsoft Visual Studio"
                  "C:/Program Files (x86)/Microsoft Visual Studio")
    if(EXISTS "${vs_base}")
      # Search in Redist directories
      file(
        GLOB
        vs_redist_dirs
        "${vs_base}/*/*/VC/Redist/MSVC/*/debug_nonredist/${ARCH_SUBDIR}/Microsoft.VC*.DebugOpenMP"
      )
      list(APPEND SEARCH_PATHS ${vs_redist_dirs})

      # Search in Tools/MSVC/bin directories
      file(
        GLOB vs_tools_dirs
        "${vs_base}/*/*/VC/Tools/MSVC/*/bin/Host${ARCH_SUBDIR}/${ARCH_SUBDIR}")
      list(APPEND SEARCH_PATHS ${vs_tools_dirs})
    endif()
  endforeach()

  message(STATUS "Searching for OpenMP DLL in ${ARCH_SUBDIR} architecture...")
  message(STATUS "Search paths (${ARCH_SUBDIR}):")
  foreach(path ${SEARCH_PATHS})
    message(STATUS "  - ${path}")
  endforeach()

  # Search for the DLL
  find_file(
    OpenMP_DLL
    NAMES libomp140.x86_64.dll libomp140.dll libomp.dll
    PATHS ${SEARCH_PATHS}
    NO_DEFAULT_PATH NO_CMAKE_FIND_ROOT_PATH)

  # If still not found, try recursive search in VS directories
  if(NOT OpenMP_DLL)
    message(
      STATUS
        "OpenMP DLL not found in standard locations, searching Visual Studio directories recursively..."
    )
    foreach(vs_base "C:/Program Files/Microsoft Visual Studio"
                    "C:/Program Files (x86)/Microsoft Visual Studio")
      if(EXISTS "${vs_base}")
        file(GLOB_RECURSE candidates "${vs_base}/libomp*.dll")
        if(candidates)
          message(
            STATUS "Found ${ARCH_SUBDIR} OpenMP DLL candidates in ${vs_base}:")
          foreach(candidate ${candidates})
            message(STATUS "  - ${candidate}")
          endforeach()
          # Prefer architecture-specific DLLs
          foreach(candidate ${candidates})
            if(ARCH_SUBDIR STREQUAL "x64" AND candidate MATCHES "x64")
              set(OpenMP_DLL "${candidate}")
              break()
            elseif(ARCH_SUBDIR STREQUAL "x86" AND candidate MATCHES "x86")
              set(OpenMP_DLL "${candidate}")
              break()
            endif()
          endforeach()
          # Fallback to first found
          if(NOT OpenMP_DLL)
            list(GET candidates 0 OpenMP_DLL)
          endif()
        endif()
        if(OpenMP_DLL)
          break()
        endif()
      endif()
    endforeach()
  endif()

  # Install and copy DLL if found
  if(OpenMP_DLL)
    get_filename_component(OpenMP_DLL_DIR "${OpenMP_DLL}" DIRECTORY)
    get_filename_component(OpenMP_DLL_NAME "${OpenMP_DLL}" NAME)
    message(STATUS "OpenMP DLL found at: ${OpenMP_DLL}")
    message(STATUS "  Source directory: ${OpenMP_DLL_DIR}")
    message(STATUS "  DLL name: ${OpenMP_DLL_NAME}")

    # Install the DLL Note: GNUInstallDirs is safe to include multiple times
    include(GNUInstallDirs)
    install(FILES "${OpenMP_DLL}" DESTINATION ${CMAKE_INSTALL_BINDIR})

    # Copy to each target's output directory
    foreach(target ${ARGN})
      if(TARGET ${target})
        add_custom_command(
          TARGET ${target}
          POST_BUILD
          COMMAND ${CMAKE_COMMAND} -E copy_if_different "${OpenMP_DLL}"
                  "$<TARGET_FILE_DIR:${target}>"
          COMMENT
            "Copying OpenMP DLL from ${OpenMP_DLL_DIR} to ${target} output directory"
        )
      endif()
    endforeach()
  else()
    message(
      WARNING
        "OpenMP DLL not found. The binary may fail at runtime if the DLL is not in PATH.\n"
        "Searched paths:\n  ${SEARCH_PATHS}")
  endif()
endfunction()
