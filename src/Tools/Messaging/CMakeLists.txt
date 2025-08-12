add_library(Messaging
    SignalMessageBus.cpp
)

target_include_directories(Messaging
    PUBLIC ${BOOST_DIR}
    PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}
)