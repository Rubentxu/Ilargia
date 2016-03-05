set (EXAMPLE_NAME Demo)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../include)
include_directories(${ANAX_INCLUDE_DIR})


file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/resources DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})


file(GLOB_RECURSE EXAMPLE_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
add_executable(${EXAMPLE_NAME} ${EXAMPLE_SOURCES})
target_link_libraries(
        ${EXAMPLE_NAME}
        ${ILARGIA_LIBRARY_NAME}
        ${ANAX_LIBRARY_NAME}
        ${SFML_LIBRARIES}
)
