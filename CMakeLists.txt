cmake_minimum_required(VERSION 3.10)

project(threadpool_test)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_FLAGS "-Wall")

include_directories(./inc)

aux_source_directory(./src SRC)

add_executable(threadpooltest.exe main.cc ${SRC})

target_link_libraries(threadpooltest.exe pthread)