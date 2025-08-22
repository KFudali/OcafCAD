add_library(PartLabel
    PartLabel.cpp
)

target_link_libraries(PartLabel
    PUBLIC ${OpenCASCADE_LIBRARIES}
)

target_include_directories(PartLabel
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)