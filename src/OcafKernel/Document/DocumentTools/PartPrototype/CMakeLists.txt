add_library(PartPrototype INTERFACE)

target_link_libraries(PartPrototype INTERFACE
    ${OpenCASCADE_LIBRARIES}
)

target_include_directories(PartPrototype INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
)