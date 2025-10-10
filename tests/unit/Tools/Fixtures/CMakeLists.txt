add_library(ToolsFixtures INTERFACE)

target_link_libraries(ToolsFixtures INTERFACE
    Tools
)

target_include_directories(ToolsFixtures INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
)