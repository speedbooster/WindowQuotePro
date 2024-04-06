# BISMILLAAHIRRAHMAANIRRAHEEM

# CMakeList.txt : CMake project for sqlite3, include source and define
# project specific logic here.
#

cmake_minimum_required(VERSION 3.8)

project(sqlite3 LANGUAGES C)

# TODO: Add tests and install targets if needed.

set(SRCS 
	sqlite3.c
)

include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}
)

add_library(${PROJECT_NAME} STATIC ${SRCS})
