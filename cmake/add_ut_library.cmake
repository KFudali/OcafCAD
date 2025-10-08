include(cmake/collect_test_sources.cmake)

function(add_ut_library name)
    set(options)
    set(oneValueArgs)
    set(multiValueArgs LINK_LIBS SOURCE_DIRS INCLUDE_DIRS)
    cmake_parse_arguments(UT "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    add_library(${name} INTERFACE)

    set(all_ut_sources)
    foreach(dir IN LISTS UT_SOURCE_DIRS)
        collect_unit_test_sources(${dir} utSources)
        list(APPEND all_ut_sources ${utSources})
    endforeach()

    target_sources(${name} INTERFACE ${all_ut_sources})

    target_link_libraries(${name} INTERFACE
        GTest::gmock_main
        ${UT_LINK_LIBS}
    )

    target_include_directories(${name} INTERFACE
        ${UT_INCLUDE_DIRS}
    )
endfunction()
