add_subdirectory(Part)
# add_subdirectory(PartDocument)

add_library(OcafKernel
    OcafKernel.cpp
)

target_link_libraries(OcafKernel
    PRIVATE ${OpenCASCADE_LIBRARIES}
    PUBLIC ${Tools}
    PUBLIC ${Part}
)

target_include_directories(OcafKernel
    PRIVATE ${BOOST_DIR}
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)