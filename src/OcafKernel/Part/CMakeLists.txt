add_subdirectory(PartAttributes)
add_subdirectory(PartLabel)
add_subdirectory(PartTools)

add_library(Part
    Part.cpp
)

target_link_libraries(Part 
    PUBLIC PartTools
    PUBLIC PartLabel
    PUBLIC PartAttributes
    PRIVATE OcafPartTools
    PRIVATE ${OpenCASCADE_LIBRARIES}
)

target_include_directories(Part PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${BOOST_DIR}
)