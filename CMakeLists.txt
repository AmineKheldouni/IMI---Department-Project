cmake_minimum_required(VERSION 3.5)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules )
project(projet)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_executable(programme main.cpp PlanePart.h PlanePart.cpp Location.cpp Location.h Plane.cpp Plane.h)

find_package(GUROBI REQUIRED) 
include_directories(${GUROBI_INCLUDE_DIRS})
target_link_libraries(programme ${GUROBI_LIBRARIES})


