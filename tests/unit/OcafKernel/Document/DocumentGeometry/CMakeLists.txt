add_ut_library(utDocumentGeometry
    SOURCE_DIRS
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/GeometryPart
    LINK_LIBS
        DocumentGeometry
        OcafKernelFixtures
)