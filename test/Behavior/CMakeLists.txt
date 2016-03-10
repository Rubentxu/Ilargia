file(GLOB_RECURSE SRCS *.cpp)

ADD_EXECUTABLE(testBehavior ${SRCS})

TARGET_LINK_LIBRARIES(testBehavior
    Behavior
    libgtest
    libgmock
)

add_test(NAME testBehavior
        COMMAND testBehavior)
