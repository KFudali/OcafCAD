add_library(IntegrationFixtures INTERFACE)

target_link_libraries(IntegrationFixtures INTERFACE
    GeometryCore
    MeshCore
    OcafKernelFixtures
    GeometryCoreFixtures
    MeshCoreFixtures
)

target_include_directories(IntegrationFixtures INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
)