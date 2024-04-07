cmake_minimum_required(VERSION 3.12)

project(Application LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)

# wxWidgets
set(wxWidgets_ROOT_DIR ${wxWidgets_path_base})
set(wxWidgets_CONFIGURATION msw)
find_package(wxWidgets REQUIRED core base webview)
include(${wxWidgets_USE_FILE})

set(SRCS 
	src/WindowQuoteProMain.cpp
	src/DataStore.cpp
	src/Page.cpp
	src/QuotesPage.cpp
	src/DialogHelp.cpp
	src/DialogAbout.cpp
)

add_library(${PROJECT_NAME} STATIC ${SRCS})

target_compile_definitions(${PROJECT_NAME} PRIVATE
	AppVersion="${ApplicationVersion}"
)
target_include_directories(${PROJECT_NAME} PUBLIC include)
target_link_libraries(${PROJECT_NAME} PRIVATE 
	${wxWidgets_LIBRARIES}
	sqlite3
)

# copy configuration file, launch script and dependencies
configure_file(res/config.ini ${CMAKE_CURRENT_BINARY_DIR}/config.ini COPYONLY)
configure_file(res/database.db ${CMAKE_CURRENT_BINARY_DIR}/database.db COPYONLY)

configure_file(${wxWidgets_path_libs}/wxbase32u_vc14x_x64.dll ${CMAKE_CURRENT_BINARY_DIR}/wxbase32u_vc14x_x64.dll COPYONLY)
configure_file(${wxWidgets_path_libs}/wxmsw32u_core_vc14x_x64.dll ${CMAKE_CURRENT_BINARY_DIR}/wxmsw32u_core_vc14x_x64.dll COPYONLY)
configure_file(${wxWidgets_path_libs}/wxmsw32u_webview_vc14x_x64.dll ${CMAKE_CURRENT_BINARY_DIR}/wxmsw32u_webview_vc14x_x64.dll COPYONLY)

if (EnableTests)
    add_subdirectory(tests)
endif()