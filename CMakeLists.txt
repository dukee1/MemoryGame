cmake_minimum_required(VERSION 3.14)
project(MemoryGame VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(APPLE)
    execute_process(
            COMMAND xcrun --show-sdk-path
            OUTPUT_VARIABLE CMAKE_OSX_SYSROOT
            OUTPUT_STRIP_TRAILING_WHITESPACE
    )
endif()

include(FetchContent)
FetchContent_Declare(
        SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.1
        GIT_SHALLOW ON
)
FetchContent_MakeAvailable(SFML)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)

include_directories(include)

file(GLOB SOURCES "src/*.cpp")

add_executable(MemoryGame main.cpp ${SOURCES})

target_link_libraries(MemoryGame PRIVATE sfml-graphics sfml-window sfml-system)

# Absolute path to assets in the source tree (fallback when run from an IDE)
target_compile_definitions(MemoryGame PRIVATE
        ASSETS_DIR="${CMAKE_CURRENT_SOURCE_DIR}/assets")

# Copy assets next to the executable so the game also works when moved/run directly
add_custom_command(TARGET MemoryGame POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${CMAKE_CURRENT_SOURCE_DIR}/assets
                $<TARGET_FILE_DIR:MemoryGame>/assets)

if(MINGW)
    target_link_options(MemoryGame PRIVATE -static-libgcc -static-libstdc++)
endif()