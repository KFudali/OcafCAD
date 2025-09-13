add_library(Utils INTERFACE)

target_link_libraries(Utils
    INTERFACE Tools
    INTERFACE OcafKernel
)

target_include_directories(Utils
    INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
)