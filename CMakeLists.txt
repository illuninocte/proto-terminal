cmake_minimum_required(VERSION 3.5)

project(proto-terminal)

set(C_STANDARD 11)
include_directories(header)
file(GLOB SOURCES src/*.c header/*.h)

add_executable(terminal main.c ${SOURCES})