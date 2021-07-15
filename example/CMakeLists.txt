cmake_minimum_required(VERSION 3.12)

project(SR_example C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

add_executable(SR_example example.cpp)

# Pull in our pico_stdlib which aggregates commonly used features
target_link_libraries(SR_example pico_stdlib ShiftRegister74HC595)
pico_add_extra_outputs(SR_example)