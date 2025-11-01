function(add_interface_library name)
    add_library(${name} INTERFACE)

    set(options)
    set(one_value_args)
    set(multi_value_args LINK_LIBS INCLUDE_DIRS)
    cmake_parse_arguments(ARG "${options}" "${one_value_args}" "${multi_value_args}" ${ARGN})

    if(ARG_LINK_LIBS)
        target_link_libraries(${name} INTERFACE ${ARG_LINK_LIBS})
    endif()

    if(ARG_INCLUDE_DIRS)
        target_include_directories(${name} INTERFACE ${ARG_INCLUDE_DIRS})
    endif()
endfunction()
