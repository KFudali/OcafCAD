add_library(GeometryPart
    GeometryPart.cpp
)

target_link_libraries(GeometryPart 
    PUBLIC DocumentTools
)

target_include_directories(GeometryPart PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)