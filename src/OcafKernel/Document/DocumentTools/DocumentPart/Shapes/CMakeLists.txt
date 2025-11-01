add_subdirectory(SubShapes)

add_interface_library(Shapes
    LINK_LIBS ${OpenCASCADE_LIBRARIES} SubShapes
    INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}
)