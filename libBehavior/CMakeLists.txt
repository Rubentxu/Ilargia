 set(PROJECT_NAME "Behavior" CXX)
 project(${PROJECT_NAME})

 file(GLOB SRCS ${PROJECT_SOURCE_DIR}/*.cpp)

 set (BOOST_ROOT ../../boost)
 set (Boost_INCLUDE_DIR ${BOOST_ROOT})
 set (BOOST_MAIN_LIBRARY ${BOOST_ROOT}/lib)
 set (BOOST_LIBRARY ${BOOST_ROOT}/lib)

 set(Boost_NO_SYSTEM_PATHS ON)
 set(Boost_USE_MULTITHREADED ON)
 set(Boost_USE_STATIC_LIBS ON)
 set(Boost_USE_STATIC_RUNTIME OFF)
 set(BOOST_ALL_DYN_LINK OFF)

 #find_package(Boost 1.60 COMPONENTS date_time filesystem program_options regex serialization system thread REQUIRED)
 find_package(Boost REQUIRED)
 if (Boost_FOUND)
     MESSAGE("Boost Found: ${Boost_INCLUDE_DIR}")
     include_directories(${PROJECT_SOURCE_DIR}/include)
     include_directories(SYSTEM ${Boost_INCLUDE_DIR})

     link_directories(${Boost_LIBRARY_DIRS})
     add_library(${PROJECT_NAME} STATIC ${SRCS})
     target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})
     target_include_directories(${PROJECT_NAME} SYSTEM PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include ${Boost_INCLUDE_DIRS})
 ELSE(Boost_FOUND)
     MESSAGE(FATAL_ERROR "Boost is needed to build ${PROJECT_NAME}!")
 endif ()

 #set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)