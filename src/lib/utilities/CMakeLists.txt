target_sources(
  ${LIBRARY_NAME} PRIVATE progress_tracker.cpp
                          tests/progress_tracker_helper.cpp resources.cpp)

target_sources(${UNIT_TESTS_NAME} PRIVATE tests/test_progress_tracker.cpp)
