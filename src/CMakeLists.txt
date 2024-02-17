target_sources(${EXECUTABLE_NAME} PRIVATE blaze.cpp)
target_sources(${UNIT_TESTS_NAME} PRIVATE unit_tests.cpp)

add_subdirectory(lib)
