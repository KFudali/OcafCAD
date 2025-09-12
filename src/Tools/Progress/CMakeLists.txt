add_library(Progress)

target_sources(Progress
    PUBLIC PublisherProgressScope.cpp
    PUBLIC EventProgressPublisher.cpp
)

target_link_libraries(Progress
    PUBLIC Messaging
)

target_include_directories(Progress
    PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}
)