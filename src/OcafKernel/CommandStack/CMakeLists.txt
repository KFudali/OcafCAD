add_library(CommandStack
    CommandStack.cpp
    DeltaPublisher.cpp
)

target_link_libraries(CommandStack
    PUBLIC DocumentTools
)

target_include_directories(CommandStack
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)