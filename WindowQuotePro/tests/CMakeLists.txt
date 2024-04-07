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


#[[

### Common

set(Component Common)
set(SRCS 
    test${Component}.cpp
)
add_executable(${PROJECT_NAME}${Component} ${SRCS})
target_include_directories(${PROJECT_NAME}${Component} PUBLIC include)
target_link_libraries(${PROJECT_NAME}${Component} PRIVATE 
    ${Libraries}
)


### Core

set(Component Core)
set(SRCS 
    test${Component}.cpp
)
add_executable(${PROJECT_NAME}${Component} ${SRCS})
target_include_directories(${PROJECT_NAME}${Component} PUBLIC include)
target_link_libraries(${PROJECT_NAME}${Component} PRIVATE 
    ${Libraries}
)

]]
