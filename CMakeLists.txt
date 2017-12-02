cmake_minimum_required(VERSION 3.2.0 FATAL_ERROR)
project(pedeconstructor)

find_package(Qt5Widgets 5.4 REQUIRED)
find_package(win32pe REQUIRED)

set(CMAKE_AUTOMOC ON)

add_subdirectory(src)
