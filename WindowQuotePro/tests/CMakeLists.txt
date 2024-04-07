cmake_minimum_required(VERSION 3.8)

project(WindowQuoteProTest LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)

enable_testing()

set(Libraries 
    GTest::gtest_main
    # Backend (DataStore and Page as a library)
)


set(SRCS 
    test.cpp
)
add_executable(${PROJECT_NAME} ${SRCS})
target_include_directories(${PROJECT_NAME} PUBLIC include)
target_link_libraries(${PROJECT_NAME} PRIVATE 
    ${Libraries}
)


