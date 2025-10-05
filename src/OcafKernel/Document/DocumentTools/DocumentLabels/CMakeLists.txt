add_library(DocLabels)

target_sources(DocLabels PRIVATE
    DocLabel.cpp
    DocLabelUtils.cpp   
    PartLabel.cpp
    PrototypeLabel.cpp
)

target_link_libraries(DocLabels
    PUBLIC ${OpenCASCADE_LIBRARIES}
    PRIVATE LabelMarkerAttributes
)

target_include_directories(DocLabels
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)