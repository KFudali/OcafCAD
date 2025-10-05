add_subdirectory(PartTools)

add_library(Part
    Part.cpp
)

target_link_libraries(Part 
    PUBLIC PartDocTools
    PUBLIC PartTools
    PRIVATE OcafPartTools
    PRIVATE ${OpenCASCADE_LIBRARIES}
)

target_include_directories(Part PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${BOOST_DIR}
)