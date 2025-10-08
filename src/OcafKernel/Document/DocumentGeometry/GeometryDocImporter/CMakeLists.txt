add_library(GeometryDocImporter)

target_sources(GeometryDocImporter
    PUBLIC GeometryDocImporter.cpp
)

target_link_libraries(GeometryDocImporter PUBLIC
    DocumentGeometryCore
    DocumentTools
    Tools
)

target_include_directories(GeometryDocImporter
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)