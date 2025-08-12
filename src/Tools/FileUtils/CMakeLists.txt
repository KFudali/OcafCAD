add_library(FileUtils
    PathUtils.cpp
)

target_include_directories(FileUtils
    PRIVATE ${BOOST_DIR}
    PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}
)