# FindOpenMPDLL.cmake Finds the OpenMP DLL required for LLVM OpenMP runtime on
# Windows
#
# Sets up discovery, POST_BUILD copy, and install rules for the OpenMP runtime.
# Usage: find_openmp_dll(<target1> [<target2> ...])

function(_blaze_openmp_dll_is_debug dll_path result_var)
  get_filename_component(dll_name "${dll_path}" NAME)
  if(dll_name MATCHES "libomp[0-9]+d[\\.]" OR dll_path MATCHES
                                              "debug_nonredist")
    set(${result_var}
        TRUE
        PARENT_SCOPE)
  else()
    set(${result_var}
        FALSE
        PARENT_SCOPE)
  endif()
endfunction()

function(_blaze_openmp_dll_matches_arch dll_path arch_subdir result_var)
  if(arch_subdir STREQUAL "arm64")
    if(dll_path MATCHES "aarch64|arm64")
      set(${result_var}
          TRUE
          PARENT_SCOPE)
    else()
      set(${result_var}
          FALSE
          PARENT_SCOPE)
    endif()
  elseif(arch_subdir STREQUAL "x64")
    if(dll_path MATCHES "x86_64")
      set(${result_var}
          TRUE
          PARENT_SCOPE)
    elseif(dll_path MATCHES "arm64|aarch64")
      set(${result_var}
          FALSE
          PARENT_SCOPE)
    elseif(dll_path MATCHES "[/\\\\]x64[/\\\\]")
      set(${result_var}
          TRUE
          PARENT_SCOPE)
    else()
      set(${result_var}
          FALSE
          PARENT_SCOPE)
    endif()
  else()
    if(dll_path MATCHES "x86_64|arm64|aarch64")
      set(${result_var}
          FALSE
          PARENT_SCOPE)
    elseif(dll_path MATCHES "x86|[/\\\\]x86[/\\\\]")
      set(${result_var}
          TRUE
          PARENT_SCOPE)
    else()
      set(${result_var}
          FALSE
          PARENT_SCOPE)
    endif()
  endif()
endfunction()

# Macros so discovered paths accumulate in find_openmp_dll()'s scope.
macro(_blaze_openmp_register_candidate dll_path arch_subdir)
  if(EXISTS "${dll_path}")
    _blaze_openmp_dll_matches_arch("${dll_path}" "${arch_subdir}" arch_match)
    if(arch_match)
      _blaze_openmp_dll_is_debug("${dll_path}" is_debug)
      if(is_debug)
        if(NOT OpenMP_DLL_DEBUG)
          set(OpenMP_DLL_DEBUG "${dll_path}")
        endif()
      elseif(NOT OpenMP_DLL_RELEASE)
        set(OpenMP_DLL_RELEASE "${dll_path}")
      endif()
    endif()
  endif()
endmacro()

macro(_blaze_openmp_scan_directory dir arch_subdir)
  if(IS_DIRECTORY "${dir}")
    list(APPEND SEARCH_PATHS "${dir}")
    file(GLOB omp_dlls "${dir}/libomp*.dll")
    foreach(dll ${omp_dlls})
      _blaze_openmp_register_candidate("${dll}" "${arch_subdir}")
    endforeach()
  endif()
endmacro()

macro(_blaze_openmp_scan_vs_installations arch_subdir)
  foreach(vs_base "C:/Program Files/Microsoft Visual Studio"
                  "C:/Program Files (x86)/Microsoft Visual Studio")
    if(EXISTS "${vs_base}")
      file(GLOB vs_roots "${vs_base}/*/*")
      foreach(vs_root ${vs_roots})
        file(GLOB msvc_versions "${vs_root}/VC/Redist/MSVC/*")
        list(SORT msvc_versions COMPARE NATURAL)
        list(REVERSE msvc_versions)
        foreach(msvc_version_dir ${msvc_versions})
          if(IS_DIRECTORY "${msvc_version_dir}")
            foreach(redist_leaf "" "debug_nonredist")
              if(redist_leaf STREQUAL "")
                set(redist_base "${msvc_version_dir}/${arch_subdir}")
              else()
                set(redist_base
                    "${msvc_version_dir}/${redist_leaf}/${arch_subdir}")
              endif()
              file(GLOB omp_dirs "${redist_base}/Microsoft.VC*.OpenMP.LLVM")
              foreach(omp_dir ${omp_dirs})
                _blaze_openmp_scan_directory("${omp_dir}" "${arch_subdir}")
              endforeach()
            endforeach()
          endif()
        endforeach()
      endforeach()
    endif()
  endforeach()
endmacro()

