
file(GLOB_RECURSE Components ${test_SOURCE_DIR}/Ilargia/Components/*.*)

set(INDEX 0)
set(COMPONENT_IDS "ICOMPONENT = 0")
foreach (_ComponentsFile ${Components})
    get_filename_component(_dir ${_ComponentsFile} NAME_WE)
    MATH(EXPR INDEX "${INDEX}+1")
    set (COMPONENT_IDS ${COMPONENT_IDS},\n\t\t${_dir}=${INDEX})
endforeach()

#message(FATAL_ERROR "Not found components "${COMPONENT_IDS})

# Config Project init values
set(MAX_AMOUNT_OF_COMPONENTS 4)


# set up the configure file for the library
configure_file(${Ilargia_SOURCE_DIR}/src/include/Config.h.inl ${Ilargia_SOURCE_DIR}/src/include/Config.h)
