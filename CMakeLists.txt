cmake_minimum_required(VERSION 3.7)

project(hangman)

if (NOT CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall -Wextra -Wpedantic")
endif()

include_directories(
    include
)

file(GLOB hangmanlib_sources "lib/*")
add_library(hangmanlib ${hangmanlib_sources})

file(GLOB main_sources "src/*")
add_executable(main ${main_sources})
target_link_libraries(main hangmanlib)
