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
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/externalLib/modules-cmake)


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
#add_subdirectory(libEntitas)
#add_subdirectory(libBitScan)
#add_subdirectory(demos)

if (test)
    add_subdirectory(test)
endif ()

set (ANAX_ROOT ../anax)
find_package(anax REQUIRED)
include_directories(${ANAX_INCLUDE_DIR})

#set (SDL2 ../SDL/x86_64-w64-mingw32)
set (SDLDIR ../SDL2-2.0.4/x86_64-w64-mingw32)
find_package(SDL2 COMPONENTS mixer gfx image)
include_directories(${SDL_INCLUDE_DIR})

#set (GLM_ROOT_DIR ../glm)
#find_package (GLM REQUIRED)
#include_directories(${GLM_INCLUDE_DIRS})


# find SFML 2
#find_package(SFML 2 COMPONENTS system window graphics REQUIRED)
#if(SFML_FOUND)
#    include_directories(${SFML_INCLUDE_DIR})
#ELSE(SFML_FOUND)
#    MESSAGE(FATAL_ERROR "SFML is needed to build ${PROJECT_NAME}!")
#endif()

# Look up SDL2 and add the include directory to our include path



#include(Config)

# Add include directories
include_directories(${Ilargia_SOURCE_DIR}/src/core/include)
include_directories(${Ilargia_SOURCE_DIR}/src/sdl2/include)
#include_directories(${BitScan_SOURCE_DIR}/include)
file(GLOB ILARGIA_LIBRARY_SOURCES ${Ilargia_SOURCE_DIR}/src/sdl2/*.cpp)
add_library(${ILARGIA_LIBRARY_NAME}
        ${ILARGIA_LIBRARY_SOURCES})

set_target_properties(${ILARGIA_LIBRARY_NAME} PROPERTIES
        VERSION ${PROJECT_VERSION}
        SOVERSION ${ILARGIA_VERSION_MAJOR}
        )



if(APPLE)
    set_target_properties(${ILARGIA_LIBRARY_NAME} PROPERTIES OSX_ARCHITECTURES "i386;x86_64;")
endif()

target_link_libraries(
        ${ILARGIA_LIBRARY_NAME}
        Behavior
        #BitScan
        ${ANAX_LIBRARY_NAME}
        #${SFML_LIBRARIES}
        ${SDL_LIBRARY}
)