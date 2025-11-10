add_subdirectory(PartNamedSelection)

add_interface_library(PartGeometryTools
    LINK_LIBS PartNamedSelection
    INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}
)