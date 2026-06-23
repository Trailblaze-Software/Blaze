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

  # Determine architecture (check ARM64 first, then x64, then x86) Check
  # multiple sources to reliably detect ARM64
  if(CMAKE_VS_PLATFORM_NAME STREQUAL "ARM64"
     OR CMAKE_GENERATOR_PLATFORM STREQUAL "ARM64"
     OR (DEFINED VCPKG_TARGET_TRIPLET AND VCPKG_TARGET_TRIPLET MATCHES "arm64")
     OR (DEFINED MSVC_CXX_ARCHITECTURE_ID AND MSVC_CXX_ARCHITECTURE_ID STREQUAL
                                              "ARM64"))
    set(ARCH_SUBDIR "arm64")
  elseif(
    CMAKE_VS_PLATFORM_NAME STREQUAL "x64"
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

  # 1. Search in Visual Studio OpenMP.LLVM directories (correct location)
  foreach(vs_base "C:/Program Files/Microsoft Visual Studio"
                  "C:/Program Files (x86)/Microsoft Visual Studio")
    if(EXISTS "${vs_base}")
      # Search in Redist/MSVC OpenMP.LLVM directories (the correct location)
      file(
        GLOB
        vs_openmp_dirs
        "${vs_base}/*/*/VC/Redist/MSVC/*/debug_nonredist/${ARCH_SUBDIR}/Microsoft.VC*.OpenMP.LLVM"
      )
      list(APPEND SEARCH_PATHS ${vs_openmp_dirs})
    endif()
  endforeach()

  # Search for the DLL (architecture-specific names first)
  if(ARCH_SUBDIR STREQUAL "arm64")
    set(DLL_NAMES_RELEASE libomp140.arm64.dll libomp140.dll libomp.dll)
    set(DLL_NAMES_DEBUG libomp140d.arm64.dll libomp140d.dll)
  elseif(ARCH_SUBDIR STREQUAL "x64")
    set(DLL_NAMES_RELEASE libomp140.x86_64.dll libomp140.dll libomp.dll)
    set(DLL_NAMES_DEBUG libomp140d.x86_64.dll libomp140d.dll)
  else()
    set(DLL_NAMES_RELEASE libomp140.dll libomp.dll)
    set(DLL_NAMES_DEBUG libomp140d.dll)
  endif()

  find_file(
    OpenMP_DLL_RELEASE
    NAMES ${DLL_NAMES_RELEASE}
    PATHS ${SEARCH_PATHS}
    NO_DEFAULT_PATH NO_CMAKE_FIND_ROOT_PATH)

  find_file(
    OpenMP_DLL_DEBUG
    NAMES ${DLL_NAMES_DEBUG}
    PATHS ${SEARCH_PATHS}
    NO_DEFAULT_PATH NO_CMAKE_FIND_ROOT_PATH)

  # Backward-compatible alias for install rules.
  if(OpenMP_DLL_RELEASE)
    set(OpenMP_DLL "${OpenMP_DLL_RELEASE}")
  elseif(OpenMP_DLL_DEBUG)
    set(OpenMP_DLL "${OpenMP_DLL_DEBUG}")
  endif()

  # If still not found, try recursive search in VS directories
  if(NOT OpenMP_DLL_RELEASE AND NOT OpenMP_DLL_DEBUG)
    message(STATUS "Searching Visual Studio directories recursively...")
    foreach(vs_base "C:/Program Files/Microsoft Visual Studio"
                    "C:/Program Files (x86)/Microsoft Visual Studio")
      if(EXISTS "${vs_base}")
        file(GLOB_RECURSE candidates "${vs_base}/libomp*.dll")
        if(candidates)
          # Prefer architecture-specific DLLs
          foreach(candidate ${candidates})
            if(ARCH_SUBDIR STREQUAL "arm64" AND candidate MATCHES "arm64")
              if(candidate MATCHES "d\\.dll$")
                set(OpenMP_DLL_DEBUG "${candidate}")
              else()
                set(OpenMP_DLL_RELEASE "${candidate}")
              endif()
            elseif(ARCH_SUBDIR STREQUAL "x64" AND candidate MATCHES
                                                  "x86_64|x64")
              if(candidate MATCHES "d\\.dll$")
                set(OpenMP_DLL_DEBUG "${candidate}")
              else()
                set(OpenMP_DLL_RELEASE "${candidate}")
              endif()
            elseif(ARCH_SUBDIR STREQUAL "x86" AND candidate MATCHES "x86")
              if(candidate MATCHES "d\\.dll$")
                set(OpenMP_DLL_DEBUG "${candidate}")
              else()
                set(OpenMP_DLL_RELEASE "${candidate}")
              endif()
            endif()
          endforeach()
          if(NOT OpenMP_DLL_RELEASE AND NOT OpenMP_DLL_DEBUG)
            list(GET candidates 0 OpenMP_DLL_RELEASE)
          endif()
        endif()
        if(OpenMP_DLL_RELEASE OR OpenMP_DLL_DEBUG)
          break()
        endif()
      endif()
    endforeach()
    if(OpenMP_DLL_RELEASE)
      set(OpenMP_DLL "${OpenMP_DLL_RELEASE}")
    elseif(OpenMP_DLL_DEBUG)
      set(OpenMP_DLL "${OpenMP_DLL_DEBUG}")
    endif()
  endif()

  # Install and copy DLL if found
  if(OpenMP_DLL_RELEASE OR OpenMP_DLL_DEBUG)
    if(OpenMP_DLL_RELEASE)
      get_filename_component(OpenMP_DLL_RELEASE_DIR "${OpenMP_DLL_RELEASE}"
                             DIRECTORY)
      get_filename_component(OpenMP_DLL_RELEASE_NAME "${OpenMP_DLL_RELEASE}"
                             NAME)
      message(STATUS "OpenMP release DLL found: ${OpenMP_DLL_RELEASE_NAME}")
      message(STATUS "  Location: ${OpenMP_DLL_RELEASE}")
    endif()
    if(OpenMP_DLL_DEBUG)
      get_filename_component(OpenMP_DLL_DEBUG_DIR "${OpenMP_DLL_DEBUG}"
                             DIRECTORY)
      get_filename_component(OpenMP_DLL_DEBUG_NAME "${OpenMP_DLL_DEBUG}" NAME)
      message(STATUS "OpenMP debug DLL found: ${OpenMP_DLL_DEBUG_NAME}")
      message(STATUS "  Location: ${OpenMP_DLL_DEBUG}")
    endif()

    # Install the release DLL (runtime redistributable)
    include(GNUInstallDirs)
    if(OpenMP_DLL_RELEASE)
      install(FILES "${OpenMP_DLL_RELEASE}" DESTINATION ${CMAKE_INSTALL_BINDIR})
    endif()

    # Copy the config-appropriate DLL to each target's output directory.
    foreach(target ${ARGN})
      if(TARGET ${target})
        if(OpenMP_DLL_RELEASE AND OpenMP_DLL_DEBUG)
          add_custom_command(
            TARGET ${target}
            POST_BUILD
            COMMAND
              ${CMAKE_COMMAND} -E copy_if_different
              "$<IF:$<CONFIG:Debug>,${OpenMP_DLL_DEBUG},${OpenMP_DLL_RELEASE}>"
              "$<TARGET_FILE_DIR:${target}>"
            COMMENT
              "Copying OpenMP DLL to ${target} output directory ($<CONFIG>)")
        elseif(OpenMP_DLL_RELEASE)
          add_custom_command(
            TARGET ${target}
            POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
                    "${OpenMP_DLL_RELEASE}" "$<TARGET_FILE_DIR:${target}>"
            COMMENT
              "Copying OpenMP DLL from ${OpenMP_DLL_RELEASE_DIR} to ${target} output directory"
          )
        else()
          add_custom_command(
            TARGET ${target}
            POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different "${OpenMP_DLL_DEBUG}"
                    "$<TARGET_FILE_DIR:${target}>"
            COMMENT
              "Copying OpenMP debug DLL from ${OpenMP_DLL_DEBUG_DIR} to ${target} output directory"
          )
        endif()
      endif()
    endforeach()
  else()
    message(
      WARNING
        "OpenMP DLL not found. The binary may fail at runtime if the DLL is not in PATH.\n"
        "Searched paths:\n  ${SEARCH_PATHS}")
  endif()
endfunction()
