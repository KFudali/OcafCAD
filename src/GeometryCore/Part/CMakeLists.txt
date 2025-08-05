add_library(Part
    Part.cpp
    PartLabelKey.cpp
)

target_link_libraries(Part PRIVATE
    ${OpenCASCADE_LIBRARIES}
)

target_include_directories(Part PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${BOOST_DIR}
)