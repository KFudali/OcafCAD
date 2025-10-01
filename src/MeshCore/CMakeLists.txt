add_subdirectory(Events)
add_subdirectory(Transfer)
add_subdirectory(MeshEngine)
add_subdirectory(MeshObject)

add_library(MeshCore
    MeshCore.cpp
)

target_link_libraries(MeshCore
    PUBLIC GeometryCore
    PUBLIC Tools
)

target_include_directories(MeshCore
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)