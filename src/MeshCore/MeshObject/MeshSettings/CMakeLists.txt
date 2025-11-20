add_library(MeshSettings INTERFACE)

target_link_libraries(MeshSettings INTERFACE
    GeometryObject
    ${Netgen_LIBRARIES}
)

target_include_directories(MeshSettings INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
)