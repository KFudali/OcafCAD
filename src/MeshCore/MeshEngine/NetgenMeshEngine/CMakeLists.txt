add_library(NetgenMeshEngine
    NetgenMeshEngine.cpp
)

target_link_libraries(NetgenMeshEngine
    PUBLIC MeshEngine
    PRIVATE ${Netgen_LIBRARIES}
)

target_include_directories(NetgenMeshEngine
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)