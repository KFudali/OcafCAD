add_library(MeshPostprocessor
    MeshPostprocessor.cpp
    MeshExtractionUtils.cpp
    SurfaceExtraction.cpp
    VolumeExtraction.cpp
)

target_link_libraries(MeshPostprocessor PUBLIC
    MeshObject
    MeshPreprocessor
    Tools
    ${Netgen_LIBRARIES}
    ${VTK_LIBRARIES}
)

target_include_directories(MeshPostprocessor
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)