add_library(DocumentDeltaObserver
    PublisherDeltaObserver.cpp
)

target_link_libraries(DocumentDeltaObserver
    PUBLIC OcafKernelMessaging
    PUBLIC PartDocument
    PUBLIC Tools
)

target_include_directories(DocumentDeltaObserver
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)