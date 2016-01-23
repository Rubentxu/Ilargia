file(GLOB SRCS *.cpp)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

ADD_EXECUTABLE(testBehavior ${SRCS})

TARGET_LINK_LIBRARIES(testBehavior
    libEntitas
    libBehavior
    libgtest
    libgmock
)

add_test(NAME testBehavior
         COMMAND testBehavior)
