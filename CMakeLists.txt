cmake_minimum_required(VERSION 3.16)

project(from-scratch-fft LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(fft
    src/fft.cpp
)

target_include_directories(fft PUBLIC
    include
)

target_compile_options(fft PRIVATE
    -Wall
    -Wextra
    -Wpedantic
)

add_executable(from-scratch-fft
    main.cpp
)

target_link_libraries(from-scratch-fft PRIVATE fft)

add_executable(test_fft
    tests/test_fft.cpp
)

target_link_libraries(test_fft PRIVATE fft)
