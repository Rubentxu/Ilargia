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

#set (SDL2 ../SDL/x86_64-w64-mingw32)
set (SDL2DIR ../SDL2-2.0.4/x86_64-w64-mingw32 CACHE STRING "")
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_mixer REQUIRED)

# Add include directories
set(ILARGIA_INCLUDE_DIRS
        ${ANAX_INCLUDE_DIR}
        ${MathFu_SOURCE_DIR}/include
        ${SDL2_INCLUDE_DIR}
        ${SDL2_IMAGE_INCLUDE_DIR}
        ${SDL2_TTF_INCLUDE_DIR}
        ${SDL2_MIXER_INCLUDE_DIR}
        ${Ilargia_SOURCE_DIR}/include
        CACHE STRING "")

include_directories(${ILARGIA_INCLUDE_DIRS})

#include_directories(${BitScan_SOURCE_DIR}/include)
file(GLOB_RECURSE ILARGIA_LIBRARY_SOURCES ${Ilargia_SOURCE_DIR}/src/*.cpp)
add_library(${ILARGIA_LIBRARY_NAME} ${ILARGIA_LIBRARY_SOURCES} include/core/IOCContainer.h)

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
        PUBLIC anax
        #${SFML_LIBRARIES}
        PUBLIC ${SDL2_LIBRARY}
        #PUBLIC ${SDL2MAIN_LIBRARY}
        PUBLIC ${SDL2_IMAGE_LIBRARY}
        PUBLIC ${SDL2_TTF_LIBRARY}
        PUBLIC ${SDL2_MIXER_LIBRARY}
)
target_include_directories(${PROJECT_NAME} SYSTEM PUBLIC ILARGIA_INCLUDE_DIRS)