add_subdirectory(DocumentGeometry)
add_subdirectory(DocumentMesh)
add_subdirectory(DocumentTools)
add_subdirectory(DocumentPart)

add_library(utDocument INTERFACE)

target_link_libraries(utDocument INTERFACE
    # utDocumentGeometry
    utDocumentPart
    utDocumentTools
)

