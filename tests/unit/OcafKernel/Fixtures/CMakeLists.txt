add_subdirectory(CommonOccFixtures)
add_subdirectory(DocumentFixtures)

add_library(OcafKernelFixtures INTERFACE)

target_link_libraries(OcafKernelFixtures INTERFACE
    CommonOccFixtures
    DocumentFixtures
)

target_include_directories(OcafKernelFixtures INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
)