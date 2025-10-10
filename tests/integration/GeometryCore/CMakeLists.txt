add_subdirectory(Transfer)

add_library(itGeometryCore INTERFACE)
target_link_libraries(itGeometryCore INTERFACE
    itGeometryCoreTransfer 
    GTest::gmock_main
)
target_include_directories(itGeometryCore INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

add_executable(itGeometryCoreRun
    itRunGeometryCore.cpp
)
target_link_libraries(itGeometryCoreRun
    PRIVATE itGeometryCore
)

include(GoogleTest)
gtest_discover_tests(itGeometryCoreRun)