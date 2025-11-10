add_subdirectory(LabelMarkerAttributes)

add_library(DocumentAttributes
    NamedRefTreeAttribute.cpp
)

target_link_libraries(DocumentAttributes
    PUBLIC LabelMarkerAttributes
    PUBLIC ${OpenCASCADE_LIBRARIES}
)

target_include_directories(DocumentAttributes
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)