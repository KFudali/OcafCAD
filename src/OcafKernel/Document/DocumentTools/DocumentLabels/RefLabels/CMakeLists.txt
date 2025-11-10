add_library(RefLabels
    RefTreeLabel.cpp
    NamedRefTreeLabel.cpp
)

target_link_libraries(RefLabels PUBLIC
    DocLabel
)

target_include_directories(RefLabels PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)