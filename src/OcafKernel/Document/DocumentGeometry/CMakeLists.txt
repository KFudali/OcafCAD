add_subdirectory(GeometryDocImporter)
add_subdirectory(GeometryPart)
add_subdirectory(PrototypeRegistry)
add_subdirectory(RootAssembly)

add_library(DocumentGeometryCore
    DocumentGeometry.cpp 
)

target_link_libraries(DocumentGeometryCore PUBLIC
    GeometryPart
    PrototypeRegistry
    RootAssembly
)

target_include_directories(DocumentGeometryCore PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

add_library(DocumentGeometry INTERFACE)
target_link_libraries(DocumentGeometry INTERFACE
    DocumentGeometry
    GeometryDocImporter
)