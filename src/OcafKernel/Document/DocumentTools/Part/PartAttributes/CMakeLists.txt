add_library(PartAttributes INTERFACE)

target_link_libraries(PartAttributes
    INTERFACE ${OpenCASCADE_LIBRARIES}
)

target_include_directories(PartAttributes
    INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
)