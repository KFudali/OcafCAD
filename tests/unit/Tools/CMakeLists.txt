add_subdirectory(MathUtils)
add_subdirectory(Messaging)
add_subdirectory(OccTools)
add_subdirectory(Progress)

add_library(utToolsLib INTERFACE)

target_link_libraries(utToolsLib INTERFACE
    utMathUtils
    utMessaging
    utOccTools
    utProgress
    
    GTest::gmock_main
)

target_compile_definitions(utToolsLib INTERFACE
    TEST_DATA_DIR="${testDataDir}"
)

add_executable(utTools
    utRunTools.cpp
)

target_link_libraries(utTools PRIVATE
    utToolsLib
)

include(GoogleTest)
gtest_discover_tests(utTools)