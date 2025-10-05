add_library(DocumentLabels)

target_sources(DocumentLabels PRIVATE
    DocLabel.cpp
    DocLabelUtils.cpp   
    PartLabel.cpp
    PrototypeLabel.cpp
)

target_link_libraries(DocumentLabels
    PUBLIC ${OpenCASCADE_LIBRARIES}
    PRIVATE LabelMarkerAttributes
)

target_include_directories(DocumentLabels
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)