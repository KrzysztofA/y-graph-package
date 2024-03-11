# CMakeList.txt : CMake project for y-graph-package, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.12)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("y-graph-package-lib" VERSION 0.1.0)

# Add source to this project's executable.
add_executable (y-graph-package-lib 
				"y-graph-package-lib.cpp" 
				"y-graph-package-lib.hpp" 
				"SortsLibrary/Sorts.inl"
				"Utils/Headers/Stopwatch.inl"
				"Utils/Headers/Numeric.inl"
				"Utils/Headers/Nodes.hpp"
				"Utils/Source/Nodes.cpp"
				"Utils/Headers/Graphs.hpp"
				"Utils/Source/Graphs.cpp"
				"MinimumSpanningTreeLibrary/Headers/MinimumSpanningTreeAlgorithm.inl"
				"MinimumSpanningTreeLibrary/Headers/Kruskals.hpp"
				"MinimumSpanningTreeLibrary/Source/Kruskals.cpp"
				"MinimumSpanningTreeLibrary/Headers/Prims.hpp"
				"MinimumSpanningTreeLibrary/Source/Prims.cpp"
				"MinimumSpanningTreeLibrary/Headers/Boruvka.hpp"
				"MinimumSpanningTreeLibrary/Source/Boruvka.cpp"
				"MinimumSpanningTreeLibrary/Tests/MstTest.cpp"
				"SortsLibrary/Tests/SortsTest.cpp"
)

set_property(TARGET y-graph-package-lib PROPERTY CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# TODO: Add tests and install targets if needed.
