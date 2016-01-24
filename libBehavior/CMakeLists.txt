message( STATUS "Configuring Boost SuperBuild..." )
include( ExternalProject )

set( ext.Boost_VERSION "1.60.0" CACHE STRING "Boost version to download/use" )
mark_as_advanced( ext.Boost_VERSION )
string( REPLACE "." "_" ext.Boost_Version_Underscore ${ext.Boost_VERSION} )

message( STATUS "ext.Boost_VERSION: " ${ext.Boost_VERSION} )

# Purely for debugging the file downloading URLs
# file( DOWNLOAD "http://downloads.sourceforge.net/project/boost/boost/1.49.0/boost_1_49_0.7z"
# "${CMAKE_CURRENT_BINARY_DIR}/download/boost-${ext.Boost_VERSION}/boost_1_49_0.7z" SHOW_PROGRESS STATUS fileStatus LOG fileLog )
# message( STATUS "status: " ${fileStatus} )
# message( STATUS "log: " ${fileLog} )

# Initialize various command names based on platform
if ( UNIX )
    set(Boost.B2 "./b2")
    set(Boost.Bootstrap "./bootstrap.sh")
else( )
    set(Boost.B2 "b2")
    set(Boost.Bootstrap "bootstrap.bat")
endif( )

set( Boost.Command ${Boost.B2} -j 4 --with-program_options --with-thread --with-system --with-date_time --with-chrono )


if( MSVC )
    if( MSVC_VERSION VERSION_LESS 1700 )
        list( APPEND Boost.Command toolset=msvc-10.0 )
    elseif( MSVC_VERSION VERSION_LESS 1800 )
        list( APPEND Boost.Command toolset=msvc-11.0 )
    else()
        list( APPEND Boost.Command toolset=msvc-12.0 )
    endif( )
endif( )

list( APPEND Boost.Command link=static stage )

# If the user has cached the Boost download to a local location, they may prefer to download the package from there instead of from the internet, as the
# internet could be unpredictable or slow.
# If the user has a local copy stored somewhere, they can define the full path to the package in a BOOST_URL environment variable
if( DEFINED ENV{BOOST_URL} )
    set( ext.Boost_URL "$ENV{BOOST_URL}" CACHE STRING "URL to download Boost from" )
else( )
    set( ext.Boost_URL "http://sourceforge.net/projects/boost/files/boost/${ext.Boost_VERSION}/boost_${ext.Boost_Version_Underscore}.zip/download" CACHE STRING "URL to download Boost from" )
endif( )
mark_as_advanced( ext.Boost_URL )

# Below is a fancy CMake command to download, build and install Boost on the users computer

ExternalProject_Add(
        Boost
        PREFIX ${CMAKE_CURRENT_BINARY_DIR}/external/boost
        URL ${ext.Boost_URL}
        #    URL_MD5 f310a8198318c10e5e4932a07c755a6a
        URL_MD5 0cc5b9cf9ccdf26945b225c7338b4288
        UPDATE_COMMAND ${Boost.Bootstrap}
        #    PATCH_COMMAND ""
        CONFIGURE_COMMAND ""
        BUILD_COMMAND ${Boost.Command}
        BUILD_IN_SOURCE 1
        INSTALL_COMMAND ""
)

set_property( TARGET Boost PROPERTY FOLDER "Externals")

ExternalProject_Get_Property( Boost source_dir )
ExternalProject_Get_Property( Boost binary_dir )
set( Boost_INCLUDE_DIRS ${source_dir} )

if( MSVC )
    #    if( MSVC_VERSION VERSION_LESS 1700 )
    #        set( Boost_LIBRARIES debug;${binary_dir}/stage/lib/libboost_program_options-vc110-mt-gd-1_50.lib;optimized;${binary_dir}/stage/lib/libboost_program_options-vc110-mt-1_50.lib )
    #    else()
    #        set( Boost_LIBRARIES debug;${binary_dir}/stage/lib/libboost_program_options-vc120-mt-gd-1_50.lib;optimized;${binary_dir}/stage/lib/libboost_program_options-vc120-mt-1_50.lib )
    #    endif()
else()
    set( Boost_LIBRARIES debug;${binary_dir}/stage/lib/libboost_program_options.a;optimized;${binary_dir}/stage/lib/libboost_program_options.a )
endif()

set( Boost_FOUND TRUE )

file(GLOB SRCS *.cpp)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# Declare the library
add_library(BehaviorT STATIC ${BehaviorT_SRCS})
TARGET_LINK_LIBRARIES(BehaviorT libBoost)

# Specify here the include directories exported
# by this library
target_include_directories(BehaviorT PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

set_target_properties(BehaviorT PROPERTIES LINKER_LANGUAGE CXX)