add_subdirectory(GeometryDocImporter)
add_subdirectory(PartGeometryTools)
add_subdirectory(ShapeRegistry)
add_subdirectory(RootAssembly)

add_library(DocumentGeometryCore
    DocumentGeometry.cpp 
)

target_link_libraries(DocumentGeometryCore PUBLIC
    PartGeometryTools
    ShapeRegistry
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