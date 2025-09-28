add_library(GeometryObject
    GeometryObject.cpp
)


target_link_libraries(GeometryObject
    PUBLIC OcafKernel
    PUBLIC Tools
)

target_include_directories(GeometryObject
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)