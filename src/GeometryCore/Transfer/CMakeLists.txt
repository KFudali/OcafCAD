add_subdirectory(Import)

add_library(Transfer INTERFACE)

target_link_libraries(Transfer
    INTERFACE Import
)