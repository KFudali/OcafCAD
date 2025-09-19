collect_unit_test_sources(${CMAKE_CURRENT_SOURCE_DIR} utDocumentImportSources)

add_library(utDocumentImport INTERFACE)
target_sources(utDocumentImport INTERFACE 
    ${utDocumentImportSources}
)

target_link_libraries(utDocumentImport INTERFACE
    OcafKernelFixtures
    DocumentImport
    GTest::gtest_main
    GTest::gmock_main
)