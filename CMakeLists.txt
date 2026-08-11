cmake_minimum_required(VERSION 3.16)
project(miunte LANGUAGES C)


### lib ###

set(LIB "miunte")
add_library(${LIB} INTERFACE)

target_include_directories(${LIB} INTERFACE ./)
