add_subdirectory(Fixtures)
add_subdirectory(PartDocument)
add_subdirectory(OcafKernelMessaging)
add_subdirectory(DocumentCommands)
add_subdirectory(DocumentImport)

add_library(utOcafKernelLib INTERFACE)
target_link_libraries(utOcafKernelLib INTERFACE
    utPart
    utOcafKernelMessaging
    utDocumentCommands
    utDocumentImport
    GTest::gmock_main
)

target_compile_definitions(utOcafKernelLib INTERFACE
    TEST_DATA_DIR="${testDataDir}"
)

add_executable(utOcafKernel
    utRunOcafKernel.cpp
)
target_link_libraries(utOcafKernel 
    PRIVATE utOcafKernelLib
)

include(GoogleTest)
gtest_discover_tests(utOcafKernel)