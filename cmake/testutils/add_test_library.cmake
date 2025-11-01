include(cmake/testutils/collect_test_sources.cmake)

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

function(add_it_library name)
    set(options)
    set(oneValueArgs)
    set(multiValueArgs LINK_LIBS SOURCE_DIRS INCLUDE_DIRS)
    cmake_parse_arguments(IT "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    add_library(${name} INTERFACE)

    set(all_it_sources)
    foreach(dir IN LISTS IT_SOURCE_DIRS)
        collect_integration_test_sources(${dir} itSources)
        list(APPEND all_it_sources ${itSources})
    endforeach()

    target_sources(${name} INTERFACE ${all_it_sources})

    target_link_libraries(${name} INTERFACE
        GTest::gmock_main
        ${IT_LINK_LIBS}
    )

    target_include_directories(${name} INTERFACE
        ${IT_INCLUDE_DIRS}
    )
endfunction()
