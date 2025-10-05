add_library(LabelMarkerAttributes)

target_sources(LabelMarkerAttributes PRIVATE
    MarkerAttributeGUIDs.cpp
)

target_link_libraries(LabelMarkerAttributes
    PUBLIC ${OpenCASCADE_LIBRARIES}
)

target_include_directories(LabelMarkerAttributes
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)