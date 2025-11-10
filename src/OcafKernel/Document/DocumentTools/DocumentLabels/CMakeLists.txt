add_subdirectory(DocLabel)
add_subdirectory(PartLabel)
add_subdirectory(RefLabels)

add_interface_library(DocumentLabels
    LINK_LIBS ${OpenCASCADE_LIBRARIES} DocLabel PartLabel RefLabels
    INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}
)