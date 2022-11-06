cmake_minimum_required(VERSION 3.23)
project(mega_calc)

set(CMAKE_CXX_STANDARD 20)

add_executable(mega_calc main.cpp src/classes/Mat2D/Mat2D.h src/classes/Mat2D/Mat2D.cpp src/classes/VecND/VecND.h src/classes/VecND/VecND.cpp)
