file(GLOB_RECURSE SRCS *.cpp)

ADD_EXECUTABLE(testIlargia ${SRCS} Components/TestComponent.h)

include_directories(${Ilargia_SOURCE_DIR}/src/include)

if (ILARGIA_INCLUDE_DIR)
    message(ERROR "No existe Ilargia includes")
endif ()


TARGET_LINK_LIBRARIES(testIlargia
    Ilargia
    libgtest
    libgmock
)

add_test(NAME testIlargia COMMAND testIlargia)