add_subdirectory(CommandStack)
add_subdirectory(Document)
add_subdirectory(Events)

add_library(OcafKernel
    OcafKernel.cpp
)

target_link_libraries(OcafKernel
    PUBLIC Tools
    PUBLIC CommandStack
    PUBLIC Document
    PUBLIC OcafKernelEvents
    PUBLIC DocumentDeltaObservers
)

target_include_directories(OcafKernel
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)