add_subdirectory(FileUtils)
add_subdirectory(Messaging)
add_subdirectory(Progress)

add_library(Tools INTERFACE)

target_link_libraries(Tools 
    INTERFACE FileUtils
    INTERFACE Progress
    INTERFACE Messaging
)