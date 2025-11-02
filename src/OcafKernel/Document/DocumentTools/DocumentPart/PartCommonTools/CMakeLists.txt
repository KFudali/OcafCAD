add_library(PartCommonTools
    PartAttributeTool.cpp
    PartAssemblyTool.cpp
    PartSubShapeTool.cpp
    PartShapeTool.cpp
)

target_link_libraries(PartCommonTools
    PUBLIC DocumentLabels
    PUBLIC PartAttributes
    PUBLIC Shapes
)

target_include_directories(PartCommonTools
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)