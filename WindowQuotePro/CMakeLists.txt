# BISMILLAAHIRRAHMAANIRRAHEEM

# CMakeList.txt : CMake project for WindowQuotePro, include source and define
# project specific logic here.
#

cmake_minimum_required(VERSION 3.8)

project(WindowQuotePro LANGUAGES CXX)

# TODO: Add tests and install targets if needed.

set(CMAKE_CXX_STANDARD 11)
# wxWidgets
set(wxWidgets_ROOT_DIR ${wxWidgets_path_base})
#set(wxWidgets_LIB_DIR ${wxWidgets_path_base}/lib/vc_x64_dll)
set(wxWidgets_CONFIGURATION msw)
find_package(wxWidgets REQUIRED core base webview)
include(${wxWidgets_USE_FILE})

set(SRCS 
	WindowQuoteProApp.cpp
	WindowQuoteProMain.cpp
	DataStore.cpp
	Page.cpp
	QuotesPage.cpp
	DialogHelp.cpp
	DialogAbout.cpp
#	res/resource.rc
)

include_directories(
	include
	res
	${wxWidgets_INCLUDE_DIRS}
	../extern/sqlite
)

add_executable(${PROJECT_NAME} WIN32 ${SRCS})

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET WindowQuotePro PROPERTY CXX_STANDARD 20)
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE 
	${wxWidgets_LIBRARIES}
	sqlite3
)

# copy configuration file, launch script and dependencies
configure_file(res/icon.ico icon.ico COPYONLY)
configure_file(res/config.ini config.ini COPYONLY)
configure_file(res/database.db database.db COPYONLY)

# file(COPY lib DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
