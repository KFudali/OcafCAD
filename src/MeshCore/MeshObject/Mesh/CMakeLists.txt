add_subdirectory(MeshComponents)
add_subdirectory(MeshDomains)

add_library(Mesh INTERFACE)

target_link_libraries(Mesh INTERFACE
    Tools
    OcafKernel
    MeshDomains
    MeshComponents
)

target_include_directories(Mesh INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
)