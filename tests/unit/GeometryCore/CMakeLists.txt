# add_subdirectory(Part)
add_executable(utGeometryCore
    utRunGeometryCore.cpp
)

target_link_libraries(utGeometryCore PRIVATE
    GeometryCore
    utPart
    GTest::gtest_main
    GTest::gmock_main
)

target_compile_definitions(utGeometryCore PRIVATE
    TEST_DATA_DIR="${testDataDir}"
)

include(GoogleTest)
gtest_discover_tests(utGeometryCore)