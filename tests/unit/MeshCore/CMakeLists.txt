add_subdirectory(MeshObject)
add_subdirectory(MeshEngine)
add_subdirectory(Fixtures)

add_library(utMeshCore INTERFACE)

target_link_libraries(utMeshCore INTERFACE
    utMeshObject
    utMeshEngine
    utMeshPostprocessor
    GTest::gmock_main
)

target_compile_definitions(utMeshCore INTERFACE
    TEST_DATA_DIR="${testDataDir}"
)

add_executable(utMeshCoreRun
    utRunMeshCore.cpp
)
target_link_libraries(utMeshCoreRun
    PRIVATE utMeshCore
)

include(GoogleTest)
gtest_discover_tests(utMeshCoreRun)