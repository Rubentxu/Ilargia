PROJECT ("Ilargia Engine" C CXX)
cmake_minimum_required(VERSION 3.3.2)

set(dir ${CMAKE_CURRENT_SOURCE_DIR}/build/)
set(EXECUTABLE_OUTPUT_PATH ${dir} CACHE PATH "Build directory" FORCE)
set(LIBRARY_OUTPUT_PATH ${dir} CACHE PATH "Build directory" FORCE)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${dir})
set(CMAKE_BUILD_FILES_DIRECTORY ${dir})
set(CMAKE_BUILD_DIRECTORY ${dir})
set(Ilargia_BINARY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/bin)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${dir}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${dir}/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${dir}/bin")
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/externalLib/modules-cmake ${CMAKE_CURRENT_SOURCE_DIR}/externalLib/libSDL2pp/cmake CACHE STRING "" )


# uncomment to be in Release mode [default]
# SET(CMAKE_BUILD_TYPE Release)

# uncomment to build in debug mode
# SET(CMAKE_BUILD_TYPE Debug)

# uncomment to be in coverage testing mode
# SET(CMAKE_BUILD_TYPE Coverage)

# uncomment to build in profile mode
# SET(CMAKE_BUILD_TYPE Profile)

# uncomment to build in release mode with debug information
# SET(CMAKE_BUILD_TYPE RelWithDebInfo)

# default build type
IF (CMAKE_BUILD_TYPE STREQUAL "")
    SET(CMAKE_BUILD_TYPE Debug)
ENDIF (CMAKE_BUILD_TYPE STREQUAL "")

MESSAGE(STATUS "Build type: ${CMAKE_BUILD_TYPE}")


option(test "Build all tests." ON) #



INCLUDE(CheckIncludeFiles)
INCLUDE(CheckCCompilerFlag)
INCLUDE(CheckCXXCompilerFlag)

################################################################################
######################### Functions  ###########################################

##
## TRY_C_COMPILER_FLAG
##
function(TRY_C_COMPILER_FLAG flag name)
    CHECK_C_COMPILER_FLAG("${flag}" ${name})

    if(${name})
        if(NOT "${CMAKE_C_FLAGS_LIST}" MATCHES "${name}" )
            set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${flag}" CACHE STRING "" FORCE)
            set(CMAKE_C_FLAGS_LIST "${CMAKE_C_FLAGS_LIST} ${name}" CACHE INTERNAL "" FORCE)
        endif()
    endif()
endfunction()

##
## TRY_CXX_COMPILER_FLAG
##
function(TRY_CXX_COMPILER_FLAG flag name)
    CHECK_CXX_COMPILER_FLAG(${flag} ${name})

    if(${name})
        if(NOT "${CMAKE_CXX_FLAGS_LIST}" MATCHES "${name}" )
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${flag}" CACHE STRING "" FORCE)
            set(CMAKE_CXX_FLAGS_LIST "${CMAKE_CXX_FLAGS_LIST} ${name}" CACHE INTERNAL "" FORCE)
        endif()
    endif()
endfunction()


################################################################################
######################### Compiler: Features  ##################################
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    TRY_CXX_COMPILER_FLAG(-std=c++11 FLAG_CXX_stdcxx11)
endif()


################################################################################
######################### Compiler: Warnings  ##################################
if(CMAKE_C_COMPILER_ID STREQUAL "GNU" OR CMAKE_C_COMPILER_ID STREQUAL "Clang")
    TRY_C_COMPILER_FLAG(-Wall   FLAG_C_Wall)
    #TRY_C_COMPILER_FLAG(-Wextra FLAG_C_Wextra)
endif()

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    TRY_CXX_COMPILER_FLAG(-Wall   FLAG_CXX_Wall)
    #TRY_CXX_COMPILER_FLAG(-Wextra FLAG_CXX_Wextra)
endif()

if(CMAKE_C_COMPILER_ID STREQUAL "Intel")
    TRY_C_COMPILER_FLAG(-Wall              FLAG_C_Wall)
    TRY_C_COMPILER_FLAG(-Wcheck            FLAG_C_Wcheck)
    TRY_C_COMPILER_FLAG(-Wp64              FLAG_C_Wp64)
    TRY_C_COMPILER_FLAG(-Wshorten-64-to-32 FLAG_C_Wshorten_64_to_32)
endif()

if(CMAKE_CXX_COMPILER_ID STREQUAL "Intel")
    TRY_CXX_COMPILER_FLAG(-Wall              FLAG_CXX_Wall)
    TRY_CXX_COMPILER_FLAG(-Wcheck            FLAG_CXX_Wcheck)
    TRY_CXX_COMPILER_FLAG(-Wp64              FLAG_CXX_Wp64)
    TRY_CXX_COMPILER_FLAG(-Wshorten-64-to-32 FLAG_CXX_Wshorten_64_to_32)
endif()

if(MSVC)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
    add_definitions(-D_CRT_NONSTDC_NO_WARNINGS)
endif()


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





#anax
add_subdirectory(libBehavior)
set(BUILD_SHARED_LIBS false CACHE BOOL "")
set(ANAX_STATIC_LIBRARIES true CACHE BOOL "")
add_subdirectory(externalLib/anax)

#mathfu
set(dependencies_root "${Ilargia_SOURCE_DIR}/externalLib/mathfu/dependencies" CACHE PATH "Directory holding the dependencies pulled from github.")
set(mathfu_build_benchmarks OFF CACHE BOOL "")
set(mathfu_build_tests OFF CACHE BOOL "")
add_subdirectory(externalLib/mathfu)

set(BOX2D_BUILD_EXAMPLES OFF CACHE BOOL "")
add_subdirectory(externalLib/Box2D/Box2D)

set(SDL2PP_WITH_EXAMPLES OFF CACHE BOOL "")
set(SDL2PP_WITH_TESTS OFF CACHE BOOL "")
set(SDL2PP_ENABLE_LIVE_TESTS OFF CACHE BOOL "")
SET(SDL2PP_WITH_IMAGE ON) # if you need SDL_image support
SET(SDL2PP_WITH_MIXER ON) # if you need SDL_mixer support
SET(SDL2PP_WITH_TTF ON) # if you need SDL_ttf support
add_subdirectory(externalLib/libSDL2pp)

add_subdirectory(libIlargia)
#add_subdirectory(demos)

if (test)
    add_subdirectory(test)
endif ()