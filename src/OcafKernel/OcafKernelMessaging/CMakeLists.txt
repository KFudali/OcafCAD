add_subdirectory(OcafKernelEvents)

add_library(OcafKernelMessaging
    SignalOcafKernelPublisher.cpp
)

target_link_libraries(OcafKernelMessaging
    PUBLIC PartDocTools
    PUBLIC OcafKernelEvents
    PUBLIC Tools
)

target_include_directories(OcafKernelMessaging
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)