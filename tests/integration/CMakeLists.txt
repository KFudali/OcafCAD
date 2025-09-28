add_subdirectory(GeometryCore)

add_executable(itAll
    itRun.cpp
)

target_link_libraries(itAll PRIVATE
    itGeometryCoreLib
)

include(GoogleTest)
gtest_discover_tests(itAll)