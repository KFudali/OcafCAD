add_subdirectory(PartAttributes)
add_subdirectory(PartCommonTools)
add_subdirectory(Shapes)

add_library(DocumentPart
    Part.cpp
)

target_link_libraries(DocumentPart PUBLIC
    DocumentLabels
    PartAttributes
    PartCommonTools
    Shapes
)

target_include_directories(DocumentPart PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)