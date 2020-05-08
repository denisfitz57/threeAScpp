add_executable(tests main.cpp Timer.cpp)
target_compile_options(tests PRIVATE ${THREEAS_WARNINGS})
target_link_libraries(tests threeAS testcpplite)
