add_subdirectory(Fixtures)

add_subdirectory(GeometryCore)
add_subdirectory(MeshCore)

add_executable(itAll
    itRun.cpp
)

target_link_libraries(itAll PRIVATE
    itGeometryCoreLib
    itMeshCoreLib
)

include(GoogleTest)
gtest_discover_tests(itAll)