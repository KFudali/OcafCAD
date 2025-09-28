add_library(GeometryEvents
    GeometryEventSource.cpp
)

target_link_libraries(GeometryEvents
    PUBLIC Tools
    PUBLIC OcafKernel
)

target_include_directories(GeometryEvents
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)