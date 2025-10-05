add_library(DeltaEvents INTERFACE)

target_link_libraries(DeltaEvents
    INTERFACE DocumentLabels
    INTERFACE Tools
)

target_include_directories(DeltaEvents INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/Geometry
    ${CMAKE_CURRENT_SOURCE_DIR}/Mesh
    ${CMAKE_CURRENT_SOURCE_DIR}
)