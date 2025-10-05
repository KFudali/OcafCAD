add_library(PrototypeRegistry)

target_sources(PrototypeRegistry PRIVATE
    PrototypeRegistry.cpp
)

target_link_libraries(PrototypeRegistry
    PUBLIC PartDocTools
    PRIVATE RootAssembly
)

target_include_directories(PrototypeRegistry
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)