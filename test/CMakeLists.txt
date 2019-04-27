file(GLOB UNIT_TEST_SRC
    "*.cpp"
)

add_executable(
  unit_tests
  ${UNIT_TEST_SRC}
)

target_link_libraries(
  unit_tests
  gtest
  ${OUTPUT_LIB}
)

add_test(
  NAME
    unit
  COMMAND
    ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}/unit_tests
)