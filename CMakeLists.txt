cmake_minimum_required(VERSION 2.8.12.2)

project(Ilargia)

set(ILARGIA_LIBRARY_NAME "Ilargia")
set(ILARGIA_VERSION_MAJOR 2)
set(ILARGIA_VERSION_MINOR 1)
set(ILARGIA_VERSION_PATCH 0)
set(PROJECT_VERSION ${ILARGIA_VERSION_MAJOR}.${ILARGIA_VERSION_MINOR}.${ILARGIA_VERSION_PATCH})


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



add_subdirectory(libBehavior)
set(BUILD_SHARED_LIBS false CACHE BOOL "")
set(ANAX_STATIC_LIBRARIES true)
add_subdirectory(externalLib/anax)

find_path(ANAX_INCLUDE_DIR anax/anax.hpp PATH_SUFFIXES include PATHS ${ANAX_SOURCE_DIR})
# debug
find_library(ANAX_LIBRARY NAMES "anax_d_s" "libanax_d_s" PATH_SUFFIXES lib lib64 PATHS ${EXECUTABLE_OUTPUT_PATH})
# release
#find_library(ANAX_LIBRARY NAMES "anax_s" "libanax_s" PATH_SUFFIXES lib lib64 PATHS ${EXECUTABLE_OUTPUT_PATH})



set(dependencies_root "${Ilargia_SOURCE_DIR}/externalLib/mathfu/dependencies" CACHE PATH "Directory holding the dependencies pulled from github.")
set(mathfu_build_benchmarks OFF CACHE BOOL "")
set(mathfu_build_tests OFF CACHE BOOL "")
add_subdirectory(externalLib/mathfu)
add_subdirectory(externalLib/Box2D/Box2D)


add_subdirectory(demos)

if (test)
    add_subdirectory(test)
endif ()


#set (SDL2 ../SDL/x86_64-w64-mingw32)
set (SDLDIR ../SDL2-2.0.4/x86_64-w64-mingw32)
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_mixer REQUIRED)

# Add include directories
include_directories(${ANAX_INCLUDE_DIR}
        ${SDL2_INCLUDE_DIR}
        ${SDL2_IMAGE_INCLUDE_DIR}
        ${SDL2_TTF_INCLUDE_DIR}
        ${SDL2_MIXER_INCLUDE_DIR}
        ${Ilargia_SOURCE_DIR}/include)

#include_directories(${BitScan_SOURCE_DIR}/include)
file(GLOB_RECURSE ILARGIA_LIBRARY_SOURCES ${Ilargia_SOURCE_DIR}/src/*.cpp)
add_library(${ILARGIA_LIBRARY_NAME}
        ${ILARGIA_LIBRARY_SOURCES} src/Systems/SensorSystem.cpp include/Systems/SensorSystem.h include/Components/SensorComponent.h include/controllers/Controller.h include/actuators/ViewActuator.h include/Components/StateComponent.h)

set_target_properties(${ILARGIA_LIBRARY_NAME} PROPERTIES
        VERSION ${PROJECT_VERSION}
        SOVERSION ${ILARGIA_VERSION_MAJOR}
        )


if(APPLE)
    set_target_properties(${ILARGIA_LIBRARY_NAME} PROPERTIES OSX_ARCHITECTURES "i386;x86_64;")
endif()

target_link_libraries(
        ${ILARGIA_LIBRARY_NAME}
        PUBLIC Behavior
        #BitScan
        PUBLIC ${ANAX_LIBRARY}
        #${SFML_LIBRARIES}
        PUBLIC ${SDL2_LIBRARY}
        PUBLIC ${SDL2_IMAGE_LIBRARIES}
        PUBLIC ${SDL2_TTF_LIBRARIES}
        PUBLIC ${SDL2_MIXER_LIBRARIES}
)