add_subdirectory(Part)

add_library(OcafKernel
    OcafKernel.cpp
)

target_link_libraries(OcafKernel
    PRIVATE ${OpenCASCADE_Libraries}
    PUBLIC ${Tools}
    PUBLIC ${Part}
)

target_include_directories(OcafKernel
    PRIVATE ${BOOST_DIR}
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)