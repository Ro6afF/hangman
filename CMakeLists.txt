cmake_minimum_required(VERSION 3.7)

project(hangman)

if (NOT CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++17 -Wall -Wextra -Wpedantic")
endif()

add_subdirectory(external)

include_directories(
    include
    external/libbcrypt/include
)

file(GLOB hangmanlib_sources "lib/*")
add_library(hangmanlib ${hangmanlib_sources})
link_libraries(hangmanlib bcrypt)

file(GLOB main_sources "src/*")
add_executable(main ${main_sources})
target_link_libraries(main hangmanlib bcrypt)
