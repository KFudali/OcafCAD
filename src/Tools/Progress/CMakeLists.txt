add_library(Progress
    EventProgressPublisher.cpp  
    ProgressRange.cpp
)

target_link_libraries(Progress
    PUBLIC Messaging
    PUBLIC MathUtils
)

target_include_directories(Progress
    PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}
)