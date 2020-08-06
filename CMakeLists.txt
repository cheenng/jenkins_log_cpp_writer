cmake_minimum_required(VERSION 3.0)
project(my_test)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHa")

add_subdirectory(tinyxml)
add_subdirectory(test)