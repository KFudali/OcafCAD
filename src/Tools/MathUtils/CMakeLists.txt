add_library(MathUtils INTERFACE)

# target_link_libraries(MathUtils
#     INTERFACE 
# )

target_include_directories(MathUtils
    INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
    INTERFACE ${BOOST_DIR}
)