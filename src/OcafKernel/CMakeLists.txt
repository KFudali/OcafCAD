add_subdirectory(PartDocument)
add_subdirectory(OcafKernelEvents)

add_library(OcafKernel
    OcafKernel.cpp
)

target_link_libraries(OcafKernel
    PRIVATE ${OpenCASCADE_LIBRARIES}
    PUBLIC PartDocument
    PUBLIC OcafKernelEvents
    PUBLIC Tools
)

target_include_directories(OcafKernel
    PRIVATE ${BOOST_DIR}
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)