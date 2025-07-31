cmake_minimum_required(VERSION 3.20)
project(OcafCAD)

option(BUILD_TESTS "Build the tests" ON)

include(cmake/find_vtk.cmake)
include(cmake/find_occt.cmake)
include(cmake/find_boost.cmake)
include(cmake/find_gtest.cmake)

add_subdirectory(src)
if(BUILD_TESTS)
    enable_testing()
    include(cmake/collect_test_sources.cmake)
    add_subdirectory(tests)
endif()