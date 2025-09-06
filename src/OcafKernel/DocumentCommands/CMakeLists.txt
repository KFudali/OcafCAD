add_subdirectory(DocumentDeltaObserver)

add_library(DocumentCommands
    DocCommandStack.cpp
)

target_link_libraries(DocumentCommands
    PUBLIC PartDocument
    PUBLIC DocumentDeltaObserver
    PUBLIC Tools
)

target_include_directories(DocumentCommands
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)