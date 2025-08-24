add_subdirectory(DocLabels)
add_subdirectory(PartAttributes)

add_library(PartDocTools INTERFACE)

target_link_libraries(PartDocTools INTERFACE
    INTERFACE PartAttributes
    INTERFACE DocLabels
)

target_include_directories(PartDocTools INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
)