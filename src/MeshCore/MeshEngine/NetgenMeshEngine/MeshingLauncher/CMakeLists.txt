add_library(MeshingLauncher
    MeshingLauncher.cpp
)

target_link_libraries(MeshingLauncher
    PUBLIC MeshObject
    PUBLIC MeshPreprocessor
    PUBLIC Tools
    PRIVATE ${Netgen_LIBRARIES}
)

target_include_directories(MeshingLauncher
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)