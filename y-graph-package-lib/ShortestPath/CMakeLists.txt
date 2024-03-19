# CMakeList.txt : CMake project for y-graph-package, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.28)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("y-graph-package-lib-shortest-path" VERSION 0.0.1)

file(GLOB UTILS_LIBRARY_HEADERS "../Utils/Headers/*")
file(GLOB UTILS_LIBRARY_SOURCE "../Utils/Source/*")

# Add source to this project's executable.
add_executable (y-graph-package-lib-shortest-path
				"y-graph-package-lib-path-search.cpp" 
				"y-graph-package-lib-path-search.hpp"
				${UTILS_LIBRARY_SOURCE}
				${UTILS_LIBRARY_HEADERS}
				"Headers/ShortestPath.inl"
				"Headers/Dijkstra.hpp"
				"Source/Dijkstra.cpp"
)

include_directories("../Utils/Headers")
include_directories("Headers")

set_property(TARGET y-graph-package-lib-shortest-path PROPERTY CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# TODO: Add tests and install targets if needed.
