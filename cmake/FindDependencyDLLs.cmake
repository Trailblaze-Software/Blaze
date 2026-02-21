# FindDependencyDLLs.cmake Finds and copies GDAL and OpenCV DLLs for Windows
# builds without vcpkg
#
# Usage: find_and_copy_dependency_dlls(<target1> [<target2> ...])

function(find_and_copy_dependency_dlls)
  if(NOT WIN32 OR BLAZE_USE_VCPKG)
    return()
  endif()

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
            get_filename_component(dll_name "${dll}" NAME)
            add_custom_command(
              TARGET ${target}
              POST_BUILD
              COMMAND ${CMAKE_COMMAND} -E copy_if_different "${dll}"
                      "$<TARGET_FILE_DIR:${target}>"
              COMMAND ${CMAKE_COMMAND} -E echo
                      "Copied ${dll_name} to $<TARGET_FILE_DIR:${target}>"
              COMMENT "Copying ${dll_name} to ${target} output directory")
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
          get_filename_component(dll_name "${dll}" NAME)
          add_custom_command(
            TARGET ${target}
            POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different "${dll}"
                    "$<TARGET_FILE_DIR:${target}>"
            COMMAND ${CMAKE_COMMAND} -E echo
                    "Copied ${dll_name} to $<TARGET_FILE_DIR:${target}>"
            COMMENT "Copying ${dll_name} to ${target} output directory")
        endif()
      endforeach()
      install(FILES "${dll}" DESTINATION ${CMAKE_INSTALL_BINDIR})
    endforeach()
  endif()
endfunction()
