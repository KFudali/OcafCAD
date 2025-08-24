add_subdirectory(Part)
add_subdirectory(PartDocTools)
add_subdirectory(PrototypeRegistry)
add_subdirectory(RootAssembly)

target_sources(PartDocument PRIVATE
    PartDocument.cpp
)

target_link_libraries(PartDocument 
    PUBLIC Part
    PUBLIC PartDocTools
    PRIVATE ${OpenCASCADE_LIBRARIES}
)

target_include_directories(PartDocument
    PRIVATE ${BOOST_DIR}
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)