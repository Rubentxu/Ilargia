cmake_minimum_required(VERSION 2.8.12.2)

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
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/externalLib/modules-cmake)


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

if (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU" OR ${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -std=c++11")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_DEBUG} -g")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_RELEASE} -O2")
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC")
    if (CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
        string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    else()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
    endif()
endif()
if(CYGWIN)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lcygwin")
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

add_subdirectory(libIlargia)
add_subdirectory(demos)

if (test)
    add_subdirectory(test)
endif ()