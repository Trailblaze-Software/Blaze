target_sources(${UNIT_TESTS_NAME} PRIVATE test_process.cpp test_e2e.cpp)

target_compile_definitions(
  ${UNIT_TESTS_NAME}
  PRIVATE BLAZE_TEST_DATA_DIR="${CMAKE_CURRENT_SOURCE_DIR}/data")
