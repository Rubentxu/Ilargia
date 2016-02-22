cmake_minimum_required(VERSION 3.1.2)

project(Ilargia)

set(Ilargia_BINARY_DIR )

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

# ===============================================================
# Detect different compilers and OS'es, tweak flags as necessary.

IF (CMAKE_COMPILER_IS_GNUCXX)
    # aiiee cmake version 2.8.8 or newer is needed for below to
    # work...
    # IF (CMAKE_CXX_COMPILER_VERSION VERSION_LESS 4.6.4)
    #	MESSAGE(FATAL_ERROR "GCC version must be at least 4.6.4!")
    # ENDIF (CMAKE_CXX_COMPILER_VERSION VERSION_LESS 4.6.4)

    IF (APPLE)
        SET(CMAKE_C_FLAGS "-Wall -Wno-long-long -Wno-conversion")
        SET(CMAKE_C_FLAGS_DEBUG "-O0 -g")
        SET(CMAKE_C_FLAGS_PROFILE "-O0 -pg")
        SET(CMAKE_C_FLAGS_RELEASE "-O2 -g0")
        # Vital to do this otherwise unresolved symbols everywhere:
        SET(CMAKE_SHARED_LINKER_FLAGS "-Wl,-flat_namespace,-undefined,dynamic_lookup")
        SET(CMAKE_EXE_LINKER_FLAGS "-Wl,-flat_namespace,-undefined,dynamic_lookup")
    ELSE (APPLE)
        #SET(CMAKE_C_FLAGS "-Wall -fPIC")
        # SET(CMAKE_C_FLAGS "-Wl,--copy-dt-needed-entries")
        SET(CMAKE_C_FLAGS_DEBUG "-ggdb3 -fstack-protector")
        SET(CMAKE_C_FLAGS_PROFILE "-O2 -g3 -fstack-protector -pg")
        SET(CMAKE_C_FLAGS_RELEASE "-O2 -g -fstack-protector")
    ENDIF (APPLE)

    # 1) -Wno-variadic-macros is to avoid warnings regarding using
    # variadic in macro OC_ASSERT (the warning warns that this is only
    # available from C99, lol!)
    #
    # 2) -fopenmp for multithreading support
    #
    # 3) -std=gnu++0x for C++0x and GNU extensions support
    SET(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -Wno-variadic-macros -fopenmp -std=gnu++11")

    SET(CMAKE_CXX_FLAGS_DEBUG ${CMAKE_C_FLAGS_DEBUG})
    SET(CMAKE_CXX_FLAGS_PROFILE ${CMAKE_C_FLAGS_PROFILE})
    SET(CMAKE_CXX_FLAGS_RELEASE ${CMAKE_C_FLAGS_RELEASE})

    # Options for generating gcov code coverage output
    SET(CMAKE_C_FLAGS_COVERAGE "-O0 -g -fprofile-arcs -ftest-coverage -fno-inline")
    SET(CMAKE_CXX_FLAGS_COVERAGE "${CMAKE_C_FLAGS_COVERAGE} -fno-default-inline")
    # Might be needed for some combinations of ln and gcc
    IF (CMAKE_BUILD_TYPE STREQUAL "Coverage")
        LINK_LIBRARIES(gcov)
    ENDIF (CMAKE_BUILD_TYPE STREQUAL "Coverage")
ENDIF (CMAKE_COMPILER_IS_GNUCXX)

# Do the windows build
IF (WIN32)
    ADD_DEFINITIONS(-DWIN32)
    IF (CYGWIN)
        ADD_DEFINITIONS(-DCYGWIN)
        #   SET(WIN32 1)
    ENDIF (CYGWIN)

    # It is "not unix" when the code is compiled under windows but not
    # under cygwin
   IF (NOT UNIX)
        LINK_LIBRARIES(pthread)
        IF (CYGWIN)
            SET(CMAKE_SHARED_LINKER_FLAGS "-Wl")
        ELSE (CYGWIN)
            SET(CMAKE_SHARED_LINKER_FLAGS "-Wl,--enable-new-dtags")
        ENDIF (CYGWIN)
    ENDIF (NOT UNIX)
ENDIF (WIN32)


option(test "Build all tests." ON) #

include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
if(COMPILER_SUPPORTS_CXX11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
else()
    message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

# Optional, currently needed only to hush up DRD in util/Logger.cc
#[[FIND_PACKAGE(VALGRIND)
IF (VALGRIND_FOUND)
    MESSAGE(STATUS "VALGRIND was found.")
    IF (VALGRIND_INCLUDE_DIR)
        MESSAGE(STATUS "VALGRIND devel headers found.")
        ADD_DEFINITIONS(-DHAVE_VALGRIND)
    ELSE (VALGRIND_INCLUDE_DIR)
        MESSAGE(STATUS "VALGRIND devel headers NOT FOUND: needed for thread debugging.")
    ENDIF (VALGRIND_INCLUDE_DIR)
ELSE (VALGRIND_FOUND)
    MESSAGE(STATUS "VALGRIND missing: needed for thread debugging.")
ENDIF (VALGRIND_FOUND)]]


#[[# create a shared C++ library
IF(NOT CMAKE_CXX_CREATE_SHARED_LIBRARY)
    IF (WIN32 AND CMAKE_COMPILER_IS_GNUCXX)
        SET(CMAKE_CXX_CREATE_SHARED_LIBRARY
                "<CMAKE_CXX_COMPILER> <CMAKE_SHARED_LIBRARY_CXX_FLAGS> -Wl,--out-implib,<TARGET>.a <LINK_FLAGS> <CMAKE_SHARED_LIBRARY_CREATE_CXX_FLAGS> <CMAKE_SHARED_LIBRARY_SONAME_CXX_FLAG><TARGET_SONAME> -o <TARGET> <OBJECTS> <LINK_LIBRARIES>")
    ELSE (WIN32 AND CMAKE_COMPILER_IS_GNUCXX)
        SET(CMAKE_CXX_CREATE_SHARED_LIBRARY
                "<CMAKE_CXX_COMPILER> <CMAKE_SHARED_LIBRARY_CXX_FLAGS> <LINK_FLAGS> <CMAKE_SHARED_LIBRARY_CREATE_CXX_FLAGS> <CMAKE_SHARED_LIBRARY_SONAME_CXX_FLAG><TARGET_SONAME> -o <TARGET> <OBJECTS> <LINK_LIBRARIES>")
    ENDIF (WIN32 AND CMAKE_COMPILER_IS_GNUCXX)
ENDIF(NOT CMAKE_CXX_CREATE_SHARED_LIBRARY)

IF(CMAKE_COMPILER_IS_GNUCXX)
    IF (NOT WIN32)
        SET(CMAKE_CXX_CREATE_SHARED_LIBRARY "${CMAKE_CXX_CREATE_SHARED_LIBRARY} -lgcc")
    ENDIF (NOT WIN32)
ENDIF(CMAKE_COMPILER_IS_GNUCXX)]]

add_subdirectory(libBehavior)
add_subdirectory(libEntitas)
add_subdirectory(demos)
if (test)
    add_subdirectory(test)
endif()



