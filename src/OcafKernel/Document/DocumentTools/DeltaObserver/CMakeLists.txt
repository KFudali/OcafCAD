add_library(DeltaObserver INTERFACE)

target_link_libraries(DeltaObserver INTERFACE
    ${OpenCASCADE_LIBRARIES}
)

target_include_directories(DocumentDelta INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
)