add_subdirectory(OcafPartTools)
add_library(PartTools INTERFACE)

target_link_libraries(PartTools INTERFACE
    PartAttributes
)

target_include_directories(PartTools
    INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
)