add_library(OcafAttributes)

target_sources(OcafAttributes PRIVATE
    MarkerAttributeGUIDs.cpp
)

target_link_libraries(OcafAttributes
    PUBLIC ${OpenCASCADE_LIBRARIES}
)

target_include_directories(OcafAttributes
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)