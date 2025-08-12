collect_unit_test_sources(${CMAKE_CURRENT_SOURCE_DIR} utMessagingSources)

add_library(utMessaging INTERFACE)

target_sources(utMessaging INTERFACE ${utMessagingSources})

target_link_libraries(utMessaging INTERFACE
    Messaging
    GTest::gtest_main
    GTest::gmock_main
)