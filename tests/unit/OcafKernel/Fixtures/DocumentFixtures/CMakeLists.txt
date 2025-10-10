add_library(DocumentFixtures INTERFACE)

target_link_libraries(DocumentFixtures INTERFACE
    CommonOccFixtures
    ToolsFixtures
    Document
)

target_include_directories(DocumentFixtures INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
)