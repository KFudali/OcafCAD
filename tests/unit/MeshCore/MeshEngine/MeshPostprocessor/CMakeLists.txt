collect_unit_test_sources(${CMAKE_CURRENT_SOURCE_DIR} utMeshPostprocessorSources)

add_library(utMeshPostprocessor INTERFACE)
target_sources(utMeshPostprocessor INTERFACE 
    ${utMeshPostprocessorSources}
)

target_link_libraries(utMeshPostprocessor INTERFACE
    MeshPostprocessor
    MeshCoreFixtures
    GTest::gmock_main
)