add_subdirectory(DeltaObserver)
add_subdirectory(DocumentAttributes)
add_subdirectory(DocumentLabels)
add_subdirectory(DocumentPart)

add_library(DocumentTools INTERFACE)

target_link_libraries(DocumentTools INTERFACE
    DeltaObserver
    DocumentAttributes
    DocumentLabels
    DocumentPart
    Tools
)

target_include_directories(DocumentTools INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
)