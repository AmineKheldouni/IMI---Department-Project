cmake_minimum_required(VERSION 3.5)

project(projet)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_executable(programme main.cpp PlanePart.h PlanePart.cpp Location.cpp Location.h Plane.cpp Plane.h)

