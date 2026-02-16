# FindProjData.cmake - Finds and copies PROJ data files for Windows builds
#
# This function uses the GDAL package location to find PROJ data files from
# vcpkg and copies them to the build output directory so PROJ can find them
# automatically.
#
# Usage: find_proj_data(<target1> [<target2> ...])
#
# PROJ automatically searches ../share/proj/ relative to the binary

# Helper function to get vcpkg installed directory from GDAL package
function(_get_vcpkg_installed_dir result_var)
  # Use GDAL::GDAL target location (most reliable since GDAL was already found)
  if(TARGET GDAL::GDAL)
    get_target_property(GDAL_LIBRARY GDAL::GDAL IMPORTED_LOCATION_RELEASE)
    if(NOT GDAL_LIBRARY)
      get_target_property(GDAL_LIBRARY GDAL::GDAL IMPORTED_LOCATION)
    endif()

    if(GDAL_LIBRARY)
      # In vcpkg: <triplet>/lib/gdal.lib -> <triplet>/share/proj
      get_filename_component(triplet_dir "${GDAL_LIBRARY}" DIRECTORY)
      get_filename_component(triplet_dir "${triplet_dir}" DIRECTORY)
      if(EXISTS "${triplet_dir}/share/proj")
        set(${result_var}
            "${triplet_dir}"
            PARENT_SCOPE)
        message(STATUS "Found PROJ data files in ${triplet_dir}")
        return()
      endif()
    endif()
  endif()

  # Fallback: FetchContent vcpkg location
  if(EXISTS "${CMAKE_BINARY_DIR}/vcpkg_installed/${VCPKG_TARGET_TRIPLET}")
    set(${result_var}
        "${CMAKE_BINARY_DIR}/vcpkg_installed/${VCPKG_TARGET_TRIPLET}"
        PARENT_SCOPE)
    message(
      STATUS
        "Found PROJ data files in ${CMAKE_BINARY_DIR}/vcpkg_installed/${VCPKG_TARGET_TRIPLET} using fallback"
    )
    return()
  endif()

  message(STATUS "Fallback: FetchContent vcpkg location not found")
  set(${result_var}
      ""
      PARENT_SCOPE)
endfunction()

function(find_proj_data)
  if(NOT WIN32
     OR NOT BLAZE_USE_VCPKG
     OR NOT TARGET GDAL::GDAL)
    return()
  endif()

  _get_vcpkg_installed_dir(VCPKG_INSTALLED_DIR)
  if(NOT VCPKG_INSTALLED_DIR)
    return()
  endif()

  set(PROJ_DATA_DIR "${VCPKG_INSTALLED_DIR}/share/proj")
  if(NOT EXISTS "${PROJ_DATA_DIR}/proj.db")
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
  if(NOT WIN32
     OR NOT BLAZE_USE_VCPKG
     OR NOT TARGET GDAL::GDAL)
    return()
  endif()

  include(GNUInstallDirs)
  _get_vcpkg_installed_dir(VCPKG_INSTALLED_DIR)

  if(VCPKG_INSTALLED_DIR AND EXISTS "${VCPKG_INSTALLED_DIR}/share/proj/proj.db")
    install(
      DIRECTORY "${VCPKG_INSTALLED_DIR}/share/proj/"
      DESTINATION ${CMAKE_INSTALL_DATADIR}/proj
      FILES_MATCHING
      PATTERN "*.db"
      PATTERN "*.csv"
      PATTERN "*.json"
      PATTERN "*.sql"
      PATTERN "*.txt")
  endif()
endfunction()
