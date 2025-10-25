add_library(GeometryNamedSelection
    GeometryNamedSelection.cpp
    GeometryNamedSelectionAttribute.cpp
)

target_link_libraries(GeometryNamedSelection
    PUBLIC DocumentTools
)

target_include_directories(GeometryNamedSelection
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)