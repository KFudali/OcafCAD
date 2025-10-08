collect_integration_test_sources(${CMAKE_CURRENT_SOURCE_DIR} itNetgenMeshEngineSources)

add_library(itNetgenMeshEngine INTERFACE)
target_sources(itNetgenMeshEngine INTERFACE 
    ${itNetgenMeshEngineSources}
)

target_link_libraries(itNetgenMeshEngine INTERFACE
    NetgenMeshEngine 
    IntegrationFixtures
    GTest::gmock_main
)