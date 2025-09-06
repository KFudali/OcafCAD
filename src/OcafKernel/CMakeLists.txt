add_subdirectory(PartDocument)
add_subdirectory(OcafKernelMessaging)
add_subdirectory(DocumentCommands)

add_library(OcafKernel
    OcafKernel.cpp
)

target_link_libraries(OcafKernel
    PRIVATE ${OpenCASCADE_LIBRARIES}
    PUBLIC PartDocument
    PUBLIC DocumentCommands
    PUBLIC OcafKernelMessaging
    PUBLIC Tools
)

target_include_directories(OcafKernel
    PRIVATE ${BOOST_DIR}
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)