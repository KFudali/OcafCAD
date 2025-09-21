add_library(OccTools
    OccProgressIndicator.cpp
)

target_link_libraries(OccTools
    PUBLIC ${OpenCASCADE_LIBRARIES}
    PUBLIC FileUtils
    PUBLIC MathUtils
    PUBLIC Progress
)

target_include_directories(OccTools
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)