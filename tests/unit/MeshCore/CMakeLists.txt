add_subdirectory(MeshObject)
add_subdirectory(Fixtures)

add_library(utMeshCoreLib INTERFACE)

target_link_libraries(utMeshCoreLib INTERFACE
    MeshCore
    MeshCoreFixtures
    utMeshObject
    GTest::gmock_main
)

target_compile_definitions(utMeshCoreLib INTERFACE
    TEST_DATA_DIR="${testDataDir}"
)

add_executable(utMeshCore
    utRunMeshCore.cpp
)
target_link_libraries(utMeshCore
    PRIVATE utMeshCoreLib
)

include(GoogleTest)
gtest_discover_tests(utMeshCore)