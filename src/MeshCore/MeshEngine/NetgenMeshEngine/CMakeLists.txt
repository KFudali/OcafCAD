add_subdirectory(MeshPreprocessor)
add_subdirectory(MeshingLauncher)
add_subdirectory(MeshPostprocessor)

add_library(NetgenMeshEngine
    NetgenMeshEngine.cpp
    NetgenToVTK.cpp
)

target_link_libraries(NetgenMeshEngine
    PUBLIC AbstractMeshEngine
    PUBLIC MeshPreprocessor
    PUBLIC MeshPostprocessor
    PUBLIC MeshingLauncher
    PRIVATE ${Netgen_LIBRARIES}
    PRIVATE ${VTK_LIBRARIES}
)

target_include_directories(NetgenMeshEngine
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)