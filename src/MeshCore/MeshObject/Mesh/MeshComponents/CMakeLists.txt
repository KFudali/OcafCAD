add_interface_library(MeshComponents
    LINK_LIBS ${VTK_LIBRARIES} Tools OcafKernel
    INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}
)