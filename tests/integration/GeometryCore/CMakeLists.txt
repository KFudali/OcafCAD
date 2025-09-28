collect_integration_test_sources(${CMAKE_CURRENT_SOURCE_DIR} itGeometryCoreSources)

add_library(itGeometryCoreLib INTERFACE)
target_sources(itGeometryCoreLib INTERFACE ${itGeometryCoreSources})

target_link_libraries(itGeometryCoreLib INTERFACE
    GeometryCore
    GTest::gmock_main
)
target_compile_definitions(itGeometryCoreLib INTERFACE
    TEST_DATA_DIR="${testDataDir}"
)

add_executable(itGeometryCore
    runGeometryCore.cpp
)
target_link_libraries(itGeometryCore PRIVATE itGeometryCoreLib)
