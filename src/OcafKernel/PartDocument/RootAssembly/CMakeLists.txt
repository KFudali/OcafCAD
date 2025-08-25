add_library(RootAssembly)

target_sources(RootAssembly PRIVATE
    RootAssembly.cpp
)

target_link_libraries(RootAssembly
    PUBLIC PartDocTools
    PUBLIC ${OpenCASCADE_LIBRARIES}
)

target_include_directories(RootAssembly
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)