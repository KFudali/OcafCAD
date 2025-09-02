collect_unit_test_sources(${CMAKE_CURRENT_SOURCE_DIR} utOcafKernelMessagingSources)

add_library(utOcafKernelMessaging INTERFACE)
target_sources(utOcafKernelMessaging INTERFACE 
    ${utOcafKernelMessagingSources}
)

target_link_libraries(utOcafKernelMessaging INTERFACE
    OcafKernelMessaging
    OcafKernelFixtures
    GTest::gtest_main
    GTest::gmock_main
)