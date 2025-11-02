add_subdirectory(NamedSelection)

add_library(PartGeometryTools
    PartNamedSelectionTool.cpp
)

target_link_libraries(PartGeometryTools
    PUBLIC DocumentTools
    PUBLIC GeometryNamedSelection
)

target_include_directories(PartGeometryTools
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)