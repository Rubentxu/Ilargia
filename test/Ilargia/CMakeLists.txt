file(GLOB_RECURSE SRCS *.cpp)

ADD_EXECUTABLE(testIlargia ${SRCS})

TARGET_LINK_LIBRARIES(testIlargia
    Ilargia
    libgtest
    libgmock
)

add_test(NAME testIlargia COMMAND testIlargia)