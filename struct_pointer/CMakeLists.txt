cmake_minimum_required(VERSION 3.10)
project(AlgoData)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Existing console app
add_executable(prob1 prob1.cpp line.cpp circle.cpp)
add_executable(prob2 prob2.cpp line.cpp circle.cpp)
