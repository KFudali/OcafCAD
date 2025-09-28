add_library(View
    GeometryView.cpp
)

target_link_libraries(View PUBLIC
    OcafKernel
    Tools
    GeometryObject
)

target_include_directories(View PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)