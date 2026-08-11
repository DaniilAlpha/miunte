cmake_minimum_required(VERSION 3.16)
project(miunte-example LANGUAGES C)


### main ###

set(EXE "main")
add_executable(${EXE} ./main.c)


### add library

add_subdirectory(../ ${CMAKE_BINARY_DIR}/miunte)
target_link_libraries(${EXE} miunte)

