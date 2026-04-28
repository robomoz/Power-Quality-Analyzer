cmake_minimum_required(VERSION 3.21)
project(ProgrammingCoursework C)

set(CMAKE_C_STANDARD 99)

add_executable(ProgrammingCoursework main.c waveform.h waveform.c io.c io.h)
target_link_libraries(ProgrammingCoursework m)
