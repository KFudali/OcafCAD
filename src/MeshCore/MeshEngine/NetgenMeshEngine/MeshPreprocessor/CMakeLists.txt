add_library(MeshPreprocessor
    MeshPreprocessor.cpp
    LocalSizePreprocessor.cpp 
    MeshInput.cpp
)

target_link_libraries(MeshPreprocessor
    PUBLIC MeshObject
    PRIVATE ${Netgen_LIBRARIES}
)

target_include_directories(MeshPreprocessor
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Domains
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/MeshSettings
)