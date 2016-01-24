set(libEntitas_SRCS
        events/Event.h
        events/GroupEventType.h)

# Declare the library
add_library(entitas STATIC ${libEntitas_SRCS})

# Specify here the include directories exported
# by this library
target_include_directories(entitas PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

set_target_properties(entitas PROPERTIES LINKER_LANGUAGE CXX)