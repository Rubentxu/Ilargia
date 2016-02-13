 set (PROJECT_NAME "libBehavior" CXX)
 project (${PROJECT_NAME})
 set (PROJECT_SOURCE_DECLARATION_DIRECTORY ${PROJECT_SOURCE_DIR}/include)
 set (PROJECT_SOURCE_DEFINITION_DIRECTORY ${PROJECT_SOURCE_DIR}/src)

 file(GLOB SRCS *.*)

 set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

 #set (BOOST_ROOT "C:/MinGW")
 #set (BOOST_INCLUDEDIR "C:/MinGW/include")
 #set (BOOST_LIBRARYDIR "C:/MinGW/lib")
 set (Boost_NO_SYSTEM_PATHS ON)
 set (Boost_USE_MULTITHREADED ON)
 set (Boost_USE_STATIC_LIBS ON)
 set (Boost_USE_STATIC_RUNTIME OFF)
 set (BOOST_ALL_DYN_LINK OFF)


 find_package (Boost 1.55.0)
 if (Boost_FOUND)

     include_directories (SYSTEM ${Boost_INCLUDE_DIR})
     include_directories(${PROJECT_SOURCE_DECLARATION_DIRECTORY})

 endif ()

link_directories (${Boost_LIBRARY_DIRS})
add_library(${PROJECT_NAME} STATIC ${SRCS})
target_link_libraries (${PROJECT_NAME} ${Boost_LIBRARIES})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

include_directories (${PROJECT_SOURCE_DECLARATION_DIRECTORY})

set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)