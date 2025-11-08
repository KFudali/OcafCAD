add_library(IntegrationFixtures INTERFACE)

target_link_libraries(IntegrationFixtures
    INTERFACE OcafKernel
    INTERFACE GeometryCore
    INTERFACE MeshCore

    INTERFACE OcafKernelFixtures

    INTERFACE Tools
    INTERFACE GTest::gmock_main
)

target_include_directories(IntegrationFixtures
    INTERFACE ${TEST_DATA_PATH}
    INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/Mocks
    INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/Stubs
    INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_definitions(IntegrationFixtures 
    INTERFACE TEST_DATA_DIR="${TEST_DATA_DIR}"
)