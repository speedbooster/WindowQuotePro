cmake_minimum_required(VERSION 3.8)

project(ApplicationTests LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(Library UIComponents)

enable_testing()


### Page

set(Component DataStore)
set(SRCS 
    test${Component}.cpp
)
add_executable(${PROJECT_NAME}${Component} ${SRCS})
target_link_libraries(${PROJECT_NAME}${Component} PRIVATE 
    GTest::gtest_main
    ${Library}
)
