function(collect_unit_test_sources base_dir out_var)
    file(GLOB_RECURSE collected_files CONFIGURE_DEPENDS
        "${base_dir}/ut*.cpp"
    )
    set(${out_var} ${collected_files} PARENT_SCOPE)
endfunction()

function(collect_integration_test_sources base_dir out_var)
    file(GLOB_RECURSE collected_files CONFIGURE_DEPENDS
        "${base_dir}/it*.cpp"
    )
    set(${out_var} ${collected_files} PARENT_SCOPE)
endfunction()