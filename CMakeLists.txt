cmake_minimum_required(VERSION 3.20)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(OcafCAD)

option(BUILD_TESTS "Build the tests" ON)

include(cmake/find_dependencies.cmake)
include(cmake/include_utils.cmake)

add_subdirectory(src)
if(BUILD_TESTS)
    enable_testing()
    include(cmake/include_testutils.cmake)
    add_subdirectory(tests)
endif()