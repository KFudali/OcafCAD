add_library(DocumentDeltaObservers
    GeometryDeltaObserver.cpp
)

target_link_libraries(DocumentDeltaObservers PUBLIC
    Tools
    DocumentTools
    DeltaEvents
)

target_include_directories(DocumentDeltaObservers PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)