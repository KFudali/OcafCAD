add_subdirectory(GeometryEvents)
add_subdirectory(Transfer)
add_subdirectory(GeometryObject)
add_subdirectory(View)

add_library(GeometryCore
    GeometryCore.cpp
)

target_link_libraries(GeometryCore PUBLIC
    OcafKernel
    Tools

    GeometryEvents
    Transfer
    View
)

target_include_directories(GeometryCore PRIVATE
    ${BOOST_DIR}
)