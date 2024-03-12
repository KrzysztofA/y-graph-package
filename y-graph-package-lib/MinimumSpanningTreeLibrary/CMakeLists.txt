# CMakeList.txt : CMake project for y-graph-package, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.28)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("y-graph-package-lib-mst" VERSION 0.5.3)

# Add source to this project's executable.
add_library (y-graph-package-lib-mst STATIC
				"Headers/MinimumSpanningTreeAlgorithm.inl"
				"Headers/Kruskals.hpp"
				"Source/Kruskals.cpp"
				"Headers/Prims.hpp"
				"Source/Prims.cpp"
				"Headers/Boruvka.hpp"
				"Source/Boruvka.cpp"
				"Headers/ReverseDelete.hpp"
				"Source/ReverseDelete.cpp"
)


set_property(TARGET y-graph-package-lib-mst PROPERTY CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# TODO: Add tests and install targets if needed.
