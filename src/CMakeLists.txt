cmake_minimum_required(VERSION 3.12)

project(ShiftRegister74HC595 C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

add_library(ShiftRegister74HC595 ShiftRegister74HC595.cpp ShiftRegister74HC595.hpp ShiftRegister74HC595.h)

# Pull in our pico_stdlib which aggregates commonly used features
target_link_libraries(ShiftRegister74HC595 pico_stdlib hardware_spi)