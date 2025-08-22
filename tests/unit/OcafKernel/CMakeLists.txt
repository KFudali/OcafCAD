add_subdirectory(Part)
add_subdirectory(Fixtures)
add_executable(utOcafKernel
    utRunOcafKernel.cpp
)

target_link_libraries(utOcafKernel PRIVATE
    OcafKernel
    utPart
    GTest::gtest_main
    GTest::gmock_main
)


target_compile_definitions(utOcafKernel PRIVATE
    TEST_DATA_DIR="${testDataDir}"
)

include(GoogleTest)
gtest_discover_tests(utOcafKernel)