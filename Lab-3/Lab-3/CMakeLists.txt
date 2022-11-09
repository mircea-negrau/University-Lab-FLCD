# CMakeList.txt : CMake project for Lab-3, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (Lab-3 "Lab-3.cpp" "Lab-3.h" "Models/Core/Node.cpp" "Models/Core/BinarySearchTree.cpp" "Models/Storage/SymbolTable.cpp" "Models/Scanner/Scanner.cpp"  "Models/Storage/ProgramInternalForm.cpp" "Models/Tokens/Tokens.cpp" "Utils/TextHelper.cpp" "Models/Scanner/Result.cpp" "Models/Tokens/TokenType.cpp" "Models/TokensIdentifier/TokensIdentifier.cpp" "Models/Core/Tuple.cpp" "Constants/Tokens.cpp" "Constants/Scanner.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Lab-3 PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
