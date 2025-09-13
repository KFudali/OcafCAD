add_subdirectory(Transfer)
add_subdirectory(Utils)

add_library(GeometryCore
    GeometryCore.cpp
)

target_link_libraries(GeometryCore PUBLIC
    OcafKernel
    Tools
    Transfer
)

target_include_directories(GeometryCore PRIVATE
    ${BOOST_DIR}
)