set (EXAMPLE_NAME Demo)


include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include ${ILARGIA_INCLUDE_DIRS})

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})


#[[

################################################################################
######################### Compiler: Hardening  #################################
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    if(CMAKE_C_COMPILER_ID STREQUAL "GNU" OR CMAKE_C_COMPILER_ID STREQUAL "Clang")
        TRY_C_COMPILER_FLAG(-fstack-protector FLAG_C_fstack_protector)

        if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
            TRY_C_COMPILER_FLAG(-fPIC              FLAG_C_fPIC)
            TRY_C_COMPILER_FLAG(-pie               FLAG_C_pie)
            TRY_C_COMPILER_FLAG(-Wl,-z,relro       FLAG_C_Wl_z_relro)
            TRY_C_COMPILER_FLAG(-Wl,-z,now         FLAG_C_Wl_z_now)
            TRY_C_COMPILER_FLAG(-Wl,--as-needed    FLAG_C_Wl_as_needed)
            TRY_C_COMPILER_FLAG(-Wl,-z,noexecstack FLAG_C_Wl_z_noexecstack)
        endif()
    endif()

    if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
        TRY_CXX_COMPILER_FLAG(-fstack-protector FLAG_CXX_fstack_protector)

        if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
            TRY_CXX_COMPILER_FLAG(-fPIC              FLAG_CXX_fPIC)
            TRY_CXX_COMPILER_FLAG(-pie               FLAG_CXX_pie)
            TRY_CXX_COMPILER_FLAG(-Wl,-z,relro       FLAG_CXX_Wl_z_relro)
            TRY_CXX_COMPILER_FLAG(-Wl,-z,now         FLAG_CXX_Wl_z_now)
            TRY_CXX_COMPILER_FLAG(-Wl,--as-needed    FLAG_CXX_Wl_as_needed)
            TRY_CXX_COMPILER_FLAG(-Wl,-z,noexecstack FLAG_CXX_Wl_z_noexecstack)
        endif()
    endif()

    if(CMAKE_C_COMPILER_ID STREQUAL "Intel")
        TRY_C_COMPILER_FLAG(-fstack-protector  FLAG_C_fstackprotector)
        TRY_C_COMPILER_FLAG(-fPIC              FLAG_C_fPIC)
        TRY_C_COMPILER_FLAG(-pie               FLAG_C_pie)
        TRY_C_COMPILER_FLAG(-Wl,-z,relro       FLAG_C_Wl_z_relro)
        TRY_C_COMPILER_FLAG(-Wl,-z,now         FLAG_C_Wl_z_now)
        TRY_C_COMPILER_FLAG(-Wl,--as-needed    FLAG_C_Wl_as_needed)
        TRY_C_COMPILER_FLAG(-Wl,-z,noexecstack FLAG_C_Wl_z_noexecstack)
    endif()

    if(CMAKE_CXX_COMPILER_ID STREQUAL "Intel")
        TRY_CXX_COMPILER_FLAG(-fstack-protector  FLAG_CXX_fstackprotector)
        TRY_CXX_COMPILER_FLAG(-fPIC              FLAG_CXX_fPIC)
        TRY_CXX_COMPILER_FLAG(-pie               FLAG_CXX_pie)
        TRY_CXX_COMPILER_FLAG(-Wl,-z,relro       FLAG_CXX_Wl_z_relro)
        TRY_CXX_COMPILER_FLAG(-Wl,-z,now         FLAG_CXX_Wl_z_now)
        TRY_CXX_COMPILER_FLAG(-Wl,--as-needed    FLAG_CXX_Wl_as_needed)
        TRY_CXX_COMPILER_FLAG(-Wl,-z,noexecstack FLAG_CXX_Wl_z_noexecstack)
    endif()

    if(MSVC)
        TRY_C_COMPILER_FLAG(/GS FLAG_C_GS)

        TRY_CXX_COMPILER_FLAG(/GS FLAG_CXX_GS)
    endif()
endif()


################################################################################
######################### Compiler: Optimisation  ##############################
if(CMAKE_BUILD_TYPE STREQUAL "MinSizeRel" OR CMAKE_BUILD_TYPE STREQUAL "Release")
    if(CMAKE_C_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
        TRY_C_COMPILER_FLAG(-fomit-frame-pointer FLAG_C_fomit_frame_pointer)
    endif()

    if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
        TRY_CXX_COMPILER_FLAG(-fomit-frame-pointer FLAG_CXX_fomit_frame_pointer)
    endif()

    if(CMAKE_C_COMPILER_ID STREQUAL "Intel")
        TRY_C_COMPILER_FLAG(-fomit-frame-pointer FLAG_C_fomit_frame_pointer)
        TRY_C_COMPILER_FLAG(-ipo                 FLAG_C_ipo)
    endif()

    if(CMAKE_CXX_COMPILER_ID STREQUAL "Intel")
        TRY_CXX_COMPILER_FLAG(-fomit-frame-pointer FLAG_CXX_fomit_frame_pointer)
        TRY_CXX_COMPILER_FLAG(-ipo                 FLAG_CXX_ipo)
    endif()
endif()
]]


#mathfu_configure_flags(${EXAMPLE_NAME})

file(GLOB_RECURSE EXAMPLE_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
add_executable(${EXAMPLE_NAME} ${EXAMPLE_SOURCES})

target_link_libraries(
        ${EXAMPLE_NAME}
        ${ILARGIA_LIBRARY_NAME}
        ${ANAX_LIBRARY}
        ${SDL2_LIBRARY}
        ${SDL2_IMAGE_LIBRARIES}
        ${SDL2_TTF_LIBRARIES}
        ${SDL2_MIXER_LIBRARIES}

)
