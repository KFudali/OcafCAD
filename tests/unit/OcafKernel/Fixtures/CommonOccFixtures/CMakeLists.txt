add_library(CommonOccFixtures
    StubAttribute.cpp
)

target_include_directories(CommonOccFixtures
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(CommonOccFixtures
    PUBLIC
        ${OpenCASCADE_LIBRARIES}
)
