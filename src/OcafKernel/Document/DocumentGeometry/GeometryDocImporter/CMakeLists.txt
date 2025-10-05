add_library(DocumentImport)

target_sources(DocumentImport
    PUBLIC GeometryDocImporter.cpp
)

target_link_libraries(DocumentImport
    PUBLIC PartDocument
    PUBLIC Tools
    PRIVATE ${OpenCASCADE_LIBRARIES}
)

target_include_directories(DocumentImport
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)