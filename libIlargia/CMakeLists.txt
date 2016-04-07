cmake_minimum_required(VERSION 2.8.12.2)

set(ILARGIA_LIBRARY_NAME "Ilargia")
project(${ILARGIA_LIBRARY_NAME})

set(ILARGIA_VERSION_MAJOR 2)
set(ILARGIA_VERSION_MINOR 1)
set(ILARGIA_VERSION_PATCH 0)
set(PROJECT_VERSION ${ILARGIA_VERSION_MAJOR}.${ILARGIA_VERSION_MINOR}.${ILARGIA_VERSION_PATCH})


find_path(ANAX_INCLUDE_DIR anax/anax.hpp PATH_SUFFIXES include PATHS ${ANAX_SOURCE_DIR})
# debug
find_library(ANAX_LIBRARY NAMES "anax_d_s" "libanax_d_s" PATH_SUFFIXES lib lib64 PATHS ${EXECUTABLE_OUTPUT_PATH})
# release
#find_library(ANAX_LIBRARY NAMES "anax_s" "libanax_s" PATH_SUFFIXES lib lib64 PATHS ${EXECUTABLE_OUTPUT_PATH})
if(ANAX_LIBRARY)
else()
    set(ANAX_LIBRARY ${EXECUTABLE_OUTPUT_PATH}/lib/libanax_d_s.a CACHE STRING "" FORCE)
endif(ANAX_LIBRARY)

set(ILARGIA_INCLUDE_DIRS ${Ilargia_SOURCE_DIR}/include)
include_directories(${ILARGIA_INCLUDE_DIRS})
include_directories(${SDL2PP_INCLUDE_DIRS})
include_directories(${ANAX_INCLUDE_DIR})
include_directories(${MathFu_SOURCE_DIR}/include)

#include_directories(${BitScan_SOURCE_DIR}/include)
file(GLOB_RECURSE ILARGIA_LIBRARY_SOURCES ${Ilargia_SOURCE_DIR}/src/*.cpp)
add_library(${ILARGIA_LIBRARY_NAME} ${ILARGIA_LIBRARY_SOURCES})

set_target_properties(${ILARGIA_LIBRARY_NAME} PROPERTIES
        VERSION ${PROJECT_VERSION}
        SOVERSION ${ILARGIA_VERSION_MAJOR}
        )


if(APPLE)
    set_target_properties(${ILARGIA_LIBRARY_NAME} PROPERTIES OSX_ARCHITECTURES "i386;x86_64;")
endif()

target_link_libraries(
        ${ILARGIA_LIBRARY_NAME}
        #PUBLIC Behavior
        #BitScan
        PUBLIC ${ANAX_LIBRARY}
        #${SFML_LIBRARIES}
        PUBLIC ${SDL2PP_LIBRARIES}

)
target_include_directories(${PROJECT_NAME} SYSTEM PUBLIC ILARGIA_INCLUDE_DIRS)