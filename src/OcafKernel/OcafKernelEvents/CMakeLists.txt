add_library(OcafKernelEvents INTERFACE)

target_link_libraries(OcafKernelEvents
    INTERFACE PartDocTools
    INTERFACE Tools
)

target_include_directories(OcafKernelEvents
    INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
    INTERFACE ${BOOST_DIR}
)