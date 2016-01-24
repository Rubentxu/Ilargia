file(GLOB SRCS *.cpp)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/includes)
#
#find_package(Boost 1.56 REQUIRED COMPONENTS
#           date_time filesystem iostreams)
#   add_executable(foo foo.cc)
#   target_link_libraries(foo Boost::date_time Boost::filesystem
#                             Boost::iostreams)

ADD_EXECUTABLE(testBehavior ${SRCS})

TARGET_LINK_LIBRARIES(testBehavior
    Entitas
    BehaviorT
    libgtest
    libgmock
)

add_test(NAME testBehavior
         COMMAND testBehavior)
