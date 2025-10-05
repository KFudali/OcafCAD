add_subdirectory(PartAttributes)

add_library(Part
    Part.cpp
    PartTools/PartAttributeTool.cpp
)

target_link_libraries(Part PUBLIC
    DocumentLabels
    PartAttributes
    PartPrototype
)

target_include_directories(Part PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/PartTools
    ${CMAKE_CURRENT_SOURCE_DIR}
)