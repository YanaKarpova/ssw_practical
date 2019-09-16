cmake_minimum_required(VERSION 3.13)
project(task_01)

set(CMAKE_CXX_STANDARD 14)
set(SRC ./src)

add_executable(task_01 ${SRC}/main.cpp ${SRC}/task_01.cpp ${SRC}/task_01.h)
