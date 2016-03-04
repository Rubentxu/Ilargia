set(PROJECT_NAME "Entitas" CXX)
project(${PROJECT_NAME})

file(GLOB libEntitas_SRCS *.cpp)

include_directories(includes)

# Declare the library
add_library(${PROJECT_NAME} STATIC ${libEntitas_SRCS})

# Specify here the include directories exported
# by this library
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)