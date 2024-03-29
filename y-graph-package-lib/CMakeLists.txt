﻿# CMakeList.txt : CMake project for y-graph-package, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.28)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("y-graph-package-lib" VERSION 0.2.0)

add_subdirectory("MinimumSpanningTree")
add_subdirectory("Utils")
add_subdirectory("Sort")
add_subdirectory("ShortestPath")
add_subdirectory("PathSearch")

file(GLOB MST_LIBRARY_HEADERS "MinimumSpanningTree/Headers/*")
file(GLOB MST_LIBRARY_SOURCE "MinimumSpanningTree/Source/*")
file(GLOB UTILS_LIBRARY_HEADERS "Utils/Headers/*")
file(GLOB UTILS_LIBRARY_SOURCE "Utils/Source/*")

# Add source to this project's executable.
add_executable (y-graph-package-lib 
				"y-graph-package-lib.cpp" 
				"y-graph-package-lib.hpp"
				${UTILS_LIBRARY_SOURCE}
				${UTILS_LIBRARY_HEADERS}
				${MST_LIBRARY_SOURCE}
				${MST_LIBRARY_HEADERS}
				"Sort/Headers/Sorts.inl"
)

include_directories("MinimumSpanningTree/Headers")
include_directories("Utils/Headers")
include_directories("Sort/Headers")
include_directories("ShortestPath/Headers")
include_directories("PathSearch/Headers")

set_property(TARGET y-graph-package-lib PROPERTY CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# TODO: Add tests and install targets if needed.
