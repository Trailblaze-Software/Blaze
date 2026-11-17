target_sources(${LIBRARY_NAME} PRIVATE crs_self_check.cpp)

target_sources(${UNIT_TESTS_NAME} PRIVATE tests/test_las_point.cpp
                                          tests/test_las_file.cpp)
