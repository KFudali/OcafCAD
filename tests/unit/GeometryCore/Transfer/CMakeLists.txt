collect_unit_test_sources(${CMAKE_CURRENT_SOURCE_DIR} utTransferSources)

add_library(utTransfer INTERFACE)
target_sources(utTransfer INTERFACE 
    ${utTransferSources}
)

target_link_libraries(utTransfer INTERFACE
    Transfer
    GeometryCoreFixtures
    OcafKernelFixtures
    GTest::gtest_main
    GTest::gmock_main
)