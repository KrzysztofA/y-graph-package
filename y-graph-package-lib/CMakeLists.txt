﻿# CMakeList.txt : CMake project for y-graph-package, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.12)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("y-graph-package-lib" VERSION 0.0.1)

# Add source to this project's executable.
add_executable (y-graph-package-lib 
				"y-graph-package-lib.cpp" 
				"y-graph-package-lib.hpp" 
				"SortsLibrary/Sorts.inl"
				"Utils/Source/Benchmarks.cpp"
				"Utils/Headers/Benchmarks.hpp"
				"Utils/Source/Stopwatch.cpp"
				"Utils/Headers/Stopwatch.hpp"
)

set_property(TARGET y-graph-package-lib PROPERTY CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# TODO: Add tests and install targets if needed.