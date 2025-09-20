add_subdirectory(FileUtils)
add_subdirectory(MathUtils)
add_subdirectory(Messaging)
add_subdirectory(Progress)

add_library(Tools INTERFACE)

target_link_libraries(Tools 
    INTERFACE FileUtils
    INTERFACE MathUtils
    INTERFACE Progress
    INTERFACE Messaging
)