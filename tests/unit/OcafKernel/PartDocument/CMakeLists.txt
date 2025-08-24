collect_unit_test_sources(${CMAKE_CURRENT_SOURCE_DIR} utPartDocumentSources)
collect_unit_test_sources(${CMAKE_CURRENT_SOURCE_DIR}/Part utPartSources)

add_library(utPart INTERFACE)
target_sources(utPart INTERFACE 
    ${utPartDocumentSources}
    ${utPartSources}
)

target_link_libraries(utPart INTERFACE
    PartDocument
    OcafKernelFixtures
    GTest::gtest_main
    GTest::gmock_main
)