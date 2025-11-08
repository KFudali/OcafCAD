add_subdirectory(MeshPreprocessor)

add_library(NetgenMeshEngine
    NetgenMeshEngine.cpp
    NetgenToVTK.cpp
)

target_link_libraries(NetgenMeshEngine
    PUBLIC MeshEngine
    PUBLIC MeshPreprocessor
    PRIVATE ${Netgen_LIBRARIES}
)

target_include_directories(NetgenMeshEngine
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)