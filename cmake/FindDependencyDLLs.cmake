# FindDependencyDLLs.cmake Finds and copies DLLs for Windows builds Handles both
# vcpkg and non-vcpkg builds
#
# Usage: find_and_copy_dependency_dlls(<target1> [<target2> ...])

function(find_and_copy_dependency_dlls)
  if(NOT WIN32)
    return()
  endif()

  # Copy DLLs from all linked CMake targets (e.g. lazperf.dll built via
  # FetchContent). $<TARGET_RUNTIME_DLLS:tgt> lists every SHARED_LIBRARY the
  # target transitively depends on. Post-build steps are appended in order, so
  # this runs before the gtest_discover_tests step added later in
  # CMakeLists.txt.
  foreach(target ${ARGN})
    if(TARGET ${target})
      add_custom_command(
        TARGET ${target}
        POST_BUILD
        COMMAND
          powershell -NonInteractive -Command
          "$dllList = '$<JOIN:$<TARGET_RUNTIME_DLLS:${target}>,|>'; foreach ($dll in $dllList.Split('|')) { if ($dll) { try { Copy-Item -Path $dll -Destination '$<TARGET_FILE_DIR:${target}>' -Force -ErrorAction Stop } catch { } } }"
        COMMENT "Copying target runtime DLLs for ${target}"
        VERBATIM)
    endif()
  endforeach()

  # For vcpkg builds, copy all DLLs from vcpkg's bin directory
  if(BLAZE_USE_VCPKG)
    # Use the active triplet rather than hardcoding x64-windows; otherwise the
    # arm64-windows build copies nothing here (the x64 path doesn't exist), the
    # executables miss vcpkg's transitive runtime DLLs (proj, geos, …), and
    # running them — e.g. gtest_discover_tests launching unit_tests.exe at build
    # time — fails with 0xc0000135 (STATUS_DLL_NOT_FOUND).
    if(DEFINED VCPKG_TARGET_TRIPLET AND VCPKG_TARGET_TRIPLET)
      set(_blaze_vcpkg_triplet "${VCPKG_TARGET_TRIPLET}")
    else()
      set(_blaze_vcpkg_triplet "x64-windows")
    endif()
    if(DEFINED VCPKG_INSTALLED_DIR)
      set(VCPKG_BIN_DIR "${VCPKG_INSTALLED_DIR}/${_blaze_vcpkg_triplet}/bin")
      set(VCPKG_DEBUG_BIN_DIR
          "${VCPKG_INSTALLED_DIR}/${_blaze_vcpkg_triplet}/debug/bin")
    else()
      set(VCPKG_BIN_DIR
          "${CMAKE_BINARY_DIR}/vcpkg_installed/${_blaze_vcpkg_triplet}/bin")
      set(VCPKG_DEBUG_BIN_DIR
          "${CMAKE_BINARY_DIR}/vcpkg_installed/${_blaze_vcpkg_triplet}/debug/bin"
      )
    endif()

    foreach(target ${ARGN})
      if(TARGET ${target})
        # Debug builds need transitive deps from vcpkg's debug/bin (zlibd1,
        # proj_9_d, …). Release builds use bin/.
        add_custom_command(
          TARGET ${target}
          POST_BUILD
          COMMAND
            powershell -NonInteractive -Command
            "$dest = '$<TARGET_FILE_DIR:${target}>'; $bin = if ('$<CONFIG>' -eq 'Debug') { '${VCPKG_DEBUG_BIN_DIR}' } else { '${VCPKG_BIN_DIR}' }; if (Test-Path $bin) { foreach ($f in Get-ChildItem -Path ($bin + '/*.dll') -ErrorAction SilentlyContinue) { try { Copy-Item -Path $f.FullName -Destination $dest -Force -ErrorAction Stop } catch { } } }"
          COMMAND
            powershell -NonInteractive -Command
            "if (Test-Path '${CMAKE_BINARY_DIR}/bin/$<CONFIG>') { foreach ($f in Get-ChildItem -Path '${CMAKE_BINARY_DIR}/bin/$<CONFIG>/*.dll' -ErrorAction SilentlyContinue) { try { Copy-Item -Path $f.FullName -Destination '$<TARGET_FILE_DIR:${target}>' -Force -ErrorAction Stop } catch { } } }"
          COMMENT "Copying vcpkg and gtest DLLs for ${target}"
          VERBATIM)
      endif()
    endforeach()
    return()
  endif()

  # For non-vcpkg builds, find and copy GDAL and OpenCV DLLs

  include(GNUInstallDirs)

  # Get GDAL DLL location from target
  if(TARGET GDAL::GDAL)
    get_target_property(GDAL_LIBRARY GDAL::GDAL LOCATION)
    if(GDAL_LIBRARY)
      get_filename_component(GDAL_DIR "${GDAL_LIBRARY}" DIRECTORY)
      # DLL is typically in Library/bin (conda) or ../bin For conda: Library/lib
      # -> Library/bin For others: lib -> bin
      set(GDAL_SEARCH_PATHS "${GDAL_DIR}/../bin" "${GDAL_DIR}/bin"
                            "${GDAL_DIR}/../../bin")
      # Also check if we're in a conda Library/lib structure
      if(GDAL_DIR MATCHES "/Library/lib$")
        get_filename_component(LIBRARY_PARENT "${GDAL_DIR}" DIRECTORY)
        list(APPEND GDAL_SEARCH_PATHS "${LIBRARY_PARENT}/bin")
      endif()

      # Find the GDAL bin directory (where all DLLs are)
      set(GDAL_BIN_DIR)
      foreach(search_path ${GDAL_SEARCH_PATHS})
        # Normalize the path to avoid duplicates
        get_filename_component(normalized_path "${search_path}" ABSOLUTE)
        file(GLOB test_dlls "${normalized_path}/gdal*.dll")
        if(test_dlls)
          set(GDAL_BIN_DIR "${normalized_path}")
          break()
        endif()
      endforeach()

      if(GDAL_BIN_DIR)
        # Copy ALL DLLs from GDAL bin directory (GDAL depends on PROJ, GEOS,
        # etc.)
        file(GLOB GDAL_DLLS "${GDAL_BIN_DIR}/*.dll")
        # Remove duplicates
        list(REMOVE_DUPLICATES GDAL_DLLS)
        if(GDAL_DLLS)
          list(LENGTH GDAL_DLLS DLL_COUNT)
          message(STATUS "Found GDAL DLLs in: ${GDAL_BIN_DIR}")
          message(STATUS "  Copying ${DLL_COUNT} DLL(s)")
        else()
          message(
            WARNING "No DLLs found in GDAL bin directory: ${GDAL_BIN_DIR}")
        endif()
      else()
        message(
          WARNING
            "GDAL bin directory not found. Searched in: ${GDAL_SEARCH_PATHS}")
      endif()

      foreach(dll ${GDAL_DLLS})
        foreach(target ${ARGN})
          if(TARGET ${target})
            add_custom_command(
              TARGET ${target}
              POST_BUILD
              COMMAND ${CMAKE_COMMAND} -E copy_if_different "${dll}"
                      "$<TARGET_FILE_DIR:${target}>"
              COMMENT "Copying ${dll} to ${target} output directory")
          endif()
        endforeach()
        install(FILES "${dll}" DESTINATION ${CMAKE_INSTALL_BINDIR})
      endforeach()
    endif()
  endif()

  # Get OpenCV DLLs from OpenCV_DIR
  if(OpenCV_FOUND AND DEFINED OpenCV_DIR)
    # OpenCV DLLs can be in various locations depending on installation
    # Prioritize VS version-specific paths (x64/vc16/bin) as they have the
    # actual DLLs
    set(OpenCV_SEARCH_PATHS)
    # Check for VS version-specific paths first (x64/vc16/bin, etc.)
    file(GLOB vs_paths "${OpenCV_DIR}/x64/vc*/bin")
    list(APPEND OpenCV_SEARCH_PATHS ${vs_paths})
    # Also check build/x64/vc*/bin if OpenCV_DIR is the build directory
    file(GLOB build_vs_paths "${OpenCV_DIR}/build/x64/vc*/bin")
    list(APPEND OpenCV_SEARCH_PATHS ${build_vs_paths})
    # Fallback to generic bin directories
    list(APPEND OpenCV_SEARCH_PATHS "${OpenCV_DIR}/build/bin"
         "${OpenCV_DIR}/bin")

    # Find the first directory with OpenCV DLLs and get all DLLs from there
    set(OpenCV_BIN_DIR)
    foreach(search_path ${OpenCV_SEARCH_PATHS})
      get_filename_component(normalized_path "${search_path}" ABSOLUTE)
      file(GLOB test_dlls "${normalized_path}/opencv_*.dll")
      if(test_dlls)
        set(OpenCV_BIN_DIR "${normalized_path}")
        break()
      endif()
    endforeach()

    set(OpenCV_DLLS)
    if(OpenCV_BIN_DIR)
      file(GLOB OpenCV_DLLS "${OpenCV_BIN_DIR}/opencv_*.dll")
      list(REMOVE_DUPLICATES OpenCV_DLLS)
      if(OpenCV_DLLS)
        list(LENGTH OpenCV_DLLS DLL_COUNT)
        message(STATUS "Found OpenCV DLLs in: ${OpenCV_BIN_DIR}")
        message(STATUS "  Copying ${DLL_COUNT} OpenCV DLL(s)")
      else()
        message(WARNING "No OpenCV DLLs found in: ${OpenCV_BIN_DIR}")
      endif()
    else()
      message(
        WARNING "OpenCV DLLs not found. Searched in: ${OpenCV_SEARCH_PATHS}")
    endif()

    foreach(dll ${OpenCV_DLLS})
      foreach(target ${ARGN})
        if(TARGET ${target})
          add_custom_command(
            TARGET ${target}
            POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different "${dll}"
                    "$<TARGET_FILE_DIR:${target}>"
            COMMENT "Copying ${dll} to ${target} output directory")
        endif()
      endforeach()
      install(FILES "${dll}" DESTINATION ${CMAKE_INSTALL_BINDIR})
    endforeach()
  endif()
endfunction()
