add_subdirectory(LabelMarkerAttributes)

add_library(DocumentAttributes INTERFACE)

target_link_libraries(DocumentAttributes INTERFACE
    LabelMarkerAttributes
)