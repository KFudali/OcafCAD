add_subdirectory(Fixtures)
add_subdirectory(MathUtils)
add_subdirectory(Messaging)
add_subdirectory(OccTools)
add_subdirectory(Progress)

add_library(utTools INTERFACE)

target_link_libraries(utTools INTERFACE
    utMathUtils
    utMessaging
    utOccTools
    utProgress
    GTest::gmock_main
)

target_compile_definitions(utTools INTERFACE
    TEST_DATA_DIR="${testDataDir}"
)

add_executable(utToolsRun
    utRunTools.cpp
)

target_link_libraries(utToolsRun PRIVATE
    utToolsLib
)

include(GoogleTest)
gtest_discover_tests(utToolsRun)