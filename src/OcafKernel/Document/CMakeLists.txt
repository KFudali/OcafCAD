add_subdirectory(DocumentGeometry)
add_subdirectory(DocumentMesh)
add_subdirectory(DocumentTools)

add_library(Document 
    MainDocument.cpp
)

target_link_libraries(Document PUBLIC
    ${OpenCASCADE_LIBRARIES}
    DocumentGeometry
    DocumentMesh
    DocumentTools
)

target_include_directories(Document PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)