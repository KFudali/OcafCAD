add_library(PartLabel
    PartLabel.cpp
    ShapeLabel.cpp
    SubShapeLabel.cpp
)

target_link_libraries(PartLabel PUBLIC
    DocLabel
)

target_include_directories(PartLabel PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)