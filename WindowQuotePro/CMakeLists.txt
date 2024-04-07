# BISMILLAAHIRRAHMAANIRRAHEEM

# CMakeList.txt : CMake project for WindowQuotePro, include source and define
# project specific logic here.
#

cmake_minimum_required(VERSION 3.12)

project(WindowQuotePro LANGUAGES CXX)

# TODO: Add tests and install targets if needed.

set(CMAKE_CXX_STANDARD 11)

# wxWidgets
set(wxWidgets_ROOT_DIR ${wxWidgets_path_base})
#set(wxWidgets_LIB_DIR ${wxWidgets_path_base}/lib/vc_x64_dll)
set(wxWidgets_CONFIGURATION msw)
find_package(wxWidgets REQUIRED core base)
include(${wxWidgets_USE_FILE})

set(SRCS 
	WindowQuoteProApp.cpp
)

include_directories(
	include
	res
	${wxWidgets_INCLUDE_DIRS}
	../extern/sqlite
)

add_subdirectory(lib/application)

add_executable(${PROJECT_NAME} WIN32 ${SRCS})

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE 
	${wxWidgets_LIBRARIES}
	Application
)

# copy configuration file, launch script and dependencies
configure_file(lib/application/res/icon.ico ${CMAKE_CURRENT_BINARY_DIR}/icon.ico COPYONLY)
configure_file(lib/application/res/config.ini ${CMAKE_CURRENT_BINARY_DIR}/config.ini COPYONLY)
configure_file(lib/application/res/database.db ${CMAKE_CURRENT_BINARY_DIR}/database.db COPYONLY)

configure_file(${wxWidgets_path_libs}/wxbase32u_vc14x_x64.dll ${CMAKE_CURRENT_BINARY_DIR}/wxbase32u_vc14x_x64.dll COPYONLY)
configure_file(${wxWidgets_path_libs}/wxmsw32u_core_vc14x_x64.dll ${CMAKE_CURRENT_BINARY_DIR}/wxmsw32u_core_vc14x_x64.dll COPYONLY)
configure_file(${wxWidgets_path_libs}/wxmsw32u_webview_vc14x_x64.dll ${CMAKE_CURRENT_BINARY_DIR}/wxmsw32u_webview_vc14x_x64.dll COPYONLY)

# file(COPY lib DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

#if (EnableTests)
#    add_subdirectory(tests)
#endif()