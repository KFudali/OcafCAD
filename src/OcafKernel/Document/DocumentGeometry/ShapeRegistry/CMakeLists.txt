add_library(ShapeRegistry)

target_sources(ShapeRegistry PRIVATE
    ShapeRegistry.cpp
)

target_link_libraries(ShapeRegistry
    PUBLIC DocumentTools
    PRIVATE RootAssembly
)

target_include_directories(ShapeRegistry
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)