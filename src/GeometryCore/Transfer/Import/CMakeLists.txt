add_library(Import)

target_sources(Import 
    PUBLIC STEPImporter.cpp
)

target_link_libraries(Import
    PUBLIC Tools
    PUBLIC OcafKernel
)

target_include_directories(Import
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)