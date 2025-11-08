add_subdirectory(NetgenMeshEngine)
add_subdirectory(GmshMeshEngine)

add_library(MeshEngine INTERFACE)

target_link_libraries(MeshEngine
    INTERFACE NetgenMeshEngine
    INTERFACE MeshObject
    INTERFACE Tools
)

target_include_directories(MeshEngine
    INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
)