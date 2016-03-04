 set(PROJECT_NAME "Ilargia" CXX)
 project(${PROJECT_NAME})

 file(GLOB SRCS ${PROJECT_SOURCE_DIR}/*.cpp)

 set (ANAX_ROOT ${PROJECT_SOURCE_DIR}/../../anax/build)
 set (ANAX_INCLUDE_DIR ${ANAX_ROOT})
 set (ANAX_MAIN_LIBRARY ${ANAX_ROOT}/build)
 set (ANAX_LIBRARY ${ANAX_ROOT}/build)



 #find_package(Boost 1.60 COMPONENTS date_time filesystem program_options regex serialization system thread REQUIRED)
 find_package(ANAX REQUIRED)
 if (ANAX_FOUND)
     MESSAGE("Anax Found: ${ANAX_INCLUDE_DIR}")
     include_directories(${ANAX_INCLUDE_DIR})
 ELSE(ANAX_FOUND)
     MESSAGE(FATAL_ERROR "Anax Not Found: ${ANAX_INCLUDE_DIR}")
 endif ()

 # find SFML 2
 find_package(SFML 2 COMPONENTS system window graphics REQUIRED)
 if(SFML_FOUND)
     include_directories(${SFML_INCLUDE_DIR})
 ELSE(SFML_FOUND)
     MESSAGE(FATAL_ERROR "SFML is needed to build ${PROJECT_NAME}!")
 endif()

 #set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)