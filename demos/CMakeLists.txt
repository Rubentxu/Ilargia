set(Main_SRCS
    main.cpp
     )

add_executable(demo
    ${Main_SRCS}
)

# Specify here the libraries this program depends on
target_link_libraries(demo
    libEntitas
    libBehavior
)

install(TARGETS demo DESTINATION bin)
