add_subdirectory(MeshPostprocessor)

add_library(utMeshEngine INTERFACE)

target_link_libraries(utMeshEngine INTERFACE
    utMeshPostprocessor
)