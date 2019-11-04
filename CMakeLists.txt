cmake_minimum_required(VERSION 3.15)
project(PreciseArithmetics)

set(CMAKE_CXX_STANDARD 17)

include_directories(temp_test include)
include_directories(temp_test src/include)
include_directories(temp_test src)
add_executable(temp_test
        src/complex.cpp
        src/complex_base.cpp
        src/fft.cpp
        src/integer.cpp
        src/integer_base.cpp
        src/karatsuba.cpp
        src/newton_raphson.cpp
        src/number_base.cpp
        src/rational.cpp
        src/rational_base.cpp
        src/real.cpp
        src/real_base.cpp
        tests/tester.cpp
        )