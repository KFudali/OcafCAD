add_library(DocLabel
    DocLabel.cpp
    DocLabelUtils.cpp
)

target_link_libraries(DocLabel PUBLIC
    DocumentAttributes
    ${OpenCASCADE_Libraries}
)

target_include_directories(DocLabel PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)