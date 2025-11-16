add_subdirectory(Mesh)
add_subdirectory(MeshSettings)

add_library(MeshObject
    MeshObject.cpp
)

target_link_libraries(MeshObject
    PUBLIC Mesh
    PUBLIC MeshSettings
    PUBLIC GeometryObject
    PUBLIC ${Netgen_LIBRARIES}
    PUBLIC ${VTK_LIBRARIES}
)

target_include_directories(MeshObject
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)