add_subdirectory(Fixtures)
add_subdirectory(PartDocument)
add_subdirectory(OcafKernelMessaging)
add_subdirectory(DocumentCommands)
add_subdirectory(DocumentImport)

add_executable(utOcafKernel
    utRunOcafKernel.cpp
)

target_link_libraries(utOcafKernel PRIVATE
    utPart
    utOcafKernelMessaging
    utDocumentCommands
    utDocumentImport
    GTest::gtest_main
    GTest::gmock_main
)

target_compile_definitions(utOcafKernel PRIVATE
    TEST_DATA_DIR="${testDataDir}"
)

include(GoogleTest)
gtest_discover_tests(utOcafKernel)