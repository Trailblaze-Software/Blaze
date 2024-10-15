target_sources(${EXECUTABLE_NAME} PRIVATE blaze.cpp process.cpp)
target_sources(${UNIT_TESTS_NAME} PRIVATE unit_tests.cpp)

add_subdirectory(lib)
add_subdirectory(methods)
