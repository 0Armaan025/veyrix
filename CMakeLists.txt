cmake_minimum_required(VERSION 3.20)

project(veyrix
    VERSION 0.1.0
    DESCRIPTION "Native Linux Control Center for Hyprland"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(PkgConfig REQUIRED)

pkg_check_modules(SDL2 REQUIRED IMPORTED_TARGET sdl2)
pkg_check_modules(SDL2_TTF REQUIRED IMPORTED_TARGET SDL2_ttf)

add_executable(veyrix
    src/main.cpp
)

target_link_libraries(nexus-cc
    PRIVATE
        PkgConfig::SDL2
        PkgConfig::SDL2_TTF
)

target_compile_options(nexus-cc PRIVATE
    -Wall
    -Wextra
    -Wpedantic
)
