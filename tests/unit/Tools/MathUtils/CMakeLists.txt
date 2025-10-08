collect_unit_test_sources(${CMAKE_CURRENT_SOURCE_DIR} utMathUtilsSources)

add_library(utMathUtils INTERFACE)

target_sources(utMathUtils INTERFACE ${utMathUtilsSources})

target_link_libraries(utMathUtils INTERFACE
    MathUtils
    GTest::gmock_main
)