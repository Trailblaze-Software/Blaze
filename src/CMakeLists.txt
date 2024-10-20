target_sources(${CLI_EXE_NAME} PRIVATE blaze.cpp)
target_sources(${LIBRARY_NAME} PRIVATE run.cpp process.cpp)
target_sources(${UNIT_TESTS_NAME} PRIVATE unit_tests.cpp)

add_subdirectory(lib)
add_subdirectory(methods)
add_subdirectory(gui)
