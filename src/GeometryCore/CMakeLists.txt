add_subdirectory(Part)

add_library(GeometryCore
    GeometryCore.cpp
)

target_link_libraries(GeometryCore PRIVATE
    ${OpenCASCADE_LIBRARIES}
)

target_include_directories(GeometryCore PRIVATE
    ${BOOST_DIR}
)