cmake_minimum_required(VERSION 3.14)
project(MemoryGame VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -Wpedantic -Werror)
endif()

include_directories(include)

file(GLOB SOURCES "src/*.cpp")

add_executable(MemoryGame main.cpp ${SOURCES})