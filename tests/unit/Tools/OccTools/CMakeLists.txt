collect_unit_test_sources(${CMAKE_CURRENT_SOURCE_DIR} utOccToolsSources)

add_library(utOccTools INTERFACE)

target_sources(utOccTools INTERFACE ${utOccToolsSources})

target_link_libraries(utOccTools INTERFACE
    OccTools
    GTest::gtest_main
    GTest::gmock_main
)