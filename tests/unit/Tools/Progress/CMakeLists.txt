collect_unit_test_sources(${CMAKE_CURRENT_SOURCE_DIR} utProgressSources)

add_library(utProgress INTERFACE)

target_sources(utProgress INTERFACE ${utProgressSources})

target_link_libraries(utProgress INTERFACE
    Progress
    
    GTest::gmock_main
)