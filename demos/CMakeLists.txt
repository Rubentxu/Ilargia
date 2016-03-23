set (EXAMPLE_NAME Demo)


include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include
        ${ANAX_INCLUDE_DIR}
        ${SDL2_INCLUDE_DIR}
        ${SDL2_IMAGE_INCLUDE_DIR}
        ${SDL2_TTF_INCLUDE_DIR}
        ${SDL2_MIXER_INCLUDE_DIR}
        ${Ilargia_SOURCE_DIR}/include)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

link_directories(../../anax/lib)

file(GLOB_RECURSE EXAMPLE_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
add_executable(${EXAMPLE_NAME} ${EXAMPLE_SOURCES})
target_link_libraries(
        ${EXAMPLE_NAME}
        ${ILARGIA_LIBRARY_NAME}
        ${ANAX_LIBRARY_RELEASE}
        ${SDL2_LIBRARY}
        ${SDL2_IMAGE_LIBRARIES}
        ${SDL2_TTF_LIBRARIES}
        ${SDL2_MIXER_LIBRARIES}

)
