set(libEntitas_SRCS
        events/Event.h
        events/GroupEventType.h)

# Declare the library
add_library(libEntitas STATIC ${libEntitas_SRCS})

# Specify here the include directories exported
# by this library
target_include_directories(libEntitas PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

set_target_properties(libEntitas PROPERTIES LINKER_LANGUAGE CXX)