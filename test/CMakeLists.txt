enable_testing()

set (GTEST_ROOT ../../googletest)
set (GTEST_INCLUDE ${GTEST_ROOT}/include)
set (GTEST_MAIN_LIBRARY ${GTEST_ROOT}/lib)
set (GTEST_LIBRARY ${GTEST_ROOT}/lib)

find_package(GTest REQUIRED)

file(GLOB SRCS *.cpp)
include_directories(includes)
include_directories(${GTEST_INCLUDE_DIRS})

ADD_EXECUTABLE(testBehavior ${SRCS})

TARGET_LINK_LIBRARIES(testBehavior
    libBehavior
    ${GTEST_BOTH_LIBRARIES}
)

add_test(NAME testBehavior
         COMMAND testBehavior)
