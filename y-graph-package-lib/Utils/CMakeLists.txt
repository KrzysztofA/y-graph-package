# CMakeList.txt : CMake project for y-graph-package, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.28)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("y-graph-package-lib-utils" VERSION 1.0.0)

# Add source to this project's executable.
add_executable (y-graph-package-lib-utils
				"Headers/Stopwatch.inl"
				"Headers/Numeric.inl"
				"Headers/Nodes.hpp"
				"Source/Nodes.cpp"
				"Headers/Graphs.hpp"
				"Source/Graphs.cpp"
				"Headers/LinkedList.inl"
				"Headers/ValidValue.inl"
				"Headers/Print.inl"
)

set_property(TARGET y-graph-package-lib-utils PROPERTY CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# TODO: Add tests and install targets if needed.
