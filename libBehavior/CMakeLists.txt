set(libBehavior_SRCS
        blackboard.h any.h)

# Declare the library
add_library(libBehavior STATIC ${libBehavior_SRCS})

# Specify here the include directories exported
# by this library
target_include_directories(libBehavior PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

set_target_properties(libBehavior PROPERTIES LINKER_LANGUAGE CXX)