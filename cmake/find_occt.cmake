
set(OpenCASCADE_DIR "" CACHE PATH "Path to dir containing OpenCASCADEConfig.cmake")

find_package(OpenCASCADE REQUIRED CONFIG)
message( STATUS "OpenCASCADE found version: ${OpenCASCADE_VERSION}" )
if ( NOT OpenCASCADE_FOUND )
    message(FATAL_ERROR "Could not find OpenCASCADE.")
    return()
endif()
