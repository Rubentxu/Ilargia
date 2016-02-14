file(GLOB SRCS *.cpp)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/includes)

ADD_EXECUTABLE(testBehavior ${SRCS})

TARGET_LINK_LIBRARIES(testBehavior
    libBehavior
    libgtest
    libgmock
)


add_test(NAME testBehavior
         COMMAND testBehavior)
