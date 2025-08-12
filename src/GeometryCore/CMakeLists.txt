add_library(GeometryCore
    GeometryCore.cpp
)

target_link_libraries(GeometryCore PUBLIC
    ${OpenCASCADE_LIBRARIES}
    OcafKernel
    Tools
)

target_include_directories(GeometryCore PRIVATE
    ${BOOST_DIR}
)