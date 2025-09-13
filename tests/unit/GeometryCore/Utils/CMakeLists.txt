collect_unit_test_sources(${CMAKE_CURRENT_SOURCE_DIR} utUtils)

add_library(utUtils INTERFACE)
target_sources(utUtils INTERFACE 
    ${utUtilsSources}
)

target_link_libraries(utUtils INTERFACE
    Utils
    OcafKernelFixtures
    GTest::gtest_main
    GTest::gmock_main
)