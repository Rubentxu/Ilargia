project(test)

find_package(Threads REQUIRED)
enable_testing()

# Enable ExternalProject CMake module
include(ExternalProject)

set(externalLib ${CMAKE_CURRENT_SOURCE_DIR}/lib/)

ExternalProject_Add(
        gtest
        URL ${PROJECT_SOURCE_DIR}/../externalLib/gtest-1.7.0.zip
        PREFIX ${externalLib}/gtest
        # Disable install step
        INSTALL_COMMAND ""
)

# Create a libgtest target to be used as a dependency by test programs
add_library(libgtest IMPORTED STATIC GLOBAL)
add_dependencies(libgtest gtest)

ExternalProject_Get_Property(gtest source_dir binary_dir)
set_target_properties(libgtest PROPERTIES
        "IMPORTED_LOCATION" "${binary_dir}/libgtest.a"
        "IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
        #    "INTERFACE_INCLUDE_DIRECTORIES" "${source_dir}/include"
        )
# I couldn't make it work with INTERFACE_INCLUDE_DIRECTORIES
include_directories("${source_dir}/include")

# Download and install GoogleMock
ExternalProject_Add(
        gmock
        URL ${PROJECT_SOURCE_DIR}/../externalLib/gmock-1.7.0.zip
        PREFIX ${externalLib}/gmock
        # Disable install step
        INSTALL_COMMAND ""
)

add_library(libgmock IMPORTED STATIC GLOBAL)
add_dependencies(libgmock gmock)

# Set gmock properties
ExternalProject_Get_Property(gmock source_dir binary_dir)
set_target_properties(libgmock PROPERTIES
        "IMPORTED_LOCATION" "${binary_dir}/libgmock.a"
        "IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
        #    "INTERFACE_INCLUDE_DIRECTORIES" "${source_dir}/include"
        )
# I couldn't make it work with INTERFACE_INCLUDE_DIRECTORIES
include_directories("${source_dir}/include")


file(GLOB SRCS *.cpp)
# This adds another subdirectory, which has 'project(gtest)'. cmake -Dtest=ON .. -DGTEST_OS_CYGWIN=1


include_directories(includes)

ADD_EXECUTABLE(testBehavior ${SRCS})

TARGET_LINK_LIBRARIES(testBehavior
    Behavior
    libgtest
    libgmock
)

add_test(NAME testBehavior
        COMMAND testBehavior)