function(find_openmp_dll)
  if(NOT WIN32
     OR NOT MSVC
     OR NOT OpenMP_CXX_FOUND)
    return()
  endif()

  set(OpenMP_DLL "")
  set(OpenMP_DLL_RELEASE "")
  set(OpenMP_DLL_DEBUG "")
  set(SEARCH_PATHS "")

  if(CMAKE_VS_PLATFORM_NAME STREQUAL "ARM64"
     OR CMAKE_GENERATOR_PLATFORM STREQUAL "ARM64"
     OR (DEFINED VCPKG_TARGET_TRIPLET AND VCPKG_TARGET_TRIPLET MATCHES "arm64")
     OR (DEFINED MSVC_CXX_ARCHITECTURE_ID AND MSVC_CXX_ARCHITECTURE_ID STREQUAL
                                              "ARM64"))
    set(ARCH_SUBDIR "arm64")
    set(OPENMP_RUNTIME_DLL_NAME "libomp140.aarch64.dll")
  elseif(
    CMAKE_VS_PLATFORM_NAME STREQUAL "x64"
    OR CMAKE_GENERATOR_PLATFORM STREQUAL "x64"
    OR CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(ARCH_SUBDIR "x64")
    set(OPENMP_RUNTIME_DLL_NAME "libomp140.x86_64.dll")
  else()
    set(ARCH_SUBDIR "x86")
    set(OPENMP_RUNTIME_DLL_NAME "libomp140.dll")
  endif()

  foreach(lib ${OpenMP_CXX_LIBRARIES})
    if(lib MATCHES "libomp\\.lib$")
      get_filename_component(lib_dir "${lib}" DIRECTORY)
      _blaze_openmp_scan_directory("${lib_dir}" "${ARCH_SUBDIR}")
      _blaze_openmp_scan_directory("${lib_dir}/../bin" "${ARCH_SUBDIR}")
      _blaze_openmp_scan_directory("${lib_dir}/../../bin" "${ARCH_SUBDIR}")
      _blaze_openmp_scan_directory("${lib_dir}/../${ARCH_SUBDIR}"
                                   "${ARCH_SUBDIR}")
    endif()
  endforeach()

  if(DEFINED VCPKG_ROOT)
    _blaze_openmp_scan_directory(
      "${VCPKG_ROOT}/installed/${VCPKG_TARGET_TRIPLET}/bin" "${ARCH_SUBDIR}")
    _blaze_openmp_scan_directory(
      "${VCPKG_ROOT}/installed/${VCPKG_TARGET_TRIPLET}/tools/openmp"
      "${ARCH_SUBDIR}")
  endif()
  if(DEFINED CMAKE_TOOLCHAIN_FILE AND CMAKE_TOOLCHAIN_FILE MATCHES "vcpkg")
    get_filename_component(vcpkg_toolchain_dir "${CMAKE_TOOLCHAIN_FILE}"
                           DIRECTORY)
    get_filename_component(vcpkg_root "${vcpkg_toolchain_dir}/.." ABSOLUTE)
    if(EXISTS "${vcpkg_root}/installed")
      file(GLOB vcpkg_triplets "${vcpkg_root}/installed/*")
      foreach(triplet ${vcpkg_triplets})
        if(IS_DIRECTORY "${triplet}")
          _blaze_openmp_scan_directory("${triplet}/bin" "${ARCH_SUBDIR}")
          _blaze_openmp_scan_directory("${triplet}/tools/openmp"
                                       "${ARCH_SUBDIR}")
        endif()
      endforeach()
    endif()
  endif()

  _blaze_openmp_scan_vs_installations("${ARCH_SUBDIR}")

  if(ARCH_SUBDIR STREQUAL "arm64")
    set(DLL_NAMES_RELEASE libomp140.aarch64.dll libomp140.arm64.dll
                          libomp140.dll libomp.dll)
    set(DLL_NAMES_DEBUG libomp140d.aarch64.dll libomp140d.arm64.dll
                        libomp140d.dll)
  elseif(ARCH_SUBDIR STREQUAL "x64")
    set(DLL_NAMES_RELEASE libomp140.x86_64.dll libomp140.dll libomp.dll)
    set(DLL_NAMES_DEBUG libomp140d.x86_64.dll libomp140d.dll)
  else()
    set(DLL_NAMES_RELEASE libomp140.dll libomp.dll)
    set(DLL_NAMES_DEBUG libomp140d.dll)
  endif()

  list(REMOVE_DUPLICATES SEARCH_PATHS)

  if(NOT OpenMP_DLL_RELEASE)
    find_file(
      OpenMP_DLL_RELEASE
      NAMES ${DLL_NAMES_RELEASE}
      PATHS ${SEARCH_PATHS}
      NO_DEFAULT_PATH NO_CMAKE_FIND_ROOT_PATH)
  endif()
  if(NOT OpenMP_DLL_DEBUG)
    find_file(
      OpenMP_DLL_DEBUG
      NAMES ${DLL_NAMES_DEBUG}
      PATHS ${SEARCH_PATHS}
      NO_DEFAULT_PATH NO_CMAKE_FIND_ROOT_PATH)
  endif()

  if(OpenMP_DLL_RELEASE)
    _blaze_openmp_dll_is_debug("${OpenMP_DLL_RELEASE}" release_is_debug)
    if(release_is_debug)
      if(NOT OpenMP_DLL_DEBUG)
        set(OpenMP_DLL_DEBUG "${OpenMP_DLL_RELEASE}")
      endif()
      unset(OpenMP_DLL_RELEASE)
      unset(OpenMP_DLL_RELEASE CACHE)
    endif()
  endif()

  set(BLAZE_OPENMP_RUNTIME_DLL_SOURCE "")
  set(BLAZE_OPENMP_RUNTIME_DLL_RENAME FALSE)
  if(OpenMP_DLL_RELEASE)
    set(BLAZE_OPENMP_RUNTIME_DLL_SOURCE "${OpenMP_DLL_RELEASE}")
    set(OpenMP_DLL "${OpenMP_DLL_RELEASE}")
  elseif(OpenMP_DLL_DEBUG)
    set(BLAZE_OPENMP_RUNTIME_DLL_SOURCE "${OpenMP_DLL_DEBUG}")
    set(BLAZE_OPENMP_RUNTIME_DLL_RENAME TRUE)
    set(OpenMP_DLL "${OpenMP_DLL_DEBUG}")
  endif()

  if(BLAZE_OPENMP_RUNTIME_DLL_SOURCE)
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
    if(BLAZE_OPENMP_RUNTIME_DLL_RENAME)
      message(
        WARNING
          "OpenMP release DLL not found for ${ARCH_SUBDIR}; using "
          "${OpenMP_DLL_DEBUG_NAME} installed as ${OPENMP_RUNTIME_DLL_NAME}.")
    endif()

    include(GNUInstallDirs)
    install(
      FILES "${BLAZE_OPENMP_RUNTIME_DLL_SOURCE}"
      DESTINATION ${CMAKE_INSTALL_BINDIR}
      RENAME "${OPENMP_RUNTIME_DLL_NAME}"
      OPTIONAL)
    # Fallback: POST_BUILD copies the runtime DLL into the build tree.
    set(_blaze_openmp_build_runtime_path
        "${CMAKE_BINARY_DIR}/Release/${OPENMP_RUNTIME_DLL_NAME}")
    install(
      CODE "
set(_openmp_dst \"\${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_BINDIR}\")
if(DEFINED ENV{DESTDIR})
  set(_openmp_dst \"\$ENV{DESTDIR}\${_openmp_dst}\")
endif()
set(_openmp_file \"\${_openmp_dst}/${OPENMP_RUNTIME_DLL_NAME}\")
if(NOT EXISTS \"\${_openmp_file}\")
  if(EXISTS \"${_blaze_openmp_build_runtime_path}\")
    file(INSTALL \"${_blaze_openmp_build_runtime_path}\"
         DESTINATION \"\${_openmp_dst}\" TYPE FILE)
  else()
    message(WARNING \"OpenMP runtime DLL not found at install time\")
  endif()
endif()
")

    foreach(target ${ARGN})
      if(NOT TARGET ${target})
        continue()
      endif()
      if(OpenMP_DLL_RELEASE AND OpenMP_DLL_DEBUG)
        add_custom_command(
          TARGET ${target}
          POST_BUILD
          COMMAND
            ${CMAKE_COMMAND} -E copy_if_different
            "$<IF:$<CONFIG:Debug>,${OpenMP_DLL_DEBUG},${OpenMP_DLL_RELEASE}>"
            "$<TARGET_FILE_DIR:${target}>/$<IF:$<CONFIG:Debug>,${OpenMP_DLL_DEBUG_NAME},${OPENMP_RUNTIME_DLL_NAME}>"
          COMMENT "Copying OpenMP DLL to ${target} output directory ($<CONFIG>)"
        )
      elseif(OpenMP_DLL_RELEASE)
        add_custom_command(
          TARGET ${target}
          POST_BUILD
          COMMAND ${CMAKE_COMMAND} -E copy_if_different "${OpenMP_DLL_RELEASE}"
                  "$<TARGET_FILE_DIR:${target}>/${OPENMP_RUNTIME_DLL_NAME}"
          COMMENT
            "Copying OpenMP DLL from ${OpenMP_DLL_RELEASE_DIR} to ${target} output directory"
        )
      else()
        add_custom_command(
          TARGET ${target}
          POST_BUILD
          COMMAND ${CMAKE_COMMAND} -E copy_if_different "${OpenMP_DLL_DEBUG}"
                  "$<TARGET_FILE_DIR:${target}>/${OPENMP_RUNTIME_DLL_NAME}"
          COMMENT
            "Copying OpenMP debug DLL as ${OPENMP_RUNTIME_DLL_NAME} to ${target} output directory"
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
