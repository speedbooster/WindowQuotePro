# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("WindowQuotePro")

# Define build parameters
set(EnableTests ON)
set(wxWidgets_path_base "C:/wxWidgets")								# Path to wxWidgets `include` and `lib` directories
set(wxWidgets_path_libs ${wxWidgets_path_base}/lib/vc14x_x64_dll)	# Path to wxWidgets libraries inside the `lib` directory
set(CMAKE_BUILD_TYPE Release)
set(ApplicationVersionMajor "0")
set(ApplicationVersionMinor "1")
set(ApplicationVersionPatch "2")
set(ApplicationVersion "${ApplicationVersionMajor}.${ApplicationVersionMinor}.${ApplicationVersionPatch}")


# Include sub-projects.
if (EnableTests)
	set(gtest_force_shared_crt on)
	add_subdirectory ("extern/gtest" EXCLUDE_FROM_ALL)
endif()
add_subdirectory ("extern/sqlite")
add_subdirectory ("WindowQuotePro")
