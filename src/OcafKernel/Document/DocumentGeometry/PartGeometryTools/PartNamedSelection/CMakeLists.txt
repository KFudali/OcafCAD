add_library(PartNamedSelection
    PartNamedSelectionTool.cpp
    PartSubShapeNamedSelection.cpp
)

target_link_libraries(PartNamedSelection
    PUBLIC DocumentTools
)

target_include_directories(PartNamedSelection
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)