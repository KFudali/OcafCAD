add_library(DocumentCommands
    DocCommandStack.cpp
    DeltaPublisher.cpp
)

target_link_libraries(DocumentCommands
    PUBLIC DocumentTools
)

target_include_directories(DocumentCommands
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)