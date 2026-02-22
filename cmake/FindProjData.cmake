# FindProjData.cmake - Finds and copies PROJ data files for Windows builds
#
# This function uses the GDAL package location to find PROJ data files from
# vcpkg and copies them to the build output directory so PROJ can find them
# automatically.
#
# Usage: find_proj_data(<target1> [<target2> ...])
#
# PROJ automatically searches ../share/proj/ relative to the binary

# Helper function to find PROJ data directory
function(_find_proj_data_dir result_var)
  set(PROJ_DATA_DIR)

  # Try vcpkg location first
  if(BLAZE_USE_VCPKG)
    if(TARGET GDAL::GDAL)
      get_target_property(GDAL_LIBRARY GDAL::GDAL IMPORTED_LOCATION_RELEASE)
      if(NOT GDAL_LIBRARY)
        get_target_property(GDAL_LIBRARY GDAL::GDAL IMPORTED_LOCATION)
      endif()

      if(GDAL_LIBRARY)
        # In vcpkg: <triplet>/lib/gdal.lib -> <triplet>/share/proj
        get_filename_component(triplet_dir "${GDAL_LIBRARY}" DIRECTORY)
        get_filename_component(triplet_dir "${triplet_dir}" DIRECTORY)
        if(EXISTS "${triplet_dir}/share/proj/proj.db")
          set(PROJ_DATA_DIR "${triplet_dir}/share/proj")
        endif()
      endif()
    endif()

    # Fallback: FetchContent vcpkg location
    if(NOT PROJ_DATA_DIR
       AND EXISTS
           "${CMAKE_BINARY_DIR}/vcpkg_installed/${VCPKG_TARGET_TRIPLET}/share/proj/proj.db"
    )
      set(PROJ_DATA_DIR
          "${CMAKE_BINARY_DIR}/vcpkg_installed/${VCPKG_TARGET_TRIPLET}/share/proj"
      )
    endif()
  endif()

  # If not found, try to find from GDAL installation (conda, etc.)
  if(NOT PROJ_DATA_DIR AND TARGET GDAL::GDAL)
    get_target_property(GDAL_LIBRARY GDAL::GDAL LOCATION)
    if(NOT GDAL_LIBRARY)
      get_target_property(GDAL_LIBRARY GDAL::GDAL IMPORTED_LOCATION_RELEASE)
    endif()
    if(NOT GDAL_LIBRARY)
      get_target_property(GDAL_LIBRARY GDAL::GDAL IMPORTED_LOCATION)
    endif()

    if(GDAL_LIBRARY)
      get_filename_component(GDAL_DIR "${GDAL_LIBRARY}" DIRECTORY)
      # For conda: Library/lib -> Library/share/proj For others: lib ->
      # share/proj or ../share/proj
      set(PROJ_SEARCH_PATHS
          "${GDAL_DIR}/../share/proj" "${GDAL_DIR}/../../share/proj"
          "${GDAL_DIR}/share/proj")
      # Also check if we're in a conda Library/lib structure
      if(GDAL_DIR MATCHES "/Library/lib$")
        get_filename_component(LIBRARY_PARENT "${GDAL_DIR}" DIRECTORY)
        list(APPEND PROJ_SEARCH_PATHS "${LIBRARY_PARENT}/share/proj")
      endif()

      foreach(search_path ${PROJ_SEARCH_PATHS})
        get_filename_component(normalized_path "${search_path}" ABSOLUTE)
        if(EXISTS "${normalized_path}/proj.db")
          set(PROJ_DATA_DIR "${normalized_path}")
          break()
        endif()
      endforeach()
    endif()
  endif()

  if(PROJ_DATA_DIR)
    message(STATUS "Found PROJ data files in: ${PROJ_DATA_DIR}")
  endif()

  set(${result_var}
      "${PROJ_DATA_DIR}"
      PARENT_SCOPE)
endfunction()

function(find_proj_data)
  if(NOT WIN32 OR NOT TARGET GDAL::GDAL)
    return()
  endif()

  _find_proj_data_dir(PROJ_DATA_DIR)

  if(NOT PROJ_DATA_DIR OR NOT EXISTS "${PROJ_DATA_DIR}/proj.db")
    message(
      WARNING "PROJ data files (proj.db) not found. PROJ operations may fail.")
    return()
  endif()

  foreach(target ${ARGN})
    if(TARGET ${target})
      add_custom_command(
        TARGET ${target}
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory
                "$<TARGET_FILE_DIR:${target}>/../share/proj"
        COMMAND ${CMAKE_COMMAND} -E copy_directory "${PROJ_DATA_DIR}"
                "$<TARGET_FILE_DIR:${target}>/../share/proj"
        COMMENT "Copying PROJ data files from ${PROJ_DATA_DIR}")
    endif()
  endforeach()
endfunction()

# Install PROJ data files for installed builds
function(install_proj_data)
  if(NOT WIN32 OR NOT TARGET GDAL::GDAL)
    return()
  endif()

  include(GNUInstallDirs)
  _find_proj_data_dir(PROJ_DATA_DIR)

  if(PROJ_DATA_DIR AND EXISTS "${PROJ_DATA_DIR}/proj.db")
    install(
      DIRECTORY "${PROJ_DATA_DIR}/"
      DESTINATION ${CMAKE_INSTALL_DATADIR}/proj
      FILES_MATCHING
      PATTERN "*.db"
      PATTERN "*.csv"
      PATTERN "*.json"
      PATTERN "*.sql"
      PATTERN "*.txt")
  endif()
endfunction()
