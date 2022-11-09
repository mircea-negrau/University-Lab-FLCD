# CMakeList.txt : CMake project for Lab-4, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("Lab-4")

# Add source to this project's executable.
add_executable (Lab-4 "Lab-4.cpp" "Lab-4.h" "Models/InputSymbol.cpp" "Models/TransitionFunction.cpp" "Models/FiniteAutomata.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Lab-4 PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
