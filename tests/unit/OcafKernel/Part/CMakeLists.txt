collect_unit_test_sources(${CMAKE_CURRENT_SOURCE_DIR} utPartSources)

add_library(utPart INTERFACE)

target_sources(utPart INTERFACE ${utPartSources})

target_link_libraries(utPart INTERFACE
    Part
    OcafKernelFixtures
    GTest::gtest_main
    GTest::gmock_main
)

target_include_directories(utPart INTERFACE
    ${ocafKernelFixturesDir}
)