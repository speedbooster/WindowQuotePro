# BISMILLAAHIRRAHMAANIRRAHEEM

# CMakeList.txt : CMake project for WindowQuotePro, include source and define
# project specific logic here.
#

cmake_minimum_required(VERSION 3.18)

project(WindowQuotePro LANGUAGES CXX)

# TODO: Add tests and install targets if needed.

set(CMAKE_CXX_STANDARD 11)

# wxWidgets
set(wxWidgets_ROOT_DIR ${wxWidgets_path_base})
set(wxWidgets_CONFIGURATION msw)
find_package(wxWidgets REQUIRED core base)
include(${wxWidgets_USE_FILE})

set(SRCS 
	WindowQuoteProApp.cpp
	res/Resource.rc
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
# Copy to binary directory for running in IDE
configure_file(res/icon.ico ${CMAKE_CURRENT_BINARY_DIR}/icon.ico COPYONLY)					# For linux
configure_file(res/splashscreen.png ${CMAKE_CURRENT_BINARY_DIR}/splashscreen.png COPYONLY)	# For linux
configure_file(lib/application/res/config.ini ${CMAKE_CURRENT_BINARY_DIR}/config.ini COPYONLY)
configure_file(lib/application/res/database.db ${CMAKE_CURRENT_BINARY_DIR}/database.db COPYONLY)

configure_file(${wxWidgets_path_libs}/wxbase32u_vc14x_x64.dll ${CMAKE_CURRENT_BINARY_DIR}/wxbase32u_vc14x_x64.dll COPYONLY)
configure_file(${wxWidgets_path_libs}/wxmsw32u_core_vc14x_x64.dll ${CMAKE_CURRENT_BINARY_DIR}/wxmsw32u_core_vc14x_x64.dll COPYONLY)
configure_file(${wxWidgets_path_libs}/wxmsw32u_webview_vc14x_x64.dll ${CMAKE_CURRENT_BINARY_DIR}/wxmsw32u_webview_vc14x_x64.dll COPYONLY)

file(COPY doc/README.txt DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY doc/UserManual.html DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# Setup `install` for CPack
install(TARGETS ${PROJECT_NAME} RUNTIME CONFIGURATIONS Release)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/icon.ico DESTINATION ${CMAKE_INSTALL_BINDIR})
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/splashscreen.png DESTINATION ${CMAKE_INSTALL_BINDIR})
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/config.ini DESTINATION ${CMAKE_INSTALL_BINDIR})
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/database.db DESTINATION ${CMAKE_INSTALL_BINDIR})

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/wxbase32u_vc14x_x64.dll DESTINATION ${CMAKE_INSTALL_BINDIR})
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/wxmsw32u_core_vc14x_x64.dll DESTINATION ${CMAKE_INSTALL_BINDIR})
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/wxmsw32u_webview_vc14x_x64.dll DESTINATION ${CMAKE_INSTALL_BINDIR})

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/README.txt TYPE DOC)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/UserManual.html TYPE DOC)

set(CPACK_PACKAGE_VERSION_MAJOR ${ApplicationVersionMajor})
set(CPACK_PACKAGE_VERSION_MINOR ${ApplicationVersionMinor})
set(CPACK_PACKAGE_VERSION_PATCH ${ApplicationVersionPatch})
set(CPACK_GENERATOR "ZIP")
set(CPACK_INCLUDE_TOPLEVEL_DIRECTORY OFF)
include(CPack)

#if (EnableTests)
#    add_subdirectory(tests)
#endif()

# Package
add_custom_command(TARGET ${PROJECT_NAME} COMMAND "cd ${CMAKE_CURRENT_BINARY_DIR} && cpack")