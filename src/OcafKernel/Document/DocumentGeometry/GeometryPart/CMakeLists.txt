add_subdirectory(GeometryNamedSelection)

add_library(GeometryPart
    GeometryPart.cpp
)

target_link_libraries(GeometryPart 
    PUBLIC DocumentTools
    PUBLIC GeometryNamedSelection
)

target_include_directories(GeometryPart PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)