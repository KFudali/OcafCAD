collect_unit_test_sources(${CMAKE_CURRENT_SOURCE_DIR} utMeshObjectSources)

add_library(utMeshObject INTERFACE)
target_sources(utMeshObject INTERFACE 
    ${utMeshObjectSources}
)

target_link_libraries(utMeshObject INTERFACE
    MeshObject
    MeshCoreFixtures
    OcafKernelFixtures
    GTest::gmock_main
)