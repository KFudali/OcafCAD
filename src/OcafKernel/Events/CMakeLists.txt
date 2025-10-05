add_subdirectory(DeltaEvents)
add_library(OcafKernelEvents INTERFACE)

target_link_libraries(OcafKernelEvents
    INTERFACE DeltaEvents
)

target_include_directories(OcafKernelEvents
    INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
)

add_subdirectory(DocumentDeltaObservers)