 set(PROJECT_NAME "BitScan" CXX)
 project(${PROJECT_NAME})

 file(GLOB SRCS ${PROJECT_SOURCE_DIR}/*.cpp)

 include_directories(${PROJECT_SOURCE_DIR}/include)
 add_library(${PROJECT_NAME} STATIC ${SRCS})