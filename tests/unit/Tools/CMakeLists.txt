add_subdirectory(MathUtils)
add_subdirectory(Messaging)
add_subdirectory(OccTools)
add_subdirectory(Progress)

add_executable(utTools
    utRunTools.cpp
)

target_link_libraries(utTools PRIVATE
    utMathUtils
    utMessaging
    utOccTools
    utProgress
    GTest::gtest_main
    GTest::gmock_main
)

target_compile_definitions(utTools PRIVATE
    TEST_DATA_DIR="${testDataDir}"
)

include(GoogleTest)
gtest_discover_tests(utTools)