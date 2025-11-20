add_subdirectory(OcafKernel)
add_subdirectory(MeshCore)
add_subdirectory(Tools)

add_executable(utAll
    utRun.cpp
)

target_link_libraries(utAll PRIVATE
    utTools
    utOcafKernel
    utMeshCore
    GTest::gmock_main
)

include(GoogleTest)
gtest_discover_tests(utAll)