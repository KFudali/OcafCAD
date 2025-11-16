add_library(MeshPostprocessor
    MeshPostprocessor.cpp
)

target_link_libraries(MeshPostprocessor
    MeshObject
    MeshPreprocessor
    Tools
    ${Netgen_LIBRARIES}
)

target_include_directories(MeshPostprocessor
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)