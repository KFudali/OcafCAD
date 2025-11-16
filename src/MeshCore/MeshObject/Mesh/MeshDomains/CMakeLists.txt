add_library(MeshDomains
    ShapeDomainDescription.cpp
)

target_link_libraries(MeshDomains
    OcafKernel
    Tools
)

target_include_directories(MeshDomains INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
)