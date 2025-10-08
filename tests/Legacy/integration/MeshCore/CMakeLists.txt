add_subdirectory(NetgenMeshEngine)

add_library(itMeshCoreLib INTERFACE)
target_sources(itMeshCoreLib INTERFACE ${itMeshCoreSources})

target_link_libraries(itMeshCoreLib INTERFACE
    itNetgenMeshEngine
    MeshCore
    GTest::gmock_main
)
target_compile_definitions(itMeshCoreLib INTERFACE
    TEST_DATA_DIR="${testDataDir}"
)

add_executable(itMeshCore
    runMeshCore.cpp
)
target_link_libraries(itMeshCore PRIVATE
    itMeshCoreLib
)