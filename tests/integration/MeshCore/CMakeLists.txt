add_subdirectory(MeshInput)
add_library(itMeshCore INTERFACE)

target_link_libraries(itMeshCore INTERFACE
    itMeshInput
)

target_link_directories(itMeshCore
    INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
)

add_executable(itMeshCoreRun
    itRunMeshCore.cpp
)
target_link_libraries(itMeshCoreRun
    PRIVATE itMeshCore
)

include(GoogleTest)
gtest_discover_tests(itMeshCoreRun)