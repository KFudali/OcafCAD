add_library(NamedSelectionLabel
    NamedSelection.cpp
    NamedSelectionLabel.cpp
    NamedSelectionAttribute.cpp
)

target_link_libraries(NamedSelectionLabel
    PUBLIC DocumentTools
)

target_include_directories(NamedSelectionLabel
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)