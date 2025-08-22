add_library(OcafPartTools)

target_sources(OcafPartTools
    PUBLIC PartAssemblyTool.cpp
    PUBLIC PartAttributeTool.cpp
    PUBLIC PartGeometryTool.cpp
)

target_link_libraries(OcafPartTools
    PUBLIC PartAttributes
    PUBLIC PartLabel
    PUBLIC ${OpenCASCADE_LIBRARIES}
)

target_include_directories(OcafPartTools
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..
)