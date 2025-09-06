collect_unit_test_sources(${CMAKE_CURRENT_SOURCE_DIR} utDocumentCommandsSources)

add_library(utDocumentCommands INTERFACE)
target_sources(utDocumentCommands INTERFACE 
    ${utDocumentCommandsSources}
)

target_link_libraries(utDocumentCommands INTERFACE
    OcafKernelFixtures
    DocumentCommands
    GTest::gtest_main
    GTest::gmock_main
)