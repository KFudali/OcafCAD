add_subdirectory(Fixtures)

add_subdirectory(CommandStack)
add_subdirectory(Document)
add_subdirectory(Events)

add_library(utOcafKernel INTERFACE)
target_link_libraries(utOcafKernel INTERFACE
    utCommandStack
    utDocument
    utOcafKernelEvents
    GTest::gmock_main
)

target_compile_definitions(utOcafKernel INTERFACE
    TEST_DATA_DIR="${testDataDir}"
)

add_executable(utOcafKernelRun
    utRunOcafKernel.cpp
)
target_link_libraries(utOcafKernelRun 
    PRIVATE utOcafKernel
)

include(GoogleTest)
gtest_discover_tests(utOcafKernelRun)