
add_library(MeshCoreFixtures INTERFACE)

target_link_libraries(MeshCoreFixtures
    INTERFACE Tools
)

target_include_directories(MeshCoreFixtures
    INTERFACE ${TEST_DATA_PATH}
    INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_definitions(MeshCoreFixtures 
    INTERFACE TEST_DATA_DIR="${TEST_DATA_DIR}"
)