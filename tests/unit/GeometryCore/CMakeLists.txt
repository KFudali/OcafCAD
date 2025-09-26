add_subdirectory(Fixtures)
add_subdirectory(Transfer)

add_library(utGeometryCoreLib INTERFACE)

target_link_libraries(utGeometryCoreLib INTERFACE
    GeometryCore
    utTransfer
    
    GTest::gmock_main
)

target_compile_definitions(utGeometryCoreLib INTERFACE
    TEST_DATA_DIR="${testDataDir}"
)

add_executable(utGeometryCore
    utRunGeometryCore.cpp
)
target_link_libraries(utGeometryCore
    PRIVATE utGeometryCoreLib
)

include(GoogleTest)
gtest_discover_tests(utGeometryCore)