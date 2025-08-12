add_subdirectory(Messaging)

add_executable(utTools
    utRunTools.cpp
)

target_link_libraries(utTools PRIVATE
    utMessaging 
    GTest::gtest_main
    GTest::gmock_main
)

target_compile_definitions(utTools PRIVATE
    TEST_DATA_DIR="${testDataDir}"
)

include(GoogleTest)
gtest_discover_tests(utTools)