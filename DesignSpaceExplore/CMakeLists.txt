# CMakeList.txt : CMake project for EDAProject, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (EDAProject "EDAProject.cpp" "EDAProject.h" "Utils.cpp" "Utils.h" "LoopUnrolling.cpp" "LoopUnrolling.h" "LoopUnrollingStructs.cpp" "LoopUnrollingStructs.h")

# TODO: Add tests and install targets if needed.
