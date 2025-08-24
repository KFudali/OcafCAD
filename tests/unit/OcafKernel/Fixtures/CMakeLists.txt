add_library(OcafKernelFixtures INTERFACE)

target_link_libraries(OcafKernelFixtures INTERFACE
   OcafKernel
)

target_include_directories(OcafKernelFixtures INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
)