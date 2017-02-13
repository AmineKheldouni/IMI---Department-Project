cmake_minimum_required(VERSION 3.5)

find_package(Imagine)
add_executable(programme main.cpp Piece.h Piece.cpp Location.cpp Location.h)
ImagineUseModules(programme Graphics Images)
