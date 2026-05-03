target_sources(${CLI_EXE_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/blaze.cpp)
target_sources(${LIBRARY_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/run.cpp
                                       ${CMAKE_CURRENT_SOURCE_DIR}/process.cpp)
target_sources(${UNIT_TESTS_NAME}
               PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/unit_tests.cpp)

add_subdirectory(lib)
add_subdirectory(methods)
add_subdirectory(tests)
if(NOT BLAZE_CLI_ONLY)
  add_subdirectory(gui)
endif()
