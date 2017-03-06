cmake_minimum_required(VERSION 3.5)

project(projet)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")


add_executable(programme main.cpp Ligne.h Ligne.cpp Lieu.cpp Lieu.h Avion.cpp Avion.h Piece.cpp Piece.h)
