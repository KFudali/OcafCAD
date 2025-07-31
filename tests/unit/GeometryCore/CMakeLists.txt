collect_unit_test_sources(${CMAKE_CURRENT_SOURCE_DIR}/Part utPartSrc)

add_executable(utGeometryCore
    utGeometryCore.cpp
    ${utPartSrc}
)

target_link_libraries(utGeometryCore PRIVATE
    GeometryCore
    GTest::gmock_main
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(utGeometryCore)