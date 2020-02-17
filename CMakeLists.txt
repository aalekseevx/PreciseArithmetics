cmake_minimum_required(VERSION 3.15)
project(PreciseArithmetics)

set(CMAKE_CXX_STANDARD 17)

include_directories(temp_test include)
add_library(pa SHARED include/PreciseArithmetics/rational.h)
target_include_directories(pa PUBLIC include)
set_target_properties(pa PROPERTIES LINKER_LANGUAGE CXX)