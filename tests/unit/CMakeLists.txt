add_subdirectory(Tools)
add_subdirectory(GeometryCore)
add_subdirectory(OcafKernel)

add_executable(utAll
    utRun.cpp
)

target_link_libraries(utAll PRIVATE
    utToolsLib
    utOcafKernelLib
    utGeometryCoreLib
)

include(GoogleTest)
gtest_discover_tests(utAll)