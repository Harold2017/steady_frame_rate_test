cmake_minimum_required(VERSION 3.16)

project(steady_frame_rate)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if (MSVC)
    add_compile_options(/W4 /WX)
    add_compile_options(/permissive- /Zc:preprocessor)
else()
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

add_executable(test
    test1.cpp
)