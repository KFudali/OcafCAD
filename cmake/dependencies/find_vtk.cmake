set(VTK_DIR "" CACHE PATH "Path to dir containing vtk-config.cmake")

find_package(VTK REQUIRED CONFIG)
message( STATUS "VTK found version: ${VTK_VERSION}" )
if ( NOT VTK_FOUND )
    message(FATAL_ERROR "Could not find VTK.")
    return()
endif()