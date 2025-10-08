add_library(GeometryCoreFixtures INTERFACE)

target_link_libraries(GeometryCoreFixtures
    INTERFACE Tools
)

target_include_directories(GeometryCoreFixtures
    INTERFACE ${TEST_DATA_PATH}
    INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_definitions(GeometryCoreFixtures 
    INTERFACE TEST_DATA_DIR="${TEST_DATA_DIR}"
)