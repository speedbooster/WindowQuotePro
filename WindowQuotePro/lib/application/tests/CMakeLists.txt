cmake_minimum_required(VERSION 3.8)

project(ApplicationTests LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)


set(Library Application)

enable_testing()


### DataStore

set(Component DataStore)
set(SRCS 
    test${Component}.cpp
)
add_executable(${PROJECT_NAME}${Component} ${SRCS})
target_link_libraries(${PROJECT_NAME}${Component} PRIVATE 
    GTest::gtest_main
    ${Library}
)

configure_file(../res/config.ini ${CMAKE_CURRENT_BINARY_DIR}/config.ini COPYONLY)
configure_file(../res/database.db ${CMAKE_CURRENT_BINARY_DIR}/database.db COPYONLY)

configure_file(${wxWidgets_path_libs}/wxbase32u_vc14x_x64.dll ${CMAKE_CURRENT_BINARY_DIR}/wxbase32u_vc14x_x64.dll COPYONLY)
configure_file(${wxWidgets_path_libs}/wxmsw32u_core_vc14x_x64.dll ${CMAKE_CURRENT_BINARY_DIR}/wxmsw32u_core_vc14x_x64.dll COPYONLY)
configure_file(${wxWidgets_path_libs}/wxmsw32u_webview_vc14x_x64.dll ${CMAKE_CURRENT_BINARY_DIR}/wxmsw32u_webview_vc14x_x64.dll COPYONLY)


#[[

### Page

set(Component Page)
set(SRCS 
    test${Component}.cpp
)
add_executable(${PROJECT_NAME}${Component} ${SRCS})
target_include_directories(${PROJECT_NAME}${Component} PUBLIC include)
target_link_libraries(${PROJECT_NAME}${Component} PRIVATE 
    ${Libraries}
)


### QuotesPage

set(Component QuotesPage)
set(SRCS 
    test${Component}.cpp
)
add_executable(${PROJECT_NAME}${Component} ${SRCS})
target_include_directories(${PROJECT_NAME}${Component} PUBLIC include)
target_link_libraries(${PROJECT_NAME}${Component} PRIVATE 
    ${Libraries}
)

]]
