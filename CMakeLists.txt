cmake_minimum_required(VERSION 3.15)
project(PreciseArithmetics)

set(CMAKE_CXX_STANDARD 17)

include_directories(temp_test include)
include_directories(temp_test src/include)
include_directories(temp_test src)

enable_testing()
add_test(NAME main_test COMMAND tester)

file(GLOB pa_SRC "src/*.cpp")

add_library(pa SHARED ${pa_SRC})
target_include_directories(pa PUBLIC include)
