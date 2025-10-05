add_subdirectory(DocGeometryEvents)
add_subdirectory(GeometryDocImporter)
add_subdirectory(GeometryPart)
add_subdirectory(PrototypeRegistry)
add_subdirectory(RootAssembly)

add_library(DocumentGeometry
    DocumentGeometry.cpp 
)

target_link_libraries(DocumentGeometry PUBLIC
    DocGeometryEvents
    GeometryDocImporter
    GeometryPart
    PrototypeRegistry
    RootAssembly
)

target_include_directories(DocumentGeometry PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)