cmake_minimum_required(VERSION 3.15)
project(PreciseArithmetics)

set(CMAKE_CXX_STANDARD 17)

include_directories(temp_test include)
add_library(pa SHARED include/rational.h)
target_include_directories(pa PUBLIC include)
